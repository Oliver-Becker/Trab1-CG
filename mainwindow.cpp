#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle(tr("Teste QT OK"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ClearButton_clicked() {
    this->ui->Canvas->clearScreen();
}

void MainWindow::on_ColorR_valueChanged(double value) {
    this->ui->Canvas->R = int(value);
    this->ui->Canvas->update();
}

void MainWindow::on_ColorG_valueChanged(double value) {
    this->ui->Canvas->G = int(value);
    this->ui->Canvas->update();
}

void MainWindow::on_ColorB_valueChanged(double value) {
    this->ui->Canvas->B = int(value);
    this->ui->Canvas->update();
}
