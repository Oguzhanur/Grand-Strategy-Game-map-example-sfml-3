#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct dataType {
    int id;
    std::string stateName;
    int colorR;
    int colorG;
    int colorB;
};

std::vector<dataType> readMapCSV(const std::string filePath);

json readJsonFile(std::string filePath);



#endif // FILEREADER_HPP