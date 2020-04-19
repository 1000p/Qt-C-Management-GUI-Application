#ifndef ROOMBUTTONWRAP_H
#define ROOMBUTTONWRAP_H

#include "initializer.h"
//#include "roomwindow.h"


#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QEvent>
#include <QScrollArea>

class roomButtonWrap: public QPushButton
{
    Q_OBJECT

public:
    roomButtonWrap(int styleFlag, QWidget* parrent = nullptr );
    roomButtonWrap(int styleFlag, const QString& text, QWidget* parrent = nullptr);
    roomButtonWrap(int styleFlag, const QIcon& icon, const QString& text, QWidget* parrent=nullptr);
    virtual ~roomButtonWrap();

    static int getID()
    {
        return roomID;
    }

    bool isOccupied()
    {
        if(occupied == 0)
        {
            return false;
        }
        return true;
    }

    void save();

public slots:

    void released() ;
    void handleWindowEvent(QEvent* evt);

    void occupie(int flag)
    {
        if(flag == 1)
        {
          occupied = 1;
          setStyle(occupied);
        }
        else
        {
            if(occupied!=0)
            {
                occupied = 0;
                setStyle(occupied);
            }
        }

    }

private:
   static int roomID;

   void setStyle(int isOccupied);

   int occupied;
   Initializer& initializer;
   roomWindow* window;

};

#endif // ROOMBUTTONWRAP_H
