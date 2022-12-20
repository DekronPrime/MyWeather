#include "changeimage.h"

ChangeImage::ChangeImage()
{

}

void ChangeImage::setImage(QString selector, QLabel *label)
{
    QString style = "\nbackground-position: center;\nbackground-repeat: no-repeat;\n";
    if(selector == "Sunny")
        label->setStyleSheet(style+"background-image: url(:/img/images/sunny.png);");
    else if(selector == "Partly cloudy")
        label->setStyleSheet(style+"background-image: url(:/img/images/partly.png);");
    else if(selector == "Mostly cloudy")
        label->setStyleSheet(style+"background-image: url(:/img/images/mostly.png);");
    else if(selector == "Rainy")
        label->setStyleSheet(style+"background-image: url(:/img/images/rainy.png);");
    else if(selector == "Showers")
        label->setStyleSheet(style+"background-image: url(:/img/images/showers.png);");
    else if(selector == "Thunderstorm")
        label->setStyleSheet(style+"background-image: url(:/img/images/thunderstorm.png);");
    else if(selector == "Snowy")
        label->setStyleSheet(style+"background-image: url(:/img/images/snowy.png);");
    else
        label->setStyleSheet("");
}

void ChangeImage::setImages(QLabel *temp, QLabel *direction, QLabel *wind, QLabel *fallout, QLabel *humidity)
{
    temp->setPixmap(QPixmap(":/img/images/temperature.png"));
    direction->setPixmap(QPixmap(":/img/images/compass.png"));
    wind->setPixmap(QPixmap(":/img/images/wind.png"));
    fallout->setPixmap(QPixmap(":/img/images/fallout.png"));
    humidity->setPixmap(QPixmap(":/img/images/humidity.png"));
}

void ChangeImage::setErrorImage(QLabel *noData_img)
{
    noData_img->setPixmap(QPixmap(":/img/images/nodata.png"));
}
