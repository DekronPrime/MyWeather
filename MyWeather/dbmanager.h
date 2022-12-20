#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

#include "datadb.h"

class DBManager
{
public:
    DBManager();

    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool insertIntoTable(const QString tableName, const DataDB &data) = 0;
    virtual DataDB * selectFromWeather(QDate date) = 0;
    virtual void update(const DataDB &data) = 0;
};

#endif // DBMANAGER_H
