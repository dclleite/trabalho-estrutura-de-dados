/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Registro e Controle de Pessoas em um Determinado Local.
 * TabelaHash.cpp - Arquivo referente à estrutura Hash.
*/
#include "TabelaHash.h"
#include "Noh.h"
#include "Arduino.h"

typedef int Dado;

int Func1(int chave){ // Primeira parte da funçao que calcula hash.
  int h = (2*((chave-(chave%10))/10)) % 10;
  return h;
}

int Func2(int chave){ // Segunda e ultima etapa, que calcula o hash.
  int  k = (chave%10)-1;
  return k;
}

int TabelaHash::Posicao(int chave){ // Metodo final que faz a junçao das anteriores para calcular o hash final.
  int pos = Func1(chave) + Func2(chave);
  return pos;
}

int TabelaHash::DivideChave(Dado chave){ // Pega os valores primordiais da matricula para o calculo do hash (segundo e terceiro digitos da matricula).
    int k = chave % 10000;
    k = k/100;
    return k;
}

TabelaHash::TabelaHash(int cap){ // Construtor da tabela Hash.
  elementos = new Noh*[cap];
  capacidade = cap;
  tamanho = 0;
  for(int i = 0; i < cap; i++){
    elementos[i] = nullptr;
  }
}

TabelaHash::~TabelaHash(){ // Destrutor da tabela Hash.
  for(int i = 0; i < capacidade; i++){
    Noh* atual = elementos[i];
    while(atual != nullptr){
      Noh* aux = atual;
      atual = atual->proximo;
      delete aux;
    }
  }
  delete[] elementos;
}
  
void TabelaHash::Inserir(Dado c, int v, int hash){
  if(Recuperar(c, hash) == -1){ // checa se o usuario nao existe no sistema.
    Noh* novo = new Noh(c, v);
    if(elementos[hash] == nullptr){ // primeira posicao do vetor nula.
      elementos[hash] = novo;
      Serial.println("\nUSUARIO INSERIDO COM SUCESSO \n");
    }
    else{ // posicao ocupada, encontra a proxima posicao nula.
      Noh* atual = elementos[hash];
      while(atual->proximo != nullptr){
        atual = atual->proximo;
      }
      atual->proximo = novo;
      Serial.println("\nUSUARIO INSERIDO COM SUCESSO \n");
    } 
    tamanho++;
  }
  else{ // matricula ja cadastrada.
    Serial.println("Falha na insercao, matricula ja cadastrada!");
  }
}

int TabelaHash::Recuperar(Dado c, int hash){
  if((elementos[hash] != nullptr ) and (elementos[hash]->matricula == c)){ // testa se a posicao nao e nula, e se a matricula buscada é a mesma na primeira posicao.
    return elementos[hash]->creditos;
  }
  else{ // primeira matricula da posicao nao e a desejada, percorre a lista.
    Noh* atual = elementos[hash];
    while((atual != nullptr) and (atual->matricula != c)){ // percorre enquanto a lista nao for nula, e ate encontrar a matricula desejada.
      atual = atual->proximo;
    }
    if((atual != nullptr) and (atual->matricula == c)){ // encontrou a matricula, retorna quantidade de creditos.
      return atual->creditos;
    }
    else{ //matricula nao encontrada
      return -1;
    }
  }
}

void TabelaHash::Remover(Dado c, int hash){
  if((elementos[hash] != nullptr) and (elementos[hash]->matricula == c)){ // matricula buscada e a primeira da posicao, deleta matricula.
    Noh* removido = elementos[hash];
    elementos[hash] = elementos[hash]->proximo;
    Serial.print("\nMATRICULA ");
    Serial.print(removido->matricula);
    delete removido;
    Serial.println("DELETADA COM SUCESSO \n");
    tamanho--;
  }
  else{ //matricula nao e a primeira, percorre a lista.
    Noh* atual = elementos[hash];
    Noh* anterior;
    while((atual != nullptr) and (atual->matricula != c)){ // enquanto o atual for diferente de nulo, e a matricula diferente da buscada, recebe proxima matricula.
      anterior = atual;
      atual = atual->proximo;
    }
    if((atual != nullptr) and (atual->matricula == c)){ //encontrou a matricula, agora deleta.
      anterior->proximo = atual->proximo;
      Serial.print("\nMATRICULA ");
      Serial.print(atual->matricula);
      delete atual;
      tamanho--;
      Serial.println(" DELETADA COM SUCESSO \n");
    }
    else{ // matricula nao encontrada
      Serial.println("Falha na remocao, matricula nao encontrada!");
    }
  }
}

void TabelaHash::Percorrer(){ // imprime todos os usuarios, em suas respectivas posicoes, com matricula e quantidade de creditos.
  Noh* atual;
  for(int i = 0; i < 10; i++){
    Serial.print(i);
    Serial.print(":");
    atual = elementos[i];
    while(atual != nullptr){
      Serial.print("[");
      Serial.print(atual->matricula);
      Serial.print("/");
      Serial.print(atual->creditos);
      Serial.print("]->");
      atual = atual->proximo;
    }
    Serial.println("NULL " );
  }
  Serial.print("Quantidade de usuarios cadastrados: ");
  Serial.println(tamanho );
}
