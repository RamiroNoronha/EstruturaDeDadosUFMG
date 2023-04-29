#include<string>
#pragma once
class Erro  {
    public:
    std::string getMessage(){return message;};
    Erro(std::string message) : message(message){};
    private:
    std::string message;
    
};