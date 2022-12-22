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
        qDebug() << "Succesfully connected to database " << db.databaseName() << "@" << db.hostName();
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
                          TABLE_LOCATION_LOCATION " VARCHAR(50) UNIQUE  NOT NULL"
                          ");");

    queryData.prepare("CREATE TABLE " TABLE_WEATHER " ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "location_id INTEGER NOT NULL, "
                      TABLE_WEATHER_DATE                 " DATE UNIQUE    NOT NULL,"
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
        qDebug() << "DataBase: error of create " << TABLE_LOCATION;
        qDebug() << queryData.lastError().text();
        return false;
    }
    else if(!queryData.exec()){
        qDebug() << "DataBase: error of create " << TABLE_WEATHER;
        qDebug() << queryData.lastError().text();
        return false;
    }

    return true;
}

//bool SqliteDBManager::createTables()
//{
//    QSqlQuery query;
//    if(!query.exec( "CREATE TABLE " TABLE_WEATHER " ("
//                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                    TABLE_WEATHER_DATE                 " DATE UNIQUE    NOT NULL,"
//                    TABLE_WEATHER_CLOUDINESS           " VARCHAR(50)    NOT NULL,"
//                    TABLE_WEATHER_DAY_TEMPERATURE      " INTEGER        NOT NULL,"
//                    TABLE_WEATHER_NIGHT_TEMPERATURE    " INTEGER        NOT NULL,"
//                    TABLE_WEATHER_WIND_DIRECTION       " VARCHAR(2)     NOT NULL,"
//                    TABLE_WEATHER_DAY_WIND_POWER       " INTEGER        NOT NULL,"
//                    TABLE_WEATHER_NIGHT_WIND_POWER     " INTEGER        NOT NULL,"
//                    TABLE_WEATHER_PRECIPITATION_HOURS  " INTEGER        NOT NULL,"
//                    TABLE_WEATHER_HUMIDITY             " INTEGER        NOT NULL"
//                    " )"
//                    )){
//        qDebug() << "DataBase: error of create " << TABLE_WEATHER;
//        qDebug() << query.lastError().text();
//        return false;
//    } else
//        return true;
//}

bool SqliteDBManager::insertIntoTable(const QString tableName, const DataDB &data)
{
    QSqlQuery query;

    if (tableName == TABLE_WEATHER){
        qDebug() << tableName;
        query.prepare("INSERT INTO " TABLE_WEATHER " ( " TABLE_WEATHER_DATE ", "
                      TABLE_WEATHER_CLOUDINESS ", "
                      TABLE_WEATHER_DAY_TEMPERATURE ", "
                      TABLE_WEATHER_NIGHT_TEMPERATURE ", "
                      TABLE_WEATHER_WIND_DIRECTION ", "
                      TABLE_WEATHER_DAY_WIND_POWER ", "
                      TABLE_WEATHER_NIGHT_WIND_POWER ", "
                      TABLE_WEATHER_PRECIPITATION_HOURS ", "
                      TABLE_WEATHER_HUMIDITY " ) "
                                            "VALUES (:Date, :Cloudiness, :Daytemp, :Nighttemp,"
                                            ":Winddirection, :Daywindpower, :Nightwindpower,"
                                            ":Precipitationhours, :Humidity )");
        query.bindValue(":Date",                data.getDate());
        query.bindValue(":Cloudiness",          data.getCloudiness());
        query.bindValue(":Daytemp",             data.getDayTemp());
        query.bindValue(":Nighttemp",           data.getNightTemp());
        query.bindValue(":Winddirection",       data.getWindDirection());
        query.bindValue(":Daywindpower",        data.getDayWindPower());
        query.bindValue(":Nightwindpower",      data.getNightWindPower());
        query.bindValue(":Precipitationhours",  data.getPrecipitationHours());
        query.bindValue(":Humidity",            data.getHumidity());
    }

    if(!query.exec()){
        qDebug() << "error insert into " << tableName;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}

DataDB * SqliteDBManager::selectFromWeather(QDate date)
{
    QSqlQuery query;

        query.prepare("SELECT * FROM " TABLE_WEATHER " WHERE " TABLE_WEATHER_DATE " = :date;");
        query.bindValue(":date", date);

        DataDB *data = nullptr;

        if (!query.exec()) {
            qDebug() << "Query failed!";
            qDebug() << query.lastError().text();
            qDebug() << query.lastQuery();
            throw (QString)"Error occured while proceeding query: " + query.lastError().text() + " \nQuery: " + query.lastQuery();
        } else {
            if (query.first()) {
                data = new DataDB;
                data->setDate(query.value("Date").toDate());
                data->setCloudiness(query.value("Cloudiness").toString());
                data->setDayTemp(query.value("Day_Temp").toInt());
                data->setNightTemp(query.value("Night_Temp").toInt());
                data->setWindDirection(query.value("Wind_Direction").toString());
                data->setDayWindPower(query.value("Day_Wind_Power").toInt());
                data->setNightWindPower(query.value("Night_Wind_Power").toInt());
                data->setPrecipitationHours(query.value("Precipitation_Hours").toInt());
                data->setHumidity(query.value("Humidity").toInt());
            } else {
                qDebug () << "Data not found";
            }
        }
        return data;
}

void SqliteDBManager::update(const DataDB &data){
    QSqlQuery query;

    query.prepare("UPDATE  " TABLE_WEATHER
                  " SET " TABLE_WEATHER_CLOUDINESS " = '" + data.getCloudiness() + "', "
                  " " TABLE_WEATHER_DAY_TEMPERATURE " = " + QString::number(data.getDayTemp()) + ", "
                  " " TABLE_WEATHER_NIGHT_TEMPERATURE " = " + QString::number(data.getNightTemp()) + ", "
                  " " TABLE_WEATHER_WIND_DIRECTION " = '" + data.getWindDirection() + "', "
                  " " TABLE_WEATHER_DAY_WIND_POWER " = " + QString::number(data.getDayWindPower()) + ", "
                  " " TABLE_WEATHER_NIGHT_WIND_POWER " = " + QString::number(data.getNightWindPower()) + ", "
                  " " TABLE_WEATHER_PRECIPITATION_HOURS " = " + QString::number(data.getPrecipitationHours()) + ", "
                  " " TABLE_WEATHER_HUMIDITY " = " + QString::number(data.getHumidity()) + " "
                  " WHERE date = '" + data.getDate().toString("yyyy-MM-dd") + "';");

    if(!query.exec()){
        qDebug() << "error updating " << TABLE_WEATHER;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
    }

}
