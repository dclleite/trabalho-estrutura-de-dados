/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Registro e Controle de Pessoas em um Determinado Local
 * Noh.h - Arquivo referente ao Nó
*/
#ifndef NOH_H
#define NOH_H

typedef int Dado;

class Noh{ // definiçao da classe nó com todos os metodos e atributos, privados e publicos.
  friend class TabelaHash;
  private:
    Dado matricula;
    int creditos;
    Noh* proximo;
  public:
    Noh(Dado c, int v);
};
#endif
