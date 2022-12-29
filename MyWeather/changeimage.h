#ifndef CHANGEIMAGE_H
#define CHANGEIMAGE_H

#include <QString>
#include <QLabel>
#include <QPixmap>

class ChangeImage
{
public:
    ChangeImage();

    void setImage(QString selector,QLabel *label);
    void setImages(QLabel *temp, QLabel *direction, QLabel *wind, QLabel *fallout, QLabel *humidity);
    void setErrorImage(QLabel *noData_img);
};

#endif // CHANGEIMAGE_H
