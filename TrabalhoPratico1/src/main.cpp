#include <iostream>
#include "pilha.hpp"
#include "erro.hpp"
#include <string>
#include "arvoreposfixa.hpp"
#include "arvoreinfixa.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>

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

// Função responsável por ler o arquivo e guardar a expressão e o tipo de expressão dele, além do resultado
// # Parâmetros
// expressão: Será a expressão do arquivo em formato INFIXO ou POSFIXO
// tipo: Será o tipo da expressão, podendo ser INFIXO ou POSFIXO
// valor: resultado do arquivo que fica após a expressão "RESOLVE #"
void lerArquivo(std::string &expressao, std::string &tipo,long double &valor, std::string caminho){
    std::ifstream arquivo(caminho);
    std::string linha;
    if (arquivo.is_open()) {
        // Lê linha por linha até o final do arquivo
        while (std::getline(arquivo, linha)) {
            // Verifica se a linha começa com "LER"
            if (linha.substr(0, 3) == "LER") {
                // Divide a linha em palavras separadas por espaço
                std::istringstream iss(linha);
                std::string palavra;
                int cont = 0;
                while (iss >> palavra) {      
                    // A segunda palavra será o tipo
                    if (cont == 1) {
                        tipo = palavra;
                    }
                    // As palavras seguintes até a palavra "POSFIXA" ou "INFIXA" serão a expressão
                    else if (cont > 1 && palavra != "POSFIXA" && palavra != "INFIXA") {
                        expressao += palavra + " ";
                    }
                    cont++;
                }
            } else if (linha.find("RESOLVE #") != std::string::npos) { // Verifica se a linha contém a substring "RESOLVE #"
                        // Extrai o valor após a substring "RESOLVE #"
                        std::string valor_str = linha.substr(linha.find("RESOLVE #") + 9);
                        std::istringstream iss_valor(valor_str);
                        iss_valor >> valor;
                        break;
                    }
        }
        arquivo.close();
    }
    else {
        throw Erro("ERRO AO ABRIR ARQUIVO");
    }
}
// Limpa os espaços de uma expressão para comparação
// Exemplo: ( 3 ) + ( 5 ) após limpar ficará (3)+(5)
// # Parâmetros
// texto: Texto que perderá os espaços
void limpaEspaco(std::string &texto){
    for (int i = 0; i < texto.length(); i++) {
        if (texto[i] == ' ') {
            texto.erase(i, 1);
            i--;
        }
    }
}


// Função que faz testes em arquivos no formato dado pelo professor
// # Parâmetros
// caminhoDiretorio: caminho do diretório que tem os arquivos que serão testados
// Em caso de falha, irá imprimir no terminal : "Arquivo: <nome_arquivo> DEU ERRADO"
// No final imprirá "TOTAL DE CASOS FALHOS: <total>"

