#include <string>
template<typename T> 
#pragma once
class ArvoreBinaria
{
    protected:
        // struct No que representará o no da arvore binária
        struct No{
            public:
            No(): esq(nullptr), dir(nullptr){};
            T getItem(){
                return item;
            }
            void putItem(T item){
                this->item = item;
            }
            No *esq;
            No *dir;
            private: 
            T item;
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
        // Método dado em aula de inserir de forma recursiva
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
        // Método dado em aula que apaga todos os elementos da árvore
        void ApagaRecursivo(No* p){
            if(p!= nullptr){
                ApagaRecursivo(p->esq);
                ApagaRecursivo(p->dir);
                delete p;
            }
        };
        void PorNivel();
        // Método dado em aula de imprimir a arvore PreOrdem
        void PreOrdem(No* p){
            if(p != nullptr){
                std::cout << p->getItem() << std::endl;
                PreOrdem(p->esq);
                PreOrdem(p->dir);
            }
        };
        // Método dado em aula de imprimir a arvore InOrdem
        void InOrdem(No* p){
            if(p != nullptr){
                InOrdem(p->esq);
                std::cout << p->getItem() << std::endl;
                InOrdem(p->dir);
            }
        };
        // Método dado em aula de imprimir a arvore PosOrdem
        void PosOrdem(No* p){
            if(p != nullptr){
                PosOrdem(p->esq);    
                PosOrdem(p->dir);
                std::cout << "valor do item: " <<p->getItem() << std::endl;
            }
        };
        // Raiz da arvore
        No *raiz;

};