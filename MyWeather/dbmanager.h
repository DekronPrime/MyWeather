#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>

#include "datadb.h"

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();

    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool insert(const DataDB &data) = 0;
    virtual bool insert(const QString &location) = 0;
    virtual int getLocationID(const QString &location) = 0;
    virtual QStringList getAllLocations() = 0;
    virtual QSqlQueryModel* getQueryModel() = 0;
    virtual QSqlQuery select() const = 0;
    virtual QSqlQuery select(const QString &location) const = 0;
    virtual QSqlQuery select(QDate date, const QString &location) const = 0;
    virtual void remove(int rowId) = 0;
    virtual void remove(const QString &location) = 0;
    virtual void update(const QString &oldLocation, const QString &newLocation) = 0;
    virtual void update(const DataDB &data) = 0;
    virtual bool alreadyExists(QDate date, const QString &location) = 0;
    virtual bool alreadyExists(const QString &location) = 0;
    virtual DataDB * selectFromWeather(QDate date, const QString &location) = 0;
};

#endif // DBMANAGER_H
