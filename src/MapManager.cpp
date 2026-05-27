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

// CSV'den state'e çevirme
std::unordered_map<int, State> mapManager::CSVtoState(std::vector<dataType> data) {
    // Sonunda verilecek değişkeni unordered_map olarak tanımlıyoruz
    std::unordered_map<int, State> states;
    
    // Rehashing'i (performans kaybını) önlemek için baştan yer ayırıyoruz
    states.reserve(data.size());

    // Rengi idye çevirirken kolaylık için
    std::unordered_map<uint32_t, int> colorToID;
    for (const auto& d : data)
        colorToID[sf::Color(d.colorR, d.colorG, d.colorB).toInteger()] = d.id;

    // Harita boyutu
    sf::Vector2u size = _map.getSize();

    // Pixel -> color grouping (tek geçiş)
    std::unordered_map<uint32_t, std::vector<sf::Vector2u>> pixelsByColor;

    for (unsigned int y = 0; y < size.y; ++y)
        for (unsigned int x = 0; x < size.x; ++x)
            pixelsByColor[_map.getPixel({x, y}).toInteger()].push_back({x, y});

    // State oluşturma
    for (const auto& d : data) {
        State s;
        // s.id = d.id; satırı kaldırıldı.
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

        // Vector'e push_back yapmak yerine Map'e emplace (yerleştirme) yapıyoruz
        states.emplace(d.id, std::move(s));
    }

    pixelsByColor.clear();

    // Komşuluk ilişkisi
    const std::vector<sf::Vector2i> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    // std::unordered_map üzerinde dönerken C++17 Structured Binding kullanıyoruz
    // currentId = int (Key), state = State (Value)
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
                // state.id artık olmadığı için kontrolü map'in anahtarı olan currentId ile yapıyoruz
                if (it != colorToID.end() && it->second != currentId)
                    neighbors.insert(it->second);
            }
        }

        state.neighbors.assign(neighbors.begin(), neighbors.end());
    }
    
    return states;
}

// Koordinata göre piksel rengini dönen fonksiyon
sf::Color mapManager::getPixel(sf::Vector2u coords) {
    return _map.getPixel(coords);
}

// Sprite nesnesini dönen fonksiyon
sf::Sprite mapManager::getSprite() {
    return _mapSprite;
}

// İmage nesnesini dönen fonksiyon
sf::Image mapManager::getImage() {
    return _map;
}