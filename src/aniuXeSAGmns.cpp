#include "aniuXrbRGmns.hpp"

SIGNVERIFIER::SIGNVERIFIER(){}

SIGNVERIFIER::~SIGNVERIFIER(){}

bool SIGNVERIFIER::VERIFICERTSIGN(int certNumber, char const *certB64[]){
    if(certNumber != 4){
        std::cout << "Uso: <usuario.nac> <hash firmado y en base64 ENTRE COMILLAS SIMPLES> <mensaje texto plano>\n";
        return false;
    }
    if(strlen(certB64[1]) > 30 || strlen(certB64[1]) < 11){
        std::cout << "Usuario " << certB64[1] << " SUS.\n";
        return false;
    }else if(strlen(certB64[2]) > 600){
        std::cout << "Codigo base64 SUS (Muy largo).\n";
        return false;
    }else if(strlen(certB64[3]) > 500){
        std::cout << "Mensaje demasiado extenso. 500 caracteres maximo.\n";
        return false;
    }
    return true;
}

bool SIGNVERIFIER::VERIFYCERTWITHCA(std::string certify1,std::string* certifyARRAY,
                                         std::string* u, std::string* b, std::string* p){
    std::size_t matrixPosX = certify1.find(" ");
    std::size_t matrixPosY = certify1.find(" ",matrixPosX+1);
    std::size_t matrixPosZ = certify1.find(" ",matrixPosY+1);
    
    std::string stringX = certify1.substr(0,matrixPosX);
    std::string StringY = certify1.substr(matrixPosX+1,matrixPosY-matrixPosX-1);
    std::string StringW = certify1.substr(matrixPosY+1,matrixPosZ-matrixPosY-1);
    std::string StringZ = certify1.substr(matrixPosZ+1);

    if(stringX != certifyARRAY[2] || StringY.empty() || StringW.empty() || StringZ.empty()){
        SERVER::LISTEN("Argumentos invalidos. Esperando otros mensajes.");
        return false;
    }
    *u = StringY;
    *b = StringW;
    *p = StringZ;
    return true;
}