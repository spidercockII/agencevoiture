#include "appcli.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <string>
#include "agencelocation.hpp"
#include "date.hpp"
#include "colors.hpp"


static const std::unordered_map<std::string, void(*)(const std::vector<std::string>&)> available_commands = {
    {"quit", bye_bye},
    {"exit", bye_bye},
    {"q", bye_bye},
    {"help", help},
    {"h", help},
    {"version", version},
    {"v", version},
    {"add", add},
    {"+", add},
    {"a", add},
    {"-", remove},
    {"d", remove},
    {"delete", remove},
    {"del", remove},
    {"list", list},
    {"ls", list},
    {"l", list}
};

static AgenceLocation al;
static int            last_client_id = 0;

static inline std::vector<std::string> splitStringBySpaces(const std::string& input) {
    std::vector<std::string> result;
    std::istringstream instream(input);
    std::string word;

    while (instream >> word) {
        result.push_back(word);
    }

    return result;
}


void handle_command(const std::string& command){

    if(command.empty()) return ;

    std::vector<std::string> vectorized_cmd = splitStringBySpaces(command);
    const auto lu = available_commands.find(vectorized_cmd.at(0));
    if ( lu == available_commands.end() ){
        std::cout << RED BOLD "there is no such command as " << vectorized_cmd.at(0) << std::endl << "type \"help\" for assistance" RESET << std::endl;
        return;
    }
    void (*function)(const std::vector<std::string>&) = lu -> second;
    function({vectorized_cmd.begin()+1, vectorized_cmd.end()});

}

void bye_bye(const std::vector<std::string>& _args){
    std::cout << BLUE BOLD "see you later ..." RESET<< std::endl;
    exit(EXIT_SUCCESS);
}

void help(const std::vector<std::string>& _args){
        std::cout << YELLOW BOLD "Available Commands:" RESET << std::endl;

        // Main commands
        std::cout << GREEN "1. quit / exit" RESET << std::endl;
        std::cout << "   Exits the application." << std::endl;

        std::cout << GREEN "2. help" RESET << std::endl;
        std::cout << "   Displays this help message." << std::endl;

        std::cout << GREEN "3. version" RESET << std::endl;
        std::cout << "   Shows the current version of the car rental manager." << std::endl;

        std::cout << GREEN "4. add [user | car | rent]" RESET << std::endl;
        std::cout << "   Adds a new entity to the system:" << std::endl;
        std::cout << "   - user: Adds a new client to the system." << std::endl;
        std::cout << "   - car: Adds a new car to the system." << std::endl;
        std::cout << "   - rent: Adds a new rent (i.e., a client renting a car)." << std::endl;

        std::cout << GREEN "5. delete [user | car | rent]" RESET << std::endl;
        std::cout << "   Deletes an entity from the system:" << std::endl;
        std::cout << "   - user: Deletes a client by their ID." << std::endl;
        std::cout << "   - car: Deletes a car by its registration number." << std::endl;
        std::cout << "   - rent: Deletes a rent by client ID and car registration number." << std::endl;

        std::cout << GREEN "6. list [users | cars | rents]" RESET << std::endl;
        std::cout << "   Lists the available entities in the system:" << std::endl;
        std::cout << "   - users: Lists all clients." << std::endl;
        std::cout << "   - cars: Lists all available cars." << std::endl;
        std::cout << "   - rents: Lists all active rentals." << std::endl;

        std::cout << YELLOW BOLD "\nAliases:" RESET << std::endl;

        // Aliases section
        std::cout << "add: [+ | a]" RESET << std::endl;
        std::cout << "delete: [del | d | -]" RESET << std::endl;
        std::cout << "list: [ls | l]" << std::endl;
        std::cout << "user: [u]" RESET << std::endl;
        std::cout << "car: [c]" RESET << std::endl;
        std::cout << "rent: [r]" RESET << std::endl;
        std::cout << "version: [v]" RESET << std::endl;
        std::cout << "help: [h]" RESET << std::endl;

        std::cout << YELLOW BOLD "\nGeneral Syntax:" RESET << std::endl;
        std::cout << "  - Use [command] followed by the required arguments." << std::endl;
        std::cout << "  - Aliases are supported for most commands. For example: 'a' for 'add', 'l' for 'list', 'd' for 'delete'." << std::endl;
        std::cout << "  - Shortened commands and their aliases allow for quicker interaction." << std::endl;

        std::cout << YELLOW BOLD "\nFor any further assistance, please contact support!" RESET << std::endl;
}

void version(const std::vector<std::string>& _args){
    std::cout << MAGENTA BOLD "car rental manager v0.0.0, beta" RESET << std::endl;
}

