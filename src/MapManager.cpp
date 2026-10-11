#include "MapManager.hpp"

mapManager::mapManager(std::string imagePath) : _mapTexture(), _mapSprite(_mapTexture){
    // Haritayı Yükleme
    if (_map.loadFromFile(imagePath)) {
        _map = sf::Image(imagePath);
        _mapTexture = sf::Texture(_map);
        _mapSprite = sf::Sprite(_mapTexture);
    } else {
        // Hata durumunda konsola yaz
        std::cerr << "Harita yuklenemedi: " << imagePath << std::endl;
    }
}

// CSV'den state'e
std::unordered_map<int, State> mapManager::CSVtoState(std::vector<dataType> data) {
    std::unordered_map<int, State> states;
    
    // rezerve
    states.reserve(data.size());

    std::unordered_map<uint32_t, int> colorToID;
    for (const auto& d : data)
        colorToID[sf::Color(d.colorR, d.colorG, d.colorB).toInteger()] = d.id;

    // Harita boyutu
    sf::Vector2u size = _map.getSize();

    std::unordered_map<uint32_t, std::vector<sf::Vector2u>> pixelsByColor;

    for (unsigned int y = 0; y < size.y; ++y)
        for (unsigned int x = 0; x < size.x; ++x)
            pixelsByColor[_map.getPixel({x, y}).toInteger()].push_back({x, y});

    // State oluşturma
    for (const auto& d : data) {
        State s;
        s.stateName = d.stateName;
        s.color = sf::Color(d.colorR, d.colorG, d.colorB);

        if (d.stateName.find("DEN") != std::string::npos) {
            s.stateType = TileType::WATER;
        } else {
            s.stateType = TileType::LAND;
        }

        auto it = pixelsByColor.find(s.color.toInteger());
        if (it != pixelsByColor.end())
            s.pixelList = std::move(it->second);

        states.emplace(d.id, std::move(s));
    }

    pixelsByColor.clear();

    // Komşuluk ilişkisi
    const std::vector<sf::Vector2i> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    for (auto& [currentId, state] : states) {
        std::unordered_set<int> neighbors;

        for (const auto& p : state.pixelList) {
            for (const auto& d : dirs) {
                int nx = (int)p.x + d.x;
                int ny = (int)p.y + d.y;

                if (nx < 0 || ny < 0 || nx >= (int)size.x || ny >= (int)size.y)
                    continue;

                auto c = _map.getPixel({(unsigned)nx, (unsigned)ny}).toInteger();

                auto it = colorToID.find(c);
                
                if (it != colorToID.end() && it->second != currentId)
                    neighbors.insert(it->second);
            }
        }

        state.neighbors.assign(neighbors.begin(), neighbors.end());
    }
    
    return states;
}

// get fonksiyonları
sf::Color mapManager::getPixel(sf::Vector2u coords) {
    return _map.getPixel(coords);
}

sf::Sprite mapManager::getSprite() {
    return _mapSprite;
}

sf::Image mapManager::getImage() {
    return _map;
}
