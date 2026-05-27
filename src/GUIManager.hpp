#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <string>

class GUIManager {
private:
    sf::RenderWindow& _window;
    sf::Clock _clock;

    std::string _TopR_Path = "source/gui/TopR.png";
    sf::Texture _TopR_Texture;
    
    std::string _TopL_Path = "source/gui/TopL.png";
    sf::Texture _TopL_Texture;

    bool _ownedState_Selected = 0;
    std::string _ownedState_Path = "source/gui/testFlag.png";
    sf::Texture _ownedState_Texture;
    std::optional<sf::Sprite> _ownedState_Sprite;

    std::vector<sf::Sprite> _sprites;

public:
    GUIManager(sf::RenderWindow& window);

    void processEvent(const sf::Event& event);
    void update();
    void selectOwnedCountry(std::string path);
    
    std::vector<sf::Sprite> getSprites();
};

#endif