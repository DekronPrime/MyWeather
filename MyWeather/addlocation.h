#ifndef ADDLOCATION_H
#define ADDLOCATION_H

#include <QDialog>

namespace Ui {
class AddLocation;
}

class AddLocation : public QDialog
{
    Q_OBJECT

public:
    explicit AddLocation(QWidget *parent = nullptr);
    ~AddLocation();

private:
    Ui::AddLocation *ui;

signals:
    void newLocationSignal(QString newLocation);

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // ADDLOCATION_H
