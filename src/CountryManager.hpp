#ifndef COUNTRYMANAGER_HPP
#define COUNTRYMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include "ScenarioManager.hpp"

using json = nlohmann::json;

struct Country {
    std::string name;
    sf::Color color;
    std::vector<int> ownedStates;
    std::string flagPath;
};

class countryManager{
private:

public:
    std::unordered_map<std::string, Country> JsonToCountry(json jsonFile, std::unordered_map<std::string, CountryData> countryData);
};

#endif // COUNTRYMANAGER_HPP