#include"erro.hpp"
#include<string>
#include<iostream>
#pragma once

template<typename T> 
class Pilha {
    private:
        struct Celula{
            public:
            Celula(): prox(nullptr) {};
            private:
            T item;
            Celula *prox;
            friend class Pilha<T>;
        };
    public:
        Pilha() : tamanho(0), topo(nullptr) {};
        int getTamanho(){return tamanho;};
        bool vazia(){return getTamanho() == 0;};
        void empilha(T item){
            Celula *novoTopo = new Celula();
            novoTopo->item = item;
            novoTopo->prox = topo;
            topo = novoTopo;
            tamanho++;

        };
        T desempilha(){
            if(vazia()){
                Erro erro("Erro: A pilha está vazia!");
                throw erro;
            }
            T aux;
            Celula *antigoTopo;
            aux = topo->item;
            antigoTopo = topo;
            topo = topo->prox;
            delete antigoTopo;
            tamanho--;
            return aux;
        };
        void imprimirPilha(){
            for(auto pointer = topo; pointer != nullptr; pointer=pointer->prox){
                std::cout<< pointer->item << std::endl;
            }
        }
        ~Pilha(){
            while(!vazia()){
                desempilha();
            }
        }
    protected:
        int tamanho;
    private:  
        Celula *topo;

};

