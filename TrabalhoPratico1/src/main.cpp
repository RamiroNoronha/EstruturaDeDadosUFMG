#include <iostream>
#include "pilha.hpp"
#include "erro.hpp"
#include <string>
#include "arvoreposfixa.hpp"
#include "arvoreinfixa.hpp"

 void criarArvorePosFixa(std::string texto, ArvorePosFixa<std::string> &arvore){
        std::string meuTexto;
    for(auto itr = texto.end()-1; itr != texto.begin() -1; itr--){
        if(*itr != ' '){
            meuTexto+= *itr;
            if(itr != texto.begin()){
                continue;
            }  
        }
        if(meuTexto != " " && meuTexto != ""){
            if(arvore.isOperador(meuTexto)){
                arvore.Insere(meuTexto);
            } else {
                
                std::string textoCorreto = "";
                for(int i = 1; textoCorreto.size() != meuTexto.size(); i ++){
                    textoCorreto+= (*(meuTexto.end() - i));
                }
                arvore.Insere(textoCorreto);
            }
        meuTexto = "";
        }
    }
 }

 void preencherArvoreInfixaRecursivo(std::string textoNovo, ArvoreInFixa<std::string> &arvore){
    int count = 0;
    int posIni = 0;
    for(int i = posIni; i < textoNovo.size(); i++){
        if(textoNovo[i] == '('){
            if(count == 1){
                posIni = i;
            }
            count++;
        }
        if(textoNovo[i] == ')'){
            count--;
        }
        if(count == 1 && i != posIni && textoNovo[i] != '(' && textoNovo[i] != ')' && textoNovo[i] != ' '){          
            std::string texto = "";
            texto+=textoNovo[i];
            if(arvore.isOperador(texto)){
                arvore.Insere(texto);
                preencherArvoreInfixaRecursivo(textoNovo.substr(posIni, i - posIni), arvore);
                preencherArvoreInfixaRecursivo(textoNovo.substr(i + 1), arvore);
            } else if(textoNovo[i+1] == ' ') {  
                std::string textoCorreto = "";
                int k = i;
                while(textoNovo[k-1] != ' '){
                    k--;
                }
                int a = k;
                for(;textoNovo[k] != ' ' ;k++ ){
                    textoCorreto+=textoNovo[k];
                }   
                arvore.Insere(textoCorreto);
                break;
            } else if(textoNovo[i-1] == ' '){
                std::string textoCorreto = "";
                int k = i;
                for(; textoNovo[k] != ' ' ; k ++){
                    textoCorreto+= textoNovo[k];
                }
                arvore.Insere(textoCorreto);
                break;
            }
            
        }
    }
}

int main() {
    // // Pilha que guardará a expressão em formato infixo
    // Pilha<std::string> pilhaInfixa;
    // // Pilha que guardará a quantidade de parenteses, para saber se não tem uma quantidade inválida.
    // Pilha<int> qtdPrt;
    // std::string texto = "1.627783  2.365861  5.771913  *  +  8.718286  3.609486  +  8.733775  *  /  1.229733  6.687142  9.455672  -  +  *  0.138964  8.688749  /  8.668175  4.996990  *  8.772412  +  +  -  9.200303  /  5.066756  8.889858  9.577672  -  +  1.427157  9.378698  *  +  8.158811  4.938767  +  5.053923  *  7.014099  7.524377  +  1.256127  /  +  +  + ";
    // ArvorePosFixa<std::string> minhaArvore;
    // criarArvorePosFixa(texto, minhaArvore);

    // std::string notacao = minhaArvore.TranformarEmInFixa();
    // std::cout << notacao << std::endl;
    // try{
    //     double resultado = minhaArvore.calcularResultado();
    //     std::cout << "valor resultado: " << resultado << std::endl;
    // } catch(Erro erro){
    //     std::cout << erro.getMessage() << std::endl;
    // }
    std::string textoNovo = "( ( ( ( ( 2 ) + ( 1 ) ) * ( 4 ) ) + ( 55 ) ) - ( ( 37 ) + ( 29 ) ) )";
    ArvoreInFixa<std::string> arvoreInfixa;
    preencherArvoreInfixaRecursivo(textoNovo, arvoreInfixa);
    std::string resultado = arvoreInfixa.TranformarEmInFixa();
    std::cout << "meu resultado " << resultado << std::endl;
    double valor = arvoreInfixa.calcularResultado();
    std::cout << "valor: " << valor << std::endl;


}