void list(const std::vector<std::string>& args){
    if (args.size() != 1 || (args[0] != "users" && args[0] != "cars" && args[0] != "rents" && args[0] == "u" && args[0] == "c" && args[0] == "r")){
        std::cout << RED BOLD "Wrong Syntax, the correct one is as follows" << std::endl << "list [users-cars-rents]" RESET << std::endl;
        return;
    }
    if ( args[0] == "users" || args[0] == "u"){
        al.afficherClients();
        return;
    }
    if ( args[0] == "cars" || args[0] == "c" ){
        al.afficherVoituresDisponibles();
        return;
    }
    if( args[0] == "rents" || args[0] == "r"){
        al.afficherLocations();
    }
}


static void add_user();
static void add_car();
static void add_rent();

void add(const std::vector<std::string>& args){
    if (args.size() != 1 || (args[0] != "user" && args[0] != "car" && args[0] != "rent" && args[0] == "u" && args[0] == "c" && args[0] == "r")){
        std::cout << RED BOLD "Wrong Syntax, the correct one is as follows" << std::endl << "add [user-car-rent]" RESET << std::endl;
        return;
    }
    if ( args[0] == "user" || args[0] == "u"){
        add_user();
        return;
    }
    if ( args[0] == "car" || args[0] == "c"){
        add_car();
        return;
    }
    if( args[0] == "rent" || args[0] == "r"){
        add_rent();
    }

}

static inline void add_user(){
    std::string nom, prenom;
    std::cout << "nom: " << std::flush;
    std::getline(std::cin, nom);
    std::cout << "prenom: " << std::flush;
    std::getline(std::cin, prenom);
    Client newCl(nom, prenom, last_client_id++);
    al.ajouterClient(newCl);
}

static inline void add_car(){
    std::string marque, modele, immatriculation;
    std::cout << "marque: " << std::flush;
    std::getline(std::cin, marque);
    std::cout << "modele: " << std::flush;
    std::getline(std::cin, modele);
    std::cout << "immatriculation: " << std::flush;
    std::getline(std::cin, immatriculation);
    Voiture newVoi(marque, modele, immatriculation, true);
    al.ajouterVoiture(newVoi);

}

#include <chrono>
#include <ctime>
#include <iomanip>
#include <limits>

static inline std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

static inline void add_rent(){
    std::string immatriculation, dateFin;
    int idClient;
    std::cout << "idClient: " << std::flush;
    std::cin >> idClient;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear buffer up to the next newline
    std::cout << "immatriculation: " << std::flush;
    std::getline(std::cin, immatriculation);
    std::cout << "dateFin " << BLUE BOLD << "(format: dd/mm/yyyy): " << RESET << std::flush;
    std::getline(std::cin, dateFin);
    try {
        Date d(dateFin);
    } catch ( const std::exception& e){
        std::cout << RED BOLD << e.what() << RESET << std::endl;
        return;
    }
    try {
        al.louerVoiture(idClient, immatriculation, getCurrentDate(), dateFin);
    } catch ( const std::exception&e ){
        std::cout << RED BOLD << e.what() << RESET << std::endl;
        return;
    }
    std::cout << GREEN BOLD "Renting finished successfully!" RESET << std::endl;
}


void remove(const std::vector<std::string>& args){
    if (args.size() != 1 || (args[0] != "users" && args[0] != "cars" && args[0] != "rents" && args[0] == "u" && args[0] == "c" && args[0] == "r")){
        std::cout << RED BOLD "Wrong Syntax, the correct one is as follows" << std::endl << "delete [user-car-rent]" RESET << std::endl;
        return;
    }
    if ( args[0] == "users" || args[0] == "u"){
        int idClient;
        std::cout << "input the client id: " << std::flush;
        std::cin >> idClient;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear buffer up to the next newline
        try {
            al.effacerClient(idClient);
        } catch( const std::exception& e){
            std::cout << RED BOLD << e.what() << RESET << std::endl;
        }
        return;
    }
    if ( args[0] == "cars" || args[0] == "c" ){
        std::string mat;
        std::cout << "input the matricule: " << std::flush;
        std::getline(std::cin, mat);
        try {
            al.effacerVoiture(mat);
        } catch( const std::exception& e){
            std::cout << RED BOLD << e.what() << RESET << std::endl;
        }
        return;
    }
    if( args[0] == "rents" || args[0] == "r"){
        int idClient;
        std::cout << "input the client id: " << std::flush;
        std::cin >> idClient;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear buffer up to the next newline
        std::string mat;
        std::cout << "input the matricule: " << std::flush;
        std::getline(std::cin, mat);
        try {
            al.effacerLocation(idClient, mat);
        } catch ( const std::exception& e){
            std::cout << RED BOLD << e.what() << RESET << std::endl;
        }
    }
}
