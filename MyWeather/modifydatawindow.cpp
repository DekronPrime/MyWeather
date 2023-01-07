#include "modifydatawindow.h"
#include "ui_modifydatawindow.h"

ModifyDataWindow::ModifyDataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModifyWindow)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();

    connect(ui->sort_CB,&QComboBox::currentIndexChanged,this,&ModifyDataWindow::sortChanged);

    connect(ui->location_cb,&QComboBox::currentTextChanged,this,&ModifyDataWindow::filterLocation);

    this->SortOrder = true;

    this->setupModel(QStringList() << tr("id")
                                   << tr("Location")
                                   << tr("Date")
                                   << tr("Cloudiness")
                                   << tr("Day Temp (°C)")
                                   << tr("Night Temp (°C)")
                                   << tr("Wind Direction")
                                   << tr("Wind Power (day)")
                                   << tr("Wind Power (night)")
                                   << tr("Precitipation (hours)")
                                   << tr("Humidity(%)")
                    );

    this->createUI();

    ui->sort_CB->setCurrentIndex(1);

    this->setupComboBox();
}

ModifyDataWindow::~ModifyDataWindow()
{
    delete ui;
}

void ModifyDataWindow::setupModel(const QStringList &headers)
{
    model = db->getQueryModel();

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void ModifyDataWindow::createUI()
{
    proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);

    ui->tableView->setModel(proxy);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,75);
    ui->tableView->setColumnWidth(4,100);
}

void ModifyDataWindow::setupComboBox()
{
    ui->location_cb->insertSeparator(1);
    refcb->insertLocations(db, ui->location_cb, 2);
}

void ModifyDataWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        on_returnButton_clicked();
    else if(e->key() == Qt::Key_F5)
        refreshModel();
}

void ModifyDataWindow::on_returnButton_clicked()
{
    emit signalfromDelWindow();
}

void ModifyDataWindow::sortChanged()
{
    sortorder->sortChanged(proxy,ui->sort_CB->currentIndex() + 1,SortOrder);
}

void ModifyDataWindow::on_tableView_clicked(const QModelIndex &index)
{
     rowId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}

void ModifyDataWindow::on_removeButton_clicked()
{
    if(ui->tableView->selectionModel()->hasSelection()){
        db->remove(rowId);
        model->setQuery(db->select());
    } else
        QMessageBox::warning(this,tr("Warning"),
                             tr("Choose the row before removing"));
}

void ModifyDataWindow::on_changeSortButton_clicked()
{
    if(this->SortOrder){
        this->SortOrder = false;
        ui->changeSortButton->setText("Asc");
    }
    else{
        this->SortOrder = true;
        ui->changeSortButton->setText("Desc");
    }
    sortChanged();
}

void ModifyDataWindow::on_refreshButton_clicked()
{
    refreshModel();
}

void ModifyDataWindow::refreshModel()
{
    model->setQuery(db->select());
    filterLocation(ui->location_cb->currentText());
}

void ModifyDataWindow::filterLocation(QString location)
{
    if(location == "All")
        model->setQuery(db->select());
    else
        model->setQuery(db->select(location));
}

void ModifyDataWindow::addToComboBox(QString newLocation)
{
    refcb->addToComboBox(ui->location_cb, newLocation);
}

void ModifyDataWindow::newLocationAddedSlot(QString newLocation)
{
    addToComboBox(newLocation);
    emit newLocationAddedSignal(newLocation);
}

void ModifyDataWindow::locationRemovedSlot(QString location)
{
    refcb->removeFromComboBox(ui->location_cb, location);
    emit locationRemovedSignal(location);
}

void ModifyDataWindow::locationEditedSlot(QString oldName, QString newName)
{
    refcb->updateItemInComboBox(ui->location_cb, oldName, newName);
    emit locationEditedSignal(oldName, newName);
}

void ModifyDataWindow::on_editLocationButton_clicked()
{
    editlocation = new EditLocation;
    editlocation->setWindowTitle("Edit Location");
    editlocation->show();

    connect(editlocation,&EditLocation::newLocationAddedSignal,this,&ModifyDataWindow::newLocationAddedSlot);
    connect(editlocation,&EditLocation::locationRemovedSignal,this,&ModifyDataWindow::locationRemovedSlot);
    connect(editlocation,&EditLocation::locationEditedSignal,this,&ModifyDataWindow::locationEditedSlot);

    connect(editlocation,&QWidget::destroyed,this,&ModifyDataWindow::refreshModel);
}
