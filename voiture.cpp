#include "voiture.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "colors.hpp"

std::unordered_set<std::string> Voiture::immatriculationsSauvegardeur;

Voiture::Voiture(const std::string& ma, const std::string& mo, const std::string& im, const bool& estd):
        marque(ma), modele(mo), immatriculation(im), estDisponible(estd)
{
    if( immatriculationsSauvegardeur.find(im) != immatriculationsSauvegardeur.end() ){
        throw std::invalid_argument("L'immatriculation doit etre unique!");
    }
    else{
        immatriculationsSauvegardeur.insert(im);
    }
}

void Voiture::afficherDetails(const uint8_t& indent_level, const std::string& color) const noexcept {
    std::string indent(indent_level, '\t');
    std::cout << indent << color  << BOLD "Voiture { "                    << std::endl <<
        indent << "\tmarque: \""          << marque              << "\"," << std::endl <<
        indent << "\tmodele: \""          << modele              << "\"," << std::endl <<
        indent << "\timmatriculation: \"" << immatriculation     << "\"," << std::endl <<
        indent << "\tdisponible: "        << (estDisponible?T:F)          << std::endl <<
        indent << "}" RESET                                               << std::endl;
}

bool Voiture::estDisponiblePourLocation() const noexcept {
    return estDisponible;
}

void Voiture::changerDisponibilite(const bool& dispo) noexcept {
    estDisponible = dispo;
}

std::string Voiture::getImmatriculation() const noexcept{
    return immatriculation;
}


