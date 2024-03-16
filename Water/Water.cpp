// Water effect using a shader on sfml

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

const int WIDTH = 512;
const int HEIGHT = 512;

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
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Water Effect");
    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT)); // Create a rectangle that covers the entire window
    sf::Sprite sprite;
    sf::Shader waterShader;
    sf::Texture texture;
    sf::Texture noise;
    sf::Texture noise2;
    sf::Clock clock;

    if (!waterShader.loadFromFile("water_shader.frag", sf::Shader::Fragment)) // Load the water shader from a file
        return -1; // Error
    texture.loadFromFile("stone.jpg"); // Load the stone texture from a file
    texture.setRepeated(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, WIDTH / 4, HEIGHT / 4));
    sprite.setScale(4, 4);
    noise.setRepeated(true); // Noise texture part
    noise.loadFromFile("noise.png");
    waterShader.setUniform("noise", noise);
    noise2.setRepeated(true); // Noise 2 texture part
    noise2.loadFromFile("noise2.png");
    waterShader.setUniform("noise2", noise2);
    while (window.isOpen()) {
        handle_events(window);
        window.clear();
        waterShader.setUniform("time", clock.getElapsedTime().asSeconds());
        window.draw(sprite, &waterShader);
        window.display();
    }
    return 0;
}
