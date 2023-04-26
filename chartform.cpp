#include "chartform.h"
#include "ui_chartform.h"

ChartForm::ChartForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartForm)
{
    ui->setupUi(this);

    setFixedSize(903, 448);

    setChartView_2();

    QSqlDatabase dataBase;

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("db4free.net");
    dataBase.setPort(3306);
    dataBase.setDatabaseName("questionnairedb");
    dataBase.setUserName("testsuperadmin");
    dataBase.setPassword("12345678");

    dataBase.open();

    QSqlQuery query(dataBase);

    query.exec("SELECT name FROM Respondents");

    while (query.next())
        ui->userNameComboBox->addItem(query.value(0).toString());

    query.exec("SELECT companyName FROM Respondents");

    QSet<QString> set;

    while (query.next())
        set.insert(query.value(0).toString());

    for (const auto& element : set)
    {
        if (element != "")
            ui->companyNameComboBox->addItem(element);
    }

}

ChartForm::~ChartForm()
{
    delete ui;
}

void ChartForm::on_questionNumberComboBox_activated(int index)
{
    if (index != 0)
    {
        countMarksFromDataBase(index + 1);
        setChartView();
    }
}

void ChartForm::countMarksFromDataBase(int index)
{
    countExcellentMarks = 0;
    countGoodMarks = 0;
    countBadMarks = 0;
    countVeryBadMarks = 0;

    QSqlDatabase dataBase;

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("db4free.net");
    dataBase.setPort(3306);
    dataBase.setDatabaseName("questionnairedb");
    dataBase.setUserName("testsuperadmin");
    dataBase.setPassword("12345678");

    if (dataBase.open())
        qDebug() << "open for chart";
    else
        qDebug() << "not open for chart";

    QSqlQuery query(dataBase);

    query.exec("SELECT * FROM Answers");

    while (query.next())
    {
        if (query.value(index).toString() == "отлично")
            ++countExcellentMarks;

        if (query.value(index).toString() == "хорошо")
            ++countGoodMarks;

        if (query.value(index).toString() == "плохо")
            ++countBadMarks;

        if (query.value(index).toString() == "очень плохо")
            ++countVeryBadMarks;
    }


}

void ChartForm::setChartView()
{
    QBarSet *set0 = new QBarSet("Отлично");
    QBarSet *set1 = new QBarSet("Хорошо");
    QBarSet *set2 = new QBarSet("Плохо");
    QBarSet *set3 = new QBarSet("Очень плохо");

    *set0 << countExcellentMarks;
    *set1 << countGoodMarks;
    *set2 << countBadMarks;
    *set3 << countVeryBadMarks;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle("Диаграмма ответов на " + ui->questionNumberComboBox->currentText());
    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "Ответы";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChart *toDeleteChart;

    toDeleteChart = ui->chartView->chart();

    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    delete toDeleteChart;
}

void ChartForm::countMarksFromDataBaseForChartView_2(int (*arrayOfMarks)[10])
{
    QSqlDatabase dataBase;

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("db4free.net");
    dataBase.setPort(3306);
    dataBase.setDatabaseName("questionnairedb");
    dataBase.setUserName("testsuperadmin");
    dataBase.setPassword("12345678");

    if (dataBase.open())
        qDebug() << "open for chart";
    else
        qDebug() << "not open for chart";

    QSqlQuery query(dataBase);

    query.exec("SELECT firstQuestion, secondQuestion, thirdQuestion, fourthQuestion, fifthQuestion, sixthQuestion, seventhQuestion, eighthQuestion, ninthQuestion, tenthQuestion FROM Answers");

    while (query.next())
    {
        for (int i = 0; i < 10; ++i)
        {
            if (query.value(i).toString() == "отлично")
                ++arrayOfMarks[0][i];

            if (query.value(i).toString() == "хорошо")
                ++arrayOfMarks[1][i];

            if (query.value(i).toString() == "плохо")
                ++arrayOfMarks[2][i];

            if (query.value(i).toString() == "очень плохо")
                ++arrayOfMarks[3][i];
        }
    }
}

