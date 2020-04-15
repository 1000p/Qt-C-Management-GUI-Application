#include "roombuttonwrap.h"


int roomButtonWrap::roomID = 1;

roomButtonWrap::roomButtonWrap(QWidget* parrent):
    QPushButton(parrent), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));
    ++roomID;
    //this->show();
}

roomButtonWrap::roomButtonWrap (const QString& text, QWidget* parrent):
    QPushButton(text,parrent), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));
    ++roomID;
    setFixedSize(100,100);
    //this->show();
}


roomButtonWrap::roomButtonWrap(const QIcon& icon, const QString& text, QWidget* parrent):
    QPushButton(icon,text,parrent), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));

    ++roomID;
    //this->show();
}


void roomButtonWrap::handleWindowEvent(QEvent* evt)
{
    if(evt->type() == QEvent::Close)
    {
        delete window;
        window = nullptr;
    }
}

 void roomButtonWrap::released()
 {
     if(!window)
     {
        window = new roomWindow(this);

     }else
     {
         delete window;
         window = nullptr;
     }
 }

