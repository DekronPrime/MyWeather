#include "addlocation.h"
#include "ui_addlocation.h"

AddLocation::AddLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLocation)
{
    ui->setupUi(this);
}

AddLocation::~AddLocation()
{
    delete ui;
}

void AddLocation::on_buttonBox_rejected()
{
    this->close();
}


void AddLocation::on_buttonBox_accepted()
{
    emit newLocationSignal(ui->lineEdit->text());
    this->close();
}

