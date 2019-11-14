/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Registro e Controle de Pessoas em um Determinado Local
 * Noh.h - Arquivo referente ao Nó
*/
#include "Noh.h"

typedef int Dado;

Noh::Noh(Dado c, int v){ // construtor do nó
  matricula = c;
  creditos = v;
  proximo = nullptr;
}
