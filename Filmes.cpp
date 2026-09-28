#include "Filmes.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

int parse(const string& s) { // Validado
    int x = 0;
    string numeros = s.substr(2);
    for (char c : numeros)
        x = x * 10 + (c - '0');
    return x;
}   

int hashID(string id){
    return (parse(id)/2)-3958759;
}

void distribuiGenero(string genero, int id, vector<string>& listaGeneros, vector<vector<int>>& listaFilmesdeGenero){
    int p = -1;
    for(int i = 0; i < listaGeneros.size(); i++){
        if(!listaGeneros[i].compare(genero)){
            p = i;
            break;
        }
    }
    if(p == -1){
        listaGeneros.push_back(genero);
        vector<int> novoGenero;
        listaFilmesdeGenero.push_back(novoGenero);
        p = (int)listaGeneros.size()-1;
    }
    listaFilmesdeGenero[p].push_back(id);
}

bool carregaFilmes(vector<Filmes> &listaFilmes, vector<string> &listaGeneros, vector<vector<int>>& listaFilmesdeGenero, vector<int>& listaFilmesHash){ // Vector em referência 
    string linha, termos;
    ifstream myfile (NOMEARQUIVOFILMES);
    if(myfile.is_open()){
        cout << "Aberto com sucesso" << endl;
        getline(myfile, linha); // Pula a primeira linha do arquivo
        while(getline(myfile, linha)){
            if(!linha.empty() && linha.back() == '\r'){
                linha.pop_back();
            }
            stringstream ss(linha);
            Filmes filme;
            getline(ss, termos, '\t'); //chamar HashId para guardar com Hash e criar novo vetor int de tamanho max, usando o indice da lista filmes como indice e o int guardado como hash.
            filme.id = hashID(termos);
            listaFilmesHash.push_back(hashID(termos));
            getline(ss, termos, '\t');
            filme.tipo = termos;

            getline(ss, termos, '\t');
            filme.primeiroTitulo = termos;

            getline(ss, termos, '\t');
            filme.tituloOriginal = termos;

            getline(ss, termos, '\t');
            if (termos == "1") {
                filme.ehAdulto = true;
            } 
            else {
                filme.ehAdulto = false;
            }
            getline(ss, termos, '\t');
            try {
                filme.anoInicio = std::stoi(termos);
            } 
            catch (const std::invalid_argument&) {
                filme.anoInicio = -1;
            } 
            getline(ss, termos, '\t');
            try {
                filme.anoFim = std::stoi(termos);
            } 
            catch (const std::invalid_argument&) {
                filme.anoFim = -1;
            } 
            getline(ss, termos, '\t');
            try {
                filme.tempoDuracao = std::stoi(termos);
            } 
            catch (const std::invalid_argument&) {
                filme.tempoDuracao = -1;
            } 
            getline(ss, termos, '\t');
            stringstream ss1(termos);
            while(getline(ss1, termos, ',')){
                filme.generos.push_back(termos);
                distribuiGenero(termos, (int)listaFilmes.size(), listaGeneros, listaFilmesdeGenero);
            }

            listaFilmes.push_back(filme);
        }
    } else {
        cout << "Problema ao abrir o arquivo" << endl;
        return false;
    }
    return true;
}

bool carregaCinemas(vector<Cinemas> &listaCinemas){
    string linha, termos;
    ifstream myfile(NOMEARQUIVOCINEMAS);

    if(myfile.is_open()){
        cout << "cinemas.txt - Aberto com sucesso" << endl;
        getline(myfile, linha); // Pula o cabeçalho
        
        while(getline(myfile, linha)){
            if(!linha.empty() && linha.back() == '\r'){
                linha.pop_back();
            }

            stringstream ss(linha);
            Cinemas cinema;

            getline(ss, termos, ',');
            cinema.id = hashID(termos);

            getline(ss, termos, ',');
            if(!termos.empty() && termos[0] == ' ') termos.erase(0, 1);
            cinema.nomeCinema = termos;
            LOG(cinema.nomeCinema);

            getline(ss, termos, ',');
            if(!termos.empty() && termos[0] == ' ') termos.erase(0, 1);
            cinema.coordX = std::stoi(termos);

            getline(ss, termos, ',');
            if(!termos.empty() && termos[0] == ' ') termos.erase(0, 1);
            cinema.coordY = std::stoi(termos);

            getline(ss, termos, ',');
            if(!termos.empty() && termos[0] == ' ') termos.erase(0, 1);
            cinema.precoIngresso = std::stoi(termos);

            while(getline(ss, termos, ',')){
                if(!termos.empty() && termos[0] == ' ') termos.erase(0, 1);
                
                if(!termos.empty()){
                    int idFilme = hashID(termos);
                    cinema.filmesExibicao.push_back(idFilme);
                }
            }
            listaCinemas.push_back(cinema);
        }
        myfile.close();
        return true;
    } else {
        cout << "Problema ao abrir o arquivo cinemas.txt" << endl;
        return false;
    }
}

