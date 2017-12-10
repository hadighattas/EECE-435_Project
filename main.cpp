#include "mainwindow.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("EECE435");
    QCoreApplication::setOrganizationDomain("eece435.com");
    QCoreApplication::setApplicationName("EECE-435_Project");
    MainWindow w;
    w.show();
    return a.exec();
}
