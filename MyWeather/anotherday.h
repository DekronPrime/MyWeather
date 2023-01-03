#ifndef ANOTHERDAY_H
#define ANOTHERDAY_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDialogButtonBox>

namespace Ui {
class AnotherDay;
}

class AnotherDay : public QDialog
{
    Q_OBJECT

public:
    explicit AnotherDay(QWidget *parent = nullptr);
    ~AnotherDay();

signals:
    void signalADaccepted(QDate date);

private slots:
    void selectedDateChanged();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AnotherDay *ui;
};

#endif // ANOTHERDAY_H
