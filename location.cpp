#include "location.hpp"
#include "date.hpp"
#include "colors.hpp"
#include <iostream>

Location::Location(const Client cl, const Voiture vo, const std::string& dd, const std::string& df):
    client(cl), voiture(vo), dateDebut(dd), dateFin(df){
        Date ddDateObj(dd);
        Date dfDateObj(df);
    }

void Location::afficherDetails(const uint8_t& indent_level, const std::string& color) const noexcept{
    std::string indent(indent_level, '\t');
    std::cout << indent << color << BOLD "Location { "   << std::endl;
        client.afficherDetails(indent_level+1, color);
        voiture.afficherDetails(indent_level+1, color);
    std::cout << color << BOLD <<
        indent << "\tdateDebut: "        << dateDebut    << std::endl <<
        indent << "\tdateFin: "          << dateFin      << std::endl <<
        indent << "}" RESET                              << std::endl;
}

std::pair<int, std::string> Location::afficherIdentifiants() const noexcept{
    return {client.getIdClient(), voiture.getImmatriculation()};
}
