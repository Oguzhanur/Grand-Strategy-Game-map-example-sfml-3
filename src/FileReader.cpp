#include "FileReader.hpp"

std::vector<dataType> readMapCSV(const std::string filePath){
    std::vector<dataType> list;
    std::ifstream file(filePath);
    // Dosya açılmazsa
    if (!file.is_open()) {
        std::cerr << "Hata: Dosya acilamadi!" << std::endl;
        return list;
    }
    // değişkenler
    int curentLine = 0;
    // Satır satır okuma işlemi
    std::string line;
    while (std::getline(file, line)) {
        curentLine++;
        // Satır boşsa geç
        if (line.empty()) continue;
        // Satır parçalarını belirtme
        std::stringstream ss(line);
        std::string name, r_str, g_str, b_str;

        // Satırı parçalama
        std::getline(ss, name, ',');  // Sehir Adı
        std::getline(ss, r_str, ','); // R
        std::getline(ss, g_str, ','); // G
        std::getline(ss, b_str, ','); // B

        // Verileri yazdırma
        dataType data;
        data.id = curentLine;
        data.stateName = name;
        data.colorR = std::stoi(r_str);
        data.colorG = std::stoi(g_str);
        data.colorB = std::stoi(b_str);
        
        list.push_back(data);
    }

    file.close();
    return list;
}


json readJsonFile(std::string filePath){

    std::ifstream file(filePath);

    if (!file.is_open()) {

        std::cerr << "Dosya acilamadi!" << std::endl;

        return json{};
    }

    json data;

    file >> data;

    file.close();

    return data;
}