#include <SFML/Graphics.hpp>

int main()
{
	unsigned int width = 854;
	unsigned int height = 480;
	// Creates the window
	sf::RenderWindow window(sf::VideoMode({ width, height }), "Lingma");

	// Creates a view (the camera)
	sf::View view(sf::FloatRect({ 0.0f, 0.0f }, { static_cast<float>(width), static_cast<float>(height) }));

	while (window.isOpen()) 
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			// Handles resizing
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				float windowWidth = static_cast<float>(resized->size.x);
				float windowHeight = static_cast<float>(resized->size.y);

				// Updates the view size to match the new window size
				view.setSize({ windowWidth, windowHeight });

				// Resets the center of the view so (0,0) stays at the top-left
				view.setCenter({ windowWidth / 2.0f, windowHeight / 2.0f });

				window.setView(view);
			}
		}

		// Render sprites here

		window.clear(sf::Color(240, 240, 240)); // Light grey background

		// Draw shapes Here

		window.display();
	}

	return 0;
}