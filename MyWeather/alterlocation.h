#ifndef ALTERLOCATION_H
#define ALTERLOCATION_H

#include <QDialog>

namespace Ui {
class AlterLocation;
}

class AlterLocation : public QDialog
{
    Q_OBJECT

public:
    explicit AlterLocation(QString location, QWidget *parent = nullptr);
    ~AlterLocation();

signals:
    void locationRenamedSignal(QString renamedLocation);

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_lineEdit_textEdited(const QString &text);

private:
    Ui::AlterLocation *ui;

    QString chosenLocation;
};

#endif // ALTERLOCATION_H
