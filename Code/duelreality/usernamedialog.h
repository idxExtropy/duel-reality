#ifndef USERNAMEDIALOG_H
#define USERNAMEDIALOG_H

#include <QDialog>

#include "ui_usernamedialog.h"

class UserNameDialog : public QDialog, public Ui::UserNameDialog
{
    Q_OBJECT

public:
    UserNameDialog(QWidget *parent = 0);

signals:
    void sendUserName(const QString &str);

private slots:
    void enableContinueButton(const QString &text);
    void disableNewUserBox(int state);
    void disableReturningUserBox(int state);
    void continueClicked();
};

#endif // USERNAMEDIALOG_H
