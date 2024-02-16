#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include <ctunes.h>
#include <GenerosMusicales.h>
#include <string>
#include <iostream>
#include <InvalidRateException.h>
#include <QRegularExpression>

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
    ui->textBrowser->setText("");
}


void MainWindow::on_pushButton_8_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->textBrowser_2->setText("");
}


void MainWindow::on_pushButton_9_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->textBrowser_3->setText("");
}


void MainWindow::on_addboton_clicked()
{
    double precio;
    QString qname = ui->nombrefield->text().simplified();
    string name = qname.toStdString();
    QString qcant=ui->cantantefield->text().simplified();
    string cantant = qcant.toStdString();
    QString qgenero = ui->generobox->currentText().simplified();
    string genero = qgenero.toStdString();
    QString qprecio = ui->preciofield->text().simplified();
    int tiempo = (ui->hora->value()*3600)+(ui->minutos->value()*60)+(ui->segundos->value());
    if(tiempo > 0){
    bool isValidPrice = QRegularExpression("^[0-9]+([\\.,][0-9]+)?$").match(qprecio).hasMatch();
    GenerosMusicales::Genero gen;
    if (isValidPrice){
    precio = qprecio.toDouble();
    if(!qname.isEmpty() && !qcant.isEmpty() && !qgenero.isEmpty() && !qprecio.isEmpty()){
    if(genero=="DANCE"){gen=GenerosMusicales::GENERO_DANCE;}
    if(genero=="ELECTRONICA"){gen = GenerosMusicales::GENERO_ELECTRONICA;}
    if(genero=="POP"){gen = GenerosMusicales::GENERO_POP;}
    if(genero=="RANCHERA"){gen = GenerosMusicales::GENERO_RANCHERA;}
    if(genero=="RAP"){gen = GenerosMusicales::GENERO_RAP;}
    if(genero=="REGGAE"){gen = GenerosMusicales::GENERO_REGGAE;}
    if(genero=="ROCK"){gen = GenerosMusicales::GENERO_ROCK;}
    ctunes object;
    object.addSong(name,cantant,gen,precio,tiempo);
    ui->nombrefield->setText("");
    ui->preciofield->setText("");
    ui->cantantefield->setText("");
    ui->etiquetaerror->setText("");
    ui->textBrowser_4->setText("El codigo de tu cancion es: "+ QString::number(object.codigosave()));
    }else{
    ui->etiquetaerror->setText("tiene que llenar todos los campos");
    }
    }else{
    ui->etiquetaerror->setText("Solo puede ingresar numeros");
    }
    }else{
    ui->etiquetaerror->setText("La cancion es demasiado corta");
    }
}


void MainWindow::on_verboton_clicked()
{
QString scode;
ctunes object;
scode = ui->codigoInfo->text();
bool isValidint = QRegularExpression("^[0-9]+$").match(scode).hasMatch();
if(isValidint){
int code = scode.toInt();
QString cadena = QString::fromStdString(object.infoSong(code));
ui->textBrowser_3->setText(cadena);
ui->codigoInfo->setText("");
ui->errorlabel->setText("");
}else{
ui->errorlabel->setText("solo puede ingresar un numero entero");
}
}


void MainWindow::on_botonreview_clicked()
{
    QString scode = ui->codigoreview->text();
    QString sstrellas = ui->estrellasfield->text();
    bool isValidint = QRegularExpression("^[0-9]+$").match(scode).hasMatch();
    bool isValidint2 = QRegularExpression("^[0-9]+$").match(sstrellas).hasMatch();
    if(isValidint && isValidint2){
        int code = scode.toInt();
        int estrellas = sstrellas.toInt();
        if(estrellas>=0 && estrellas<=5){
    ctunes object;
    try{
    object.reviewSong(code,estrellas);
    ui->codigoreview->setText("");
    ui->estrellasfield->setText("");
    ui->label_18->setText("");
    }catch(const InvalidRateException &e){
        qDebug() << "Error:" << e.what();
        ui->label_18->setText(QString::number(estrellas)+e.what());
    }
        }else{
        ui->label_18->setText("El numero de estrellas no es valido");
        }
    }else{
        ui->label_18->setText("Solo puede poner numeros enteros");
    }
}


void MainWindow::on_descargarboton_clicked()
{   QString scode = ui->codigoDescargar->text();
    bool isValidint = QRegularExpression("^[0-9]+$").match(scode).hasMatch();
    if(isValidint){
    int code = scode.toInt();
    string cliente = ui->nombredownload->text().toStdString();
    ctunes object;
    ui->codigoDescargar->setText("");
    ui->nombredownload->setText("");
    ui->textBrowser->setText(QString::fromStdString(object.downloadSong(code,cliente)));
    }else{
        ui->textBrowser->setText("Solo puede colocar numeros enteros");
    }
}


void MainWindow::on_creararchivosboton_clicked()
{
    string namefile = ui->nombrearchivo->text().toStdString();
    ctunes object;
    ui->textBrowser_2->setText(object.songs(namefile));
    ui->nombrearchivo->setText("");

}


void MainWindow::on_pushButton_7_clicked()
{

}

