#include "ctunes.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <stdlib.h>
#include <GenerosMusicales.h>
#include <InvalidRateException.h>
#include <QDate>
#include <QDebug>

using namespace std;

struct cancion{
    int code;
    QString nombre;
    QString cantante;
    QString genero;
    double precio;
    int estrellas;
    int reviews;
    int duracion;
};

struct descarga
{
    int codedown;
    QString fecha;
    int codesong;
    QString cliente;
    double precio;
};

QFile codigoarchivo("codigos.itn");
QFile downloadarchivo("downloads.itn");
QFile songsarchivo("songs.itn");

QDataStream out(&codigoarchivo);
QDataStream in(&codigoarchivo);
QDataStream insongs(&songsarchivo);
QDataStream downloadin(&downloadarchivo);

ctunes::ctunes(){

    codigoarchivo.open(QIODevice::ReadWrite);
    downloadarchivo.open(QIODevice::ReadWrite);
    songsarchivo.open(QIODevice::ReadWrite);
    if(!codigoarchivo.isOpen()||!downloadarchivo.isOpen()||!songsarchivo.isOpen()){
        exit(0);
    }
    qint64 size = codigoarchivo.size();
    if(size==0 ){
        int codecancion = 1;
        int codedownload = 1;
        in << codecancion << codedownload;
    }
}

int ctunes::getcodigo(long offset){
        codigoarchivo.seek(offset);
        int tempcodesong;
        out >> tempcodesong;
        codigoarchivo.seek(offset);
        int suma = tempcodesong+1;
        in << suma;
        if(offset==0){
            codigosaves=tempcodesong;
        }
        return tempcodesong;

}


void ctunes::addSong(string nombre, string cantante, GenerosMusicales::Genero generoCantante, double precio, int duracion){

    string genero;
    switch (generoCantante) {
    case GenerosMusicales::GENERO_DANCE:
        genero = "Dance";
        break;
    case GenerosMusicales::GENERO_ELECTRONICA:
        genero = "Electronica";
        break;
    case GenerosMusicales::GENERO_POP:
        genero = "pop";
        break;
    case GenerosMusicales::GENERO_RANCHERA:
        genero = "Ranchra";
        break;
    case GenerosMusicales::GENERO_RAP:
        genero = "Rap";
        break;
    case GenerosMusicales::GENERO_REGGAE:
        genero = "Reggae";
        break;
    case GenerosMusicales::GENERO_ROCK:
        genero = "rock";
        break;
    }
    cancion nuevacancion;
    songsarchivo.seek(songsarchivo.size());
    nuevacancion.code = getcodigo(0);
    nuevacancion.nombre = QString::fromStdString(nombre);
    nuevacancion.cantante= QString::fromStdString(cantante);
    nuevacancion.genero= QString::fromStdString(genero);
    nuevacancion.precio=precio;
    nuevacancion.reviews=0;
    nuevacancion.estrellas=0;
    nuevacancion.duracion = duracion;
    insongs << nuevacancion.code << nuevacancion.nombre << nuevacancion.cantante << nuevacancion.genero << nuevacancion.precio << nuevacancion.reviews << nuevacancion.estrellas <<nuevacancion.duracion;

}
string ctunes::downloadSong(int codeSong, string cliente){

    songsarchivo.seek(0);
    while (!songsarchivo.atEnd()) {
        qDebug() << "entre1";
        cancion nuevacancion;
        insongs >> nuevacancion.code >> nuevacancion.nombre >> nuevacancion.cantante >> nuevacancion.genero >> nuevacancion.precio >> nuevacancion.reviews >> nuevacancion.estrellas >> nuevacancion.duracion;
        if (nuevacancion.code == codeSong) {

            qDebug() << "entre2";
            QDate currentDate = QDate::currentDate();
            QString stringDate = currentDate.toString("dd-MM-yyyy");

            descarga nuevadecarga;
            downloadarchivo.seek(downloadarchivo.size());
            nuevadecarga.codedown = getcodigo(4);
            nuevadecarga.fecha = stringDate;
            nuevadecarga.codesong=nuevacancion.code;
            nuevadecarga.cliente = QString::fromStdString(cliente);
            nuevadecarga.precio=nuevacancion.precio;
            downloadin << nuevadecarga.codedown << QString::fromStdString(nuevadecarga.fecha.toStdString())<< nuevadecarga.codesong << nuevadecarga.cliente << nuevadecarga.precio;

            return "GRACIAS " + nuevadecarga.cliente.toStdString()+ " por bajar " + nuevacancion.nombre.toStdString() +" a un costo de Lps. " + QString::number(nuevadecarga.precio).toStdString();
            break;
        }

    }
    return "no se encontro la cancion";
}
QString ctunes::songs(string txtFile){
    QString path = QString::fromStdString(txtFile+".txt");
    QFile file(path);
    QTextStream out(&file);

    file.open(QIODevice::ReadWrite);
    file.resize(0);

    songsarchivo.seek(0);
      while (!songsarchivo.atEnd()) {
        cancion nuevacancion;
          insongs >> nuevacancion.code >> nuevacancion.nombre >> nuevacancion.cantante >> nuevacancion.genero >> nuevacancion.precio >> nuevacancion.reviews >> nuevacancion.estrellas >> nuevacancion.duracion;
        file.seek(file.size());
          if(nuevacancion.reviews!=0){
          out << "|codigo:  " << nuevacancion.code << " | Nombre: " << nuevacancion.nombre << " | cantante: "<< nuevacancion.cantante << " | genero musical: "<< nuevacancion.genero << " | Precio de la cancion: " << nuevacancion.precio << "|TIEMPO: " << QString::number(nuevacancion.duracion/3600)<<":"<<QString::number(((nuevacancion.duracion%3600)/60))<<":"<<QString::number((nuevacancion.duracion%60))<< " | Rating: " << QString::number((nuevacancion.estrellas/nuevacancion.reviews))<< "|\n\n\n";
          }else{
          out << "|codigo:  " << nuevacancion.code << " | Nombre: " << nuevacancion.nombre << " | cantante: "<< nuevacancion.cantante << " | genero musical: "<< nuevacancion.genero << " | Precio de la cancion: " << nuevacancion.precio << "|TIEMPO: " << QString::number(nuevacancion.duracion/3600)<<":"<<QString::number(((nuevacancion.duracion%3600)/60))<<":"<<QString::number((nuevacancion.duracion%60))<< " | Rating: " << QString::number(nuevacancion.estrellas)<< "|\n\n\n";
          }
    }
      file.close();
      file.open(QIODevice::ReadOnly);
      file.seek(0);
      QString text = out.readAll();
      qDebug() << text;
      return text;
}

