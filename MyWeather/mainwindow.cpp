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

    connect(ui->modifyDataButton,&QPushButton::clicked,modWindow,&ModifyDataWindow::refreshModel);
    connect(ui->showDataButton,&QPushButton::clicked,shWindow,&ShowDataWindow::refreshData);

    connect(inWindow,&InputDataWindow::newLocationAddedSignal,modWindow,&ModifyDataWindow::addToComboBox);
    connect(inWindow,&InputDataWindow::newLocationAddedSignal,shWindow,&ShowDataWindow::newLocationAddedSlot);

    connect(modWindow,&ModifyDataWindow::newLocationAddedSignal,inWindow,&InputDataWindow::newLocationAddedSlot);
    connect(modWindow,&ModifyDataWindow::locationRemovedSignal,inWindow,&InputDataWindow::locationRemovedSlot);
    connect(modWindow,&ModifyDataWindow::locationEditedSignal,inWindow,&InputDataWindow::locationEditedSlot);

    connect(modWindow,&ModifyDataWindow::newLocationAddedSignal,shWindow,&ShowDataWindow::newLocationAddedSlot);
    connect(modWindow,&ModifyDataWindow::locationRemovedSignal,shWindow,&ShowDataWindow::locationRemovedSlot);
    connect(modWindow,&ModifyDataWindow::locationEditedSignal,shWindow,&ShowDataWindow::locationEditedSlot);
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

void MainWindow::on_inputDataButton_clicked()
{
    inWindow->show();
    this->hide();
}

void MainWindow::on_showDataButton_clicked()
{
    shWindow->show();
    this->hide();
}

void MainWindow::on_modifyDataButton_clicked()
{
    modWindow->show();
    this->hide();
}

void MainWindow::on_exitButton_clicked()
{
    exitWindow = new ExitWindow;
    exitWindow->setWindowTitle("Exit");
    exitWindow->show();
}
