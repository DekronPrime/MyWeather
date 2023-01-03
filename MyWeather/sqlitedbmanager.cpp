#include "sqlitedbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){

}

SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
    }
    return instance;
}

void SqliteDBManager::connectToDataBase()
{
    if(QFile(DATABASE_NAME).exists()){
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

QSqlDatabase SqliteDBManager::getDB()
{
    return db;
}

bool SqliteDBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Failed to restore database";
        return false;
    }
}

bool SqliteDBManager::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        qDebug() << "Succesfully connected to database " << db.databaseName();
        return true;
    } else {
        qDebug() << "Something went wrong while connecting to database";
        return false;
    }
}

void SqliteDBManager::closeDataBase()
{
    db.close();
}

bool SqliteDBManager::createTables()
{
    QSqlQuery queryLocation, queryData;

    queryLocation.prepare("CREATE TABLE " TABLE_LOCATION " ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT         NOT NULL, "
                          TABLE_LOCATION_CITY " VARCHAR(50) UNIQUE      NOT NULL"
                          ");");

    queryData.prepare("CREATE TABLE " TABLE_WEATHER " ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "location_id INTEGER NOT NULL, "
                      TABLE_WEATHER_DATE                 " DATE           NOT NULL,"
                      TABLE_WEATHER_CLOUDINESS           " VARCHAR(50)    NOT NULL,"
                      TABLE_WEATHER_DAY_TEMPERATURE      " INTEGER        NOT NULL,"
                      TABLE_WEATHER_NIGHT_TEMPERATURE    " INTEGER        NOT NULL,"
                      TABLE_WEATHER_WIND_DIRECTION       " VARCHAR(2)     NOT NULL,"
                      TABLE_WEATHER_DAY_WIND_POWER       " INTEGER        NOT NULL,"
                      TABLE_WEATHER_NIGHT_WIND_POWER     " INTEGER        NOT NULL,"
                      TABLE_WEATHER_PRECIPITATION_HOURS  " INTEGER        NOT NULL,"
                      TABLE_WEATHER_HUMIDITY             " INTEGER        NOT NULL,"
                      "FOREIGN KEY(location_id) REFERENCES " TABLE_LOCATION "(id) ON UPDATE CASCADE ON DELETE CASCADE "
                      " );");

    if(!queryLocation.exec()){
        qDebug() << "DataBase: error of create table '" << TABLE_LOCATION << "'";
        qDebug() << queryData.lastError().text();
        return false;
    }
    else if(!queryData.exec()){
        qDebug() << "DataBase: error of create table '" << TABLE_WEATHER << "'";
        qDebug() << queryData.lastError().text();
        return false;
    }

    return true;
}

int SqliteDBManager::getLocationID(const QString &location)
{
    QSqlQuery query;
    int location_id = 0;

    query.prepare("SELECT id FROM " TABLE_LOCATION " WHERE " TABLE_LOCATION_CITY " LIKE '" + location + "';");

    if(!query.exec()){
        qDebug() << "error getting id from table '" << TABLE_LOCATION << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
    } else {
        if(query.first())
            location_id = query.value("id").toInt();
        else {
            //qDebug() << "Data not found";
        }
    }

    return location_id;
}

QStringList SqliteDBManager::getAllLocations()
{
    QSqlQuery query;
    QStringList locations;

    query.prepare("SELECT " TABLE_LOCATION_CITY " FROM " TABLE_LOCATION ";");

    if(!query.exec()){
        qDebug() << "error getting all locations from table '" << TABLE_LOCATION << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
    }
    else
        while(query.next()){
            QSqlRecord record = query.record();
            locations << record.value(TABLE_LOCATION_CITY).toStringList();
        }
    return locations;
}

bool SqliteDBManager::insert(const DataDB &data)
{
    QSqlQuery query;

    query.prepare("INSERT INTO " TABLE_WEATHER " (location_id, "
                  TABLE_WEATHER_DATE ", "
                  TABLE_WEATHER_CLOUDINESS ", "
                  TABLE_WEATHER_DAY_TEMPERATURE ", "
                  TABLE_WEATHER_NIGHT_TEMPERATURE ", "
                  TABLE_WEATHER_WIND_DIRECTION ", "
                  TABLE_WEATHER_DAY_WIND_POWER ", "
                  TABLE_WEATHER_NIGHT_WIND_POWER ", "
                  TABLE_WEATHER_PRECIPITATION_HOURS ", "
                  TABLE_WEATHER_HUMIDITY " ) "
                                        "VALUES (:LocationID, :Date, :Cloudiness, :Daytemp, :Nighttemp,"
                                        ":Winddirection, :Daywindpower, :Nightwindpower,"
                                        ":Precipitationhours, :Humidity );");
    query.bindValue(":LocationID",          this->getLocationID(data.getLocation()));
    query.bindValue(":Date",                data.getDate());
    query.bindValue(":Cloudiness",          data.getCloudiness());
    query.bindValue(":Daytemp",             data.getDayTemp());
    query.bindValue(":Nighttemp",           data.getNightTemp());
    query.bindValue(":Winddirection",       data.getWindDirection());
    query.bindValue(":Daywindpower",        data.getDayWindPower());
    query.bindValue(":Nightwindpower",      data.getNightWindPower());
    query.bindValue(":Precipitationhours",  data.getPrecipitationHours());
    query.bindValue(":Humidity",            data.getHumidity());

    if(!query.exec()){
        qDebug() << "error insert into table '" << TABLE_WEATHER << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
        return false;
    } else
        return true;
}

