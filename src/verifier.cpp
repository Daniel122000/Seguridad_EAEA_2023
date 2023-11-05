#include "verifier.hpp"

Verifier::Verifier(){}

Verifier::~Verifier()
{
    X509_free(user_cert);
}

Verifier::Verifier(std::string user,
                 std::string signature64,
                 std::string plain):
                 _user(user),
                 _signature64(signature64),
                 _plain(plain)
{

}

bool Verifier::verify_certificate(){
    user_cert = certV.verify_user_certificate(_user.c_str(), &success);
    if(success){
        // Verificar si el certificado del usuario es valido, usando el certificado de CA
        certV.verify_user_certificate_with_ca(user_cert, &success);
    }
    return success;
}

bool Verifier::verify_sign(){
    // Extraer la llave publica del usuario para verificar la firma
    char* pubkey_char_user = NULL; // Llave publica formato .pem
    signV.extract_user_public_key(user_cert, &success, &pubkey_char_user);
    bool res = signV.verify_signature(pubkey_char_user, coder.sha256(_plain), (char*)_signature64.c_str());
    return res;
}