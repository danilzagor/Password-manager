//
// Created by danil on 5/21/2023.
//
#include "AppFunctions.h"
#include <iostream>
#include <fmt/core.h>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "Encryption.h"
using std::cout;
using std::string;
using std::cin;
using fmt::print;
#include "FileOperations.h"
auto FileOperations::findFile()->string{
    auto fileIterator =std::filesystem::directory_iterator(std::filesystem::current_path());
    int i=1;
    for (auto const& entry : fileIterator) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".txt") {
                cout<<entry.path()<<" - "<<i++<<'\n';
            }
        }
    }
    if(i==1){
        print("Nie ma plików do odczytu w tym folderze!");
        return "";
    }
    i=1;
    int k;
    cin>>k;
    fileIterator =std::filesystem::directory_iterator(std::filesystem::current_path());
    for (auto const& entry : fileIterator) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".txt") {
                if(k==i++){
                    fileName=entry.path().generic_string();
                }
            }
        }
    }
    return fileName;
}
auto FileOperations::readFromFile() -> string {
    std::ifstream file = std::ifstream(fileName, std::ios::binary);
    while (!file) {
        print("1 - Znaleźć plik w tym folderze"
              "\n2 - Wprowadzić ścieżkę\n");
        int condition;
        cin>>condition;
        switch (condition) {
            case 1:
                fileName=findFile();
                break;
            case 2:
                print("{}\n", "Wprowadź ścieżkę do pliku");
                std::getline(cin,fileName);
                std::getline(cin,fileName);
                break;
            default:
                print("Nie poprawny argument\n");
                break;
        }
        file = std::ifstream(fileName, std::ios::binary);
        if (!file)
            print("{}\n", "Plik o takiej nazwie nie istnieje, sprobój jeszcze raz!");
    }
    print("{}\n", "Wprowadź hasło");
    cin >> key;
    std::string ciphertext((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    auto decryptedText = Encryption::encrypt(ciphertext, key,false);
    file.close();
    return decryptedText;
}

auto FileOperations::makeChange(const std::map<std::string, std::vector<PasswordInfo>>& passwordsInfo) -> void {
    std::ofstream file = std::ofstream(fileName, std::ios::binary);
    string str;
    for (const auto& pass: passwordsInfo) {
        for (const auto& has: pass.second) {
            str+= pass.first + "," + has.name + "," + has.password + "," + has.login + "," + has.www + '\n';
        }
    }
    file << Encryption::encrypt(str,key,true);
    file.close();
}