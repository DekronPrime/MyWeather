#ifndef MODIFYDATAWINDOW_H
#define MODIFYDATAWINDOW_H

#include <QMainWindow>

#include "dbmanager.h"
#include "sortorder.h"
#include "sqlitedbmanager.h"
#include "changelocation.h"

#include <QSqlTableModel>
#include <QKeyEvent>

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
    void signalFromModWindow();

private:
    Ui::DeleteWindow *ui;
    DBManager *db;
    QSqlTableModel *model;
    SortOrder *sortorder;
    ChangeLocation *changelocation;

    int row;
    bool sortOrder;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();

protected:
    void keyPressEvent(QKeyEvent *e) override;
private slots:
    void on_returnButton_clicked();

    void sortChanged();
    void locationChanged(QString location);

    void on_tableView_clicked(const QModelIndex &index);
    void on_deleteButton_clicked();

    void on_changeSortButton_clicked();
    void on_refreshButton_clicked();
    void on_pushButton_clicked();
};

#endif // MODIFYDATAWINDOW_H
