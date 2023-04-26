#include "questionnaireform.h"
#include "ui_questionnaireform.h"

QuestionnaireForm::QuestionnaireForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionnaireForm)
{
    ui->setupUi(this);

    setFixedSize(843, 420);

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

    QSqlQuery *query = new QSqlQuery(dataBase);

    query->exec("PRAGMA foreign_keys=on;");

    query->exec("CREATE TABLE Respondents"
               "(id INTEGER PRIMARY KEY AUTO_INCREMENT, name TEXT NOT NULL, telephone TEXT NOT NULL, companyName TEXT, fieldOfCompany TEXT);");

    query->exec("CREATE TABLE Answers"
                "(id INTEGER PRIMARY KEY AUTO_INCREMENT, "
                "id_respondent INTEGER NOT NULL, "
                "firstQuestion TEXT NOT NULL,"
                "secondQuestion TEXT NOT NULL,"
                "thirdQuestion TEXT NOT NULL,"
                "fourthQuestion TEXT NOT NULL,"
                "fifthQuestion TEXT NOT NULL,"
                "sixthQuestion TEXT NOT NULL,"
                "seventhQuestion TEXT NOT NULL,"
                "eighthQuestion TEXT NOT NULL,"
                "ninthQuestion TEXT NOT NULL,"
                "tenthQuestion TEXT NOT NULL,"
                "wish TEXT,"
                "FOREIGN KEY(id_respondent) REFERENCES Respondents (id) ON DELETE CASCADE);");

    delete query;

}

QuestionnaireForm::~QuestionnaireForm()
{
    delete ui;
}

void QuestionnaireForm::getUserNameFromMainWindow(const QString &str)
{
    userName = str;
}

void QuestionnaireForm::getUserTelephoneNumberFromMainWindow(const QString &str)
{
    userTelephoneNumber = str;
}

void QuestionnaireForm::getCompanyNameFromMainWindow(const QString &str)
{
    companyName = str;
}

void QuestionnaireForm::getFieldOfCompanyFromMainWindow(const QString &str)
{
    fieldCompany = str;
}

void QuestionnaireForm::on_firstQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->firstQuestionComboBox->setEnabled(false);
        ui->secondQuestionComboBox->setEnabled(true);
    }
}


void QuestionnaireForm::on_secondQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->secondQuestionComboBox->setEnabled(false);
        ui->thirdQuestionComboBox->setEnabled(true);
    }
}


void QuestionnaireForm::on_thirdQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->thirdQuestionComboBox->setEnabled(false);
        ui->fourthQuestionComboBox->setEnabled(true);
    }
}


void QuestionnaireForm::on_fourthQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->fourthQuestionComboBox->setEnabled(false);
        ui->fifthQuestionComboBox->setEnabled(true);
    }
}

void QuestionnaireForm::on_fifthQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->fifthQuestionComboBox->setEnabled(false);
        ui->sixthQuestionComboBox->setEnabled(true);
    }
}

void QuestionnaireForm::on_sixthQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->sixthQuestionComboBox->setEnabled(false);
        ui->seventhQuestionComboBox->setEnabled(true);
    }
}

void QuestionnaireForm::on_seventhQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->seventhQuestionComboBox->setEnabled(false);
        ui->eighthQuestionComboBox->setEnabled(true);
    }
}

void QuestionnaireForm::on_eighthQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->eighthQuestionComboBox->setEnabled(false);
        ui->ninthQuestionComboBox->setEnabled(true);
    }
}

void QuestionnaireForm::on_ninthQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->ninthQuestionComboBox->setEnabled(false);
        ui->tenthQuestionComboBox->setEnabled(true);
    }
}

void QuestionnaireForm::on_tenthQuestionComboBox_activated(int index)
{
    if (index != 0)
    {
        ui->progressBar->setValue(++countProgressBar);
        ui->tenthQuestionComboBox->setEnabled(false);
    }
}

void QuestionnaireForm::on_clearButton_pressed()
{
    ui->progressBar->setValue(0);
    countProgressBar = 0;

    ui->firstQuestionComboBox->setCurrentIndex(0);
    ui->secondQuestionComboBox->setCurrentIndex(0);
    ui->thirdQuestionComboBox->setCurrentIndex(0);
    ui->fourthQuestionComboBox->setCurrentIndex(0);
    ui->fifthQuestionComboBox->setCurrentIndex(0);
    ui->sixthQuestionComboBox->setCurrentIndex(0);
    ui->seventhQuestionComboBox->setCurrentIndex(0);
    ui->eighthQuestionComboBox->setCurrentIndex(0);
    ui->ninthQuestionComboBox->setCurrentIndex(0);
    ui->tenthQuestionComboBox->setCurrentIndex(0);

    ui->firstQuestionComboBox->setEnabled(true);
}

void QuestionnaireForm::on_sendAnswersButton_pressed()
{
    if (ui->tenthQuestionComboBox->currentIndex() != 0)
    {
        QSqlQuery *queryForRespondentsTable = new QSqlQuery(dataBase);
        QSqlQuery *queryForAnswersTable = new QSqlQuery(dataBase);

        queryForRespondentsTable->prepare("INSERT INTO Respondents(name, telephone, companyName, fieldOfCompany) VALUES(:name, :telephone, :companyName, :fieldOfCompany)");
        queryForRespondentsTable->bindValue(":name", userName);
        queryForRespondentsTable->bindValue(":telephone", userTelephoneNumber);
        queryForRespondentsTable->bindValue(":companyName", companyName);
        queryForRespondentsTable->bindValue(":fieldOfCompany", fieldCompany);

        queryForRespondentsTable->exec();

        queryForAnswersTable->prepare("INSERT INTO Answers(id_respondent, firstQuestion, secondQuestion, thirdQuestion, fourthQuestion, fifthQuestion, sixthQuestion, seventhQuestion, eighthQuestion, ninthQuestion, tenthQuestion, wish) VALUES(:id_respondent, :firstQuestion, :secondQuestion, :thirdQuestion, :fourthQuestion, :fifthQuestion, :sixthQuestion, :seventhQuestion, :eighthQuestion, :ninthQuestion, :tenthQuestion, :wish)");

        queryForRespondentsTable->exec("SELECT id FROM Respondents");
        queryForRespondentsTable->last();

        queryForAnswersTable->bindValue(":id_respondent", queryForRespondentsTable->value(0).toInt());
        queryForAnswersTable->bindValue(":firstQuestion", ui->firstQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":secondQuestion", ui->secondQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":thirdQuestion", ui->thirdQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":fourthQuestion", ui->fourthQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":fifthQuestion", ui->fifthQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":sixthQuestion", ui->sixthQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":seventhQuestion", ui->seventhQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":eighthQuestion", ui->eighthQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":ninthQuestion", ui->ninthQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":tenthQuestion", ui->tenthQuestionComboBox->currentText());
        queryForAnswersTable->bindValue(":wish", ui->wishesLineEdit->text());

        if (queryForAnswersTable->exec())
            qDebug() << "Запрос на добавление ответов выполнен";
        else
            qDebug() << "Запрос на добавление ответов не выполнен";

        delete queryForAnswersTable;
        delete queryForRespondentsTable;

        QMessageBox::information(this, "Опрос пройден", "Благодарим за прохождение опроса, программа закроется автоматически");
        QApplication::exit();
    }
    else
    {
        QMessageBox::warning(this, "Даны ответы не на все вопросы", "Вы ответили не на все вопросы");
    }
}

