#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
    // The game will alwayts be in one of four states
	enum class State { PAUSED, LEVELING_UP,
			GAME_OVER, PLAYING };

	// Start with the GAME_OVER state
	State state = State::GAME_OVER;

	// Get the screen resolution and
	// create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;

	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	// Create an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Here is our clock for timing everything
	Clock clock;

	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in
	// relation to |WORLD| coordinates
	Vector2f mouseWorldPosition;

	// Where is the mouse in
	// relation to |SCREEN| coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// The main game loop
	while (window.isOpen())
	{
		/*
		******************
		Handle input
		******************
		*/

		// Handle events by polling
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{

				}
			}
		}// End event polling

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle WSDA while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WSDA keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}// End WSDA while playing

		// Handle the LEVELING up state
		if (state == State::LEVELING_UP)
		{
			// Handle the player LEVELING up
			if (event.key.code == Keyboard::Num1)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Prepare the level
				// We will modify the next two lines later
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				// We will modify this line of code later
				int tileSize = 50;

				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End LEVELING up

	}// End game loop


	return 0;
}
