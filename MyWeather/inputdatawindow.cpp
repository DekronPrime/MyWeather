#include "inputdatawindow.h"
#include "ui_inputdatawindow.h"

InputDataWindow::InputDataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();
    changeimg->setImages(ui->temperature_img,ui->compass_img,ui->wind_img,ui->perticipation_img,ui->humidity_img);
    ui->dateEdit->setDate(QDate::currentDate());
    this->setupComboBox();
    connect(ui->cloudiness_CB,&QComboBox::currentIndexChanged,this,&InputDataWindow::cloudinessChanged);
}

InputDataWindow::~InputDataWindow()
{
    delete ui;
}

void InputDataWindow::setupComboBox()
{
    refcb->insertLocations(db, ui->location_cb, 1);
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

        if(!db->alreadyExists(data.getDate(),data.getLocation())) {
            if(db->insert(data))
                QMessageBox::information(this,tr("Completed"),
                                         tr("This row has been successfully inserted into database"));
            else
                QMessageBox::critical(this,tr("Error"),
                                      tr("Something went wrong while inserting into database"));
        }
        else {
            int res = QMessageBox::question(this,tr("Error"),
                                  tr("The row with with date and location already exists.\n"
                                     "Do you want to update this row?"),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::Yes);

            if(res == QMessageBox::Yes) {
                db->update(data);
                QMessageBox::information(this,tr("Completed"),
                                         tr("Done.\nThis row was successfully updated"));
            }

        }
    }
}

void InputDataWindow::on_location_cb_currentTextChanged(const QString &text)
{
    if(text == "")
        ui->statusbar->showMessage("No location");
    else
        ui->statusbar->showMessage("Current location: " + text);
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
    if(db->insert(newLocation)) {
        emit newLocationAddedSignal(newLocation);
        newLocationAddedSlot(newLocation);
    }
    else
        QMessageBox::critical(this,tr("Error insert"),
                              tr("Error insert of new location"));
}

void InputDataWindow::newLocationAddedSlot(QString newLocation)
{
    refcb->addToComboBox(ui->location_cb, newLocation);
}

void InputDataWindow::locationRemovedSlot(QString location)
{
    refcb->removeFromComboBox(ui->location_cb, location);
}

void InputDataWindow::locationEditedSlot(QString oldName, QString newName)
{
    refcb->updateItemInComboBox(ui->location_cb, oldName, newName);
}
