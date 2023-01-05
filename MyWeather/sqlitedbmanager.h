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

    void connectToDataBase() override;
    QSqlDatabase getDB() override;
    bool insert(const DataDB &data) override;
    bool insert(const QString &location) override;
    int getLocationID(const QString &location) override;
    QStringList getAllLocations() override;
    QSqlQueryModel* getQueryModel() override;
    QSqlQuery select() const override;
    QSqlQuery select(const QString &location) const override;
    QSqlQuery select(QDate date, const QString &location) const override;
    void remove(int rowId) override;
    void remove(const QString &location) override;
    void update(const QString &oldLocation, const QString &newLocation) override;
    void update(const DataDB &data) override;
    bool alreadyExists(QDate date, const QString &location) override;
    bool alreadyExists(const QString &location) override;
    DataDB * selectFromWeather(QDate date, const QString &location) override;

private:
    QSqlDatabase db;

private:

    static SqliteDBManager* instance;

    SqliteDBManager();
    ~SqliteDBManager() override;

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();
};



#endif // DATABASE_H
