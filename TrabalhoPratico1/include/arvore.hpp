#include <string>
template<typename T> 
#pragma once
class ArvoreBinaria
{
    protected:
        // struct No que será o No da arvore binária
        struct No{
            public:
            No(): esq(nullptr), dir(nullptr){};
            T getItem(){
                return item;
            }
            void putItem(T item){
                this->item = item;
            }
            No* getEsq(){
                return esq;
            }
            No* getDir(){
                return dir;
            }
            void putEsq(No* esq){
                this->esq = esq;
            }
            void putDir(No* dir){
                this->dir = dir;
            }
            public:
            T item;
            No *esq;
            No *dir;
            friend class ArvoreBinaria;
        };
    public: 
        ArvoreBinaria() : raiz(nullptr){};
        ~ArvoreBinaria(){
            Limpa();
        };

        virtual void Insere(T item){
            InsereRecursivo(raiz, item);
        };
        virtual void Limpa(){
            ApagaRecursivo(raiz);
            raiz = nullptr;
        };

    protected:
        void InsereRecursivo(No* &p, T item){
            if(p==nullptr){
                p = new No();
                p->item = item;
            } else {
                if(item < p->getItem()){
                    InsereRecursivo(p->esq, item);
                } else {
                    InsereRecursivo(p->dir, item);
                }
            }
        };

        void ApagaRecursivo(No* p){
            if(p!= nullptr){
                ApagaRecursivo(p->esq);
                ApagaRecursivo(p->dir);
                delete p;
            }
        };
        void PorNivel();
        void PreOrdem(No* p){
            if(p != nullptr){
                std::cout << p->getItem() << std::endl;
                PreOrdem(p->esq);
                PreOrdem(p->dir);
            }
        };
        void InOrdem(No* p){
            if(p != nullptr){
                InOrdem(p->esq);
                std::cout << p->getItem() << std::endl;
                InOrdem(p->dir);
            }
        };
        void PosOrdem(No* p){
            if(p != nullptr){
                PosOrdem(p->esq);    
                PosOrdem(p->dir);
                std::cout << "valor do item: " <<p->getItem() << std::endl;
            }
        };

        No *raiz;

};