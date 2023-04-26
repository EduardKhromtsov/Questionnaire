#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1060, 568);

    ui->linkLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->linkLabel->setOpenExternalLinks(true);
    ui->linkLabel->setTextFormat(Qt::RichText);
    ui->linkLabel->setText("<a href=\"https://www.leadertask.ru/\">Сайт</a>");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getNameFromLoginForm(const QString &str)
{
    userName = str;
    ui->welcomeLabel->setText("Добро пожаловать, " + str);
}

void MainWindow::getTelephoneNumberFromLoginForm(const QString &str)
{
    userTelephoneNumber = str;
}

void MainWindow::getCompanyNameFromLoginForm(const QString &str)
{
    companyName = str;
}

void MainWindow::getFieldOfCompanyFromLoginForm(const QString &str)
{
    fieldCompany = str;
}

void MainWindow::on_toolButton_pressed()
{
    if (userName != "admin")
    {
        ptrQuestionnaireForm = new QuestionnaireForm();
        ptrQuestionnaireForm->getUserNameFromMainWindow(userName);
        ptrQuestionnaireForm->getUserTelephoneNumberFromMainWindow(userTelephoneNumber);
        ptrQuestionnaireForm->getCompanyNameFromMainWindow(companyName);
        ptrQuestionnaireForm->getFieldOfCompanyFromMainWindow(fieldCompany);
        ptrQuestionnaireForm->show();
        this->hide();
    }
    else
        QMessageBox::warning(this, "Доступ закрыт", "Администратор системы не может пройти опрос");
}


void MainWindow::on_toolButton_2_pressed()
{
    if (userName == "admin")
    {
        ptrDataBaseForm = new DataBaseForm();

        QObject::connect(ptrDataBaseForm, SIGNAL(goToMainWindow()), this, SLOT(show()));
        QObject::connect(ptrDataBaseForm, SIGNAL(goToMainWindow()), this, SLOT(deleteDataBaseForm()));

        ptrDataBaseForm->show();
        this->hide();
    }
    else
        QMessageBox::warning(this, "Доступ закрыт", "Данную вкладку может открыть только администратор системы");
}

void MainWindow::on_toolButton_3_pressed()
{
    if (userName == "admin")
    {
        ptrChartForm = new ChartForm();

        QObject::connect(ptrChartForm, SIGNAL(goToMainWindow()), this, SLOT(show()));
        QObject::connect(ptrChartForm, SIGNAL(goToMainWindow()), this, SLOT(deleteChartForm()));

        ptrChartForm->show();
        this->hide();
    }
    else
        QMessageBox::warning(this, "Доступ закрыт", "Данную вкладку может открыть только администратор системы");
}

void MainWindow::deleteChartForm()
{
    delete ptrChartForm;

    ptrChartForm = nullptr;
}

void MainWindow::deleteDataBaseForm()
{
    delete ptrDataBaseForm;

    ptrDataBaseForm = nullptr;
}


