#include "editlocation.h"
#include "ui_editlocation.h"

EditLocation::EditLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeLocation)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();

    this->setupModel(TABLE_LOCATION,
                     QStringList() << tr("id")
                                   << tr("Location")
                     );

    this->createUI();

    connect(ui->sort_cb,&QComboBox::currentTextChanged,this,&EditLocation::sortOrderChanged);
}

EditLocation::~EditLocation()
{
    delete ui;
}

void EditLocation::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this,db->getDB());
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void EditLocation::createUI()
{
    proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);

    ui->tableView->setModel(proxy);
    ui->tableView->setColumnHidden(0, true);

    model->select();
}

void EditLocation::sortOrderChanged(const QString &text)
{
    sortorder->sortChanged(model,1,text);
}

void EditLocation::on_addButton_clicked()
{
    addlocation = new AddLocation;
    addlocation->setWindowTitle("Add New Location");
    addlocation->show();

    connect(addlocation,&AddLocation::newLocationSignal,this,&EditLocation::newLocationRecieved);
}

void EditLocation::newLocationRecieved(QString newLocation)
{
    if(db->insert(newLocation)) {
        model->select();
        emit newLocationAddedSignal(newLocation);
    }
    else
        QMessageBox::critical(this,tr("Error insert"),
                              tr("Error insert of new location"));
}

void EditLocation::on_tableView_clicked(const QModelIndex &index)
{
    location = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
}

void EditLocation::on_removeButton_clicked()
{
    if(ui->tableView->selectionModel()->hasSelection()){
        emit locationRemovedSignal(location);
        db->remove(location);
        model->select();
    } else
        QMessageBox::warning(this,tr("Warning"),
                             tr("Choose the row before removing"));
}

void EditLocation::on_editbutton_clicked()
{
    if(ui->tableView->selectionModel()->hasSelection()){
        alterlocation = new AlterLocation(location, this);
        alterlocation->setWindowTitle("Rename the location");
        alterlocation->show();

        connect(alterlocation,&AlterLocation::locationRenamedSignal,this,&EditLocation::locationRenamedSlot);
    } else
        QMessageBox::warning(this,tr("Warning"),
                             tr("Choose the row before editing"));
}

void EditLocation::on_cancelButton_clicked()
{
    close();
}

void EditLocation::locationRenamedSlot(QString renamedLocation)
{
    db->update(location,renamedLocation);
    model->select();
    emit locationEditedSignal(location,renamedLocation);
}
