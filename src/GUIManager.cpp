#include "GUIManager.hpp"

GUIManager::GUIManager(sf::RenderWindow& window) : _window(window) {
    // Dokuları yükle
    if (_TopR_Texture.loadFromFile(_TopR_Path) &&
        _TopL_Texture.loadFromFile(_TopL_Path)) {

        // Window verileri
        float windowWidth = static_cast<float>(_window.getSize().x);
        
        // TOPR
        sf::Sprite topRSprite(_TopR_Texture);

        float spriteWidth = topRSprite.getGlobalBounds().size.x;
        
        topRSprite.setPosition({windowWidth - spriteWidth, 0.f});

        // TOPL
        sf::Sprite topLSprite(_TopL_Texture);
        
        topLSprite.setPosition({0.f, 0.f});


        // push back
        _sprites.push_back(topRSprite);
        _sprites.push_back(topLSprite);

    } else {
        std::cerr << "GUI LOAD ERROR: /source/gui/" << std::endl;
    }
}

void GUIManager::processEvent(const sf::Event& event) {
    // Eventler
}

void GUIManager::update() {
    // Loop içi komutlar
}

void GUIManager::selectOwnedCountry(std::string path){
    if (path!=""){
        if (!_ownedState_Texture.loadFromFile(path)) {
            std::cerr << "COUNTRY FLAG LOAD ERROR: /source/country/" << std::endl;
        }

        _ownedState_Sprite.emplace(_ownedState_Texture);

        _ownedState_Sprite->setPosition({10.f, 10.f});

        _ownedState_Selected = 1;
    } else {
        _ownedState_Selected = 0;
    }
}

std::vector<sf::Sprite> GUIManager::getSprites() {
    std::vector<sf::Sprite> output;
    output = _sprites;
    
    if (_ownedState_Selected)
        output.push_back(*_ownedState_Sprite);

    return output;
}