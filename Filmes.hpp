#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#define NOMEARQUIVOFILMES "doppelfilmesCrop.txt"
#define NOMEARQUIVOCINEMAS "cinemas(1).txt"
#define LOG(var) std::cout << #var << " = " << var << "\n"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"   

class Filmes{
    public:
        int id;
        string tipo;
        string primeiroTitulo;
        string tituloOriginal;
        bool ehAdulto;
        int anoInicio;
        int anoFim;
        int tempoDuracao;
        vector<string> generos;
};

class Cinemas{
    public:
    int id;
    string nomeCinema;
    double coordX;
    double coordY;
    float precoIngresso;
    vector<int> filmesExibicao;
    /*Cinema_ID, Nome_do_Cinema, Coordenada_X, Coordenada_Y, Preço_Ingresso, Filmes_Em_Exibição/*/
};
int parse(const string& s);
int hashID(string id);
void distribuiGenero(string genero, int id, vector<string>& listaGeneros, vector<vector<int>>& listaFilmesdeGenero);
bool carregaFilmes(vector<Filmes> &listaFilmes, vector<string> &listaGeneros, vector<vector<int>>& listaFilmesdeGenero, vector<int>& listaFilmesHash);
bool carregaCinemas(vector<Cinemas> &listaCinemas);
void imprimeFilme(const Filmes& filme);
void imprimeFilmes(const Filmes& filme);
void filtroGenero(string genero, const vector<string>& listaGeneros, const vector<vector<int>>&listaFilmesdeGenero, const vector<Filmes>& listaFilmes);
void idsGenero(const vector<string>& listaGeneros, const vector<vector<int>>&listaFilmesdeGenero);
void menu(vector<Filmes> &listaFilmes, vector<string> &listaGeneros, vector<vector<int>>& listaFilmesdeGenero, vector<Cinemas>& listaCinemas, vector<int>& listaFilmesHash);