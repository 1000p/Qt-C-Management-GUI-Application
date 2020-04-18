#include "roomwindow.h"

#include "ui_roomwindow.h"
#include <QPalette>
#include <QPainter>
#include <QDir>
#include <QtEvents>

#include <QDebug>

roomWindow::roomWindow(QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::roomWindow), changed(false)
{
    ui->setupUi(this);

    if(parent)
    {
        connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));
    }
    setWindowFlag(Qt::WindowMinimizeButtonHint );


    ui->occupants->viewport()->setAutoFillBackground(false);
    ui->roomName->viewport()->setAutoFillBackground(false);
}

roomWindow::~roomWindow()
{
    delete ui;
}

void roomWindow::init(roomButtonWrap* parent)
{
    ui->roomName->setText(parent->text());
    ui->roomName->setAlignment(Qt::AlignCenter);
    this->show();
    connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));
}

void roomWindow::changeBackdrop (QImage& image)
{
    QSize size = this->size();
    this->backdrop = image;
    backdropWidth = size.width();
    backdropHeight = size.height();
}

roomWindow* roomWindow::clone()
{
    roomWindow* window = new roomWindow();
    window->backdrop = backdrop;
    window->backdropWidth = backdropWidth;
    window->backdropHeight = backdropHeight;

    return window;
}

void roomWindow::closeEvent(QCloseEvent * evt)
{
    QDialog::closeEvent(evt);

    emit setNull(evt);
}

void roomWindow::paintEvent(QPaintEvent * evt)
{
    QPainter painter (this);
    QRect rect {0,0, backdropWidth, backdropHeight};
    //qDebug() << rect;
    painter.drawImage(rect, backdrop);

    QDialog::paintEvent(evt);
}

void roomWindow::resizeEvent(QResizeEvent *evt)
{   
    QSize winSize = size();
    if(backdropWidth>winSize.width() ||backdropWidth<winSize.width() )
    {
        backdropWidth  = winSize.width();
    }
    if(backdropHeight>winSize.height() || backdropHeight<winSize.height())
    {
        backdropHeight = winSize.height();
    }
    QDialog::resizeEvent(evt);
}
