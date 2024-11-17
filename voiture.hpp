#ifndef VOITURE_HPP
#define VOITURE_HPP

#include <cstdlib>
#include <string>
#include <unordered_set>
#include <cstdint>
#include "config.hpp"

#define T     "true"
#define F     "false"


class Voiture{
private:
	static std::unordered_set<std::string> immatriculationsSauvegardeur;
	std::string marque;
	std::string modele;
	std::string immatriculation;
	bool 	    estDisponible;
public:
	Voiture(const std::string& ma, const std::string& mo, const std::string& im, const bool& estd);

	void 		afficherDetails(const uint8_t& indent_level = 0, const std::string& color = VOITUR_DEF) 	const noexcept;
	bool 		estDisponiblePourLocation() 																const noexcept;
	void 		changerDisponibilite(const bool& dispo)	              				      					  	  noexcept;
	std::string getImmatriculation()																		const noexcept;
};

#endif
