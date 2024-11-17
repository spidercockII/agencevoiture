#ifndef APPCLI_HPP
#define APPCLI_HPP

#include <string>
#include <vector>

void handle_command(const std::string& command);
void help(const std::vector<std::string>&);
void bye_bye(const std::vector<std::string>&);
void version(const std::vector<std::string>&);
void add(const std::vector<std::string>&);
void list(const std::vector<std::string>&);
void remove(const std::vector<std::string>&);


#endif
