#include "scrollareaparent.h"

#include <QCoreApplication>
#include <QImageReader>
#include <QPainter>
#include <QDebug>

scrollAreaParent::scrollAreaParent(QWidget* parent): QWidget(parent)
{
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString filePath = applicationDir + "/Images/Main Window/Backdrop - Cork.png";


    setGeometry(280,0,1000,720);
    QImageReader reader(filePath);
    if(reader.supportsOption(QImageIOHandler::ScaledSize))
    {
         reader.setScaledSize(size()*2);
         backdrop = reader.read();
    }else
    {
        qDebug() << "ERROR at backdrop scaling for the Work Area!!" <<
                    filePath;
    }

}


void scrollAreaParent::paintEvent(QPaintEvent* evt)
{
    QPainter painter (this);
    QRect rect {0,0, backdropWidth, backdropHeight};

    painter.drawImage(rect, backdrop);
    //qDebug() << "Painting";

    QWidget::paintEvent(evt);
}

void scrollAreaParent::resizeEvent(QResizeEvent *event)
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

    QWidget::resizeEvent(event);
}
