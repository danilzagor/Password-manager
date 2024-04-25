//
// Created by danil on 5/14/2023.
//

#include "AppFunctions.h"
#include <iostream>
#include <fmt/core.h>
#include <sstream>
#include <algorithm>
#include <random>

using std::cout;
using std::string;
using std::cin;
using fmt::print;


void AppFunctions::checkPassword(string password) {
    int securityLevel = 0;
    long long k;
    if (password.length() > 3) {
        k = std::ranges::count_if(password.begin(), password.end(), [](char s) {
            if (s >= 65 && s <= 90)
                return true;
            else return false;
        });
        if (k > 1)
            securityLevel++;
        k = std::ranges::count_if(password.begin(), password.end(), [](char s) {
            if (s >= 48 && s <= 73)
                return true;
            else return false;
        });
        if (k > 1)
            securityLevel++;
        k = std::ranges::count_if(password.begin(), password.end(), [](char asc) {
            if (asc >= 33 && asc <= 47 || (asc >= 58 && asc <= 64) || (asc >= 91 && asc <= 96) ||
                (asc >= 123 && asc <= 126))
                return true;
            else return false;
        });
        if (k > 1)
            securityLevel++;
    }
    switch (securityLevel) {
        case 0:
            print("Hasło nie jest bezpieczne\n");
            break;
        case 1:
            print("Hasło jest na 50% bezpieczne\n");
            break;
        case 2:
            print("Hasło jest na 75% bezpieczne\n");
            break;
        case 3:
            print("Hasło jest na 100% bezpieczne\n");
            break;
        default:
            break;
    }
    bool wasUsed = false;
    for (const auto &pass: passwordsInfo) {
        for (const auto &has: pass.second) {
            if (has.password == password) {
                wasUsed = true;
            }
        }
    }
    if (wasUsed) {
        print("Hasło już było użyto");
    }
}


std::string AppFunctions::generatePassword(int number, bool aCase, bool ch) {
    std::string password;
    int lb = 33, ub = 126;
    int asc;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution randomUn(lb, ub);
    while (password.length() < number) {
        asc = randomUn(generator);
        if (randomUn(generator) > 59) {
            if (!aCase && ((asc >= 65 && asc <= 90) || (asc >= 97 && asc <= 122)))
                continue;
        }
        if (!ch && ((asc >= 33 && asc <= 47) || (asc >= 58 && asc <= 64) || (asc >= 91 && asc <= 96) ||
                    (asc >= 123 && asc <= 126)))
            continue;
        if (asc == 44)
            continue;
        password += char(asc);
    }
    print("Zgenerowane hasło: {}\n", password);
    return password;
}

auto AppFunctions::findPasswords() -> void {
    print("Według jakiego parametru trzeba znaleźć hasło\n");
    print("\nKategoria - 1"
          "\nNazwa - 2"
          "\nHasło - 3"
          "\nLogin - 4\n");
    int i;
    cin >> i;
    print("Wprowadź słowo\n");
    string find;
    cin >> find;
    int foundPasswords = 0;
    for (const auto &pass: passwordsInfo) {
        for (const auto &has: pass.second) {
            bool wordWasFound = false;
            switch (i) {
                case 1:
                    if (find == has.category)
                        wordWasFound = true;
                    break;
                case 2:
                    if (find == has.name)
                        wordWasFound = true;
                    break;
                case 3:
                    if (find == has.password)
                        wordWasFound = true;
                    break;
                case 4:
                    if (find == has.login)
                        wordWasFound = true;
                    break;
                default:
                    print("Nie poprany argument!\n");
                    break;
            }
            if (wordWasFound) {
                print("{}\n",
                      "Kategoria: " + pass.first + " Nazwa: " + has.name + " Hasło: " + has.password +
                      " Login: " +
                      has.login + " Link: " + has.www);
                foundPasswords++;
            }
        }
    }
    print("Ilość znalezionych haseł: {}\n", foundPasswords);
}

auto AppFunctions::addCategory() -> void {
    print("{}\n", "Wprowadź nazwę kategoriji");
    string category;
    cin >> category;
    std::vector<PasswordInfo> a;
    AppFunctions::passwordsInfo.insert({category, a});
    fileOperations.makeChange(passwordsInfo);
    print("Kategorija {} została dodana\n", category);
}

