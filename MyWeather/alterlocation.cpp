#include "alterlocation.h"
#include "ui_alterlocation.h"

AlterLocation::AlterLocation(QString location, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlterLocation),
    chosenLocation(location)
{
    ui->setupUi(this);

    changeimage->setEditLocationImage(ui->pencil_img, ui->alter_location_img);
    this->setupLineEdit();
}

void AlterLocation::setupLineEdit()
{
    ui->lineEdit->setText(this->chosenLocation);
    ui->lineEdit->selectAll();
    ui->result_lbl->setText(this->chosenLocation);
}

AlterLocation::~AlterLocation()
{
    delete ui;
}

void AlterLocation::on_cancelButton_clicked()
{
    close();
}

void AlterLocation::on_submitButton_clicked()
{
    emit locationRenamedSignal(ui->lineEdit->text());
    close();
}

void AlterLocation::on_lineEdit_textEdited(const QString &text)
{
    ui->result_lbl->setText(text);
}
