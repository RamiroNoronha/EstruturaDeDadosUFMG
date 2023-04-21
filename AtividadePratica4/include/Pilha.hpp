#include "Fila.hpp"

class Pilha{
    public:
    Pilha();
    bool pilhaVazia();
    void empilha(int valor);
    int desempilha();
    void imprimir();

    private:
    Fila filaPadrao;
    Fila filaReferencia;
};