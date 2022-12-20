#include "modifydatawindow.h"
#include "ui_modifydatawindow.h"

ModifyDataWindow::ModifyDataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeleteWindow)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();

    connect(ui->sort_CB,&QComboBox::currentIndexChanged,this,&ModifyDataWindow::sortChanged);
    this->SortOrder = true;

    this->setupModel(TABLE,
                     QStringList() << tr("id")
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
}

ModifyDataWindow::~ModifyDataWindow()
{
    delete ui;
}

void ModifyDataWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this, db->getDB());
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    model->setSort(1,Qt::AscendingOrder);
}

void ModifyDataWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(1,75);
    ui->tableView->setColumnWidth(2,90);

    model->select();
}

void ModifyDataWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        on_returnButton_clicked();
    else if(e->key() == Qt::Key_F5)
        model->select();
}

void ModifyDataWindow::on_returnButton_clicked()
{
    emit signalfromDelWindow();
}

void ModifyDataWindow::sortChanged()
{
    sortorder->sortChanged(model,ui->sort_CB,SortOrder);
}


void ModifyDataWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void ModifyDataWindow::on_deleteButton_clicked()
{
    model->removeRow(row);
    model->select();
    sortChanged();
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
    model->select();
}

