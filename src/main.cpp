#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "FileReader.hpp"
#include "MapManager.hpp"
#include "ViewManager.hpp"
#include "CountryManager.hpp"
#include "ScenarioManager.hpp"
#include "GUIManager.hpp"

int selectedStateID = 0;


int main(){
	// Ekranı oluşturma
	sf::Vector2u ScreenSize = sf::VideoMode::getDesktopMode().size;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Ekran", sf::State::Fullscreen);
	window.setFramerateLimit(60);
	
	// Map Manager
	mapManager mapMan("source/map/map.png");
    std::unordered_map<int, State> states = mapMan.CSVtoState(readMapCSV("source/map/map.csv"));

	// Scenario Manager
	scenarioManager scenarioMan;
	std::unordered_map<std::string, CountryData> countryData = scenarioMan.JsonToCountryData(readJsonFile("source/scenarios/main.json"));
	
	// Country Manager
	countryManager countryMan;
	std::unordered_map<std::string, Country> countrys = countryMan.JsonToCountry(readJsonFile("source/countrys.json"), countryData);

	// View Manager
	sf::Vector2f center = {ScreenSize.x/2.f, ScreenSize.y/2.f};
	sf::Vector2f size = (sf::Vector2f)ScreenSize;
	viewManager viewMan(center, size);
	
	// GUI Manager
	GUIManager GUIMan(window);

	// while Döngüsü
	while ( window.isOpen() ){
		// pollEventler
		while ( const std::optional event = window.pollEvent() ){
			if ( event->is<sf::Event::Closed>() )
				window.close();
			// GUI eventleri
			GUIMan.processEvent(*event);
			// Fare tıklaması
			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()){
					// Sol tık kontrolü
					if (mousePressed->button == sf::Mouse::Button::Left){
						selectedStateID = 0;
						// Konumları al
						sf::Vector2i localPosition = mousePressed->position;
						sf::Vector2f worldPosition = window.mapPixelToCoords(localPosition, window.getView());

						// Tıklanan konumun rengini alma
						if (mapMan.getSprite().getGlobalBounds().contains(worldPosition)) {
							sf::Color clickedColor = mapMan.getPixel({ 
								static_cast<unsigned int>(worldPosition.x), 
								static_cast<unsigned int>(worldPosition.y) 
							});

							std::cout
								<< +clickedColor.r << ","
								<< +clickedColor.g << ","
								<< +clickedColor.b << std::endl;
								
							// Değerleri uyuşan şehir var mı?
							for (auto& [stateID, state] : states) {
								if (state.color == clickedColor) {
									std::cout << state.stateName << ": " << (int)stateID << std::endl;
									selectedStateID = stateID;
									GUIMan.selectOwnedCountry("");
									//shaderMan.setColor(state.color,sf::Color(10,51,200));
									// Bir ülkeye aitmi?
									for (const auto& [id, country] : countrys) {
										for (int state : country.ownedStates) {
											if (state == selectedStateID){
												std::cout << country.name << std::endl;
												GUIMan.selectOwnedCountry(country.flagPath);
											}
										}
									}
								}
							}
						}
					}
				}
			}

		// Hareketler
		viewMan.handleInput();

		// GUI Update
		GUIMan.update();

		// Ekranı temizleme
		window.clear();

		// Viewi ayarla
		window.setView(viewMan.getView());

		// Çizimler
		window.draw(mapMan.getSprite());

		// Kullanıcı arayüzü
		window.setView(window.getDefaultView());
		
		const auto& guiSprites = GUIMan.getSprites();
        for (const auto& sprite : guiSprites) {
            window.draw(sprite);
        }

		window.setView(viewMan.getView());

		// Çizimleri yazdır
		window.display();
	}
}