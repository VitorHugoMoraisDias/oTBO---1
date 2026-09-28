#include "Filmes.cpp"
#include <iostream>
using namespace std;

#define TAM_MAX 8722
#define TAM_MAX_CINE 400

int main(){
    vector<Filmes> listaFilmes(TAM_MAX);
    vector<Cinemas> listaCinemas(TAM_MAX_CINE);
    vector<string> listaGeneros;
    vector<vector<int>> listaFilmesdeGenero;
    vector<int> listaFilmesHash(TAM_MAX);
    menu(listaFilmes, listaGeneros, listaFilmesdeGenero, listaCinemas, listaFilmesHash);
}