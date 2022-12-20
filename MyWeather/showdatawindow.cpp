#include "showdatawindow.h"
#include "ui_showwindow.h"


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

    this->setupModel(TABLE,
                     QStringList() << tr("id")
                                   << tr("Date")
                                   << tr("Cloudiness")
                                   << tr("Day Temp(°C)")
                                   << tr("Night Temp(°C)")
                                   << tr("Wind Direction")
                                   << tr("Wind Power(day)")
                                   << tr("Wind Power(night)")
                                   << tr("Precitipation(hours)")
                                   << tr("Humidity(%)")
                    );

    this->createUI();

    connect(ui->sort_CB,&QComboBox::currentIndexChanged,this,&ShowDataWindow::sortChanged);

    on_todayButton_clicked();
}

ShowDataWindow::~ShowDataWindow()
{
    delete ui;
}

void ShowDataWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this, db->getDB());
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    model->setSort(1,Qt::AscendingOrder);
}

void ShowDataWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(1,90);
    ui->tableView->setColumnWidth(2,90);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    //model->setFilter("Date BETWEEN DATE('now','-10 day') AND DATE('now')");
    model->setFilter("Date > DATE('now','-10 day') AND Date <= DATE('now')");
    model->select();
}

void ShowDataWindow::on_returnButton_clicked()
{
    emit signalfromShWindow();
}

void ShowDataWindow::on_todayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    printData(QDate::currentDate());
}


void ShowDataWindow::on_yesterdayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    printData(QDate::currentDate().addDays(-1));
}


void ShowDataWindow::on_tendaysButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void ShowDataWindow::on_anotherButton_clicked()
{
    adform->show();
}

void ShowDataWindow::adFormAccepted(QDate date)
{
    ui->stackedWidget->setCurrentIndex(1);
    printData(date);
}

void ShowDataWindow::printData(QDate date)
{
    this->date = date;
    DataDB * data = db->selectFromWeather(date);
    if(data){
        ui->statusbar->clearMessage();
        ui->stackedWidget->setCurrentIndex(1);
        ui->date_lbl->setText(data->getDate().toString("dddd, MMMM dd, yyyy"));
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
    else{
        ui->statusbar->showMessage(this->date.toString("dddd, MMMM dd, yyyy")+" not found");
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void ShowDataWindow::sortChanged()
{
    sortorder->sortChanged(model,ui->sort_CB,sortButton);
}

void ShowDataWindow::refreshData()
{
    if(ui->stackedWidget->currentIndex() == 2)
        model->select();
    else
        printData(this->date);
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
    if(this->sortButton){
        this->sortButton = false;
        ui->changeSortButton->setText("Asc");
    }
    else{
        this->sortButton = true;
        ui->changeSortButton->setText("Desc");
    }
    sortChanged();
}

void ShowDataWindow::on_refreshButton_clicked()
{
    refreshData();
}

