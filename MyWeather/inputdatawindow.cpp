#include "inputdatawindow.h"
#include "ui_inputdatawindow.h"

InputDataWindow::InputDataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();

    changeimg->setImages(ui->temperature_img,ui->compass_img,ui->wind_img,ui->perticipation_img,ui->humidity_img);

    connect(ui->cloudiness_CB,&QComboBox::currentIndexChanged,this,&InputDataWindow::cloudinessChanged);

    ui->dateEdit->setDate(QDate::currentDate());

    QStringList locations = db->getAllLocations();
    ui->location_cb->insertItems(1,locations);
}

InputDataWindow::~InputDataWindow()
{
    delete ui;
}

void InputDataWindow::on_returnButton_clicked()
{
    emit signalfromInWindow();
}

void InputDataWindow::cloudinessChanged()
{
    changeimg->setImage(ui->cloudiness_CB->currentText(),ui->cloudiness_img);
}

void InputDataWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape){
        on_returnButton_clicked();
    }
}

void InputDataWindow::on_insertButton_clicked()
{
    if (ui->cloudiness_CB->currentIndex() == 0 || ui->windDirection_CB->currentIndex() == 0 || ui->location_cb->currentIndex() == 0)
        QMessageBox::critical(this,tr("Error insert"),
                              tr("Fields can not be empty!\n"
                                 "Please fill in all fields"));
    else {
        DataDB data;
        data.setLocation(ui->location_cb->currentText());
        data.setDate(ui->dateEdit->date());
        data.setCloudiness(ui->cloudiness_CB->currentText());
        data.setDayTemp(ui->dayTemp_SB->value());
        data.setNightTemp(ui->nightTemp_SB->value());
        data.setWindDirection(ui->windDirection_CB->currentText());
        data.setDayWindPower(ui->dayWindPower_SB->value());
        data.setNightWindPower(ui->nightWindPower_SB->value());
        data.setPrecipitationHours(ui->perticipationHours_SB->value());
        data.setHumidity(ui->humidity_SB->value());

        if (db->insertIntoTable(TABLE_WEATHER,data))
            QMessageBox::information(this,tr("Completed"),
                                     tr("this day has been successfully inserted into the database"));
        else {
            QMessageBox::question(this,tr("Error"),
                                  tr("The database already has the row with this date\n"
                                     "Do you want to update this row?"),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::Yes);
            //int res =

            //if(res == QMessageBox::Yes)
                //db->update(data);
        }
    }
}


void InputDataWindow::on_location_cb_currentTextChanged(const QString &text)
{
    if(text == "")
        ui->statusbar->showMessage("No location");
    else{
//        DataDB data;
//        data.setLocation(text);
        ui->statusbar->showMessage("Current location: " + text);
    }

}


void InputDataWindow::on_addLocationButton_clicked()
{
    addLocation = new AddLocation;
    addLocation->setWindowTitle("Add New Location");
    addLocation->show();

    connect(addLocation,&AddLocation::newLocationSignal,this,&InputDataWindow::newLocationRecieved);
}

void InputDataWindow::newLocationRecieved(QString newLocation)
{
    if(db->insertIntoTable(newLocation)) {
        ui->location_cb->addItem(newLocation);
        emit newLocationAddedSignal(newLocation);
    }
    else
        QMessageBox::critical(this,tr("Error insert"),
                              tr("Error insert of new location"));
}

