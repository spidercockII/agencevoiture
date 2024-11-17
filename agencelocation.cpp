#include "agencelocation.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>


#define CROSS U'\u2716'
#define CHECK U'\u2714'


AgenceLocation::AgenceLocation(const std::vector<Voiture>& vs, const std::vector<Client>& cs, const std::vector<Location>& ls):
    voitures(vs), clients(cs), locations(ls){}

void AgenceLocation::ajouterVoiture(const Voiture& voiture) noexcept{
    voitures.push_back(voiture);
}

void AgenceLocation::ajouterClient(const Client& client) noexcept{
    clients.push_back(client);
}

void AgenceLocation::louerVoiture(int idClient, const std::string& immatriculation, const std::string& dateDebut, const std::string& dateFin){

    std::vector<Client>::iterator c = std::find_if(clients.begin(), clients.end(), [idClient] (const Client& client) -> bool {
        return client.getIdClient() == idClient;
    });
    if( c == clients.end() ){
        throw std::runtime_error("the client with the id you are looking for does not exist in our database ...");
    }


    std::vector<Voiture>::iterator v = std::find_if(voitures.begin(), voitures.end(), [immatriculation](const Voiture& voiture) -> bool {
        return voiture.getImmatriculation() == immatriculation;
    });
    if ( v == voitures.end() ){
        throw std::runtime_error("the car with the immatriculation you are looking for does not exist in our databse ...");
    }


    v -> estDisponiblePourLocation() ?
        locations.push_back(Location(*c, *v, dateDebut, dateFin)) :
        throw std::runtime_error("the car you are looking for is already being rented ...");

    v->changerDisponibilite(true);

}

void AgenceLocation::afficherVoituresDisponibles() const noexcept{
    std::cout << "VoituresDisponibles: [" << std::endl;
    std::for_each(voitures.begin(), voitures.end(), [](const Voiture& v) -> void {
        if(v.estDisponiblePourLocation()){
            v.afficherDetails(1);
            std::cout << ",";
        }
    });
    std::cout << "]" << std::endl;
}

void AgenceLocation::afficherClients() const noexcept{
    std::cout << "Clients: [" << std::endl;
    std::for_each(clients.begin(), clients.end(), [](const Client& c) -> void {
        c.afficherDetails(1);
    });
    std::cout << "]" << std::endl;
}

void AgenceLocation::afficherLocations() const noexcept{
    std::cout << "Locations: [" << std::endl;
    std::for_each(locations.begin(), locations.end(), [](const Location& l) -> void {
        l.afficherDetails(1);
    });
    std::cout << "]" << std::endl;
}


void AgenceLocation::effacerClient(const int& idcl){
    const auto client = std::find_if(clients.begin(), clients.end(), [&idcl](const Client& cl) -> bool {
        return idcl == cl.getIdClient();
    });
    if( client == clients.end() ){
        throw std::runtime_error("the user with the requested id is not found ...");
    }
    clients.erase(client);
}

void AgenceLocation::effacerVoiture(const std::string& mat){
    const auto voiture = std::find_if(voitures.begin(), voitures.end(), [&mat](const Voiture& voi) -> bool {
        return mat == voi.getImmatriculation();
    });
    if( voiture == voitures.end() ){
        throw std::runtime_error("the car with the requested matricule is not found ...");
    }
    voitures.erase(voiture);
}

void AgenceLocation::effacerLocation(const int& idcl, const std::string& mat){
    const auto client = std::find_if(clients.begin(), clients.end(), [&idcl](const Client& cl) -> bool {
        return idcl == cl.getIdClient();
    });
    if( client == clients.end() ){
        throw std::runtime_error("the user with the requested id is not found ...");
    }
    const auto voiture = std::find_if(voitures.begin(), voitures.end(), [&mat](const Voiture& voi) -> bool {
        return mat == voi.getImmatriculation();
    });
    if( voiture == voitures.end() ){
        throw std::runtime_error("the car with the requested matricule is not found ...");
    }
    const auto location = std::find_if(locations.begin(), locations.end(), [&idcl, &mat](const Location& location) -> bool{
        std::pair<int, std::string> out = location.afficherIdentifiants();
        return out.first == idcl && out.second == mat;
    });
    if( location == locations.end()){
        throw std::runtime_error("the location with the data you are looking for could not be located ...");
    }
    locations.erase(location);
}
