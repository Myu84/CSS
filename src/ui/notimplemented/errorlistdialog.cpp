#include "errorlistdialog.h"
#include "ui_errorlistdialog.h"

ErrorListDialog::ErrorListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorListDialog)
{
    ui->setupUi(this);
}

ErrorListDialog::~ErrorListDialog()
{
    delete ui;
}
