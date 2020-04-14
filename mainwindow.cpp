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

    QGridLayout* grid = new QGridLayout(container);
    container->setLayout(grid);


    for(int row = 0; row<10; ++row)
    {
        for(int col =0; col<10; ++col)
        {
            roomButtonWrap* button = new roomButtonWrap("text");
            button->setFixedSize(100,100);
            grid->addWidget(button, row, col);
        }
    }
    scrollArea = new QScrollArea(ui->workArea);
    scrollArea->setWidget(container);
    scrollArea->resize(1000,720);
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
    //scrollArea->setGeometry(0,0,winSize.width()-1,winSize.height()-1);
   //ui->workArea->layout()->->setGeometry(0,0,winSize.width(),winSize.height());
    //container->setGeometry(0,0,winSize.width(),winSize.height());
    QMainWindow::resizeEvent(evt);
}


void MainWindow::on_newRoomButton_released()
{
    roomButtonWrap* lastButton = nullptr;

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

    }

}

