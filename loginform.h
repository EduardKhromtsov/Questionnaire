#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QRegularExpression>
#include <QMessageBox>
#include "mainwindow.h"
#include <QKeyEvent>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_setAdminModeCheckBox_clicked(bool checked);

    void on_telephoneNumberLineEdit_textChanged(const QString &arg1);

    void on_nameLineEdit_textChanged(const QString &arg1);

    void on_loginPushButton_pressed();

    void on_isTheOrganizationCheckBox_clicked(bool checked);

private:
    Ui::LoginForm *ui;
    MainWindow *ptrMainWindow;
    bool isTelephoneNumberCorrect = false;
    bool isNameCorrect = false;

protected:
    bool event(QEvent *event) override;

};

#endif // LOGINFORM_H
