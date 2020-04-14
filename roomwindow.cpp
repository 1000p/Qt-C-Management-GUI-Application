#include "roomwindow.h"
#include "ui_roomwindow.h"
#include <QPalette>

roomWindow::roomWindow(QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::roomWindow), changed(false)
{
    ui->setupUi(this);
    backdrop.load("C:/Users/loopg/Local P"
                      "roject/Managing_System/Images/"
                      "Room Window/Backdrop.jpg");

    backdrop = backdrop.scaled(backdrop.width(),backdrop.height(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Background, backdrop);
    this->setPalette(palette);
    connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));
   // setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowMinimizeButtonHint);
    show();
    ui->occupants->viewport()->setAutoFillBackground(false);
    ui->roomName->viewport()->setAutoFillBackground(false);
}

roomWindow::~roomWindow()
{
    delete ui;
}


void roomWindow::closeEvent(QCloseEvent * evt)
{
    QDialog::closeEvent(evt);
    emit setNull(evt);
}

void roomWindow::resizeEvent(QResizeEvent *evt)
{
    temp = backdrop.scaled(this->size(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Background, temp);
    this->setPalette(palette);
    QDialog::resizeEvent(evt);
}
