#ifndef SCENARIOMANAGER_HPP
#define SCENARIOMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <unordered_map>

using json = nlohmann::json;

struct CountryData{
    std::vector<int> ownedStates;
};

class scenarioManager{
private:

public:
    std::unordered_map<std::string, CountryData> JsonToCountryData(json jsonFile);
    
};

#endif // SCENARIOMANAGER_HPP