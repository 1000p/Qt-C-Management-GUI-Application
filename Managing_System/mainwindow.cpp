#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDebug>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    initializer(Initializer::getInstance())
{
    ui->setupUi(this);
    _rooms.reserve(10); //To avoid too much reallocations

    //Create the scrollable work area and appropriate elements for it
    workArea = new scrollAreaParent(this);
    container = new QWidget(workArea);

    //Create the sidebar and set the its buttons as child
    QRect sidebarGeometry {0,0,280,this->height()};
    sidebar = new imageLabel(sidebarGeometry, this);
    ui->newRoomButton->setParent(sidebar);

    //Our work area flow layour
    FlowLayout* grid = new FlowLayout(container);
    container->setLayout(grid);
    initializer(_rooms, grid);

    //Actual scroll area widget
    scrollArea = new QScrollArea(workArea);
    scrollArea->setWidget(container);
    scrollArea->resize(1000,720);
    scrollArea->setWidgetResizable(true);

    //Set scroll area to be transperant aswell with its widget
    //Set the scroll bar to be a base scroll bar(so to avoid transperance)
    scrollArea->setStyleSheet("QScrollArea { background: transparent;}"
                              "QScrollArea > QWidget > QWidget { background: transparent;}"
                              "QScrollArea > QWidget > QScrollBar { background: palette(base);}");

    //Calls destructor on close
    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    //Calls all rooms to save to a file
    for(auto room : _rooms )
    {
        room->save();
        delete room;
    }

    //Closes our factory objects
    initializer.close();
    delete ui;

    //This is our main window so we need to exit application on close
    QApplication::quit();
}


void MainWindow::resizeEvent(QResizeEvent* evt)
{
    //Resizes its elements when resizing our window
    QSize winSize = size();
    scrollArea->resize(winSize.width()-280,winSize.height());
    sidebar->resize(winSize.width()-scrollArea->width(),winSize.height() );
    workArea->resize(scrollArea->size());

    QMainWindow::resizeEvent(evt);
}

void MainWindow::paintEvent(QPaintEvent* evt)
{
    //Unecessery for now
    QMainWindow::paintEvent(evt);
}

void MainWindow::on_newRoomButton_released()
{
    //Creates a blank button and adds it to our flow layout
    roomButtonWrap* toAdd = new roomButtonWrap(0,"Room " + QString::number(roomButtonWrap::getID()));
    container->layout()->
            addWidget(toAdd);
    _rooms.push_back(toAdd);
}



