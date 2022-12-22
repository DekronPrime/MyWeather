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
#include "changelocation.h"

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
    ChangeLocation *changelocation;

signals:
    void signalFromInWindow();

private slots:
    void locationChanged(QString location);

    void on_returnButton_clicked();

    void cloudinessChanged();

    void on_insertButton_clicked();

    void on_changeLocatioButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // INPUTDATAWINDOW_H
