#include "roombuttonwrap.h"
#include "roomwindow.h"

#include <QFlags>
int roomButtonWrap::roomID = 1;


roomButtonWrap::roomButtonWrap(int styleFlag, QWidget* parrent):
    QPushButton(parrent),occupied(styleFlag), initializer(Initializer::getInstance()),window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));
    ++roomID;
    setStyle(occupied);
    //this->show();
}

roomButtonWrap::roomButtonWrap (int styleFlag, const QString& text, QWidget* parrent):
    QPushButton(text,parrent),occupied(styleFlag),initializer(Initializer::getInstance()), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));
    ++roomID;
    setFixedSize(100,100);
    setStyle(occupied);
    //this->show();
}


roomButtonWrap::roomButtonWrap(int styleFlag, const QIcon& icon, const QString& text, QWidget* parrent):
    QPushButton(icon,text,parrent),occupied(styleFlag),initializer(Initializer::getInstance()), window(nullptr)
{
    connect(this,SIGNAL(released()), this, SLOT(released()));

    ++roomID;
    setStyle(occupied);
    //this->show();
}

 roomButtonWrap::~roomButtonWrap()
{
    --roomID;
     if(window)
     {
        delete window;
     }
}


 void roomButtonWrap::save()
 {
     static bool shouldClear = true;
     QString appllicationDir = QCoreApplication::applicationDirPath();
     QString filePath = appllicationDir.append("/Data/Rooms/Rooms.txt");

     QFile rooms(filePath);
     QFlags <QIODevice::OpenModeFlag> flags;

     if(shouldClear)
     {
        flags = (QIODevice::WriteOnly | QIODevice::Text);
        shouldClear = false;
     }
     else
     {
         flags = QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text;
     }

     if(!rooms.open(flags))
     {
         qDebug() << "Error occured while saving data for room buttons, file"
                     "could not be initialized/created at:"<<filePath;
     }else
     {
         QTextStream stream(&rooms);
         stream<<this->text()<<'\n'<<occupied<<'\n';
     }
    rooms.close();
 }


void roomButtonWrap::handleWindowEvent(QEvent* evt)
{
    if(evt->type() == QEvent::Close)
    {
        delete window;
        window = nullptr;
    }
}

void roomButtonWrap::setStyle(int isOccupied)
{
    if(isOccupied == 1)
    {
        this->setStyleSheet("QPushButton {"
                            " font:bold;"
                            " font-size: 12px;"
                            " background-color: rgba(250, 0, 0, 60);"
                            " border: 0px; }"
                            " QPushButton:hover {"
                            " border:0px solid rgb(200,0,0);"
                            " border-width: 2px;"
                            " background-color: rgba(250, 0, 0, 80); }"
                            " QPushButton:pressed { "
                            "background-color: rgba(250, 0, 0, 110);"
                            " border-style: inset; "
                            "border-width: 3px; }");
    }else
    {
        this->setStyleSheet("QPushButton"
                            " { background-color: rgba(0, 250, 0, 60); border: 0px;"
                            "font:bold;"
                            "font-size: 12px; }"
                            " QPushButton:hover { "
                            "border:0px solid rgb(0,150,0);"
                            " border-width: 2px;"
                            " background-color: rgba(0, 250, 0, 80); }"
                            " QPushButton:pressed { "
                            "background-color: rgba(0, 150, 0, 110);"
                            " border-style: inset;"
                            " border-width: 3px; }");
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
        if(window->close())
        {
            delete window;
            window = nullptr;
        }
     }
 }

