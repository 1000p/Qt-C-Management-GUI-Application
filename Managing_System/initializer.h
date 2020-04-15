#ifndef INITIALIZER_H
#define INITIALIZER_H
#include "roombuttonwrap.h"

//#include <QString>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QLayout>

//THIS CLASS IS SIGLETON
class Initializer
{
public:    

    static Initializer& getInstance()
    {
        static Initializer instance ;
        return instance;
    }

    void operator () (QVector<roomButtonWrap*>& buttons, QLayout* layout)
    {
       if(!readRooms(buttons, layout) )
       {
           qDebug() << "Error readig rooms !! readRooms returned false !";
       }

    }

   /* roomButtonWrap* newRoomButton(QString& name, QLayout* layout)
    {

        roomButtonWrap* button = new roomButtonWrap(name);
        layout->addWidget(button);

        return button;
    }*/


private:
    Initializer();
    Initializer(Initializer const& other) = delete;
    void operator = ( Initializer const& other) = delete;


    bool readRooms(QVector<roomButtonWrap*>& buttons, QLayout* layout)
    {
        bool success = true;

        QFile rooms( ":/DATA/Data/Rooms/Rooms.txt");

        if(!rooms.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Error opening the file at: /Data/Rooms/Rooms.txt";
            success = false;
        }else
        {
            QTextStream file(&rooms);
            QString line = file.readLine();
            roomButtonWrap* button = nullptr;

            while(!line.isNull())
            {
                button = new roomButtonWrap(line);
                layout->addWidget(button);
                buttons.push_back(button);
                line = file.readLine();

            }

        }

        return success;
    }


    QString roomsPath;
    QString prefix = ".txt";
};

#endif // INITIALIZER_H
