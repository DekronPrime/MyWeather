#ifndef CHANGEIMAGE_H
#define CHANGEIMAGE_H

#include <QLabel>
#include <QPixmap>

class ChangeImage
{
public:
    ChangeImage();

    void setImage(QString selector,QLabel *label);
    void setImages(QLabel *temp, QLabel *direction, QLabel *wind, QLabel *fallout, QLabel *humidity);
    void setErrorImage(QLabel *noData_img);
    void setAddLocationImage(QLabel *addLocation_lbl);
    void setEditLocationImage(QLabel *edit_lbl, QLabel *result_lbl);
    void setExitImages(QLabel *question_lbl, QLabel *exit_lbl);
};

#endif // CHANGEIMAGE_H
