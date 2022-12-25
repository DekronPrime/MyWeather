#ifndef INPUTDATAWINDOW_H
#define INPUTDATAWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QKeyEvent>
#include <QMessageBox>

#include "datadb.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include "changeimage.h"

namespace Ui {
class InputWindow;
}

class InputDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputDataWindow(QWidget *parent = nullptr);
    ~InputDataWindow();

private:
    Ui::InputWindow *ui;
    DBManager *db;
    ChangeImage *changeimg;

signals:
    void signalFromInWindow();

private slots:
    void on_returnButton_clicked();

    //void cloudinessChanged(int index);

    void on_insertButton_clicked();

    void on_location_cb_currentIndexChanged(int index);

    void on_cloudiness_CB_currentTextChanged(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // INPUTDATAWINDOW_H
