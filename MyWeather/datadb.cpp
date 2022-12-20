#include "datadb.h"

DataDB::DataDB()
{

}

QDate DataDB::getDate() const
{
    return this->date;
}

QString DataDB::getCloudiness() const
{
    return this->cloudiness;
}

int DataDB::getDayTemp() const
{
    return this->day_temp;
}

int DataDB::getNightTemp() const
{
    return this->night_temp;
}

QString DataDB::getWindDirection() const
{
    return this->wind_direction;
}

int DataDB::getDayWindPower() const
{
    return this->day_wind_power;
}

int DataDB::getNightWindPower() const
{
    return this->night_wind_power;
}

int DataDB::getPrecipitationHours() const
{
    return this->precipitation_hours;
}

int DataDB::getHumidity() const
{
    return this->humidity;
}

void DataDB::setDate(const QDate &date)
{
    this->date = date;
}

void DataDB::setCloudiness(const QString &cloudiness)
{
    this->cloudiness = cloudiness;
}

void DataDB::setDayTemp(const int &day_temp)
{
    this->day_temp = day_temp;
}

void DataDB::setNightTemp(const int &night_temp)
{
    this->night_temp = night_temp;
}

void DataDB::setWindDirection(const QString &wind_direction)
{
    this->wind_direction = wind_direction;
}

void DataDB::setDayWindPower(const int &day_wind_power)
{
    this->day_wind_power = day_wind_power;
}

void DataDB::setNightWindPower(const int &night_wind_power)
{
    this->night_wind_power = night_wind_power;
}

void DataDB::setPrecipitationHours(const int &precipitation_hours)
{
    this->precipitation_hours = precipitation_hours;
}

void DataDB::setHumidity(const int &humidity)
{
    this->humidity = humidity;
}
