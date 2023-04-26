#ifndef CHARTFORM_H
#define CHARTFORM_H

#include <QWidget>
#include <QtCharts>
#include <QtSql>

namespace Ui {
class ChartForm;
}

class ChartForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChartForm(QWidget *parent = nullptr);
    ~ChartForm();

private slots:
    void on_questionNumberComboBox_activated(int index);

    void on_backToMainWindowPushButton_pressed();

    void on_userNameComboBox_activated(int index);

    void on_searchToolButton_pressed();

    void on_companyNameComboBox_activated(int index);

    void on_searchToolButton_2_pressed();

signals:
    void goToMainWindow();

private:
    Ui::ChartForm *ui;
    int countExcellentMarks{}, countGoodMarks{}, countBadMarks{}, countVeryBadMarks{};

private:
    void countMarksFromDataBase(int index);

    void setChartView();

    void countMarksFromDataBaseForChartView_2(int (*arrayOfMarks)[10]);

    void setChartView_2();

    void setChartView_3();

};

#endif // CHARTFORM_H
