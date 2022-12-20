#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "inputdatawindow.h"
#include "showdatawindow.h"
#include "modifydatawindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    InputDataWindow *inWindow;
    ShowDataWindow *shWindow;
    ModifyDataWindow *modWindow;

private slots:
    void ReturnToMainMenu();

    void on_inputButton_clicked();
    void on_showButton_clicked();
    void on_deleteRowButton_clicked();
};



#endif // MAINWINDOW_H
