#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    initializer(Initializer::getInstance())
{

    ui->setupUi(this);
    _rooms.reserve(10);
    initializer(_rooms, this);

    container = new QWidget(ui->workArea);
   // container->resize(ui->workArea->size());

    FlowLayout* grid = new FlowLayout(container);
    container->setLayout(grid);


    for(int row = 0; row<15; ++row)
    {
        for(int col =0; col<10; ++col)
        {
            roomButtonWrap* button = new roomButtonWrap("text");
            button->setFixedSize(100,100);
            grid->addWidget(button);
        }
    }
    scrollArea = new QScrollArea(ui->workArea);
    scrollArea->setWidget(container);
    scrollArea->resize(1000,720);
    scrollArea->setWidgetResizable(true);
    qDebug() << scrollArea->size();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QSize winSize = size();

    ui->sidebarImg->setGeometry(0,0,280,winSize.height());
    scrollArea->resize(winSize.width()-280,winSize.height());
    ui->workArea->resize(scrollArea->size());

    QMainWindow::resizeEvent(evt);
}


void MainWindow::on_newRoomButton_released()
{
    /*roomButtonWrap* lastButton = nullptr;

    if(_rooms.size()>0)
    {
        lastButton = _rooms.back();
    }

    QString prepend = "Room ";

    roomButtonWrap* nextButton = initializer.newRoomButton
            (lastButton,prepend.append( QString::number(roomButtonWrap::getID())),this);
    if(nextButton != nullptr)
    {
        _rooms.push_back(nextButton);

    }*/
    container->layout()->addWidget(new roomButtonWrap("button"));

}

