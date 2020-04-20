#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include "QLabel"
#include "QImage"

class imageLabel: public QLabel
{
    Q_OBJECT
public:
    imageLabel(QRect& geometry, QWidget* parent=nullptr);

    virtual ~imageLabel() = default;

protected:
    void paintEvent(QPaintEvent* evt) override;
    void resizeEvent(QResizeEvent* evt) override;

private:

    QImage backdrop;
    int backdropWidth;
    int backdropHeight;
};

#endif // IMAGELABEL_H
