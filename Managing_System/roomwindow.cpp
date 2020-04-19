#include "roomwindow.h"

#include "ui_roomwindow.h"
#include <QPalette>
#include <QPainter>
#include <QDir>
#include <QtEvents>

#include <QDebug>

roomWindow::roomWindow(int occupiedFlag,QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::roomWindow), changed(false)
{
    ui->setupUi(this);

    if(occupiedFlag == 1)
    {
        ui->occupiedCB->setChecked(true);
    }

    if(parent)
    {
        connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));
        this->parent = static_cast<roomButtonWrap*>(parent);
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
    if(parent->isOccupied())
    {
        ui->occupiedCB->setChecked(true);
    }
    QString parentName = parent->text();
    this->setWindowTitle(parentName);
    ui->roomName->setText(parentName);
    ui->roomName->setAlignment(Qt::AlignCenter);
    this->show();
    connect(this,SIGNAL(setNull(QEvent*)),parent,SLOT(handleWindowEvent(QEvent*)));
    this->parent = parent;
    readFiles();
    connect(this->ui->occupants,SIGNAL(textChanged()),this,SLOT(setChanged()));
    connect(this->ui->notes,SIGNAL(textChanged()),this,SLOT(setChanged()));
    connect(this,SIGNAL(occupieCBEvent(int)),parent,SLOT(occupie(int)));
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
    roomWindow* window = new roomWindow(0);
    window->backdrop = backdrop;
    window->backdropWidth = backdropWidth;
    window->backdropHeight = backdropHeight;

    return window;
}

bool roomWindow::save()
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

    return true;
}

void roomWindow::closeEvent(QCloseEvent * evt)
{
    if(changed)
    {
        int ret = saveDialog(this);


        switch (ret) {
             case QMessageBox::Save:
             {
                 save();
                 changed = false;
                 break;
             }
             case QMessageBox::Cancel:
             {
                 //Just closes the message box dialog
                 evt->ignore();
                 return ;
             }
             case QMessageBox::Discard:
             {

                readFiles(); //Reloads the old information
                break;
             }
        default:
        {
            //THIS SHOULD NEVER BE TRIGGERED !
            break;
        }
       }
    }
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

void roomWindow::readFiles()
{

     QString applicationDir = QApplication::applicationDirPath()
             .append("/Data/Rooms/");

     QString roomName = parent->text() + '/';
     QString filePath = applicationDir + roomName;
     QDir dir;

     QFileInfo outDir (filePath);
     if (!outDir.exists())
     {
         return;
     }


     QFile occupantsF (filePath + "Occupants");

     if(!occupantsF.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         qDebug() << "Error occured while reading data for room window at:"<<filePath + roomName;
     }
     else
     {
         ui->occupants->clear();
         QTextStream stream(&occupantsF);
         ui->occupants->insertHtml(stream.readAll());
     }

     QFile notesF(filePath + "Notes");
     if(!notesF.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         qDebug() << "Error occured while reading data for room window at:"<<filePath + roomName;
     }
     else
     {
         ui->notes->clear();
         QTextStream stream(&notesF);
         ui->notes->insertHtml(stream.readAll());
     }

}

 int roomWindow::saveDialog(QWidget* parent)
 {
     QMessageBox message(parent);
     message.setText("The room information has been modified.");
     message.setInformativeText("Do you want to save your changes?");
     message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
     message.setDefaultButton(QMessageBox::Cancel);

     int ret = message.exec();

     return ret;
 }

void roomWindow::on_cancelButton_released()
{
    if(changed)
    {
        int ret = saveDialog(this);


        switch (ret) {
             case QMessageBox::Save:
             {
                 save();
                 changed = false;
                 close();
                 break;
             }
             case QMessageBox::Cancel:
             {
                 //Just closes the message box dialog
                 return;
             }
             case QMessageBox::Discard:
             {
                 readFiles(); //Reloads the old information
                 changed = false;
                 close();
                break;
             }
        default:
        {
            //THIS SHOULD NEVER BE TRIGGERED !
            break;
        }
        }
    }else
    {
        this->close();
    }
}

void roomWindow::on_saveButton_released()
{
    if(changed)
    {
        int ret = saveDialog(this);


        switch (ret) {
             case QMessageBox::Save:
             {
                 save();
                 changed = false;
                 break;
             }
             case QMessageBox::Cancel:
             {
                 //Just closes the message box dialog
                 return;
             }
             case QMessageBox::Discard:
             {

                 readFiles(); //Reloads the old information
                 changed = false;
                break;
             }
        default:
        {
            //THIS SHOULD NEVER BE TRIGGERED !
            break;
        }
        }
    }
}



void roomWindow::on_occupiedCB_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
    {
        emit occupieCBEvent(0);
    }else
    {
        emit occupieCBEvent(1);
    }
}
