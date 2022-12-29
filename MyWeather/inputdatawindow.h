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
#include "addlocation.h"

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
    AddLocation *addLocation;

signals:
    void signalfromInWindow();
    void newLocationAddedSignal(QString newLocation);

private slots:
    void on_returnButton_clicked();

    void cloudinessChanged();

    void on_insertButton_clicked();

    void on_location_cb_currentTextChanged(const QString &text);

    void on_addLocationButton_clicked();

    void newLocationRecieved(QString newLocation);
protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // INPUTDATAWINDOW_H
