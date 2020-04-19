#include "savedialog.h"
#include "ui_savedialog.h"

saveDialog::saveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveDialog)
{
    ui->setupUi(this);
}

saveDialog::~saveDialog()
{
    delete ui;
}
