#ifndef EXITWINDOW_H
#define EXITWINDOW_H

#include <QDialog>
#include "changeimage.h"

namespace Ui {
class ExitWindow;
}

class ExitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExitWindow(QWidget *parent = nullptr);
    ~ExitWindow();

private slots:
    void on_noButton_clicked();
    void on_yesButton_clicked();

private:
    Ui::ExitWindow *ui;
    ChangeImage *changeimage;
};

#endif // EXITWINDOW_H
