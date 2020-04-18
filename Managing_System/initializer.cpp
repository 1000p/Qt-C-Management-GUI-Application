#include "initializer.h"
#include "roombuttonwrap.h"
#include "roomwindow.h"

Initializer::Initializer()
{
    loadSpawners();

}


void Initializer::operator () (QVector<roomButtonWrap*>& buttons, QLayout* layout)
{
   if(!readRooms(buttons, layout) )
   {
       qDebug() << "Error readig rooms !! readRooms returned false !";
   }

}

void* Initializer::getObjectSpawner(int key)
{
    return _objects[key];
}

void Initializer::close()
{
    QHash <int, void*>::iterator it = _objects.begin();
    QHash <int, void*>::iterator endIt = _objects.end();
    ResourceType key;

    for(; it!= endIt; ++it)
    {
        key = static_cast<ResourceType>(it.key());
        switch (key) {
            case ResourceType::ROOM_WINDOW_SPAWNER:
            {
                delete static_cast<roomWindow*>(it.value());
                break;
            }
        }
    }
}


bool Initializer::readRooms(QVector<roomButtonWrap*>& buttons, QLayout* layout)
{
    bool success = true;

    QString applicationDir = QCoreApplication::applicationDirPath();
    QString filePath = applicationDir + "/Data/Rooms/Rooms.txt";

    QFile rooms( filePath);

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

roomWindow* Initializer::initRoomWindowSpawner(bool test)
{
    roomWindow* window = nullptr;
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString filePath = applicationDir + "/Data/Windows/RoomWindow.txt";

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error loading file at: " << filePath;
        test = false;
    }
    else
    {
        QTextStream textStream(&file);
        QSize size;
        int dimension;

        textStream>>dimension;
        size.setWidth(dimension);
        textStream>>dimension;
        size.setHeight(dimension);
        textStream.skipWhiteSpace();

        QString line = textStream.readLine();
        window = new roomWindow();

        QImageReader reader(applicationDir.append(line));

        if(reader.supportsOption(QImageIOHandler::ScaledSize))
        {
            reader.setScaledSize(size*2);
            QImage image = reader.read();

            window->changeBackdrop(image);

        }else
        {
            qDebug() << "ERROR at backdrop scaling for the Room Window!!" <<
                        applicationDir.append(line);
            test = false;
        }

    }

    return window;
}

void Initializer::loadSpawners()
{

    bool test = true;
    roomWindow* window = initRoomWindowSpawner(test);
    if(test)
    {
        int key = static_cast<int>(ResourceType::ROOM_WINDOW_SPAWNER);
        _objects[key] = window;
    }else
    {
        qDebug() << "Error loading objects from files!!";
    }
}
