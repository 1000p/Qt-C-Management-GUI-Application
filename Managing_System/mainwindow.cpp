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
    _rooms.reserve(10);
    workArea = new scrollAreaParent(this);
    container = new QWidget(workArea);

    FlowLayout* grid = new FlowLayout(container);
    container->setLayout(grid);
    initializer(_rooms, grid);

    /*for(int row = 0; row<100; ++row)
    {
        for(int col =0; col<10; ++col)
        {
            roomButtonWrap* button =
                    new roomButtonWrap("Room " + QString::number(roomButtonWrap::getID()));
            button->setFixedSize(100,100);
            grid->addWidget(button);
        }
    }*/

    scrollArea = new QScrollArea(workArea);
    scrollArea->setWidget(container);
    scrollArea->resize(1000,720);
    scrollArea->setWidgetResizable(true);    
    scrollArea->setStyleSheet("QScrollArea { background: transparent;}"
                              "QScrollArea > QWidget > QWidget { background: transparent;}"
                              "QScrollArea > QWidget > QScrollBar { background: palette(base);}");

    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    for(auto room : _rooms )
    {
        delete room;
    }
    initializer.close();
    delete ui;
    QApplication::quit();
}


void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QSize winSize = size();

    ui->sidebarImg->setGeometry(0,0,280,winSize.height());
    scrollArea->resize(winSize.width()-280,winSize.height());
    workArea->resize(scrollArea->size());

    QMainWindow::resizeEvent(evt);
}

void MainWindow::paintEvent(QPaintEvent* evt)
{

    QMainWindow::paintEvent(evt);

}

void MainWindow::on_newRoomButton_released()
{

    container->layout()->
            addWidget(new roomButtonWrap("Room " + QString::number(roomButtonWrap::getID())));

}



