#ifndef SCROLLAREACONTAINER_H
#define SCROLLAREACONTAINER_H

#include <QScrollArea>
#include <QImage>

class scrollAreaParent: public QWidget
{
protected:

    void paintEvent(QPaintEvent* evt) override;
    void resizeEvent(QResizeEvent *event) override;

public:
    scrollAreaParent(QWidget* parent = nullptr);

private:
    QImage backdrop;

    int backdropWidth;
    int backdropHeight;
};

#endif // SCROLLAREACONTAINER_H
