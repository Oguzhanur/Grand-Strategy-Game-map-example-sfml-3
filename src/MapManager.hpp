#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "FileReader.hpp"

enum class TileType {
    LAND,
    WATER
};

struct State{
    std::string stateName;
    sf::Color color;
    std::vector<sf::Vector2u> pixelList;
    std::vector<int> neighbors;
    TileType stateType;
};

class mapManager {
private:
    sf::Image _map;

    sf::Texture _mapTexture;
    sf::Sprite _mapSprite;

public:
    // Sadece fonksiyonların imzaları (prototipleri) kalıyor
    mapManager(std::string imagePath);

    std::unordered_map<int, State> CSVtoState(std::vector<dataType> data);
    
    sf::Color getPixel(sf::Vector2u coords);
    sf::Sprite getSprite();
    sf::Image getImage();
    
};

#endif // MAPMANAGER_HPP