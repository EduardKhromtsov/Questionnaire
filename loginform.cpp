#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    setFixedSize(536, 628);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_setAdminModeCheckBox_clicked(bool checked)
{
    if (checked)
    {
        ui->passwordLineEdit->setEnabled(true);

        ui->nameLineEdit->setText("admin");
        ui->nameLineEdit->setEnabled(false);

        ui->telephoneNumberLineEdit->clear();
        ui->telephoneNumberLineEdit->setEnabled(false);

        ui->isTheOrganizationCheckBox->setChecked(false);
        ui->isTheOrganizationCheckBox->setEnabled(false);
        ui->infoAboutCompanyGroupBox->setEnabled(false);
        ui->companyNameLineEdit->clear();
        ui->fieldOfCompanyLineEdit->clear();
    }
    else
    {
        ui->passwordLineEdit->setEnabled(false);
        ui->passwordLineEdit->clear();

        ui->telephoneNumberLineEdit->setEnabled(true);

        ui->nameLineEdit->setEnabled(true);
        ui->nameLineEdit->clear();

        ui->isTheOrganizationCheckBox->setEnabled(true);
    }

    ui->correctnessStatusTelephoneLineEditLabel->setPixmap(QPixmap());
    ui->correctnessStatusNameLineEditLabel->setPixmap(QPixmap());
}

void LoginForm::on_telephoneNumberLineEdit_textChanged(const QString &arg1)
{
    QRegularExpression reTelephoneNumber("^\\+?(7 |)[0-9]{3}+(-|)[0-9]{3}+(-|)[0-9]{2}+(-|)[0-9]{2}$");
    QRegularExpressionMatch match = reTelephoneNumber.match(arg1);

    QPixmap pixmap;

    if (match.hasMatch())
    {
        pixmap.load(":/images/correct.png");
        ui->correctnessStatusTelephoneLineEditLabel->setPixmap(pixmap);
        isTelephoneNumberCorrect = true;
    }
    else
    {
        pixmap.load(":/images/x-button.png");
        ui->correctnessStatusTelephoneLineEditLabel->setPixmap(pixmap);
        isTelephoneNumberCorrect = false;
    }

}

void LoginForm::on_nameLineEdit_textChanged(const QString &arg1)
{
    QRegularExpression reNameAndSurname("[A-Za-zА-Яа-я]( [A-Za-zА-Яа-я]+)*$");
    QRegularExpressionMatch match = reNameAndSurname.match(arg1);

    QPixmap pixmap;

    if (match.hasMatch())
    {
        pixmap.load(":/images/correct.png");
        ui->correctnessStatusNameLineEditLabel->setPixmap(pixmap);
        isNameCorrect = true;
    }
    else
    {
        pixmap.load(":/images/x-button.png");
        ui->correctnessStatusNameLineEditLabel->setPixmap(pixmap);
        isNameCorrect = false;
    }
}


void LoginForm::on_loginPushButton_pressed()
{    

    if (ui->setAdminModeCheckBox->isChecked())
    {
        if (ui->passwordLineEdit->text() == "admin")
        {
            ptrMainWindow = new MainWindow();
            ptrMainWindow->show();
            ptrMainWindow->getNameFromLoginForm(ui->nameLineEdit->text());
            this->hide();

            delete this;
        }
        else
            QMessageBox::warning(this, "Вход не выполнен", "Неправильный пароль");
    }
    else
    {
        bool sameUser = false;

        QSqlDatabase dataBase;

        dataBase = QSqlDatabase::addDatabase("QMYSQL");
        dataBase.setHostName("db4free.net");
        dataBase.setPort(3306);
        dataBase.setDatabaseName("questionnairedb");
        dataBase.setUserName("testsuperadmin");
        dataBase.setPassword("12345678");

        if (dataBase.open())
            qDebug() << "open";
        else
            qDebug() << "not open";

        QSqlQuery query(dataBase);

        query.exec("SELECT name FROM Respondents");

        while (query.next())
        {
            if (query.value(0).toString() == ui->nameLineEdit->text())
            {
                sameUser = true;
                break;
            }
        }

        if (sameUser)
            QMessageBox::warning(this, "Вход не выполнен", "Человек с именем " + ui->nameLineEdit->text() + " уже прошел данный опрос");
        else if (isNameCorrect && isTelephoneNumberCorrect && ui->nameLineEdit->text() != "admin")
        {
            if ((ui->isTheOrganizationCheckBox->isChecked() && ui->companyNameLineEdit->text() != "" && ui->fieldOfCompanyLineEdit->text() != "") || !(ui->isTheOrganizationCheckBox->isChecked()))
            {
                ptrMainWindow = new MainWindow();
                ptrMainWindow->show();

                ptrMainWindow->getNameFromLoginForm(ui->nameLineEdit->text());
                ptrMainWindow->getTelephoneNumberFromLoginForm(ui->telephoneNumberLineEdit->text());
                ptrMainWindow->getCompanyNameFromLoginForm(ui->companyNameLineEdit->text());
                ptrMainWindow->getFieldOfCompanyFromLoginForm(ui->fieldOfCompanyLineEdit->text());

                this->hide();

                delete this;
            }
            else
                QMessageBox::warning(this, "Вход не выполнен", "Укажите название и сферу деятельности организации");
        }
        else
            QMessageBox::warning(this, "Вход не выполнен", "Неправильно заполнены данные о имени/номере телефона");
    }
}

bool LoginForm::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* pKeyEvent = dynamic_cast<QKeyEvent*>(event);

        if (pKeyEvent->key() == Qt::Key_Enter)
        {
            on_loginPushButton_pressed();
            return true;
        }

    }
    return QWidget::event(event);
}

void LoginForm::on_isTheOrganizationCheckBox_clicked(bool checked)
{
    if (checked)
        ui->infoAboutCompanyGroupBox->setEnabled(true);
    else
    {
        ui->infoAboutCompanyGroupBox->setEnabled(false);
        ui->companyNameLineEdit->clear();
        ui->fieldOfCompanyLineEdit->clear();
    }
}

