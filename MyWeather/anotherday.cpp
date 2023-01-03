#include "anotherday.h"
#include "ui_anotherday.h"

AnotherDay::AnotherDay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnotherDay)
{
    ui->setupUi(this);

    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->anotherDate_lbl->setText("You selected: "+QDate::currentDate().toString());
    connect(ui->calendarWidget,&QCalendarWidget::selectionChanged,this,&AnotherDay::selectedDateChanged);
}

AnotherDay::~AnotherDay()
{
    delete ui;
}

void AnotherDay::selectedDateChanged()
{
    ui->anotherDate_lbl->setText("You selected: "+ui->calendarWidget->selectedDate().toString());
}

void AnotherDay::on_buttonBox_accepted()
{
    emit signalADaccepted(ui->calendarWidget->selectedDate());
    delete this;
}

void AnotherDay::on_buttonBox_rejected()
{
    delete this;
}
