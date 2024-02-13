
#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GenerosMusicales.h>

using namespace std;

class ctunes
{
public:
    ctunes();
    int getcodigo(long);
    void addSong(string, string, GenerosMusicales::Genero ,double);
    void reviewSong(int, int);
    void downloadSong(int , string );
    void songs(string);
    void infoSong(int);
    fstream codigoarchivo;
    fstream downloadarchivo;
    fstream songsarchivo;
};

#endif // CTUNES_H
