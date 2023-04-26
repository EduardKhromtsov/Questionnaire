#include "databaseform.h"
#include "ui_databaseform.h"

DataBaseForm::DataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataBaseForm)
{
    ui->setupUi(this);

    setFixedSize(997, 456);

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("db4free.net");
    dataBase.setPort(3306);
    dataBase.setDatabaseName("questionnairedb");
    dataBase.setUserName("testsuperadmin");
    dataBase.setPassword("12345678");

    dataBase.open();

    model.setQuery("SELECT Respondents.name AS Имя, Respondents.telephone AS Телефон, Respondents.companyName AS Организация, Respondents.fieldOfCompany AS \"Сфера деятельности организации\","
                   "Answers.firstQuestion AS \"Вопрос 1\", "
                   "Answers.secondQuestion AS \"Вопрос 2\", Answers.thirdQuestion AS \"Вопрос 3\", Answers.fourthQuestion AS \"Вопрос 4\", Answers.fifthQuestion AS \"Вопрос 5\","
                   "Answers.sixthQuestion AS \"Вопрос 6\", Answers.seventhQuestion AS \"Вопрос 7\", Answers.eighthQuestion AS \"Вопрос 8\", Answers.ninthQuestion AS \"Вопрос 9\", "
                   "Answers.tenthQuestion AS \"Вопрос 10\", Answers.wish AS Пожелания FROM Respondents INNER JOIN Answers ON Respondents.id = Answers.id_respondent");

    ui->dataBaseTableView->setModel(&model);
}

DataBaseForm::~DataBaseForm()
{
    delete ui;
}

void DataBaseForm::on_searchLineEdit_textChanged(const QString &arg1)
{
    model.setQuery(QString("SELECT Respondents.name AS Имя, Respondents.telephone AS Телефон, Respondents.companyName AS Организация, Respondents.fieldOfCompany AS \"Сфера деятельности организации\","
                   "Answers.firstQuestion AS \"Вопрос 1\","
                   "Answers.secondQuestion AS \"Вопрос 2\", Answers.thirdQuestion AS \"Вопрос 3\", Answers.fourthQuestion AS \"Вопрос 4\", Answers.fifthQuestion AS \"Вопрос 5\","
                   "Answers.sixthQuestion AS \"Вопрос 6\", Answers.seventhQuestion AS \"Вопрос 7\", Answers.eighthQuestion AS \"Вопрос 8\", Answers.ninthQuestion AS \"Вопрос 9\", "
                   "Answers.tenthQuestion AS \"Вопрос 10\", Answers.wish AS Пожелания FROM Respondents INNER JOIN Answers ON Respondents.id = Answers.id_respondent WHERE Respondents.name LIKE '%1\%'").arg(arg1));
}

void DataBaseForm::on_printToolButton_pressed()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->dataBaseTableView->model()->rowCount();
    const int columnCount = ui->dataBaseTableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>Список ответов на вопросы опросника</title>\n")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; ++column)
        if (!ui->dataBaseTableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->dataBaseTableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; ++row) {
        out << "<tr>";
        for (int column = 0; column < columnCount; ++column) {
            if (!ui->dataBaseTableView->isColumnHidden(column)) {
                QString data = ui->dataBaseTableView->model()->data(ui->dataBaseTableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    printer.setPageOrientation(QPageLayout::Landscape);

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}


void DataBaseForm::on_backToMainWindowPushButton_pressed()
{
    this->hide();
    emit goToMainWindow();
}

