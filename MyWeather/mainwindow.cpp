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

    connect(inWindow,&InputDataWindow::signalFromInWindow,this,&MainWindow::returnToMainMenu);
    connect(shWindow,&ShowDataWindow::signalFromShWindow,this,&MainWindow::returnToMainMenu);
    connect(modWindow,&ModifyDataWindow::signalFromModWindow,this,&MainWindow::returnToMainMenu);

    connect(ui->exitButton,&QPushButton::clicked,this,&QApplication::exit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::returnToMainMenu()
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

