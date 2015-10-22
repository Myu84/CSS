#ifndef ERRORLISTDIALOG_H
#define ERRORLISTDIALOG_H

#include <QDialog>

namespace Ui {
class ErrorListDialog;
}

class ErrorListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorListDialog(QWidget *parent = 0);
    ~ErrorListDialog();

private:
    Ui::ErrorListDialog *ui;
};

#endif // ERRORLISTDIALOG_H
