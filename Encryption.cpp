//
// Created by danil on 5/21/2023.
//

#include <iostream>
#include "Encryption.h"
#include <sstream>
#include <iomanip>

std::string Encryption::readTimeStamp(const std::string &plaintext) {
    std::string outputText;
    auto plaintextStream = std::stringstream(plaintext);
    int lineNumber=1;
    std::string timeStampLast;
    for (auto line = std::string(); std::getline(plaintextStream, line);) {
        if(lineNumber%7==0){
            timeStampLast+=line[0];
            timeStampLast+=line[1];
            line.erase(line.begin());
            line.erase(line.begin());
        }
        lineNumber++;
        outputText+=line+'\n';
    }
    std::string tmp=timeStampLast;
    timeStampLast="";
    for(int i=0;i<tmp.length();i++){
        if(i==2 || i==4)
            timeStampLast+='.';
        else if(i==8)
            timeStampLast+=' ';
        else if (i==10 || i==12)
            timeStampLast+=':';
        timeStampLast+=tmp[i];
    }
    if(!timeStampLast.empty())
        std::cout<<"Plik byl zmodyfikowany w ostatni raz "<<timeStampLast<<'\n';
    return outputText;
}
std::string Encryption::putTimeStamp(const std::string &plaintext) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::string ciphertext;
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d%m%Y%H%M%S");
    std::string timeStamp = oss.str();
    int lineNumber = 1;
    int timeStampSymbol = 0;
    auto plaintextStream = std::stringstream(plaintext);
    for(std::string line; std::getline(plaintextStream,line);){
        if(lineNumber%7==0){
            ciphertext+=timeStamp[timeStampSymbol++];
            ciphertext+=timeStamp[timeStampSymbol++];
        }
        ciphertext+=line+'\n';
        lineNumber++;
    }
    while(timeStampSymbol<timeStamp.length()){
        if(lineNumber%7==0){
            ciphertext+=timeStamp[timeStampSymbol++];
            ciphertext+=timeStamp[timeStampSymbol++];
        }
        ciphertext+='\n';
        lineNumber++;
    }
    return ciphertext;
}
std::string Encryption::encrypt(const std::string &plaintext, const std::string &password,bool readOrWrite) {
    std::string cplain=plaintext;
    if(readOrWrite)
        cplain+="\n";
    std::string ciphertext = cplain;
    if(!readOrWrite)
        ciphertext = readTimeStamp(ciphertext);

    for (int i = 0; i < cplain.length(); i++) {
       ciphertext[i] ^= password[i % password.length()];
    }
    if(readOrWrite)
    {
        ciphertext = putTimeStamp(ciphertext);
    }


    return ciphertext;
}