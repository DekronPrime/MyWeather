#include "sortorder.h"

SortOrder::SortOrder()
{

}

void SortOrder::sortChanged(QSortFilterProxyModel *proxy, int column, bool sortButton)
{
    Qt::SortOrder order;
    if (sortButton)
        order = Qt::AscendingOrder;
    else
        order = Qt::DescendingOrder;
    proxy->sort(column, order);
}

void SortOrder::sortChanged(QSqlTableModel *model, int column, QString sortOrder)
{
    if(sortOrder == "Asc")
        model->setSort(column,Qt::AscendingOrder);
    else if(sortOrder == "Desc")
        model->setSort(column,Qt::DescendingOrder);
    model->select();
}
