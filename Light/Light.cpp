// Description: A simple (and normalized) light effect using shaders.

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

const int WIDTH = 1024;
const int HEIGHT = 1024;

void handle_events(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Light Effect");
    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT));
    sf::Shader lightShader;
    sf::Texture texture;
    sf::Texture normalMap;
    sf::Sprite sprite;
    sf::Vector2i mouse_pos;

    if (!lightShader.loadFromFile("light.frag", sf::Shader::Fragment)) // Load the light shader from a file
        return -1; // Error
    texture.loadFromFile("diffuse.png");
    sprite.setTexture(texture);
    normalMap.loadFromFile("normal.png");
    lightShader.setUniform("normalMap", normalMap);
    while (window.isOpen()) {
        handle_events(window);
        window.clear();
        mouse_pos = sf::Mouse::getPosition(window);
        mouse_pos.y = HEIGHT - mouse_pos.y;
        lightShader.setUniform("lightPos", sf::Vector2f(mouse_pos.x, mouse_pos.y));
        window.draw(sprite, &lightShader);
        window.display();
    }
    return 0;
}
