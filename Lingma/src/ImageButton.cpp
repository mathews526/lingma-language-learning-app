#include "ImageButton.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
using namespace std;

/*==== Constructors ====*/
ImageButton::ImageButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName)
	: Button(size, position, color), icon(TextureManager::GetTexture(textureName))
{
	UpdateIcon();
}

/*==== Main Functions ====*/
void ImageButton::DrawButton(sf::RenderWindow& window)
{
	Button::DrawButton(window);
	window.draw(icon);
}

/*==== Helper Functions ====*/
void ImageButton::UpdateIcon()
{
	const sf::Texture texture = icon.getTexture();

	sf::Vector2u textureSize = texture.getSize();
	sf::Vector2f buttonSize = button.getSize();

	float availableWidth = buttonSize.x;
	float availableHeight = buttonSize.y;

	float scaleX = availableWidth / static_cast<float>(textureSize.x);
	float scaleY = availableHeight / static_cast<float>(textureSize.y);

	float scale = min(scaleX, scaleY);

	icon.setScale({ scale, scale });

	sf::FloatRect bounds = icon.getLocalBounds();
	icon.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f }); // Moves sprite's origin to its center

	icon.setPosition(button.getPosition());
}
void ImageButton::SetPosition(const sf::Vector2f& pos)
{
	Button::SetPosition(pos);
	icon.setPosition(pos);
}