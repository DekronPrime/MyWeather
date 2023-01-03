#include "refreshcombobox.h"

RefreshComboBox::RefreshComboBox()
{

}

void RefreshComboBox::insertLocations(DBManager *db, QComboBox *combobox, int index)
{
    QStringList locations = db->getAllLocations();
    combobox->insertItems(index, locations);
}

void RefreshComboBox::addToComboBox(QComboBox *combobox, QString value)
{
    combobox->addItem(value);
}

void RefreshComboBox::removeFromComboBox(QComboBox *combobox, QString value)
{
    combobox->removeItem(combobox->findText(value));
}

void RefreshComboBox::updateItemInComboBox(QComboBox *combobox, QString oldValue, QString newValue)
{
    combobox->setItemText(combobox->findText(oldValue), newValue);
}
