#include "imagelabel.h"

#include "QImageReader"
#include "QDebug"
#include "QPainter"

imageLabel::imageLabel(QRect& geometry, QWidget* parent): QLabel(parent)
{
    setGeometry(geometry);

    //Get our .exe directory
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString filePath = applicationDir + "/Images/Main Window/Sidebar - Chalkboard.png";

    //Create image reader with the file path
    QImageReader reader(filePath);
    QSize size {(geometry.width()*2),(geometry.height()*2)};

    //Can be scalled, else it wont load
    if(reader.supportsOption(QImageIOHandler::ScaledSize))
    {
        reader.setScaledSize(size);
        QImage image = reader.read();

        backdrop = image;
        backdropWidth = size.width();
        backdropHeight = size.height();

    }else
    {
        qDebug() << "ERROR at backdrop scaling for the Room Window!!" <<
                   filePath;
    }

}


void imageLabel::paintEvent(QPaintEvent* evt)
{
    //Called on every paint event
    QPainter painter (this);
    QRect rect {0,0,backdropWidth,backdropHeight};
    painter.drawImage(rect, backdrop);

    QLabel::paintEvent(evt);
}
void imageLabel::resizeEvent(QResizeEvent* evt)
{
    //Called on any resize event;
    QSize winSize = size();
    if(backdropWidth>winSize.width() ||backdropWidth<winSize.width() )
    {
        backdropWidth  = winSize.width();
    }
    if(backdropHeight>winSize.height() || backdropHeight<winSize.height())
    {
        backdropHeight = winSize.height();
    }

    QLabel::resizeEvent(evt);
}
