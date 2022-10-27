#pragma once
#include "Display.h"
#include "GameObject/Rectangle.h"
#include "GameObject/Sprite.h"
#include "Shader.h"
#include "stadfx.h"




class Game
{
public:
	void newGameObject(const std::string &id, hg::Rectangle*obj) {
		rects.insert({ id,obj });
	}
	void newGameObject(const std::string& id, hg::Sprite* obj) {
		sprites.insert({ id,obj });
	}
	double calculateDistance(sf::Vector2f x, sf::Vector2f y)
	{
		return sqrt(pow(x.x - y.x, 2) +
			pow(x.y - y.y, 2));
	}
	template<typename T>
	void checkCollisionsFor(T & obj, hg::GameObject::Type type) {
		switch (type)
		{
		case hg::GameObject::RectangleShape:
			for (auto& r : rects) {
			
				if (obj.id != r.second->id) {
						if (obj.hitbox.intersects(r.second->hitbox)) {
							obj.absMove(-(obj.getPhysics().velocity.x),
								-(obj.getPhysics().velocity.y+10*250), (deltaTime / 250));
						}
				}
				else {
					std::cout << obj.id << ',' << r.second->id << '\n';
				}
			}
			break;
		case hg::GameObject::Sprite:
			break;
		default:
			break;
		}
	}
	hg::GameObject &getGameObject(const std::string& id, hg::GameObject::Type type) {
		switch (type)
		{
		case hg::GameObject::RectangleShape:
			return *(hg::Rectangle*)rects.at(id);
			break;
		case hg::GameObject::Sprite:
			return *(hg::Sprite*)sprites.at(id);
			break;
		default:
			std::cout << "getGameObject() - method is not implemented for this shape type yet.";
			break;
		}
	}
	
	bool isKeyPressed(sf::Keyboard::Key key) {
		return display.isKeyPressed(key);
	}
	
	Game() {
		
		shader.loadShaders(std::make_pair("Shaders\\Fragment_shader.frag", "Shaders\Vertex_shader.vert"));
		display.createWindow("Game");
		gameInit();
		view.setSize(display.getSize().x, display.getSize().y);
		m_gameLoop();
	}
	void setCameraPosition(sf::Vector2f pos) {
		view.setCenter(pos);
	}
	void setCameraPosition(float x,float y) {
		view.setCenter({x,y});
	}
private:
	sf::View view;
	std::map<std::string, hg::Rectangle*> rects;
	std::map < std::string, hg::Sprite* > sprites;
	hg::Shader shader;
	float deltaTime = 0.0f;
	sf::Clock deltaCock;
	void m_gameLoop() {
		while (running) {
			while (display.hasEvents()) {
				if (display.shouldClose()) {
					display.closeWindow();
					running = false;
				}
			}
			display.clearDisplay();
			display.setView(view);
			for (auto& rect : rects) {
				rect.second->draw(display, &shader);
				rect.second->Update(deltaTime);
			}
			for (auto& rect : sprites) {
				rect.second->draw(display,&shader);
				rect.second->Update(deltaTime);
			}
			gameLoop(deltaTime);
			display.show();
			deltaTime = deltaCock.restart().asMicroseconds()/100;
		}
	}
	bool running = true;
	Display display;
	void gameInit();
	void gameLoop(float delta);
};