bool SqliteDBManager::insert(const QString &location)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_LOCATION " ( " TABLE_LOCATION_CITY " ) "
                                                                          "VALUES (:Location)");
    query.bindValue(":Location", location);

    if(!query.exec()){
        qDebug() << "error insert into table '" << TABLE_LOCATION << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
        return false;
    } else
        return true;
}

QSqlQueryModel* SqliteDBManager::getQueryModel()
{
    QSqlQueryModel *sqlmodel = new QSqlQueryModel;
    sqlmodel->setQuery(this->select());
    return sqlmodel;
}

QSqlQuery SqliteDBManager::select() const
{
    QSqlQuery query("SELECT "
                    TABLE_WEATHER ".id, "
                    TABLE_LOCATION "." TABLE_LOCATION_CITY ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DATE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_CLOUDINESS ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DAY_TEMPERATURE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_NIGHT_TEMPERATURE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_WIND_DIRECTION ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DAY_WIND_POWER ", "
                    TABLE_WEATHER "." TABLE_WEATHER_NIGHT_WIND_POWER ", "
                    TABLE_WEATHER "." TABLE_WEATHER_PRECIPITATION_HOURS ", "
                    TABLE_WEATHER "." TABLE_WEATHER_HUMIDITY
                    " FROM " TABLE_WEATHER " INNER JOIN " TABLE_LOCATION
                    " ON (" TABLE_WEATHER ".location_id = " TABLE_LOCATION ".id);");
    return query;
}

QSqlQuery SqliteDBManager::select(const QString &location) const
{
    QSqlQuery query("SELECT "
                    TABLE_WEATHER ".id, "
                    TABLE_LOCATION "." TABLE_LOCATION_CITY ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DATE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_CLOUDINESS ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DAY_TEMPERATURE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_NIGHT_TEMPERATURE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_WIND_DIRECTION ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DAY_WIND_POWER ", "
                    TABLE_WEATHER "." TABLE_WEATHER_NIGHT_WIND_POWER ", "
                    TABLE_WEATHER "." TABLE_WEATHER_PRECIPITATION_HOURS ", "
                    TABLE_WEATHER "." TABLE_WEATHER_HUMIDITY
                    " FROM " TABLE_WEATHER " INNER JOIN " TABLE_LOCATION
                    " ON (" TABLE_WEATHER ".location_id = " TABLE_LOCATION ".id)"
                    " WHERE " TABLE_LOCATION_CITY " LIKE '" + location + "';");
    return query;
}

QSqlQuery SqliteDBManager::select(QDate date, const QString &location) const
{
    QSqlQuery query("SELECT "
                    TABLE_WEATHER ".id, "
                    TABLE_LOCATION "." TABLE_LOCATION_CITY ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DATE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_CLOUDINESS ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DAY_TEMPERATURE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_NIGHT_TEMPERATURE ", "
                    TABLE_WEATHER "." TABLE_WEATHER_WIND_DIRECTION ", "
                    TABLE_WEATHER "." TABLE_WEATHER_DAY_WIND_POWER ", "
                    TABLE_WEATHER "." TABLE_WEATHER_NIGHT_WIND_POWER ", "
                    TABLE_WEATHER "." TABLE_WEATHER_PRECIPITATION_HOURS ", "
                    TABLE_WEATHER "." TABLE_WEATHER_HUMIDITY
                    " FROM " TABLE_WEATHER " INNER JOIN " TABLE_LOCATION
                    " ON (" TABLE_WEATHER ".location_id = " TABLE_LOCATION ".id)"
                    " WHERE " TABLE_LOCATION "." TABLE_LOCATION_CITY " LIKE '" + location +
                    "' AND " TABLE_WEATHER "." TABLE_WEATHER_DATE " > " + date.toString("yyyy-MM-dd") + " AND "
                    TABLE_WEATHER "." TABLE_WEATHER_DATE " <= DATE('now');");
    return query;
}

