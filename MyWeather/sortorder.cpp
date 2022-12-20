#include "sortorder.h"

SortOrder::SortOrder()
{

}

void SortOrder::sortChanged(QSqlTableModel *model, QComboBox *comboBox, bool sortButton)
{
    Qt::SortOrder order;
    if (sortButton)
        order = Qt::AscendingOrder;
    else
        order = Qt::DescendingOrder;
    switch(comboBox->currentIndex()){
        case 0:
            model->setSort(1,order);
            break;
        case 1:
            model->setSort(2,order);
            break;
        case 2:
            model->setSort(3,order);
            break;
        case 3:
            model->setSort(4,order);
            break;
        case 4:
            model->setSort(5,order);
            break;
        case 5:
            model->setSort(6,order);
            break;
        case 6:
            model->setSort(7,order);
            break;
        case 7:
            model->setSort(8,order);
            break;
        case 8:
            model->setSort(9,order);
            break;

        default:
            break; //never be reached
    }
    model->select();
}
