#include <string>
template<typename T> 
class ArvoreBinaria
{
    private:
        struct No{
            public:
            No(): esq(nullptr), dir(nullptr){};
            T getItem(){
                return item;
            }
            private:
            T item;
            No *esq;
            No *dir;
            friend class ArvoreBinaria;
        };
    public: 
        ArvoreBinaria() : raiz(nullptr){};
        ArvoreBinaria(std::string){
            
        }
        ~ArvoreBinaria(){
            Limpa();
        };

        void Insere(T item){
            InsereRecursivo(raiz, item);
        };
        void Caminha();
        void Limpa(){
            ApagaRecursivo(raiz);
            raiz = nullptr;
        };

    private:
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

        void InserePosFixa(T item)
        {

        }
        {

        }
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
            PosOrdem(p->esq);    
            PosOrdem(p->dir);
            std::cout << p->getItem() << std::endl;
        };

        No *raiz;

};