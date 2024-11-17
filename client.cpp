#include "client.hpp"
#include "colors.hpp"
#include <iostream>

Client::Client(const std::string& n, const std::string& p, const int& ic):
    nom(n), prenom(p), idClient(ic)
{}

void Client::afficherDetails(const uint8_t& indent_level, const std::string& color) const noexcept{
    std::string indent(indent_level, '\t');
    std::cout << indent << color << BOLD "Client { "          << std::endl <<
        indent << "\tnom: \""    << nom              << "\"," << std::endl <<
        indent << "\tprenom: \"" << prenom           << "\"," << std::endl <<
        indent << "\tidClient: " << idClient                  << std::endl <<
        indent << "}" RESET                                   << std::endl;
}

int Client::getIdClient() const noexcept {
    return idClient;
}
