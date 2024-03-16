// Sticky effect using a fragment shader

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <random>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

void handle_events(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void update(std::vector<sf::Vector2f> &points, std::vector<sf::Vector2f> &dir)
{
    static sf::Clock clock;
    float dt = clock.restart().asSeconds() * 100.f;

    for (ulong i = 0; i < points.size(); i++)
    {
        points[i] += dir[i] * dt;
        if (points[i].x < 0) {
            points[i].x = 0;
            dir[i].x *= -1;
        }
        if (points[i].x > WIDTH) {
            points[i].x = WIDTH;
            dir[i].x *= -1;
        }
        if (points[i].y < 0) {
            points[i].y = 0;
            dir[i].y *= -1;
        }
        if (points[i].y > HEIGHT) {
            points[i].y = HEIGHT;
            dir[i].y *= -1;
        }
        dir[i] += sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50) / 5000.f;
        dir[i] /= sqrtf(dir[i].x * dir[i].x + dir[i].y * dir[i].y);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sticky Effect");
    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT));
    sf::Shader waterShader;
    std::vector<sf::Vector2f> pointsGlsl;
    std::vector<sf::Vector2f> dir;
    sf::Vector2f v;

    if (!waterShader.loadFromFile("sticky.frag", sf::Shader::Fragment)) // Load the sticky shader from a file
        return -1; // Error
    for (int i = 0; i < 100; i++)
        pointsGlsl.push_back(sf::Vector2f(rand() % WIDTH, rand() % HEIGHT));
    for (int i = 0; i < 100; i++) {
        v = sf::Vector2f(rand() % 100, rand() % 100);
        dir.push_back(v / sqrtf(v.x * v.x + v.y * v.y));
    }
    waterShader.setUniformArray("points", pointsGlsl.data(), pointsGlsl.size());
    while (window.isOpen()) {
        handle_events(window);
        window.clear();
        update(pointsGlsl, dir);
        waterShader.setUniformArray("points", pointsGlsl.data(), pointsGlsl.size());
        window.draw(rectangle, &waterShader);
        window.display();
    }
    return 0;
}
