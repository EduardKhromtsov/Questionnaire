#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "questionnaireform.h"
#include "databaseform.h"
#include "chartform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getNameFromLoginForm(const QString& str);
    void getTelephoneNumberFromLoginForm(const QString& str);
    void getCompanyNameFromLoginForm(const QString& str);
    void getFieldOfCompanyFromLoginForm(const QString& str);

private slots:
    void on_toolButton_pressed();

    void on_toolButton_2_pressed();

    void on_toolButton_3_pressed();

    void deleteChartForm();

    void deleteDataBaseForm();

private:
    Ui::MainWindow *ui;
    QuestionnaireForm *ptrQuestionnaireForm;
    DataBaseForm *ptrDataBaseForm;
    ChartForm *ptrChartForm;
    QString userName;
    QString userTelephoneNumber;
    QString companyName;
    QString fieldCompany;
};
#endif // MAINWINDOW_H
