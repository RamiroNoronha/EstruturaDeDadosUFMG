#include <iostream>
#include "pilha.hpp"
#include "erro.hpp"
#include <string>
#include "arvoreposfixa.hpp"
#include "arvoreinfixa.hpp"

// Função que preenche uma ArvorePosFixa a partir da entrada
// # Parâmetros
// - texto: string que recebe a entrada em formato de texto
// - arvore: ArvorePosFixa que é passada por referência para guarda a expressão em formato pos fixada
void preencheArvorePosFixa(std::string texto, ArvorePosFixa<std::string> &arvore){
    int countOperador = 0; // conta a quantidade de operadores + - * / para verificar se a operação e consitente
    int countNumero = 0; // conta a quantidade de números para verificar se a operação e consistente
    std::string item; // item que será guardado na arvove - Pode ser operador ou um número.
    for(auto itr = texto.end()-1; itr != texto.begin() -1; itr--){ // texto lido de trás para frente para pegar a ultima operação a ser realizada
        if(*itr != ' '){
            item+= *itr;
            if(itr != texto.begin()){
                continue;
            }  
        }
        if(item != " " && item != ""){
            if(arvore.isOperador(item)){ // verifica se é um operador
                arvore.Insere(item);
                countOperador++;
            } else { // caso não seja operador, é um numéro que está escrito ao contrário
                std::string textoCorreto = "";
                for(int i = 1; textoCorreto.size() != item.size(); i ++){ // Ajeitando o número que estaria escrito de forma contrária
                    textoCorreto+= (*(item.end() - i));
                }
                arvore.Insere(textoCorreto);
                countNumero++;
            }
        item = "";
        }
    }
    if(countOperador != countNumero -1){ // Verifica se possui uma quantidade válida de operadores
        arvore.Limpa();
        throw Erro("Quantidade de operadores inválida");
    }
    if(!arvore.arvoreValida()){ // Verifica se a arvore formada é valida
        arvore.Limpa();
        throw Erro("Ordem dos operadores inválida");
    }
 }

 // Função que preenche uma ArvoreInFixa a partir da entrada e de forma recursiva
// # Parâmetros
// - texto: string que recebe a entrada em formato de texto
// - arvore: ArvoreInFixa que é passada por referência para guarda a expressão em formato infixo
// - countOperador: conta a quantidade de operadores + - * / para verificar se a operação e consitente
// - countNumero: conta a quantidade de números para verificar se a operação e consistente
void preencherArvoreInfixaRecursivo(std::string texto, ArvoreInFixa<std::string> &arvore, int &countOperador, int &countNumero){
    int count = 0; // Contador de parenteses para encontrar a operação central em relação a um par abre fecha parenteses ou valores
    int posIni = 0; // Posição inicial da expressão
    for(int i = posIni; i < texto.size(); i++){ // for que caminha pela expressão toda
        if(texto[i] == '('){ // Caso seja um abre parenteses, irá incrementar
            if(count == 1){ // Quando tiver contado um abre parenteses, estará dentro de uma operação fechada 
                posIni = i;
            }
            count++;
        }
        if(texto[i] == ')'){ // Caso seja um fecha parenteses, irá decrementar
            count--;
        }
        if(count == 1 && i != posIni && texto[i] != '(' && texto[i] != ')' && texto[i] != ' '){ // Só entrará nesse if se encontrar um numero ou operador que esteja dentro de uma operação fechada  
            std::string valor = "";
            valor+=texto[i];
            if(arvore.isOperador(valor) && texto[i+1] == ' ' && texto[i-1] == ' '){ // Verifica se é um operador, caso seja, produra os valores ou expressões a esquerda e a direita
                arvore.Insere(valor);
                countOperador++;
                preencherArvoreInfixaRecursivo(texto.substr(posIni, i - posIni), arvore, countOperador, countNumero);
                preencherArvoreInfixaRecursivo(texto.substr(i + 1), arvore, countOperador, countNumero);
            } else if(texto[i+1] == ' ') {  // Entra se for um número que esteja escrito ao contrário
                std::string valorCorreto = "";
                int k = i;
                while(texto[k-1] != ' '){
                    k--;
                }
                while(texto[k] != ' '){
                    valorCorreto+=texto[k];
                    k++;
                }
                arvore.Insere(valorCorreto);
                countNumero++;
                break;
            } else if(texto[i-1] == ' '){ // Entra se for um número que esteja escrito de forma normal
                std::string valorCorreto = "";
                int k = i;
                for(; texto[k] != ' ' ; k ++){
                    valorCorreto+= texto[k];
                }
                arvore.Insere(valorCorreto);
                countNumero++;
                break;
            }
            
        }
    }
}
// Função que preencher uma ArvoreInfixa 
// # Parâmetros
// - texto: string que recebe a entrada em formato de texto
// - arvore: ArvoreInFixa que é passada por referência para guarda a expressão em formato infixo
void preencherArvoreInfixa(std::string texto, ArvoreInFixa<std::string> &arvore){
    int countOperador = 0; // conta a quantidade de operadores + - * / para verificar se a operação e consitente
    int countNumero = 0; // conta a quantidade de números para verificar se a operação e consistente
    preencherArvoreInfixaRecursivo(texto, arvore, countOperador, countNumero);
    if(countOperador != countNumero -1){ // Verifica se possui uma quantidade válida de operadores
        std::cout << "quantidade operadores: " << countOperador << " quantidade numeros: " << countNumero << std::endl;
        arvore.Limpa();
        throw Erro("Quantidade de operadores inválida");
    }
    if(!arvore.arvoreValida()){ // Verifica se a arvore formada é valida
        arvore.Limpa();
        throw Erro("Ordem dos operadores inválida");
    }
}




int main() {


    // try{
    //     std::string texto = " 2 + - 4 3";
    //     ArvorePosFixa<std::string> minhaArvore;
    //     preencheArvorePosFixa(texto, minhaArvore);
    //     std::string notacao = minhaArvore.TranformarEmInFixa();
    //     std::cout << notacao << std::endl;
    //     double resultado = minhaArvore.calcularResultado();
    //     std::cout << "valor resultado: " << resultado << std::endl;
    // } catch(Erro erro){
    //     std::cout << erro.getMessage() << std::endl;
    // } catch(...){
    //     std::cout << "Erro desconhecido" << std::endl;
    // }


    try{
        std::string textoNovo = "( ( ( ( 2.071122 ) + ( ( ( 1.036112 ) / ( 9.212616 ) ) * ( ( 7.151603 ) * ( 2.203524 ) ) ) ) / ( ( ( 9.007030 ) + ( 2.889450 ) ) - ( 1.554032 ) ) ) * ( ( 3.186413 ) / ( 7.180392 ) ) )";
        ArvoreInFixa<std::string> arvoreInfixa;
        preencherArvoreInfixa(textoNovo, arvoreInfixa);
        std::string resultado = arvoreInfixa.TranformarEmPosFixa();
        std::cout << "meu resultado " << resultado << std::endl;
        double valor = arvoreInfixa.calcularResultado();
        std::cout << "valor: " << valor << std::endl;
    } catch(Erro erro){
        std::cout << erro.getMessage() << std::endl;
    } catch(...){
        std::cout << "Erro desconhecido" << std::endl;
    }

}


