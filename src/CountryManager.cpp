#include "CountryManager.hpp"

std::unordered_map<std::string, Country> countryManager::JsonToCountry(json jsonFile, std::unordered_map<std::string, CountryData> countryData){
    std::unordered_map<std::string, Country> output;

    for (auto& [ID, jsonData] : jsonFile.items()){
        Country country;
        // Json Verileri
        country.name = jsonData["name"];

        country.color = sf::Color(
            jsonData["color"][0],
            jsonData["color"][1],
            jsonData["color"][2]
        );

        // Senaryo verileri
        country.ownedStates = countryData[ID].ownedStates;

        // Harita verileri
        country.flagPath = jsonData["flag"];

        // Çıktı
        output[ID] = country;
    }

    return output;
}