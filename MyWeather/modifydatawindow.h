#ifndef MODIFYDATAWINDOW_H
#define MODIFYDATAWINDOW_H

#include <QMainWindow>

#include "dbmanager.h"
#include "sortorder.h"
#include "sqlitedbmanager.h"
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

signals:
    void signalfromDelWindow();

private:
    Ui::DeleteWindow *ui;
    DBManager *db;
    QSqlQueryModel *model;
    QSortFilterProxyModel *proxy;
    SortOrder *sortorder;

    int rowId;
    bool SortOrder;

private:
    void setupModel(const QStringList &headers);
    void createUI();

protected:
    void keyPressEvent(QKeyEvent *e) override;
private slots:
    void on_returnButton_clicked();

    void sortChanged();
    void on_tableView_clicked(const QModelIndex &index);
    void on_deleteButton_clicked();

    void on_changeSortButton_clicked();
    void on_refreshButton_clicked();

    void filterLocation(QString location);

public slots:
    void refreshComboBox(QString newLocation);
};

#endif // MODIFYDATAWINDOW_H
