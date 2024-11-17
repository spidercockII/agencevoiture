#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "config.hpp"
#include <cstdint>
#include <string>

class Client{
private:
    std::string nom     ;
    std::string prenom  ;
    int         idClient;
public:
    Client(const std::string& n, const std::string& p, const int& ic);

    void afficherDetails(const uint8_t& indent_level = 0, const std::string& color = CLIENT_DEF ) const noexcept;
    int  getIdClient()                                                                            const noexcept;
};

#endif
