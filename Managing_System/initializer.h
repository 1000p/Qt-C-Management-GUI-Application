#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "ResourceType.h"
//#include "roomwindow.h"

//#include <QString>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QLayout>
#include <QHash>

class roomButtonWrap;
class roomWindow;

//THIS CLASS IS SIGLETON
class Initializer
{
public:    

    static Initializer& getInstance()
    {
        static Initializer instance ;
        return instance;
    }

    void operator () (QVector<roomButtonWrap*>& buttons, QLayout* layout);

    void* getObjectSpawner(int key);

    void close();


private:
    Initializer();


    Initializer(Initializer const& other) = delete;
    void operator = ( Initializer const& other) = delete;


    bool readRooms(QVector<roomButtonWrap*>& buttons, QLayout* layout);

    roomWindow* initRoomWindowSpawner(bool test);

    void loadSpawners();

    QHash <int, void*> _objects;


};

#endif // INITIALIZER_H
