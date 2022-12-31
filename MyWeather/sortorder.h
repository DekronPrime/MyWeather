#ifndef SORTORDER_H
#define SORTORDER_H

#include <QComboBox>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QTableView>

class SortOrder
{
public:
    SortOrder();
    void sortChanged(QSortFilterProxyModel *proxy, int column, bool sortButton);
    void sortChanged(QSqlTableModel *model, int column, QString sortOrder);

};

#endif // SORTORDER_H
