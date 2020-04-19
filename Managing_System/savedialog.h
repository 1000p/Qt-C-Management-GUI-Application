#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

namespace Ui {
class saveDialog;
}

class saveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveDialog(QWidget *parent = nullptr);
    ~saveDialog();

private:
    Ui::saveDialog *ui;
};

#endif // SAVEDIALOG_H