void ChartForm::setChartView_2()
{
    QBarSet *set0 = new QBarSet("Отлично");
    QBarSet *set1 = new QBarSet("Хорошо");
    QBarSet *set2 = new QBarSet("Плохо");
    QBarSet *set3 = new QBarSet("Очень плохо");

    int arrayOfMarks[4][10]{};

    countMarksFromDataBaseForChartView_2(arrayOfMarks);

    for (int i = 0; i < 10; ++i)
    {
        *set0 << arrayOfMarks[0][i];
        *set1 << arrayOfMarks[1][i];
        *set2 << arrayOfMarks[2][i];
        *set3 << arrayOfMarks[3][i];
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle("Диаграмма ответов на все вопросы опросника");
    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "1 вопрос" << "2 вопрос" << "3 вопрос" << "4 вопрос" << "5 вопрос" << "6 вопрос" << "7 вопрос" << "8 вопрос" << "9 вопрос" << "10 вопрос";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView_2->setChart(chart);
    ui->chartView_2->setRenderHint(QPainter::Antialiasing);

}


void ChartForm::on_backToMainWindowPushButton_pressed()
{
    this->hide();
    emit goToMainWindow();
}

void ChartForm::on_userNameComboBox_activated(int index)
{
    ui->companyNameLabel->setText("");
    ui->fieldOfCompanyLabel->setText("");

    QSqlDatabase dataBase;

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("db4free.net");
    dataBase.setPort(3306);
    dataBase.setDatabaseName("questionnairedb");
    dataBase.setUserName("testsuperadmin");
    dataBase.setPassword("12345678");

    if (dataBase.open())
        qDebug() << "open for chart";
    else
        qDebug() << "not open for chart";

    QSqlQuery query(dataBase);

    query.exec(QString("SELECT Respondents.name, Respondents.companyName, Respondents.fieldOfCompany,"
               "Answers.firstQuestion,"
               "Answers.secondQuestion, Answers.thirdQuestion, Answers.fourthQuestion, Answers.fifthQuestion,"
               "Answers.sixthQuestion, Answers.seventhQuestion, Answers.eighthQuestion, Answers.ninthQuestion,"
               "Answers.tenthQuestion FROM Respondents INNER JOIN Answers ON Respondents.id = Answers.id_respondent WHERE Respondents.name = '%1'").arg(ui->userNameComboBox->currentText()));

    QBarSet *set0 = new QBarSet("Отлично");
    QBarSet *set1 = new QBarSet("Хорошо");
    QBarSet *set2 = new QBarSet("Плохо");
    QBarSet *set3 = new QBarSet("Очень плохо");

    while (query.next())
    {
        for (int i = 3; i < 13; ++i)
        {
            if (query.value(i).toString() == "отлично")
                *set0 << 1;
            else
                *set0 << 0;

            if (query.value(i).toString() == "хорошо")
                *set1 << 1;
            else
                *set1 << 0;

            if (query.value(i).toString() == "плохо")
                *set2 << 1;
            else
                *set2 << 0;

            if (query.value(i).toString() == "очень плохо")
                *set3 << 1;
            else
                *set3 << 0;
        }

        ui->companyNameLabel->setText(query.value(1).toString());
        ui->fieldOfCompanyLabel->setText(query.value(2).toString());
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle("Диаграмма ответов клиента " + ui->userNameComboBox->currentText());
    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "1 вопрос" << "2 вопрос" << "3 вопрос" << "4 вопрос" << "5 вопрос" << "6 вопрос" << "7 вопрос" << "8 вопрос" << "9 вопрос" << "10 вопрос";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChart *toDeleteChart;

    toDeleteChart = ui->chartView_3->chart();

    ui->chartView_3->setChart(chart);
    ui->chartView_3->setRenderHint(QPainter::Antialiasing);

    delete toDeleteChart;
}

void ChartForm::on_searchToolButton_pressed()
{
    ui->userNameComboBox->setCurrentIndex(ui->userNameComboBox->findText(ui->searchLineEdit->text()));
    on_userNameComboBox_activated(ui->userNameComboBox->findText(ui->searchLineEdit->text()));
}

void ChartForm::on_companyNameComboBox_activated(int index)
{
    if (index == 0)
        return;

    QSqlDatabase dataBase;

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("db4free.net");
    dataBase.setPort(3306);
    dataBase.setDatabaseName("questionnairedb");
    dataBase.setUserName("testsuperadmin");
    dataBase.setPassword("12345678");

    if (dataBase.open())
        qDebug() << "open for chart";
    else
        qDebug() << "not open for chart";

    QSqlQuery query(dataBase);

    query.exec(QString("SELECT Respondents.companyName, Respondents.fieldOfCompany,"
               "Answers.firstQuestion,"
               "Answers.secondQuestion, Answers.thirdQuestion, Answers.fourthQuestion, Answers.fifthQuestion,"
               "Answers.sixthQuestion, Answers.seventhQuestion, Answers.eighthQuestion, Answers.ninthQuestion,"
               "Answers.tenthQuestion FROM Respondents INNER JOIN Answers ON Respondents.id = Answers.id_respondent WHERE Respondents.companyName = '%1'").arg(ui->companyNameComboBox->currentText()));

    QBarSet *set0 = new QBarSet("Отлично");
    QBarSet *set1 = new QBarSet("Хорошо");
    QBarSet *set2 = new QBarSet("Плохо");
    QBarSet *set3 = new QBarSet("Очень плохо");

    int arrayOfMarks[4][10]{};

    while (query.next())
    {
        for (int i = 2; i < 12; ++i)
        {
            if (query.value(i).toString() == "отлично")
                ++arrayOfMarks[0][i - 2];

            if (query.value(i).toString() == "хорошо")
                ++arrayOfMarks[1][i - 2];

            if (query.value(i).toString() == "плохо")
                ++arrayOfMarks[2][i - 2];

            if (query.value(i).toString() == "очень плохо")
                ++arrayOfMarks[3][i - 2];
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        *set0 << arrayOfMarks[0][i];
        *set1 << arrayOfMarks[1][i];
        *set2 << arrayOfMarks[2][i];
        *set3 << arrayOfMarks[3][i];
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle("Диаграмма ответов из компании " + ui->companyNameComboBox->currentText());
    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "1 вопрос" << "2 вопрос" << "3 вопрос" << "4 вопрос" << "5 вопрос" << "6 вопрос" << "7 вопрос" << "8 вопрос" << "9 вопрос" << "10 вопрос";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChart *toDeleteChart;

    toDeleteChart = ui->chartView_4->chart();

    ui->chartView_4->setChart(chart);
    ui->chartView_4->setRenderHint(QPainter::Antialiasing);

    delete toDeleteChart;
}

void ChartForm::on_searchToolButton_2_pressed()
{
    ui->companyNameComboBox->setCurrentIndex(ui->companyNameComboBox->findText(ui->searchLineEdit_2->text()));
    on_companyNameComboBox_activated(ui->companyNameComboBox->findText(ui->searchLineEdit_2->text()));
}

