#ifndef SHOWDATAWINDOW_H
#define SHOWDATAWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDialog>
#include <QDate>
#include <QSqlTableModel>
#include <QKeyEvent>

#include "anotherday.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include "datadb.h"
#include "sortorder.h"
#include "changeimage.h"

namespace Ui {
class ShowWindow;
}

class ShowDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowDataWindow(QWidget *parent = nullptr);
    ~ShowDataWindow();

private:
    Ui::ShowWindow *ui;
    AnotherDay *adform;
    DBManager *db;
    QSqlTableModel  *model;
    SortOrder *sortorder;
    ChangeImage *changeimg;
    bool sortButton;
    QDate date;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();

    void setDate(const QDate &date);
    QDate getDate() const;

signals:
    void signalfromShWindow();

private slots:
    void on_returnButton_clicked();

    void on_todayButton_clicked();
    void on_yesterdayButton_clicked();
    void on_tendaysButton_clicked();
    void on_anotherButton_clicked();

    void adFormAccepted(QDate date);
    void printData(QDate date);
    void sortChanged();

    void on_changeSortButton_clicked();

    void on_refreshButton_clicked();

public slots:
    void refreshData();


protected:
    void keyPressEvent(QKeyEvent *e) override;

};



#endif // SHOWDATAWINDOW_H
