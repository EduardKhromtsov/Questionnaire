
#include <QApplication>
#include "loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginForm *ptrLoginForm = new LoginForm();

    ptrLoginForm->show();

    return a.exec();
}
