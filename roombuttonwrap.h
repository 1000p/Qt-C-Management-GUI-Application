#ifndef ROOMBUTTONWRAP_H
#define ROOMBUTTONWRAP_H
#include "roomwindow.h"

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

    static int getID()
    {
        return roomID;
    }

    virtual ~roomButtonWrap() = default;

public slots:

    void released() ;
    void handleWindowEvent(QEvent* evt);

private:
   static int roomID;
    roomWindow* window;


};

#endif // ROOMBUTTONWRAP_H
