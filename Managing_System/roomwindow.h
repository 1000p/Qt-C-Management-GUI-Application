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
    roomWindow(QWidget *parent = nullptr);
    virtual ~roomWindow();

    void init(QWidget* parent);
    void changeBackdrop (QImage& image);
    roomWindow* clone();

signals:
    Q_SIGNAL void setNull(QEvent * evt);

protected:
    void resizeEvent(QResizeEvent* evt) override;
    void paintEvent(QPaintEvent * evt) override;
    void closeEvent(QCloseEvent *evt) override;


private:
    Ui::roomWindow *ui;
    QImage backdrop;

    int backdropWidth;
    int backdropHeight;

    bool changed;
};

#endif // ROOMWINDOW_H
