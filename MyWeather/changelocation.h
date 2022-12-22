#ifndef CHANGELOCATION_H
#define CHANGELOCATION_H

#include <QDialog>

namespace Ui {
class ChangeLocation;
}

class ChangeLocation : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeLocation(QWidget *parent = nullptr);
    ~ChangeLocation();

signals:
    void locationchangedSignal(QString location);

private slots:
    void on_cancelButton_clicked();

    void on_chooseButton_clicked();

private:
    Ui::ChangeLocation *ui;
};

#endif // CHANGELOCATION_H