void imprimeFilme(const Filmes& filme){
    cout << "ID: " << filme.id << "| ";
    cout << "Tipo: " << filme.tipo << "| ";
    cout << "Primeiro Titulo: " << filme.primeiroTitulo << "| ";
    cout << "Titulo Original: " << filme.tituloOriginal << "| ";
    cout << "Eh Adulto: " << filme.ehAdulto << "| ";
    cout << "Ano Inicio: " << filme.anoInicio << "| ";
    cout << "Ano Fim: " << filme.anoFim << "| ";
    cout << "Tempo Duracao: " << filme.tempoDuracao << "| ";
    cout << "Generos: ";
    for(int j = 0; j < filme.generos.size(); j++){
        cout << ", " << filme.generos[j];
    }
    cout << endl;
    cout << endl;
    }

void imprimeFilmes(const vector<Filmes>& filmes){
    if(filmes.size() < 1){
        cout << "Nenhum filme encontrado!" << endl;
    }
    for(const Filmes& f : filmes){
        if(f.id == 0) continue;
        cout << f.id << " | " << f.tipo << " | " << f.primeiroTitulo
             << " | " << f.anoInicio << " | ";
        for(size_t i = 0; i < f.generos.size(); i++)
            cout << (i ? ", " : "") << f.generos[i];
        cout << "\n";
    }
    cout << "\n";
}

void filtroGenero(string genero, const vector<string>& listaGeneros, const vector<vector<int>>&listaFilmesdeGenero, const vector<Filmes>& listaFilmes){
    if(listaGeneros.size() != listaFilmesdeGenero.size()){
        cout<<"Tamanhos diferentes";
        return;
    }
    system("clear");
    for(int i = 0; i < listaGeneros.size(); i++){
        if(!listaGeneros[i].compare(genero)){
            for(int j = 0; j < listaFilmesdeGenero[i].size(); j++){
                if(listaFilmes[listaFilmesdeGenero[i][j]].id == 0) continue;
                imprimeFilme(listaFilmes[listaFilmesdeGenero[i][j]]);
            }
            return;
        }
    }
    cout << "Filmes do gênero: " + genero + " não encontrados!"<<endl;
}

void idsGenero(const vector<string>& listaGeneros, const vector<vector<int>>&listaFilmesdeGenero){
    getchar();
    for(int i = 0; i < listaGeneros.size(); i++){
        cout << listaGeneros[i] + ": " << endl;
        getchar();
        for(int j = 0; j < listaFilmesdeGenero[i].size(); j++){
            cout << ", " << listaFilmesdeGenero[i][j]; 
        }
    }
}

void menu(vector<Filmes>& listaFilmes, vector<string>& listaGeneros, vector<vector<int>>& listaFilmesdeGenero, vector<Cinemas>& listaCinemas, vector<int>& listaFilmesHash){
    int opcao, conxt = 1;
    string genero;
    while(conxt != 0){    
        cout << "1. Carregar banco de dados\n";
        cout << "2. Buscar por genero\n";
        cout << "3. Listar filmes\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";
        cin >> opcao;
        switch(opcao){
            case 1:
                system("clear");
                carregaFilmes(listaFilmes, listaGeneros, listaFilmesdeGenero, listaFilmesHash);
                carregaCinemas(listaCinemas);
                break;
            case 2:
                system("clear");
                cout << "Insira o gênero: \n";
                cin >> genero;
                filtroGenero(genero, listaGeneros, listaFilmesdeGenero, listaFilmes);
                break;
            case 3:
                system("clear");
                imprimeFilmes(listaFilmes);
                break;
            case 4:
                system("clear");
                idsGenero(listaGeneros, listaFilmesdeGenero);
                break;
            case 0:
                system("clear");
                cout << "Encerrando...";
                conxt = 0;
                break;
        }
    }
}   