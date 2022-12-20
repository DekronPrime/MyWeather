#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>

#include <dbmanager.h>

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME   "DataBase"
#define DATABASE_NAME       "DataBase.db"

#define TABLE                       "weather"

#define TABLE_DATE                  "date"
#define TABLE_CLOUDINESS            "cloudiness"
#define TABLE_DAY_TEMPERATURE       "day_temp"
#define TABLE_NIGHT_TEMPERATURE     "night_temp"
#define TABLE_WIND_DIRECTION        "wind_direction"
#define TABLE_DAY_WIND_POWER        "day_wind_power"
#define TABLE_NIGHT_WIND_POWER      "night_wind_power"
#define TABLE_PRECIPITATION_HOURS   "precipitation_hours"
#define TABLE_HUMIDITY              "humidity"

class SqliteDBManager : public DBManager {

public:
    static SqliteDBManager* getInstance();

    void connectToDataBase();
    QSqlDatabase getDB();
    bool insertIntoTable(const QString tableName, const DataDB &data);
    DataDB * selectFromWeather(QDate date);
    void update(const DataDB &data);

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