void testes(std::string caminhoDiretorio){
    // Contador de casos errados
    int totalCasosFalhos = 0;
    // Esse for caminha por todos os arquivos do diretório
    for (const auto& entrada : std::filesystem::directory_iterator(caminhoDiretorio)) {
        // inteiro que conta para verificar se falhou nos dois casos de teste
        int teste = 0;
        // Boleano que verifica se a conversão funcionou
        bool conversaoFuncionou = true;
        if (std::filesystem::is_regular_file(entrada)) {
            try{
            std::string texto = "";
            long double valor = 0;
            std::string opcao = "";
            std::string arquivo = entrada.path().string();
            lerArquivo(texto, opcao,valor, arquivo);
            if(opcao == "POSFIXA"){
                ArvorePosFixa<std::string> arvorePosFixa;
                preencheArvorePosFixa(texto, arvorePosFixa);
                std::string notacao = arvorePosFixa.TranformarEmInFixa();
                double resultado = arvorePosFixa.calcularResultado();
                // Verifica a diferença do valor capturado pelo lerArquivo e o resultado calculado a partir do calcularResultado
                if(std::abs(valor - resultado) > 1){
                    teste++;
                }
                // Criação de uma engenharia reversa para voltar a expressão em seu formato original após a conversão
                ArvoreInFixa<std::string> arvoreInfixa;
                preencherArvoreInfixa(notacao, arvoreInfixa);
                std::string resultadoReverso = arvoreInfixa.TranformarEmPosFixa();
                limpaEspaco(resultadoReverso);
                limpaEspaco(texto);
                // Comparação da expressão original e e o resultadoReverso
                if(resultadoReverso != texto){
                    teste++;
                    conversaoFuncionou = false;
                }
                // Caso não atenda as existências do teste 
                if(teste > 1 || !conversaoFuncionou){
                    std::cout << "Arquivo: " << arquivo  << " DEU ERRADO" << std::endl;
                    totalCasosFalhos++;
                }
            } else if(opcao == "INFIXA"){
                ArvoreInFixa<std::string> arvoreInfixa;
                preencherArvoreInfixa(texto, arvoreInfixa);
                std::string notacao = arvoreInfixa.TranformarEmPosFixa();
                double resultado = arvoreInfixa.calcularResultado();
                // Verifica a diferença do valor capturado pelo lerArquivo e o resultado calculado a partir do calcularResultado
               if(std::abs(valor - resultado) > 1){
                    teste++;
                }
                // Criação de uma engenharia reversa para voltar a expressão em seu formato original após a conversão
                ArvorePosFixa<std::string> arvorePosFixa;
                preencheArvorePosFixa(notacao, arvorePosFixa);
                std::string resultadoReverso = arvorePosFixa.TranformarEmInFixa();
                limpaEspaco(resultadoReverso);
                limpaEspaco(texto);
                // Comparação da expressão original e e o resultadoReverso
                if(resultadoReverso != texto){
                    teste++;
                    conversaoFuncionou = false;
                }
                // Caso não atenda as existências do teste 
                if(teste > 1 || !conversaoFuncionou){
                    std::cout << "Arquivo: " << arquivo  << " DEU ERRADO" << std::endl;
                    totalCasosFalhos++;
                }
            }
            }catch(Erro erro){
            std::cout << erro.getMessage() << std::endl;
            }catch(...){
            std::cout << "Erro desconhecido" << std::endl;
            }
        }
    }

    std::cout << "TOTAL DE CASOS FALHOS: " << totalCasosFalhos << std::endl;
}

void criarArquivo(std::string tipo,std::string tipoContrario ,std::string expressao, std::string resultado, double valor, std::string nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo << tipo << "  " << expressao << std::endl;
        arquivo << tipoContrario << "  " << resultado << std::endl;
        arquivo << "RESOLVE # " << valor << std::endl;
        arquivo.close();
    }
    else {
        std::cout << "ERRO AO CRIAR ARQUIVO.\n";
    }
}

void implementacao(std::string arquivo){
    try{
        std::string expressao;
        std::string tipo;
        long double valor;
        lerArquivo(expressao, tipo, valor, arquivo);
        if(tipo == "INFIXA"){
            ArvoreInFixa<std::string> arvoreInfixa;
            preencherArvoreInfixa(expressao, arvoreInfixa);
            std::string notacao = arvoreInfixa.TranformarEmPosFixa();
            double resultado = arvoreInfixa.calcularResultado();
            criarArquivo(tipo,"POSFIXA" ,expressao, notacao, resultado, "resultado.txt");
        } else if(tipo == "POSFIXA"){
            ArvorePosFixa<std::string> arvorePosFixa;
            preencheArvorePosFixa(expressao, arvorePosFixa);
            std::string notacao = arvorePosFixa.TranformarEmInFixa();
            double resultado = arvorePosFixa.calcularResultado();
            criarArquivo(tipo,"INFIXA" ,expressao, notacao, resultado, "resultado.txt");
        }  
    } catch(Erro erro){
        std::cout << erro.getMessage() << std::endl;
    } catch(...){
        std::cout << "Erro desconhecido" << std::endl;
    }

}
int main(int argc, char *argv[]) {
    std::string caminho = argv[1];
    implementacao(caminho);
}


