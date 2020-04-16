#include "roombuttonwrap.h"


int roomButtonWrap::roomID = 1;


roomButtonWrap::roomButtonWrap(QWidget* parrent):
    QPushButton(parrent), initializer(Initializer::getInstance()),window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));
    ++roomID;
    //this->show();
}

roomButtonWrap::roomButtonWrap (const QString& text, QWidget* parrent):
    QPushButton(text,parrent),initializer(Initializer::getInstance()), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));
    ++roomID;
    setFixedSize(100,100);
    //this->show();
}


roomButtonWrap::roomButtonWrap(const QIcon& icon, const QString& text, QWidget* parrent):
    QPushButton(icon,text,parrent),initializer(Initializer::getInstance()), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));

    ++roomID;
    //this->show();
}

 roomButtonWrap::~roomButtonWrap()
{
    --roomID;
     delete window;
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
        roomWindow* spawner =
        static_cast<roomWindow*>
                (initializer.getObjectSpawner
                 (static_cast<int>(ResourceType::ROOM_WINDOW_SPAWNER)));
        window = spawner->clone();

        window->init(this);

     }else
     {       
        delete window;
         window = nullptr;
     }
 }

