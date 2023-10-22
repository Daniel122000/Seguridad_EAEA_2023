#include "argsVerifier.hpp"

ArgsVerifier::ArgsVerifier(){}

ArgsVerifier::~ArgsVerifier(){}

bool ArgsVerifier::verify_arguments_delivery(int argc, char const *argv[]){
    if(argc != 4){
        std::cout << "Uso: <usuario.nac> <hash firmado y en base64 ENTRE COMILLAS SIMPLES> <mensaje texto plano>\n";
        return false;
    }
    if(strlen(argv[1]) > 30 || strlen(argv[1]) < 15){
        std::cout << "Usuario " << argv[1] << " SUS.\n";
        return false;
    }else if(strlen(argv[2]) > 500){
        std::cout << "Codigo base64 SUS.\n";
        return false;
    }else if(strlen(argv[3]) > 500){
        std::cout << "Mensaje demasiado extenso. 500 caracteres maximo.\n";
        return false;
    }
    return true;
}

bool ArgsVerifier::verify_arguments_node(std::string args,std::string* strings,
                                         std::string* u, std::string* b, std::string* p){
    std::size_t pos = args.find(" ");
    std::size_t pos2 = args.find(" ",pos+1);
    std::size_t pos3 = args.find(" ",pos2+1);
    
    std::string stringX = args.substr(0,pos);
    std::string user = args.substr(pos+1,pos2-pos-1);
    std::string base64 = args.substr(pos2+1,pos3-pos2-1);
    std::string plain = args.substr(pos3+1);

    if(stringX != strings[2] || user.empty() || base64.empty() || plain.empty()){
        return false;
    }
    *u = user;
    *b = base64;
    *p = plain;
    return true;
    //std::cout << "Client message user:" << user << ":"<< std::endl;
    //std::cout << "Client message base64:" << base64 << ":"<< std::endl;
    //std::cout << "Client message plaintext:" << plain << ":"<< std::endl;
}