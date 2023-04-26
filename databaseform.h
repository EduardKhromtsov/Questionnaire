#ifndef DATABASEFORM_H
#define DATABASEFORM_H

#include <QWidget>
#include <QtSql>
#include <QPrinter>
#include <QPrintDialog>

namespace Ui {
class DataBaseForm;
}

class DataBaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataBaseForm(QWidget *parent = nullptr);
    ~DataBaseForm();

private slots:
    void on_searchLineEdit_textChanged(const QString &arg1);

    void on_printToolButton_pressed();

    void on_backToMainWindowPushButton_pressed();

signals:
    void goToMainWindow();

private:
    QSqlDatabase dataBase;
    QSqlQueryModel model;
    Ui::DataBaseForm *ui;
};

#endif // DATABASEFORM_H
