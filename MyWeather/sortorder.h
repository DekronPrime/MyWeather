#ifndef SORTORDER_H
#define SORTORDER_H

#include <QComboBox>
#include <QSqlTableModel>

class SortOrder
{
public:
    SortOrder();
    void sortChanged(QSqlTableModel *model, QComboBox *comboBox, bool sortButton);
};

#endif // SORTORDER_H
