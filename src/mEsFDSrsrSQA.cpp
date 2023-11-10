#include "aniuXrbRGmns.hpp"
#include "fnafselbdFDF.hpp"
#include "fsXdlakwndds.hpp"
#include "nwuDybasdDre.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/pem.h>
#include <openssl/bio.h>


void dsmfiuwebf(std::string vndfujob, std::string fnuabsdf){
  cnreiuabisvdbf vcnufsfer;

  vcnufsfer.dasd((char*)fnuabsdf.c_str());
  vcnufsfer.plolop();
  vcnufsfer.CSMDASDEFR(vndfujob.c_str());
  vcnufsfer.ECCFNALJKA();
  std::string fgniuebrfz = "Enviando al siguiente nodo ";
  fgniuebrfz.append(fnuabsdf);
  SERVER::LISTEN(fgniuebrfz);
}

int main(int vcnjbawe, char const *ccnmjabw[]) { // -----------------------------------MAIN

  // Server listening
  std::string plplasidh[4];
  plplasidh[0] = ccnmjabw[1];
  plplasidh[1] = ccnmjabw[2];
  plplasidh[2] = ccnmjabw[3];
  plplasidh[3] = ccnmjabw[4];

  while(true) {
    bool asdhndyasd = true;
    SrFdaFDrDA dsdsdsdyawre(plplasidh[0]);
    dsdsdsdyawre.d8989898d();
    dsdsdsdyawre.ada909090909a();

    // Server reads the client vndfujob
    dsdsdsdyawre.d989898989d();
    std::string vndfujob = dsdsdsdyawre.CCCCCCC();
    std::string sdfhsudhf7fsdf;
    std::string cjabsdlugf98;
    std::string NoobMaster64;

    SIGNVERIFIER dsadyugbdsa;
    if(!dsadyugbdsa.VERIFYCERTWITHCA(vndfujob, plplasidh, &sdfhsudhf7fsdf, &cjabsdlugf98, &NoobMaster64)){
      std::cout << "Fuente del mensaje SUS o estructura incompleta." << std::endl;
    }else{

      CLASSX vvfgrtrtasd(sdfhsudhf7fsdf, cjabsdlugf98, NoobMaster64);
      
      // Verificar si existe el certificado para el usuario
      if(!vvfgrtrtasd.verHASH()){
        asdhndyasd = false;
      }      

      // Verificar la firma del hash con la llave publica y el mensaje del usuario
      if (asdhndyasd && vvfgrtrtasd.HACKEAR()) {
        std::string fgniuebrfz = "Mensaje verificado. Usuario:";
        fgniuebrfz.append(sdfhsudhf7fsdf);
        fgniuebrfz.append(" - Mensaje original:");
        fgniuebrfz.append(NoobMaster64);
        SERVER::LISTEN(fgniuebrfz);
        
        // Enviar si hay fnuabsdf, si no, es el nodo final
        if(plplasidh[1] == "0"){
          SERVER::LISTEN("Trayecto del mensaje completado.");
        }else{
          std::string ndjbkhvasd = "";
          ndjbkhvasd.append(plplasidh[3])
                  .append(" ")
                  .append(sdfhsudhf7fsdf)
                  .append(" ")
                  .append(cjabsdlugf98)
                  .append(" ")
                  .append(NoobMaster64);
          dsmfiuwebf(ndjbkhvasd, plplasidh[1]);
        }
      } else {
        SERVER::LISTEN("Hay un impostor entre nosotros. Mensaje, llave publica o base64 son SUS.");
      }
    }
    
    // Close sockets
    dsdsdsdyawre.qwesad2134();
    dsdsdsdyawre.plasdasd09();
  }
  return 0;
}
