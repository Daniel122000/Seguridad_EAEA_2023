#include "certVerifier.hpp"

void CertVerifier::verify_user_certificate_with_ca(X509* cert_user, bool* success){
  // Validar certificado usuario con certificado CA
  // Cargar certificado CA
  X509* cert_CA = try_read_crt("../ca/CAG5.crt", success);
  if (!success) {
    std::cout << "No existe el certificado de la CA. Ya valimos." << std::endl;
    X509_free(cert_CA);
    return;
  }
  // Extraer .csr de CA
  X509_REQ* csr_CA = signV.try_read_csr(cert_CA, success);
  if (!success) {
    X509_free(cert_CA);
    X509_REQ_free(csr_CA);
    std::cout << "No se pudo cargar el .csr del certificado de la CA. Ya valimos." << std::endl;
    return;
  }
  // Extraer llave publica de .csr de CA
  char* pubkey_char_CA = nullptr;
  EVP_PKEY* pubkey_CA = signV.try_read_pubkey(csr_CA, &pubkey_char_CA);
  if(!pubkey_char_CA){
    X509_free(cert_CA);
    X509_REQ_free(csr_CA);
    EVP_PKEY_free(pubkey_CA);
    std::cout << "Error al leer llave publica de la CA." << std::endl;
    return;
  }
  // Verificar con la lalve publica de CA el certificado del usuario
  // Verificar la firma del certificado
  if (X509_verify(cert_user, pubkey_CA) != 1) {
    X509_free(cert_CA);
    X509_REQ_free(csr_CA);
    EVP_PKEY_free(pubkey_CA);
    std::cout << "El certificado del usuario esta SUS, cancelar." << std::endl;
    return;
  } else {
    std::cout << "El certificado del usuario esta legal." << std::endl;
  }
  X509_free(cert_CA);
  X509_REQ_free(csr_CA);
  EVP_PKEY_free(pubkey_CA);
  return;
}

X509* CertVerifier::try_read_crt(const char* path, bool* success){
  // Abrir el archivo del certificado
  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    *success = false;
    std::cout << "No existe el certificado para el usuario dado." << std::endl;
    return NULL;
  }

  // Leer el certificado del archivo
  X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);
  fclose(fp);
  
  return cert;
}

X509* CertVerifier::verify_user_certificate(const char* user, bool* success){
  std::string user_crt_path = "../crt/"; // Certificado del usuario
  user_crt_path.append(user).append(".crt");
  
  return CertVerifier::try_read_crt(user_crt_path.c_str(), success);
}