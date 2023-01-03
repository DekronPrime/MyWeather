#include "mainwindow.h"
#include <QApplication>
#include "dbmanager.h"
#include "sqlitedbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBManager *obj = SqliteDBManager::getInstance();
    obj->connectToDataBase();
    MainWindow w;
    w.show();
    w.setWindowTitle("MyWeather");
    return a.exec();
}
