#include <QString>

#include "ErrorListDialog.h"
#include "ui_ErrorListDialog.h"

ErrorListDialog::ErrorListDialog(const QString &errorLog, int numErrors, int numWarnings) {
    ui.setupUi(this);
	
	ui.errorCountLabel->setText("There were " + QString::number(numErrors) + " errors and " + QString::number(numWarnings) + " warnings.");
	ui.errorListText->setPlainText(errorLog);
}
