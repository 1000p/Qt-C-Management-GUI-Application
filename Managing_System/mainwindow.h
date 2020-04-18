#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "initializer.h"
#include "roombuttonwrap.h"
#include "flowlayout.h"
#include "scrollareaparent.h"

#include <QMainWindow>

#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
  void  on_newRoomButton_released();

protected:
  void resizeEvent(QResizeEvent* evt) override;
  void paintEvent(QPaintEvent* evt) override;

private:


    Ui::MainWindow *ui;

    Initializer& initializer;
    QVector<roomButtonWrap*> _rooms;
    scrollAreaParent* workArea;

    QScrollArea* scrollArea;
    QWidget* container;


};
#endif // MAINWINDOW_H
