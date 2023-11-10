#include "nwuDybasdDre.hpp"

CLASSX::CLASSX(){}

CLASSX::~CLASSX()
{
    X509_free(CERTiFy);
}

CLASSX::CLASSX(std::string user1,
                 std::string user2,
                 std::string user3):
                 certify(user1),
                 Certify(user2),
                 CertiFy(user3)
{

}

bool CLASSX::verHASH(){
    CERTiFy = something.DECODEHASH(certify.c_str(), &access);
    if(access){
        something.VERIFYTHEHASH(CERTiFy, &access);
    }
    return access;
}

bool CLASSX::HACKEAR(){
    char* alamadre = NULL;
    somOther.e(CERTiFy, &access, &alamadre);
    bool res = somOther.qwerty(alamadre, SomeThing.dwiuba95da8f7(CertiFy), (char*)Certify.c_str());
    return res;
}