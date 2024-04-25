//
// Created by danil on 5/14/2023.
//
#pragma once
#ifndef PASSWORDMANAGER_PASSWORDINFO_H
#define PASSWORDMANAGER_PASSWORDINFO_H

#include <iostream>
/**
 * @brief Represents information about passwords.
 *
 * This structure represents an information about password: passwords name, password, link, login and category.
 */
struct PasswordInfo {
    /**
     * @brief Name of the password.
     */
    std::string name;
    /**
     * @brief Password.
     */
    std::string password;
    /**
     * @brief Link to a site where this password is used.
     */
    std::string www;
    /**
     * @brief Login which is used with a password.
     */
    std::string login;
    /**
     * @brief Category of a password.
     */
    std::string category;

    PasswordInfo(const std::string &name, const std::string &password,
                  const std::string &login, const std::string &www, const std::string &category);
    PasswordInfo();

};


#endif //PASSWORDMANAGER_PASSWORDINFO_H
