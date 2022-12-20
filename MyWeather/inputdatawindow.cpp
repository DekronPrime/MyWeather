#include "inputdatawindow.h"
#include "ui_inputwindow.h"
#include <QPixmap>

InputDataWindow::InputDataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);

    db = SqliteDBManager::getInstance();

    changeimg->setImages(ui->temperature_img,ui->compass_img,ui->wind_img,ui->perticipation_img,ui->humidity_img);

    connect(ui->cloudiness_CB,&QComboBox::currentIndexChanged,this,&InputDataWindow::CloudinessChanged);

    ui->dateEdit->setDate(QDate::currentDate());
}

InputDataWindow::~InputDataWindow()
{
    delete ui;
}

void InputDataWindow::on_returnButton_clicked()
{
    emit signalfromInWindow();
}

void InputDataWindow::CloudinessChanged()
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
    if (ui->cloudiness_CB->currentIndex() == 0 || ui->windDirection_CB->currentIndex() == 0)
        QMessageBox::critical(this,tr("Error insert"),
                              tr("Fields can not be empty!\n"
                                 "Please fill in all fields"));
    else {
        DataDB data;
        data.setDate(ui->dateEdit->date());
        data.setCloudiness(ui->cloudiness_CB->currentText());
        data.setDayTemp(ui->dayTemp_SB->value());
        data.setNightTemp(ui->nightTemp_SB->value());
        data.setWindDirection(ui->windDirection_CB->currentText());
        data.setDayWindPower(ui->dayWindPower_SB->value());
        data.setNightWindPower(ui->nightWindPower_SB->value());
        data.setPrecipitationHours(ui->perticipationHours_SB->value());
        data.setHumidity(ui->humidity_SB->value());

        if (db->insertIntoTable(TABLE,data))
            QMessageBox::information(this,tr("Completed"),
                                     tr("this day has been successfully inserted into the database"));
        else {
            int res = QMessageBox::question(this,tr("Error"),
                                  tr("The database already has the row with this date\n"
                                     "Do you want to update this row?"),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::Yes);
            if(res == QMessageBox::Yes)
                db->update(data);
        }
    }
}

