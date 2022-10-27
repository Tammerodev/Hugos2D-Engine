#pragma once
#include <iostream>
#include "..\GameObject.h"



namespace hg {
	struct texture {
		void load(std::string filepath) {
			if (!text.loadFromFile(filepath)) {
				std::cout << "Cant load the texture. Check if \"" << filepath << "\"is correct";
			}
			fpath = filepath;
			resolution = text.getSize();
		}
		std::string getFilePath() {
			return fpath;
		}
		sf::Texture getTexture() {
			return text;
		}
		sf::Vector2u resolution;
	private:
		std::string fpath;
		sf::Texture text;
	};

	class Sprite : public GameObject
	{
	public:
		Sprite(sf::Vector2f siz, sf::Vector2f pos, texture txt, bool phys, uint16_t i) : GameObject(pos, siz,phys,i)
		{
			txSize = txt.resolution;
			txtr.loadFromFile(txt.getFilePath());
			sprite.setTexture(txtr);
		}
		void draw(sf::RenderTarget& target, const sf::Shader*shader) {
			target.draw(sprite,shader);
		}
		void Update(const uint16_t deltaTime) {
			getPhysics().update(deltaTime);
			move(getPhysics().velocity, deltaTime);
			sprite.setScale(getSize().x / txSize.x,getSize().y / txSize.y);
			sprite.setPosition(getPosition());
		}
	//private:
		sf::Texture txtr;
		sf::Vector2u txSize;
		sf::Sprite sprite;
	};
}
