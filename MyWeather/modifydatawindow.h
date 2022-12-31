#ifndef MODIFYDATAWINDOW_H
#define MODIFYDATAWINDOW_H

#include <QMainWindow>

#include "dbmanager.h"
#include "sortorder.h"
#include "sqlitedbmanager.h"
#include "editlocation.h"

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QKeyEvent>
#include <QMessageBox>

namespace Ui {
class DeleteWindow;
}

class ModifyDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyDataWindow(QWidget *parent = nullptr);
    ~ModifyDataWindow();

private:
    Ui::DeleteWindow *ui;
    DBManager *db;
    QSqlQueryModel *model;
    QSortFilterProxyModel *proxy;
    SortOrder *sortorder;
    EditLocation *editlocation;

    int rowId;
    bool SortOrder;

private:
    void setupModel(const QStringList &headers);
    void createUI();

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
    void refreshModel();

    void filterLocation(QString location);

    void on_editLocationButton_clicked();

public slots:
    void addToComboBox(QString newLocation);
    void removeFromComboBox(QString location);
    void updateItemInComboBox(QString oldLocation, QString newLocation);

    void newLocationAddedSlot(QString newLocation);
    void locationRemovedSlot(QString location);
    void locationEditedSlot(QString oldName, QString newName);
};

#endif // MODIFYDATAWINDOW_H
