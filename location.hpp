#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <cstdint>
#include "voiture.hpp"
#include "client.hpp"
#include "config.hpp"

class Location{
private:
    Client      client;
    Voiture     voiture;
    std::string dateDebut;
    std::string dateFin;
public:
    Location(const Client cl, const Voiture vo, const std::string& dd, const std::string& df);

    void                        afficherDetails(const uint8_t& indent_level = 0, const std::string& color = LOCATI_DEF) const noexcept;
    std::pair<int, std::string> afficherIdentifiants()                                                                  const noexcept;
};


#endif
