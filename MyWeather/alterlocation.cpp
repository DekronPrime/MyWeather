#include "alterlocation.h"
#include "ui_alterlocation.h"

AlterLocation::AlterLocation(QString location, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlterLocation),
    chosenLocation(location)
{
    ui->setupUi(this);

    ui->lineEdit->setText(location);
    ui->lineEdit->selectAll();
    ui->result_lbl->setText(location);
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

