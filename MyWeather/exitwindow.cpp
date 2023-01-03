#include "exitwindow.h"
#include "ui_exitwindow.h"

ExitWindow::ExitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitWindow)
{
    ui->setupUi(this);

    changeimage->setExitImages(ui->question_img, ui->exit_img);
}

ExitWindow::~ExitWindow()
{
    delete ui;
}

void ExitWindow::on_noButton_clicked()
{
    this->close();
}

void ExitWindow::on_yesButton_clicked()
{
    QApplication::exit();
}
