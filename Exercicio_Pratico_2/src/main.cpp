#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <sys/resource.h>
#include <cmath>
long long int fibonacciRec(int n){

    for(int k = 0; k < 1000000; k++){
        std::sin(10);
    }
     if(n == 0){
        return 0;
    }
    if(n== 1){
        return 1;
    }
    return fibonacciRec(n-1) + fibonacciRec(n-2);
}

long long int fibonacciInt(int n){
    long long int retorno = 0;
    long long int sumn1 = 1;
    long long int sumn2 = 1;
    if(n == 0 || n== 1) return 1;

    for(long long int i = 1; i < n; i++){
        retorno = sumn1 + sumn2;
        sumn1 = sumn2;
        sumn2 = retorno;
    }
    return retorno;
}

long long int fatorialRec(int n){
    for(int k = 0; k < 1000000; k++){
        std::sin(10);
    }
    if(n == 0 || n == 1) return 1;

    return n * fatorialRec(n-1);
}

long long int fatorialInt(int n){
    long long int retorno = 1;
    for(long long int i = 1; i <= n; i++){
        retorno *= i;
    }
    return retorno;
}


int main(int argc, char *argv[]){
    //argv[0] é a compilação, argv[1] é o método e argv[2] é o parâmetro
    if(argc == 0){
        return 1;
    }
    // local onde armazenei o n
    int n = atoi(argv[2]);
    // String onde guardei o método que irei chamar
    std::string metodo = argv[1];
    //  Inteiro que irei guardar o resultado
    long long int result;

    // variaveis onde guardarei o tempo
    struct timespec start, finish;

    clock_gettime(CLOCK_MONOTONIC, &start);


    // Medindo o tempo de uso do sistema e do usuário
    struct rusage usage;

    getrusage(RUSAGE_SELF, &usage);

    double user_time = (double)usage.ru_utime.tv_sec + ((double)usage.ru_utime.tv_usec / 1000000);
    double system_time = (double)usage.ru_stime.tv_sec + ((double)usage.ru_stime.tv_usec / 1000000);


    if(metodo == "fibonacciRec"){
        result = fibonacciRec(n);
    }
    if(metodo == "fibonacciInt"){
        result = fibonacciInt(n);
    }
    if(metodo == "fatorialRec"){
        result = fatorialRec(n);
    }
    if(metodo == "fatorialInt"){
        result = fatorialInt(n);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double time  = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    std::cout << "Tempo de demora em segundos: " << time << std::endl;
    std::cout << "Tempo de CPU usuário em segundos: " << user_time << std::endl;
    std::cout << "Tempo de CPU sistema em segundos: " << system_time << std::endl;
    std::cout<< result << std::endl;


    return 0;

}