string ctunes::infoSong(int codeSong) {
    songsarchivo.seek(0);
    int numerodescargas=0;
    string textoconcatenado;
    while (!songsarchivo.atEnd()) {
    cancion nuevacancion;
        insongs >> nuevacancion.code >> nuevacancion.nombre >> nuevacancion.cantante >> nuevacancion.genero >> nuevacancion.precio >> nuevacancion.reviews >> nuevacancion.estrellas >> nuevacancion.duracion;
        if (nuevacancion.code == codeSong) {
            downloadarchivo.seek(0);
         while (!downloadarchivo.atEnd()) {
        descarga nuevadecarga;
        downloadin >> nuevadecarga.codedown >> nuevadecarga.fecha >> nuevadecarga.codesong >> nuevadecarga.cliente >> nuevadecarga.precio;
        if(codeSong==nuevadecarga.codesong){
            numerodescargas+=1;

            textoconcatenado = textoconcatenado+"\n--------------------------------\nCodigo de descarga: " + QString::number(nuevadecarga.codedown).toStdString() + "\nfecha de descarga: " + nuevadecarga.fecha.toStdString()+ "\nCodigo de la cancion: "+QString::number(nuevadecarga.codesong).toStdString()+"\nNombre Cliente: "+nuevadecarga.cliente.toStdString()+ "\nPrecio de compra: "+QString::number(nuevadecarga.precio).toStdString();
        }
        }
         if(nuevacancion.reviews!=0){
         double ratin =nuevacancion.estrellas/nuevacancion.reviews;
         return "Codigo: " + QString::number(nuevacancion.code).toStdString() + "\nCancion: " + nuevacancion.nombre.toStdString() + "\ncantante: " + nuevacancion.cantante.toStdString() + "\nGenero: " + nuevacancion.genero.toStdString() + "\nPrecio: " +QString::number(nuevacancion.precio).toStdString() + "\nreviews: "+QString::number(nuevacancion.reviews).toStdString()+ "\nEstrellas: "+QString::number(nuevacancion.estrellas).toStdString()+"\nRating: "+ QString::number(ratin).toStdString()+"\nNumero de descargas: "+ QString::number(numerodescargas).toStdString()+ "\nDuracion: " +  QString::number(nuevacancion.duracion/3600).toStdString()+":"+QString::number(((nuevacancion.duracion%3600)/60)).toStdString()+":"+QString::number((nuevacancion.duracion%60)).toStdString()+ textoconcatenado;
         }else{
         return "Codigo: " + QString::number(nuevacancion.code).toStdString() + "\nCancion: " + nuevacancion.nombre.toStdString() + "\ncantante: " + nuevacancion.cantante.toStdString() + "\nGenero: " + nuevacancion.genero.toStdString() + "\nPrecio: " +QString::number(nuevacancion.precio).toStdString() + "\nreviews: "+QString::number(nuevacancion.reviews).toStdString()+ "\nEstrellas: "+QString::number(nuevacancion.estrellas).toStdString()+"\nRating: "+ QString::number(nuevacancion.estrellas).toStdString()+"\nNumero de descargas: "+ QString::number(numerodescargas).toStdString()+ "\nDuracion: " +  QString::number(nuevacancion.duracion/3600).toStdString()+":"+QString::number(((nuevacancion.duracion%3600)/60)).toStdString()+":"+QString::number((nuevacancion.duracion%60)).toStdString()+ textoconcatenado;
         }
         }
         }
    return "no se encontro";
}
int ctunes::codigosave(){
    return codigosaves;
}

void ctunes::reviewSong(int code, int stars){
    songsarchivo.seek(0);
    int reviewCont;
    while (!songsarchivo.atEnd()) {
        cancion nuevacancion;
        insongs >> nuevacancion.code >> nuevacancion.nombre >> nuevacancion.cantante >> nuevacancion.genero >> nuevacancion.precio >> nuevacancion.reviews >> nuevacancion.estrellas >> nuevacancion.duracion;
        reviewCont=nuevacancion.reviews+1;
        if (nuevacancion.code == code) {
            if(stars>=0 && stars<=5){
            songsarchivo.seek(songsarchivo.pos()-12);
                insongs << reviewCont << stars+nuevacancion.estrellas << nuevacancion.duracion;
            break;
            }
        }
    }
}
