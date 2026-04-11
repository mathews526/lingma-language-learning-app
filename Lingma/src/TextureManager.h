#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>
using std::unordered_map;
using std::string;
using std::unique_ptr;

class TextureManager
{
	static unordered_map<string, unique_ptr<sf::Texture>> textures;
	static void LoadTexture(const string& textureName);
public:
	static sf::Texture& GetTexture(const string& textureName);
	static void Clear();
};