
#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GenerosMusicales.h>
#include <qfile.h>

using namespace std;

class ctunes
{
public:
    ctunes();
    int getcodigo(long);
    void addSong(string, string, GenerosMusicales::Genero ,double);
    void reviewSong(int, int);
    string downloadSong(int , string );
    QString songs(string);
    string infoSong(int);

private:
    int codecancion = 1;
    int codedownload = 1;
};


#endif // CTUNES_H
