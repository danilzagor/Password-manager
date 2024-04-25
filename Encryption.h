//
// Created by danil on 5/21/2023.
//
#pragma once
#ifndef PASSWORDMANAGER_ENCRYPTION_H
#define PASSWORDMANAGER_ENCRYPTION_H


class Encryption {
public :
    /**
     * @brief Encrypts/decrypts a file.
     *
     * This function takes text and encrypts/decrypts it with a password by using XOR cipher.
     *
     * @param plaintext Text to encrypt/decrypt.
     * @param password Password to encrypt/decrypt.
     * @param readOrWrite Is this function is used to read from a file or to write in a file.
     * @return Encrypted/decrypted text.
     */
    static std::string encrypt(const std::string &plaintext, const std::string &password, bool readOrWrite);

private:
    /**
     * @brief Reads timestamp from a text.
     *
     * This function reads a timestamp from a text and then modifies it, removes this timestamp and returns modified string.
     * @param plaintext Text with timestamp.
     * @return Text without timestamp.
     */
    static std::string readTimeStamp(const std::string &plaintext);
    /**
     * @brief Puts timestamp from a text.
     *
     * This function puts a timestamp on a text and returns modified string.
     * @param plaintext Text without timestamp.
     * @return Text with timestamp.
     */
    static std::string putTimeStamp(const std::string &plaintext);
};


#endif //PASSWORDMANAGER_ENCRYPTION_H
