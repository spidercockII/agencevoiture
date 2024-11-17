#ifndef AGENCELOCATION_HPP
#define AGENCELOCATION_HPP


#include <vector>
#include "voiture.hpp"
#include "client.hpp"
#include "location.hpp"

class AgenceLocation{
private:
    std::vector<Voiture> voitures;
    std::vector<Client> clients;
    std::vector<Location> locations;

public:
    AgenceLocation(const std::vector<Voiture>& vs = std::vector<Voiture>(),
                   const std::vector<Client>& cs = std::vector<Client>(),
                   const std::vector<Location>& ls = std::vector<Location>());

    void ajouterVoiture(const Voiture& voiture)                                                                                         noexcept;
    void ajouterClient(const Client& client)                                                                                            noexcept;
    void louerVoiture(int idClient, const std::string& immatriculation, const std::string& dateDebut, const std::string& dateFin)               ;
    void afficherVoituresDisponibles()                                                                                            const noexcept;
    void afficherClients()                                                                                                        const noexcept;
    void afficherLocations()                                                                                                      const noexcept;
    void effacerVoiture(const std::string& mat)                                                                                                 ;
    void effacerClient(const int& idcl)                                                                                                         ;
    void effacerLocation(const int& idcl, const std::string& mat)                                                                               ;
};

#endif
