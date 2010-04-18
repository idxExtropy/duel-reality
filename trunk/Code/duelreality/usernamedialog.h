#ifndef USERNAMEDIALOG_H
#define USERNAMEDIALOG_H

#include <QDialog>

#include "ui_usernamedialog.h"

class UserNameDialog : public QDialog, public Ui::UserNameDialog
{
    Q_OBJECT

public:
    UserNameDialog(QWidget *parent = 0);

private slots:
    void enableContinueButton(const QString &text);
    void disableNewUserBox(int state);
    void disableReturningUserBox(int state);
};

#endif // USERNAMEDIALOG_H
