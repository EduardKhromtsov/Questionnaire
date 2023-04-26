#ifndef QUESTIONNAIREFORM_H
#define QUESTIONNAIREFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql>


namespace Ui {
class QuestionnaireForm;
}

class QuestionnaireForm : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionnaireForm(QWidget *parent = nullptr);
    ~QuestionnaireForm();
    void getUserNameFromMainWindow(const QString& str);
    void getUserTelephoneNumberFromMainWindow(const QString& str);
    void getCompanyNameFromMainWindow(const QString& str);
    void getFieldOfCompanyFromMainWindow(const QString& str);

private slots:
    void on_firstQuestionComboBox_activated(int index);

    void on_secondQuestionComboBox_activated(int index);

    void on_thirdQuestionComboBox_activated(int index);

    void on_fourthQuestionComboBox_activated(int index);

    void on_fifthQuestionComboBox_activated(int index);

    void on_sixthQuestionComboBox_activated(int index);

    void on_seventhQuestionComboBox_activated(int index);

    void on_eighthQuestionComboBox_activated(int index);

    void on_ninthQuestionComboBox_activated(int index);

    void on_tenthQuestionComboBox_activated(int index);

    void on_clearButton_pressed();

    void on_sendAnswersButton_pressed();

private:
    Ui::QuestionnaireForm *ui;
    QSqlDatabase dataBase;
    QString userName;
    QString userTelephoneNumber;
    QString companyName;
    QString fieldCompany;
    int countProgressBar = 0;
};

#endif // QUESTIONNAIREFORM_H
