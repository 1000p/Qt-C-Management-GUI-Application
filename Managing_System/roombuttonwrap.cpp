#include "roombuttonwrap.h"
#include "roomwindow.h"

#include <QFlags>
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
         stream<<this->text()<<'\n';
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

