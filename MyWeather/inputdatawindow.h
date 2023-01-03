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
#include "refreshcombobox.h"

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
    RefreshComboBox *refcb;

private:
    void setupComboBox();

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

public slots:
    void newLocationAddedSlot(QString newLocation);
    void locationRemovedSlot(QString location);
    void locationEditedSlot(QString oldName, QString newName);

protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // INPUTDATAWINDOW_H
