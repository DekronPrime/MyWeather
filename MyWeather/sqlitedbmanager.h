#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QStringList>
#include <QVector>
#include <QSqlRecord>

#include <dbmanager.h>

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME   "DataBase"
#define DATABASE_NAME       "DataBase.db"

#define TABLE_LOCATION                      "location"
#define TABLE_LOCATION_CITY                 "city"

#define TABLE_WEATHER                       "weather"

#define TABLE_WEATHER_DATE                  "date"
#define TABLE_WEATHER_CLOUDINESS            "cloudiness"
#define TABLE_WEATHER_DAY_TEMPERATURE       "day_temp"
#define TABLE_WEATHER_NIGHT_TEMPERATURE     "night_temp"
#define TABLE_WEATHER_WIND_DIRECTION        "wind_direction"
#define TABLE_WEATHER_DAY_WIND_POWER        "day_wind_power"
#define TABLE_WEATHER_NIGHT_WIND_POWER      "night_wind_power"
#define TABLE_WEATHER_PRECIPITATION_HOURS   "precipitation_hours"
#define TABLE_WEATHER_HUMIDITY              "humidity"

class SqliteDBManager : public DBManager {

public:
    static SqliteDBManager* getInstance();

    void connectToDataBase();
    QSqlDatabase getDB();
    bool insertIntoTable(const QString tableName, const DataDB &data);
    bool insertIntoTable(const QString &location);
    int getLocationID(const QString &location);
    QStringList getAllLocations();
    QSqlQueryModel* getQueryModel();
    QSqlQuery select() const;
    QSqlQuery select(const QString &location) const;
    void remove(int rowId);
    void remove(const QString &location);
//    DataDB * selectFromWeather(QDate date);
//    void update(const DataDB &data);

private:
    QSqlDatabase    db;

private:

    static SqliteDBManager* instance;

    SqliteDBManager();

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();
};



#endif // DATABASE_H
