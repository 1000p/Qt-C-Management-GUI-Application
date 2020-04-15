#include "roomwindow.h"
#include "ui_roomwindow.h"
#include <QPalette>

#include <QDebug>

roomWindow::roomWindow(QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::roomWindow), changed(false)
{
    ui->setupUi(this);
    QImageReader reader(":/IMG/Images/Room Window/Backdrop.png");

    if(reader.supportsOption(QImageIOHandler::ScaledSize))
    {
        reader.setScaledSize(this->size());
        backdrop = reader.read();
        palette.setBrush(QPalette::Background, backdrop);
        this->setPalette(palette);

    }else
    {
        qDebug() << "ERROR at backdrop scaling for the Room Window!!";
    }



    connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));

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
   QImageReader reader (":/IMG/Images/Room Window/Backdrop.png");
   reader.setScaledSize(this->size());
   QPalette palette;
   palette.setBrush(QPalette::Background, reader.read());
    this->setPalette(palette);
    QDialog::resizeEvent(evt);
}
