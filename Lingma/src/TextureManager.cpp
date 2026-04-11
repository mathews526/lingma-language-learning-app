#include "TextureManager.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

unordered_map<string, unique_ptr<sf::Texture>> TextureManager::textures;

void TextureManager::LoadTexture(const string& fileName)
{
	string path = "visuals/" + fileName + ".png";

	auto texture = make_unique<sf::Texture>();

	if (!texture->loadFromFile(path))
		std::cerr << "Error: TextureManager failed to load " << path << "\n";

	textures[fileName] = move(texture);
}

sf::Texture& TextureManager::GetTexture(const string& textureName)
{
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return *textures[textureName];
}

void TextureManager::Clear()
{
	textures.clear();
}