//
// Created by danil on 5/21/2023.
//
#pragma once
#ifndef PASSWORDMANAGER_FILEOPERATIONS_H
#define PASSWORDMANAGER_FILEOPERATIONS_H

#include <iostream>
class FileOperations {
    /**
     * @brief Name of the file that user provides.
     */
    std::string fileName;
    /**
     * @brief Password to the file to encrypt and decrypt file.
     */
    std::string key;
public:
    /**
     * @brief Reads information from file.
     *
     * This function takes a file from a user. User can choose file in the directory of a program or give an absolute path to it.
     * When file was given, reads information from it and sends it to the decryption.
     * At the end returns decrypted string with passwords.
     *
     * @return a decrypted string of passwords.
     */
    std::string readFromFile();
    /**
     * @brief Writes to the file information about passwords.
     *
     * This function sends string that contains all information about passwords to the encryption
     * and then writes this string to the file.
     * @param passwordsInfo Map of passwords.
     */
    void makeChange(const std::map<std::string, std::vector<PasswordInfo>>&);
private:
    /**
     * @brief Finds files in a directory.
     *
     * This function finds files with a .txt extension in a directory where program is located and if user
     * chooses one of this files then returns a path to it.
     *
     * @return Path to the file as a string.
     */
    std::string findFile();
};


#endif //PASSWORDMANAGER_FILEOPERATIONS_H
