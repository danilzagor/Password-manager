//
// Created by danil on 5/14/2023.
//

#include "PasswordInfo.h"

PasswordInfo::PasswordInfo(const std::string &name, const std::string &password,
                            const std::string &login,const std::string &www, const std::string &category) : name(name),
                                                                                                            password(
                                                                                                                    password),
                                                                                                            www(www),
                                                                                                            login(login),
                                                                                                            category(
                                                                                                                    category) {}

PasswordInfo::PasswordInfo() = default;



