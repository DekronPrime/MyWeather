#ifndef MODIFYDATAWINDOW_H
#define MODIFYDATAWINDOW_H

#include <QMainWindow>

#include "dbmanager.h"
#include "sortorder.h"
#include "sqlitedbmanager.h"
#include "editlocation.h"
#include "refreshcombobox.h"
#include "qsqlquery.h"

#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QKeyEvent>
#include <QMessageBox>

namespace Ui {
class ModifyWindow;
}

class ModifyDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyDataWindow(QWidget *parent = nullptr);
    ~ModifyDataWindow();

private:
    Ui::ModifyWindow *ui;
    DBManager *db;
    QSqlQueryModel *model;
    QSortFilterProxyModel *proxy;
    SortOrder *sortorder;
    EditLocation *editlocation;
    RefreshComboBox *refcb;
    int rowId;
    bool SortOrder;

private:
    void setupModel(const QStringList &headers);
    void createUI();
    void setupComboBox();

protected:
    void keyPressEvent(QKeyEvent *e) override;

signals:
    void signalfromDelWindow();
    void newLocationAddedSignal(QString newLocation);
    void locationRemovedSignal(QString location);
    void locationEditedSignal(QString oldName, QString newName);

private slots:
    void on_returnButton_clicked();
    void sortChanged();
    void on_tableView_clicked(const QModelIndex &index);
    void on_removeButton_clicked();
    void on_changeSortButton_clicked();
    void on_refreshButton_clicked();
    void filterLocation(QString location);
    void on_editLocationButton_clicked();

public slots:
    void addToComboBox(QString newLocation);
    void newLocationAddedSlot(QString newLocation);
    void locationRemovedSlot(QString location);
    void locationEditedSlot(QString oldName, QString newName);
    void refreshModel();

};

#endif // MODIFYDATAWINDOW_H
