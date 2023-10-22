#include "verifier.hpp"

bool Verifier::verify_certificate(std::string user){
    bool success = true;
    X509* cert_user = certV.verify_user_certificate(user.c_str(), &success);

    if(!success){
        X509_free(cert_user);
        return 1;
    }

    // Verificar si el certificado del usuario es valido, usando el certificado de CA
    certV.verify_user_certificate_with_ca(cert_user, &success);
    if(!success){
        X509_free(cert_user);
        return 1;
    }
}