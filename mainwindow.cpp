#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include <ctunes.h>
#include <GenerosMusicales.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addsongboton_clicked()
{

}


void MainWindow::on_addsongboton_pressed()
{
    ctunes fefo;
    fefo.addSong("fefo","fefi", GenerosMusicales::GENERO_DANCE,0.15);
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_2_pressed()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_pressed()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_4_pressed()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_5_pressed()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_6_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_7_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_8_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_9_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}

