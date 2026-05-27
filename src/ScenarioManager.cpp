#include "ScenarioManager.hpp"

std::unordered_map<std::string, CountryData> scenarioManager::JsonToCountryData(json jsonFile){
    std::unordered_map<std::string, CountryData> output;

    for (auto& [ID, jsonData] : jsonFile.items()){
        CountryData countryData;

        countryData.ownedStates = jsonData["ownedStates"].get<std::vector<int>>();

        output[ID] = countryData;
    }

    return output;
}