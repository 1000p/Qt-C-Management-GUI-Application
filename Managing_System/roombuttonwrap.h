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
    roomButtonWrap(QWidget* parrent = nullptr);
    roomButtonWrap(const QString& text, QWidget* parrent = nullptr);
    roomButtonWrap(const QIcon& icon, const QString& text, QWidget* parrent=nullptr);
    virtual ~roomButtonWrap();

    static int getID()
    {
        return roomID;
    }



public slots:

    void released() ;
    void handleWindowEvent(QEvent* evt);

private:
   static int roomID;
   Initializer& initializer;
    roomWindow* window;

};

#endif // ROOMBUTTONWRAP_H
