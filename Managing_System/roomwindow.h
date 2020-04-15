#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QDialog>
#include <QImageReader>
namespace Ui {
class roomWindow;
}

class roomWindow : public QDialog
{
    Q_OBJECT

public:
    explicit roomWindow(QWidget *parent);
    ~roomWindow();

signals:
    Q_SIGNAL void setNull(QEvent * evt);


protected:
    void resizeEvent(QResizeEvent* evt) override;
    void closeEvent(QCloseEvent *evt) override;


private:
    Ui::roomWindow *ui;
    QImage backdrop;
    QPalette palette;

    bool changed;
};

#endif // ROOMWINDOW_H
