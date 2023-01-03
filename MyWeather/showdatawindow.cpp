#include "showdatawindow.h"
#include "qsqlquery.h"
#include "ui_showdatawindow.h"


ShowDataWindow::ShowDataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowWindow)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();

    adform = new AnotherDay;
    adform->setWindowTitle("Choose another day");

    connect(adform,&AnotherDay::signalADaccepted,this,&ShowDataWindow::adFormAccepted);

    changeimg->setErrorImage(ui->nodata_img);
    changeimg->setImages(ui->temp_img,ui->direction_img,ui->wind_img,ui->fallout_img,ui->humidity_img);

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

    connect(ui->sort_CB,&QComboBox::currentIndexChanged,this,&ShowDataWindow::sortChanged);

    on_todayButton_clicked();

    this->setupComboBox();
    setLocation(ui->location_cb->currentText());
}

ShowDataWindow::~ShowDataWindow()
{
    delete ui;
}

void ShowDataWindow::setupModel(const QStringList &headers)
{
    model = db->getQueryModel();

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void ShowDataWindow::createUI()
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

void ShowDataWindow::setupComboBox()
{
    refcb->insertLocations(db, ui->location_cb, 0);
}

void ShowDataWindow::setDate(const QDate &date)
{
    this->date = date;
}

QDate ShowDataWindow::getDate() const
{
    return this->date;
}

void ShowDataWindow::setLocation(const QString &location)
{
    this->location = location;
}

QString ShowDataWindow::getLocation() const
{
    return this->location;
}

void ShowDataWindow::on_returnButton_clicked()
{
    emit signalfromShWindow();
}

void ShowDataWindow::on_todayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->setDate(QDate::currentDate());
    printData(this->getDate());
}


void ShowDataWindow::on_yesterdayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->setDate(QDate::currentDate().addDays(-1));
    printData(this->getDate());
}


void ShowDataWindow::on_tendaysButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    refreshData();
}


void ShowDataWindow::on_anotherButton_clicked()
{
    adform->show();
}

void ShowDataWindow::adFormAccepted(QDate date)
{
    this->setDate(date);
    ui->stackedWidget->setCurrentIndex(1);
    printData(this->getDate());
}

void ShowDataWindow::printData(QDate date)
{
    DataDB * data = db->selectFromWeather(date, this->getLocation());
    if(data){
        ui->statusbar->clearMessage();
        ui->stackedWidget->setCurrentIndex(1);
        ui->date_lbl->setText(data->getDate().toString("dddd, MMMM dd, yyyy"));
        ui->location_lbl->setText(data->getLocation());
        ui->cloudiness_lbl->setText(data->getCloudiness());
        changeimg->setImage(ui->cloudiness_lbl->text(),ui->cloudiness_img);
        ui->daytemp_lbl->setText(QString::number(data->getDayTemp()));
        ui->nighttemp_lbl->setText(QString::number(data->getNightTemp()));
        ui->winddirection_lbl->setText(data->getWindDirection());
        ui->daywindpower_lbl->setText(QString::number(data->getDayWindPower()));
        ui->nightwindpower_lbl->setText(QString::number(data->getNightWindPower()));
        ui->precitipationhours_lbl->setText(QString::number(data->getPrecipitationHours()));
        if(ui->precitipationhours_lbl->text() == '1')
            ui->label_11->setText("hour");
        else
            ui->label_11->setText("hours");
        ui->humidity_lbl->setText(QString::number(data->getHumidity()));
    }
    else {
        ui->statusbar->showMessage(date.toString("dddd, MMMM dd, yyyy") + " in " + location + " not found");
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void ShowDataWindow::sortChanged()
{
    sortorder->sortChanged(proxy, ui->sort_CB->currentIndex() + 2, SortOrder);
}

void ShowDataWindow::refreshData()
{
    if(ui->stackedWidget->currentIndex() == 2)
        model->setQuery(db->select(QDate::currentDate().addDays(-10), this->getLocation()));
    else
        printData(this->getDate());
}

void ShowDataWindow::newLocationAddedSlot(QString newLocation)
{
    refcb->addToComboBox(ui->location_cb, newLocation);
}

void ShowDataWindow::locationRemovedSlot(QString location)
{
    refcb->removeFromComboBox(ui->location_cb, location);
}

void ShowDataWindow::locationEditedSlot(QString oldName, QString newName)
{
    refcb->updateItemInComboBox(ui->location_cb, oldName, newName);
}

void ShowDataWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        on_returnButton_clicked();
    else if(e->key() == Qt::Key_F5){
        on_refreshButton_clicked();
    }

}

void ShowDataWindow::on_changeSortButton_clicked()
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

void ShowDataWindow::on_refreshButton_clicked()
{
    refreshData();
}

void ShowDataWindow::on_location_cb_currentTextChanged(const QString &location)
{
    this->setLocation(location);
    refreshData();
}
