/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Registro e Controle de Pessoas em um Determinado Local
 * TabelaHash.h - Arquivo referente à estrutura Hash
*/
#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "Noh.h"
typedef int Dado;

class TabelaHash{ // definiçao da classe tabelaHash com todos os metodos e atributos, privados e publicos.
  private:
    Noh** elementos;
    int capacidade;
    int tamanho;
  public:
    TabelaHash(int cap = 100);
    ~TabelaHash();
    void Inserir(Dado c, int v, int hash);
    int Recuperar(Dado c, int hash);
    void Remover(Dado c, int hash);
    void Percorrer();
    int Posicao(int chave);
    int DivideChave(Dado chave);
};
#endif
