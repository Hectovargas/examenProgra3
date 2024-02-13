#include "ctunes.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GenerosMusicales.h>

using namespace std;

ctunes::ctunes(){
    codigoarchivo.open("codigos.itn");
    downloadarchivo.open("downloads.itn");
    songsarchivo.open("songs.itn");

    if(!codigoarchivo.is_open()||!downloadarchivo.is_open()||!songsarchivo.is_open()){
        exit(0);
        return;
    }
    streampos size= codigoarchivo.tellg();
    cout << size;
    if(size==0 ){
        int codecancion = 1;
        int codedownload = 1;
        codigoarchivo.write(reinterpret_cast<const char*>(&codecancion), sizeof(codecancion));
        codigoarchivo.write(reinterpret_cast<const char*>(&codedownload), sizeof(codedownload));
        downloadarchivo.write(reinterpret_cast<const char*>(&codedownload),sizeof(codecancion));
    }
}

int ctunes::getcodigo(long offset){

}
void ctunes::addSong(string nombre, string cantante, GenerosMusicales::Genero generoCantante, double precio){

}
void ctunes::downloadSong(int codeSong, string cliente){

}
void ctunes::songs(string txtFile){

}
void ctunes::infoSong(int codeSong){

}
void ctunes::reviewSong(int code, int stars){

}
