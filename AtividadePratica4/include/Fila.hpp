#include <iostream>

using namespace std;

class Fila{
	public:
		Fila();
		bool filavazia();
		void adiciona(int valor);
		int remove();
		int tamanh();
		void limpa();
		void imprimir();
		~Fila();
		
	private:
		static const int MAXTAM = 10;
		int tamanho = 0;
		int vet[MAXTAM];
		int inicio = 0;
		int prox = 0;
};