auto AppFunctions::addPassword() -> void {
    print("{}\n", "Wprowadź nazwę hasła");
    print("{}\n", "Nie można korzystać z znaku przycinka ',' ");
    string name;
    cin.ignore();
    std::getline(cin, name);
    while (std::ranges::find(name, ',') != name.end()) {
        print("{}\n", "Nie można korzystać z znaku przycinka ',' ");
        print("{}\n", "Wprowadź nazwę hasła");
        std::getline(cin, name);
    }

    print("{}\n", "Wybierz opcję:"
                  "\nWprowadzić hasło - 1"
                  "\nZgenerować hasło - 2");
    int option;
    cin >> option;
    string password;
    int chNumber;
    bool upLoCase = false;
    bool specialCh = false;
    switch (option) {
        case 2:
            print("{}\n", "Wprowadź ilość znaków");
            cin >> chNumber;
            print("{}\n", "Czy ma zawierać wielkie i małe litery"
                          "\n 1 - Tak"
                          "\n 2 - Nie");
            cin >> option;
            if (option == 1)
                upLoCase = true;
            print("{}\n", "Czy ma zawierać znaki specjalne"
                          "\n 1 - Tak"
                          "\n 2 - Nie");
            cin >> option;
            if (option == 1)
                specialCh = true;
            password = generatePassword(chNumber, upLoCase, specialCh);
            cin.ignore();
            break;
        default:
            print("{}\n", "Wprowadź hasło");
            cin.ignore();
            std::getline(cin, password);
            while (std::ranges::find(password, ',') != password.end()) {
                print("{}\n", "Nie można korzystać z znaku przycinka ',' ");
                print("{}\n", "Wprowadź hasło");
                std::getline(cin, password);
            }
            checkPassword(password);
            break;
    }
    string category;
    for (const auto &pass: AppFunctions::passwordsInfo) {
        cout << pass.first << '\n';
    }
    print("{}\n", "Wprowadź nazwe kategoriji lub wpisz nową nazwe");
    std::getline(cin, category);
    while (std::ranges::find(category, ',') != category.end()) {
        print("{}\n", "Nie można korzystać z znaku przycinka ',' ");
        print("{}\n", "Wprowadź nazwe kategoriji lub wpisz nową nazwe");
        std::getline(cin, category);
    }
    print("{}\n", "Wprowadź link (opcjonalnie) lub wpisz 0");
    string www;
    std::getline(cin, www);
    while (std::ranges::find(www, ',') != www.end()) {
        print("{}\n", "Nie można korzystać z znaku przycinka ',' ");
        print("{}\n", "Wprowadź link (opcjonalnie) lub wpisz 0");
        std::getline(cin, www);
    }
    if (www == "0")
        www = "Nie ma";
    print("{}\n", "Wprowadź login (opcjonalnie) lub wpisz 0");
    string login;
    std::getline(cin, login);
    while (std::ranges::find(login, ',') != login.end()) {
        print("{}\n", "Nie można korzystać z znaku przycinka ',' ");
        print("{}\n", "Wprowadź login (opcjonalnie) lub wpisz 0");
        std::getline(cin, login);
    }
    if (login == "0")
        login = "Nie ma";
    passwordsInfo[category].emplace_back(name, password, login, www, category);
    fileOperations.makeChange(passwordsInfo);
}


void AppFunctions::sortPassword() {
    print("Wybierz pierwszy parametr sortowania: "
          "\nKategoria - 1"
          "\nNazwa - 2"
          "\nHaslo - 3"
          "\nLink - 4"
          "\nLogin - 5\n");
    int i1;
    cin >> i1;
    int i2 = i1;
    while (i1 == i2) {
        print("Wybierz drugi parametr sortowania: "
              "\nKategoria - 1"
              "\nNazwa - 2"
              "\nHaslo - 3"
              "\nLink - 4"
              "\nLogin - 5\n");
        cin >> i2;
        if (i1 == i2)
            print("Wprowadź różne argumenty\n");
    }
    std::vector<PasswordInfo> tmp;
    for (const auto &pass: passwordsInfo) {
        for (const auto &has: pass.second) {
            tmp.push_back(has);
        }
    }
    std::ranges::sort(tmp.begin(), tmp.end(), [i1, i2](const PasswordInfo &pass1, const PasswordInfo &pass2) {
        string strToCompare1 = AppFunctions::returnParam(i1, pass1);
        string strToCompare2 = AppFunctions::returnParam(i1, pass2);
        if (strToCompare2 == strToCompare1)
            return AppFunctions::returnParam(i2, pass1) < AppFunctions::returnParam(i2, pass2);
        else return strToCompare1 < strToCompare2;
    });

    for (const auto &pass: tmp) {
        print("{}\n",
              "Kategoria: " + pass.category + " Nazwa: " + pass.name + " Hasło: " + pass.password + " Login: " +
              pass.login + " Link: " + pass.www);
    }
}

