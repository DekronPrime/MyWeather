#ifndef SHOWDATAWINDOW_H
#define SHOWDATAWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDialog>
#include <QDate>
#include <QKeyEvent>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

#include "anotherday.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include "datadb.h"
#include "sortorder.h"
#include "changeimage.h"
#include "refreshcombobox.h"

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
    QSqlQueryModel *model;
    QSortFilterProxyModel *proxy;
    SortOrder *sortorder;
    ChangeImage *changeimg;
    RefreshComboBox *refcb;
    bool SortOrder;
    QDate date;
    QString location;

private:
    void setupModel(const QStringList &headers);
    void createUI();
    void setupComboBox();
    void setDate(const QDate &date);
    QDate getDate() const;
    void setLocation(const QString &location);
    QString getLocation() const;

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
    void refreshData();
    void on_location_cb_currentTextChanged(const QString &location);

public slots:
    void newLocationAddedSlot(QString newLocation);
    void locationRemovedSlot(QString location);
    void locationEditedSlot(QString oldName, QString newName);

protected:
    void keyPressEvent(QKeyEvent *e) override;
};



#endif // SHOWDATAWINDOW_H
