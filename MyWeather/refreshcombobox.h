#ifndef REFRESHCOMBOBOX_H
#define REFRESHCOMBOBOX_H

#include "dbmanager.h"
#include "sqlitedbmanager.h"

#include <QComboBox>

class RefreshComboBox
{
public:
    RefreshComboBox();

    void insertLocations(DBManager *db, QComboBox *combobox, int index);
    void addToComboBox(QComboBox *combobox, QString value);
    void removeFromComboBox(QComboBox *combobox, QString value);
    void updateItemInComboBox(QComboBox *combobox, QString oldValue, QString newValue);
};

#endif // REFRESHCOMBOBOX_H
