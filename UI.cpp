//
// Created by danil on 5/3/2023.
//

#include "UI.h"
#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include "AppFunctions.h"

using std::cout;
using std::string;
using std::cin;
using fmt::print;


auto UI::interfaceMain() -> void {
    AppFunctions appFunctions;
    appFunctions.dataInsert();
    int option = -1;
    while (option != 0) {

        fmt::print("{}\n", "Wyszukaj hasła - 1");
        fmt::print("{}\n", "Posortuj hasła - 2");
        fmt::print("{}\n", "Dodaj hasło - 3");
        fmt::print("{}\n", "Edytuj hasło - 4");
        fmt::print("{}\n", "Usuń hasło - 5");
        fmt::print("{}\n", "Dodaj kategorie - 6");
        fmt::print("{}\n", "Usuń kategorie - 7");
        fmt::print("{}\n", "Wyjść z programu - 8");
        std::cin >> option;
        switch (option) {
            case 1:
                appFunctions.findPasswords();
                break;
            case 2:
                appFunctions.sortPassword();
                break;
            case 3:
                appFunctions.addPassword();
                break;
            case 4:
                appFunctions.editPassword();
                break;
            case 5:
                appFunctions.removePassword();
                break;
            case 6:
                appFunctions.addCategory();
                break;
            case 7:
                appFunctions.removeCategory();
                break;
            case 8:
                return;
            default:
                std::cout << "Niepoprany argument!" << '\n';
        }
    }
}