void SqliteDBManager::remove(int rowId) {
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_WEATHER " WHERE id = " + QString::number(rowId) + ";");

    if(!query.exec()){
        qDebug() << "error deleting from table '" << TABLE_WEATHER << "'";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
    }
}

void SqliteDBManager::remove(const QString &location)
{
    QSqlQuery query1, query2;
    query1.prepare("DELETE FROM " TABLE_LOCATION " WHERE " TABLE_LOCATION_CITY " LIKE '" + location + "';");
    query2.prepare("DELETE FROM " TABLE_WEATHER " WHERE location_id = " + QString::number(getLocationID(location)) + ";");

    if(!query1.exec()){
        qDebug() << "error deleting from table '" << TABLE_LOCATION << "'";
        qDebug() << query1.lastError().text() + " caused by: " + query1.lastQuery();
    }

    if(!query2.exec()){
        qDebug() << "error deleting from table '" << TABLE_WEATHER << "'";
        qDebug() << query2.lastError().text() + " caused by: " + query2.lastQuery();
    }
}

void SqliteDBManager::update(const QString &oldLocation, const QString &newLocation)
{
    QSqlQuery query;
    query.prepare("UPDATE " TABLE_LOCATION " SET " TABLE_LOCATION_CITY " = '" + newLocation +"' "
                  "WHERE " TABLE_LOCATION_CITY " LIKE '" + oldLocation + "';");

    if(!query.exec()){
        qDebug() << "error updating table '" << TABLE_LOCATION << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
    }
}

void SqliteDBManager::update(const DataDB &data)
{
    QSqlQuery query;
    query.prepare("UPDATE " TABLE_WEATHER " SET "
                  TABLE_WEATHER_CLOUDINESS " = '" + data.getCloudiness() + "', "
                  TABLE_WEATHER_DAY_TEMPERATURE " = " + QString::number(data.getDayTemp()) + ", "
                  TABLE_WEATHER_NIGHT_TEMPERATURE " = " + QString::number(data.getNightTemp()) + ", "
                  TABLE_WEATHER_WIND_DIRECTION " = '" + data.getWindDirection() + "', "
                  TABLE_WEATHER_DAY_WIND_POWER " = " + QString::number(data.getDayWindPower()) + ", "
                  TABLE_WEATHER_NIGHT_WIND_POWER " = " + QString::number(data.getNightWindPower()) + ", "
                  TABLE_WEATHER_PRECIPITATION_HOURS " = " + QString::number(data.getPrecipitationHours()) + ", "
                  TABLE_WEATHER_HUMIDITY " = " + QString::number(data.getHumidity()) + " "
                  "WHERE " TABLE_WEATHER_DATE " = '" + data.getDate().toString("yyyy-MM-dd") + "' AND "
                  "location_id = " + QString::number(getLocationID(data.getLocation())) + ";");

    if(!query.exec()){
        qDebug() << "error updating table '" << TABLE_WEATHER << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
    }
}


bool SqliteDBManager::alreadyExists(QDate date, const QString &location)
{
    QSqlQuery query;
    bool result = false;

    query.prepare("SELECT EXISTS( SELECT 1 FROM " TABLE_WEATHER
                  " WHERE " TABLE_WEATHER_DATE " = (:Date) AND location_id = (:LocationID) );");

    query.bindValue(":Date", date);
    query.bindValue(":LocationID", getLocationID(location));

    if(!query.exec()){
        qDebug() << "error checking table '" << TABLE_WEATHER << "'";
        qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
    }
    else
        if(query.first())
            result = query.value(0).toBool();

    return result;
}

DataDB * SqliteDBManager::selectFromWeather(QDate date, const QString &location)
{
    QSqlQuery query;

        query.prepare("SELECT * FROM " TABLE_WEATHER " WHERE " TABLE_WEATHER_DATE " = :Date"
                      " AND location_id = :LocationID;");
        query.bindValue(":Date", date);
        query.bindValue(":LocationID", getLocationID(location));

        DataDB *data = nullptr;

        if (!query.exec()) {
            qDebug() << "Query failed!";
            qDebug() << query.lastError().text() << "caused by: " << query.lastQuery();
        } else {
            if (query.first()) {
                data = new DataDB;
                data->setDate(query.value("date").toDate());
                data->setLocation(location);
                data->setCloudiness(query.value("cloudiness").toString());
                data->setDayTemp(query.value("day_temp").toInt());
                data->setNightTemp(query.value("night_temp").toInt());
                data->setWindDirection(query.value("wind_direction").toString());
                data->setDayWindPower(query.value("day_wind_power").toInt());
                data->setNightWindPower(query.value("night_wind_power").toInt());
                data->setPrecipitationHours(query.value("precipitation_hours").toInt());
                data->setHumidity(query.value("humidity").toInt());
            } else {
                //qDebug () << "Data not found";
            }
        }
        return data;
}
