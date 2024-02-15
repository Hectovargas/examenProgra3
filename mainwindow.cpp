#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include <ctunes.h>
#include <GenerosMusicales.h>
#include <string>
#include <iostream>
#include <InvalidRateException.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ctunes object;
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


void MainWindow::on_addboton_clicked()
{
 try{
    double precio;
    QString qname = ui->nombrefield->text().simplified();
    string name = qname.toStdString();
    QString qcant=ui->cantantefield->text().simplified();
    string cantant = qcant.toStdString();
    QString qgenero = ui->generobox->currentText().simplified();
    string genero = qgenero.toStdString();
    QString qprecio = ui->preciofield->text().simplified();
    precio = qprecio.toDouble();
    GenerosMusicales::Genero gen;
    if(!qname.isEmpty() && !qcant.isEmpty() && !qgenero.isEmpty() && !qprecio.isEmpty()){
    if(genero=="DANCE"){gen=GenerosMusicales::GENERO_DANCE;}
    if(genero=="ELECTRONICA"){gen = GenerosMusicales::GENERO_ELECTRONICA;}
    if(genero=="POP"){gen = GenerosMusicales::GENERO_POP;}
    if(genero=="RANCHERA"){gen = GenerosMusicales::GENERO_RANCHERA;}
    if(genero=="RAP"){gen = GenerosMusicales::GENERO_RAP;}
    if(genero=="REGGAE"){gen = GenerosMusicales::GENERO_REGGAE;}
    if(genero=="ROCK"){gen = GenerosMusicales::GENERO_ROCK;}
    ctunes object;
    object.addSong(name,cantant,gen,precio);
    }else{
    ui->etiquetaerror->setText("tiene que llenar todos los campos");
    }
 }catch (const invalid_argument& e){
     ui->etiquetaerror->setText("solo puede ingresar numeros en el apartado de precio");
 }
}


void MainWindow::on_verboton_clicked()
{
ctunes object;
QString cadena = QString::fromStdString(object.infoSong(ui->codigoInfo->text().toInt()));
ui->textEdit->setText(cadena);
}


void MainWindow::on_botonreview_clicked()
{
    int code = ui->codigoreview->text().toInt();
    int estrellas = ui->estrellasfield->text().toInt();
    ctunes object;
    try{
    object.reviewSong(code,estrellas);
    }catch(const InvalidRateException &e){
    }
}


void MainWindow::on_descargarboton_clicked()
{
    int code = ui->codigoDescargar->text().toInt();
    string cliente = ui->nombredownload->text().toStdString();
    ctunes object;
    object.downloadSong(code,cliente);
    ui->textBrowser->setText(QString::fromStdString(object.downloadSong(code,cliente)));
}


void MainWindow::on_creararchivosboton_clicked()
{
    string namefile = ui->nombrearchivo->text().toStdString();
    ctunes object;
    ui->textBrowser_2->setText(object.songs(namefile));
}

