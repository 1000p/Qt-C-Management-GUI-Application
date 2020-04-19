#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include "roombuttonwrap.h"
#include <QDialog>
#include <QImageReader>
#include <QMessageBox>

namespace Ui {
class roomWindow;
}

class roomWindow : public QDialog
{
    Q_OBJECT

public:
    roomWindow(int occupiedFlag, QWidget *parent = nullptr);
    virtual ~roomWindow();

    void init(roomButtonWrap* parent);
    void changeBackdrop (QImage& image);
    roomWindow* clone();

    bool save();

signals:
    Q_SIGNAL void setNull(QEvent * evt);
    void occupieCBEvent(int flag);

protected:
    void resizeEvent(QResizeEvent* evt) override;
    void paintEvent(QPaintEvent * evt) override;
    void closeEvent(QCloseEvent *evt) override;

protected slots:
    void setChanged();

private slots:
    void on_cancelButton_released();

    void on_saveButton_released();

    void on_occupiedCB_stateChanged(int arg1);

private:
    void readFiles();

    int saveDialog(QWidget* parent);

    Ui::roomWindow *ui;
    QImage backdrop;
    roomButtonWrap* parent;

    int backdropWidth;
    int backdropHeight;

    bool changed;
};

#endif // ROOMWINDOW_H
