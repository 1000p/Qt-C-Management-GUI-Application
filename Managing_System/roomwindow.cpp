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
        this->parent = static_cast<roomButtonWrap*>(parent);
    }
    setWindowFlag(Qt::WindowMinimizeButtonHint );


    ui->occupants->viewport()->setAutoFillBackground(false);
    ui->roomName->viewport()->setAutoFillBackground(false);

    connect(this->ui->occupants,SIGNAL(textChanged()),this,SLOT(setChanged()));
    connect(this->ui->notes,SIGNAL(textChanged()),this,SLOT(setChanged()));
}

roomWindow::~roomWindow()
{
    save();
    delete ui;
}

void roomWindow::init(roomButtonWrap* parent)
{
    ui->roomName->setText(parent->text());
    ui->roomName->setAlignment(Qt::AlignCenter);
    this->show();
    connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));
    this->parent = parent;
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

void roomWindow::save()
{

    if(changed)
    {
        QString applicationDir = QApplication::applicationDirPath()
                .append("/Data/Rooms/");

        QString roomName = parent->text() + '/';
        QString filePath = applicationDir + roomName;
        QDir dir;

        QFileInfo outDir (filePath);
        if (!outDir.exists())
        {
            dir.mkdir(filePath);
        }


        QFile occupantsF (filePath + "Occupants");

        if(!occupantsF.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error occured while saving data for room window, file"
                        "could not be initialized/created at:"<<filePath + roomName;
        }
        else
        {
            QTextStream stream(&occupantsF);
            stream << ui->occupants->toHtml();
        }

        QFile notesF(filePath + "Notes");
        if(!notesF.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error occured while saving data for room window, file"
                        "could not be initialized/created at:"<<filePath + roomName;
        }
        else
        {
            QTextStream stream(&notesF);
            stream << ui->notes->toHtml();
        }
    }
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

void roomWindow::setChanged()
{
    changed = true;
}
