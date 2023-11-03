#include "clientEAEA.hpp"
#include "argsVerifier.hpp"
#include "logger.hpp"

#define IP_ADDR "192.168.5.56"

std::string prepare_delivery_message(char const *argv[]){
    std::string x = argv[0];
    std::string user = argv[1];
    std::string signature = argv[2];
    std::string plainText = argv[3];

    std::string message = x.append(" ");
    message.append(user).append(" ").append(signature).append(" ").append(plainText);
    return message;
}

void deliver_message(std::string message){
    ClientEAEA client;
    client.convert_Addresses((char*)IP_ADDR);
    client.create_Connection();
    client.sendMessage(message.c_str());
    std::string log_message = "Message sent to ";
    log_message.append(IP_ADDR);
    Logger::log(log_message);
    client.endConnection();
}

int main(int argc, char const *argv[])
{
    ArgsVerifier verifier;
    if(!verifier.verify_arguments_delivery(argc, argv)){
        return 1;
    }
    
    std::string message = prepare_delivery_message(argv);

    deliver_message(message);

    return 0;
}
