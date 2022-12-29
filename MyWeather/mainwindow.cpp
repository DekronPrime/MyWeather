#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    inWindow = new InputDataWindow;
    inWindow->setWindowTitle("Input Data");

    shWindow = new ShowDataWindow;
    shWindow->setWindowTitle("Show Data");

    modWindow = new ModifyDataWindow;
    modWindow->setWindowTitle("Modify Data");

    connect(inWindow,&InputDataWindow::signalfromInWindow,this,&MainWindow::ReturnToMainMenu);
    connect(shWindow,&ShowDataWindow::signalfromShWindow,this,&MainWindow::ReturnToMainMenu);
    connect(modWindow,&ModifyDataWindow::signalfromDelWindow,this,&MainWindow::ReturnToMainMenu);

    connect(ui->exitButton,&QPushButton::clicked,this,&QApplication::exit);

    connect(inWindow,&InputDataWindow::newLocationAddedSignal,modWindow,&ModifyDataWindow::refreshComboBox);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReturnToMainMenu()
{
    inWindow->hide();
    shWindow->hide();
    modWindow->hide();
    this->show();
}


void MainWindow::on_inputButton_clicked()
{
    inWindow->show();
    this->hide();
}


void MainWindow::on_showButton_clicked()
{
    shWindow->show();
    this->hide();
}


void MainWindow::on_deleteRowButton_clicked()
{
    modWindow->show();
    this->hide();
}

