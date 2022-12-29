#ifndef DATADB_H
#define DATADB_H

#include <QDate>


class DataDB
{
private:
    QString location;

    QDate date;
    QString cloudiness;
    int day_temp;
    int night_temp;
    QString wind_direction;
    int day_wind_power;
    int night_wind_power;
    int precipitation_hours;
    int humidity;

public:
    DataDB();

    void setLocation(const QString &location);

    void setDate(const QDate &date);
    void setCloudiness(const QString &cloudiness);
    void setDayTemp(const int &day_temp);
    void setNightTemp(const int &night_temp);
    void setWindDirection(const QString &wind_direction);
    void setDayWindPower(const int &day_wind_power);
    void setNightWindPower(const int &night_wind_power);
    void setPrecipitationHours(const int &precipitation_hours);
    void setHumidity(const int &humidity);

    QString getLocation() const;

    QDate getDate() const;
    QString getCloudiness() const;
    int getDayTemp() const;
    int getNightTemp() const;
    QString getWindDirection() const;
    int getDayWindPower() const;
    int getNightWindPower() const;
    int getPrecipitationHours() const;
    int getHumidity() const;
};

#endif // DATADB_H
