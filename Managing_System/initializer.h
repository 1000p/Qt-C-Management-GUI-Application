#ifndef INITIALIZER_H
#define INITIALIZER_H
#include "roombuttonwrap.h"

//#include <QString>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>

//THIS CLASS IS SIGLETON
class Initializer
{
public:    

    static Initializer& getInstance()
    {
        static Initializer instance ;
        return instance;
    }

    void operator () (QVector<roomButtonWrap*>& buttons, QWidget* parent)
    {
       if(!readRooms(buttons, parent) )
       {
           qDebug() << "Error readig rooms !! readRooms returned false !";
       }

    }

    roomButtonWrap* newRoomButton(roomButtonWrap* lastButton,QString& name, QWidget* parent)
    {

        QRect newButtonGeometry;

        int bX, bY;

        if(lastButton == nullptr)
        {
            bX = 280;
            bY = 0;
            newButtonGeometry = {bX,bY,200,120};
        }
        else
        {
           QRect lastButtonPos = lastButton->geometry();
            bX = lastButtonPos.x() + lastButtonPos.width();
            if(bX + lastButtonPos.width() > parent->width())
            {
                bY = lastButtonPos.y() + lastButtonPos.height();
                bX = 280;
                if(bY + lastButtonPos.height() > parent->height())
                {
                    qDebug() << "No more space";
                    return nullptr;
                }
            }
            else
            {
                bY = lastButtonPos.y();
            }

           newButtonGeometry = {bX,bY,lastButtonPos.width(),lastButtonPos.height()};
        }
        roomButtonWrap* button = new roomButtonWrap(name, parent);
        button->setGeometry(newButtonGeometry);

        return button;
    }


private:
    Initializer();
    Initializer(Initializer const& other) = delete;
    void operator = ( Initializer const& other) = delete;


    bool readRooms(QVector<roomButtonWrap*>& buttons, QWidget* parent)
    {
        bool success = true;

        QFile rooms( QCoreApplication::applicationDirPath() +
                    "/Data/Rooms/Rooms.txt");

        if(!rooms.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Error opening the file at: /Data/Rooms/Rooms.txt";
            success = false;
        }else
        {
            QTextStream file(&rooms);
            QString line = file.readLine();
            roomButtonWrap* lastButton = nullptr;

            while(!line.isNull())
            {
                lastButton = newRoomButton(lastButton,line,  parent);
                buttons.push_back(lastButton);
                line = file.readLine();

            }

        }

        return success;
    }


    QString roomsPath;
    QString prefix = ".txt";
};

#endif // INITIALIZER_H
