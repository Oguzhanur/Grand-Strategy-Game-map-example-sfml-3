#include "ViewManager.hpp"
#include <iostream>
viewManager::viewManager(sf::Vector2f center, sf::Vector2f size){
    _view = sf::View(center, size);
}

sf::View viewManager::getView(){
    return _view;
}

void viewManager::handleInput(){
    float movementSpeed = 3.f * (_view.getSize().x/800);
    // Y ekseni
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        _view.move({0.0f, -movementSpeed});
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        _view.move({0.0f, movementSpeed});
    }
    // X ekseni
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
        _view.move({-movementSpeed, 0.0f});
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
        _view.move({movementSpeed, 0.0f});
    }
    // Zoom
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q)) {
        _view.zoom(0.9f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)) {
        _view.zoom(1.1f);
    }
}