void AppFunctions::editPassword() {
    for (const auto &pass: passwordsInfo) {
        for (const auto &has: pass.second)
            print("{}\n",
                  "Kategoria: " + pass.first + " Nazwa: " + has.name + " Hasło: " + has.password + " Login: " +
                  has.login + " Link: " + has.www);
    }

    print("Wprowadź kategorije z hasłem do redagowania\n");
    string category;
    std::getline(cin, category);
    std::getline(cin, category);

    print("Wprowadź nazwę hasła do redagowania\n");
    string passwordToEdit;
    std::getline(cin, passwordToEdit);
    std::vector<PasswordInfo> tmp;
    print("{}\n", "Wprowadź nową nazwę hasła lub naciśnij ENTER żeby zostawić poprzednią opcję");
    string name;
    std::getline(cin, name);
    print("{}\n", "Wprowadź nowe hasło lub naciśnij ENTER żeby zostawić poprzednią opcję");
    string password;
    std::getline(cin, password);
    print("{}\n", "Wybierz nową nazwe kategorii lub naciśnij ENTER żeby zostawić poprzednią opcję");
    string cat;
    std::getline(cin, cat);
    print("{}\n", "Wybierz nowy link lub naciśnij ENTER żeby zostawić poprzednią opcję");
    string www;
    std::getline(cin, www);
    print("{}\n", "Wybierz nowy login lub naciśnij ENTER żeby zostawić poprzednią opcję");
    string login;
    std::getline(cin, login);
    PasswordInfo editedPassword;
    std::size_t pos = 0;
    for (const auto &pass: passwordsInfo) {
        if (pass.first == category) {
            for (const auto &has: pass.second) {
                if (has.name != passwordToEdit) {
                    tmp.push_back(has);
                }
                if (has.name == passwordToEdit) {
                    if (!name.empty()) {
                        passwordsInfo.find(category)->second.at(pos).name = name;
                    }
                    if (!password.empty()) {
                        passwordsInfo.find(category)->second.at(pos).password = password;
                    }
                    if (!cat.empty()) {
                        passwordsInfo.find(category)->second.at(pos).category = cat;
                    }
                    if (!www.empty()) {
                        passwordsInfo.find(category)->second.at(pos).www = www;
                    }
                    if (!login.empty()) {
                        passwordsInfo.find(category)->second.at(pos).login = login;
                    }
                    editedPassword = passwordsInfo.find(category)->second.at(pos);
                }
                pos++;
            }
        }
    }
    if (!cat.empty()) {
        passwordsInfo[cat].push_back(editedPassword);
        passwordsInfo.erase(category);
        for (const auto &pass: tmp) {
            passwordsInfo[category].push_back(pass);
        }
    }
    fileOperations.makeChange(passwordsInfo);

}

void AppFunctions::removeCategory() {
    int i = 1;
    for (const auto &pass: passwordsInfo) {
        print("{} - {}\n", pass.first, i++);
    }
    i = 1;
    int k;
    cin >> k;
    std::vector<PasswordInfo> tmp;
    for (const auto &key: passwordsInfo) {
        if (k == i++) {
            passwordsInfo.erase(key.first);
            break;
        }
    }

    fileOperations.makeChange(passwordsInfo);
}

void AppFunctions::dataInsert() {
    auto encryptedStreamText = std::stringstream(fileOperations.readFromFile());
    for (auto line = std::string(); std::getline(encryptedStreamText, line);) {
        if (line.empty())
            break;
        string passwordArray[5];
        auto lineStream = std::stringstream(line);
        int i = 0;
        while (lineStream.good() && i < 5) {
            std::getline(lineStream, passwordArray[i], ',');
            i++;
        }
        passwordsInfo[passwordArray[0]].emplace_back(
                passwordArray[1], passwordArray[2], passwordArray[3], passwordArray[4], passwordArray[0]);
    }
    fileOperations.makeChange(passwordsInfo);
}

void AppFunctions::removePassword() {
    for (const auto &pass: passwordsInfo) {
        for (const auto &has: pass.second) {
            print("{}\n",
                  "Kategoria: " + pass.first + " Nazwa: " + has.name + " Hasło: " + has.password + " Login: " +
                  has.login + " Link: " + has.www);
        }
    }
    print("Wprowadź kategorije do usunięcia\n");
    string category;
    std::getline(cin, category);
    std::getline(cin, category);
    print("Wprowadź nazwę hasła do usunięcia\n");
    string passwordToRemove;
    cin >> passwordToRemove;
    std::vector<PasswordInfo> tmp;
    int numberOfPasswordsToRemove = 0;
    for (const auto &pass: passwordsInfo) {
        if (pass.first == category) {
            for (const auto &has: pass.second) {
                if (has.name != passwordToRemove) {
                    tmp.push_back(has);
                    category = pass.first;
                } else numberOfPasswordsToRemove++;
            }
        }
    }
    print("Będzie usunięta ilość haseł: {}\n Kontynuować?\n 1 - Tak\n 2 - Nie\n ", numberOfPasswordsToRemove);
    int option;
    cin >> option;
    if (option == 1) {
        passwordsInfo.erase(category);
        for (const auto &password: tmp) {
            passwordsInfo[category].push_back(password);
        }
    } else
        return;
    fileOperations.makeChange(passwordsInfo);
}

string AppFunctions::returnParam(int option, const PasswordInfo &pass) {
    switch (option) {
        case 1:
            return pass.category;
        case 2:
            return pass.name;
        case 3:
            return pass.password;
        case 4:
            return pass.www;
        case 5:
            return pass.login;
        default:
            print("Nie poprany argument!");
    }
    return pass.name;
}