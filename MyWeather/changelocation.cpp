#include "changelocation.h"
#include "ui_changelocation.h"

ChangeLocation::ChangeLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeLocation)
{
    ui->setupUi(this);
}

ChangeLocation::~ChangeLocation()
{
    delete ui;
}

void ChangeLocation::on_cancelButton_clicked()
{
    this->close();
}


void ChangeLocation::on_chooseButton_clicked()
{
    emit locationchangedSignal("LOCATION");
    this->close();
}

