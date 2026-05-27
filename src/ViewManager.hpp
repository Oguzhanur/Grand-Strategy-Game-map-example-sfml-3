#ifndef VIEWMANAGER_HPP
#define VIEWMANAGER_HPP

#include <SFML/Graphics.hpp>

class viewManager{
private:
    sf::View _view;
    float zoomFactor = 1.0001f;
public:
    viewManager(sf::Vector2f center, sf::Vector2f size);

    sf::View getView();
    void handleInput();
};

#endif // MAPMANAGER_HPP