//
// Created by danil on 5/14/2023.
//
#pragma once
#ifndef PASSWORDMANAGER_APPFUNCTIONS_H
#define PASSWORDMANAGER_APPFUNCTIONS_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "PasswordInfo.h"
#include "FileOperations.h"

/**
 * @brief All operations related to passwords.
 *
 * A structure that contains functions related to password operations:
 * adding, removing categories, adding, removing, editing, sorting passwords.
 */
struct AppFunctions {
    /**
     * @brief Password information.
     *
     * A map that uses category names as keys and stores a vector of password information as values.
     */
    std::map<std::string, std::vector<PasswordInfo>> passwordsInfo;
    /**
     * @brief Class for file operations.
     *
     * A class that handles file operations to make changes to the file.
     */
    FileOperations fileOperations;

    /**
     * @brief Adds a category.
     */
    void addCategory();

    /**
     * @brief Adds a password.
     *
     * This function adds a password to a category. The password can be entered or generated.
     * Entering a password displays its security level and information on whether it has been used.
     */
    void addPassword();

    /**
     * @brief Finds passwords.
     *
     * This function finds and displays passwords based on 4 selectable parameters: category, name, password, login.
     */
    void findPasswords();

    /**
     * @brief Inserts previous passwords into the program.
     *
     * This function receives the entire decrypted text from the source file and creates categories and passwords.
     */
    void dataInsert();

    /**
     * @brief Edits a password.
     *
     * This function edits a password. All parameters can be edited at the same time.
     */
    void editPassword();

    /**
     * @brief Sorts and displays passwords.
     *
     * This function sorts passwords based on 2 parameters at the same time. You can sort by category and name or vice versa.
     */
    void sortPassword();

    /**
     * @brief Removes a password.
     *
     * This function finds and removes a password.
     */
    void removePassword();

    /**
     * @brief Removes a category.
     */
    void removeCategory();

private:
    /**
     * @brief Checks the security of a password and whether it has been used before.
     *
     * This function checks the security of a password based on 3 parameters: length, presence of special characters, presence of uppercase letters,
     * and checks if the password has been used in other passwords.
     *
     * @param password The password to be checked.
     */
    void checkPassword(std::string password);

    /**
     * @brief Generates a password.
     *
     * This function generates a password based on 3 parameters: length, presence of uppercase letters, presence of special characters.
     *
     * @param number The length of the generated password.
     * @param aCase Presence of uppercase letters.
     * @param ch Presence of special characters.
     */
    static std::string generatePassword(int number, bool aCase, bool ch);
    /**
     * @brief Returns parameter of a PasswordInfo class
     *
     * This function returns a parameter of a PasswordInfo class depending on an option argument. Is used for sorting.
     *
     * @param option What parameter do you want to get.
     * @param pass Object of PasswordInfo class.
     * @return parameter as a string.
     */
    static std::string returnParam(int option, const PasswordInfo& pass);
};


#endif //PASSWORDMANAGER_APPFUNCTIONS_H
