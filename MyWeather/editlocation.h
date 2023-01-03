#ifndef EDITLOCATION_H
#define EDITLOCATION_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>

#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include "sortorder.h"
#include "addlocation.h"
#include "alterlocation.h"


namespace Ui {
class ChangeLocation;
}

class EditLocation : public QDialog
{
    Q_OBJECT

public:
    explicit EditLocation(QWidget *parent = nullptr);
    ~EditLocation();

private:
    Ui::ChangeLocation *ui;
    DBManager *db;
    QSqlTableModel *model;
    QSortFilterProxyModel *proxy;
    AddLocation *addlocation;
    AlterLocation *alterlocation;
    SortOrder *sortorder;
    QString location;

private:
    void setupModel(const QString& tableName, const QStringList &headers);
    void createUI();

signals:
    void newLocationAddedSignal(QString newLocation);
    void locationRemovedSignal(QString location);
    void locationEditedSignal(QString oldName, QString newName);

private slots:
    void sortOrderChanged(const QString &text);
    void on_addButton_clicked();
    void newLocationRecieved(QString newLocation);
    void on_tableView_clicked(const QModelIndex &index);
    void on_removeButton_clicked();
    void on_editbutton_clicked();
    void on_cancelButton_clicked();
    void locationRenamedSlot(QString renamedLocation);
};

#endif // EDITLOCATION_H
