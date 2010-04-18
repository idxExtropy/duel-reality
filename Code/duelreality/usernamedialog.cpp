#include <QtGui>

#include "usernamedialog.h"

UserNameDialog::UserNameDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableContinueButton(const QString &)));
    connect(continueButton, SIGNAL(clicked()), this, SLOT(continueClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(newUserBox, SIGNAL(stateChanged(int)), this, SLOT(disableReturningUserBox(int)));
    connect(returningUserBox, SIGNAL(stateChanged(int)), this, SLOT(disableNewUserBox(int)));
}

void UserNameDialog::enableContinueButton(const QString &text)
{
    continueButton->setEnabled(!text.isEmpty());
}

void UserNameDialog::disableNewUserBox(int state)
{
    newUserBox->setDisabled(state);
}

void UserNameDialog::disableReturningUserBox(int state)
{
    returningUserBox->setDisabled(state);
}

void UserNameDialog::continueClicked()
{
    QString text = lineEdit->text();
    emit sendUserName(text);
}
