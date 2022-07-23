#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265358979323846 
using namespace sf;
const Vector2f playerSize(120.f, 10.f);

struct Player {
    RectangleShape shape;
    float moveStep;
    Player() {
        shape.setSize(playerSize);
        shape.setOrigin(Vector2f(playerSize.x / 2, 0));
        shape.setPosition(Vector2f(WIDTH / 2, HEIGHT - 45.f));
        moveStep = 25.f;
    }
    void move(float f) {
        shape.move(Vector2f(f, 0));
    }
};

struct Ball {
    int x, y;
    float radius;
    CircleShape shape;
    Ball(float param_radius) {
        radius = param_radius;
        shape.setRadius(radius);
        x = WIDTH /4;
        y = HEIGHT/2;
        shape.setPosition(Vector2f(x, y));
        shape.setOrigin(Vector2f(shape.getRadius() / 1.414f, shape.getRadius() / 1.414f));
    }
    void setPosition() {
        x = shape.getPosition().x;
        y = shape.getPosition().y;
    }
};
struct rectangle {
    RectangleShape shape;
    int status;
    rectangle() {
        status = 0;
    }
};
int rectangleCount = 10;
Ball ball(10.f);
Vector2f move(cos(PI/4), -sin(PI/4));
float moveStep = 0.5f;
Player player;
enum GameStates { active, paused, finished };
Vector2f rectanglesSize(40.f, 40.f);
rectangle rectangles[10];
int count = 10;
int main()
{
    for (int i = 0; i < 10; ++i) {
        rectangles[i].shape.setSize(rectanglesSize);
        rectangles[i].shape.setOrigin(Vector2f(rectanglesSize.x / 2.f , rectanglesSize.y ));
        rectangles[i].shape.setPosition(Vector2f(40.f +  ((WIDTH / 10) * i) , 80.f));
    }
    Font font;
    if (!font.loadFromFile("BebasNeue-Regular.ttf")) {
        std::cout << "unable to load font" << std::endl;
    }

    RenderWindow window(VideoMode(HEIGHT, WIDTH), "I don't know this game's name :(");
    GameStates gameState = active;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (player.shape.getPosition().x - player.shape.getSize().x / 2 >= 0)
                        player.move(-player.moveStep);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (player.shape.getPosition().x + player.shape.getSize().x / 2 <= WIDTH)
                        player.move(player.moveStep);
                }
            }
        }
        if (gameState == active) {
            if (count == 0) {
                Text winmsg("You Won!", font, 20U);
                winmsg.setPosition(Vector2f(WIDTH / 2, HEIGHT / 2));
                winmsg.setScale(Vector2f(4.f , 4.f));
                winmsg.setOrigin(Vector2f(30.f, 10.f));
                window.clear();
                window.draw(winmsg);
                window.display();
            }
            else {
                window.clear();
                window.draw(ball.shape);
                window.draw(player.shape);
                for (int i = 0; i < 10; ++i) {
                    if (rectangles[i].status == 0) {
                        window.draw(rectangles[i].shape);
                    }
                }
                window.display();

                if (ball.shape.getPosition().y <= ball.radius) {
                    move.y = -move.y;
                }
                else if (ball.shape.getPosition().y >= HEIGHT - ball.radius) {
                    ball.shape.setPosition(Vector2f(20.f, 50.f));
                    move = Vector2f(1.f, -1.f);
                    Clock resetBallClock;
                    while (resetBallClock.getElapsedTime().asSeconds() < 1.f) {

                    }
                    resetBallClock.restart();
                }
                else if (ball.shape.getPosition().x <= ball.radius) {
                    move.x = -move.x;
                }
                else if (ball.shape.getPosition().x >= WIDTH - ball.radius) {
                    move.x = -move.x;
                }
                else if ((ball.shape.getPosition().y + ball.radius - player.shape.getPosition().y < 0) && (ball.shape.getPosition().y + ball.radius - player.shape.getPosition().y > -2.f)) {
                    if ((ball.shape.getPosition().x <= player.shape.getPosition().x + (playerSize.x / 2) + ball.radius + 10.f) && (ball.shape.getPosition().x >= player.shape.getPosition().x - (playerSize.x / 2) - ball.radius - 10.f)) {
                        float ratio = ((ball.shape.getPosition().x - player.shape.getPosition().x)) / (playerSize.x / 2 + ball.radius);
                        if ((abs(ratio) >= 0.f) && (abs(ratio) < 0.25f)) {
                            move.x = cos(3*PI / 8);
                            move.y = -sin(3*PI / 8);
                        }
                        else if ((abs(ratio) >= 0.25f) && (abs(ratio) < 0.5f)) {
                            move.x = cos(PI / 4);
                            move.y = -move.x;
                        }
                        else if ((abs(ratio) >= 0.5f) && (abs(ratio) < 0.75f)) {
                            move.x = cos(PI / 6);
                            move.y = -sin(PI / 6);
                        }
                        else if ((abs(ratio) >= 0.75f) && (abs(ratio) < 1.f)) {
                            move.x = cos(PI / 8);
                            move.y = -sin(PI / 8);
                        }
                        if (ratio < 0) {
                            move.x = -move.x;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 10; ++i) {
                        if ((ball.shape.getPosition().y + ball.radius - rectangles[i].shape.getPosition().y <= 0) && (ball.shape.getPosition().y + ball.radius - rectangles[i].shape.getPosition().y >= -rectanglesSize.y)) {
                            if ((ball.shape.getPosition().x <= rectangles[i].shape.getPosition().x + (rectanglesSize.x / 2) + ball.radius) && (ball.shape.getPosition().x >= rectangles[i].shape.getPosition().x - (rectanglesSize.x / 2) - ball.radius)) {
                                if (rectangles[i].status == 0) {
                                    move.y = -move.y;
                                    rectangles[i].status = 1;
                                    count--;
                                }
                            }
                        }
                    }
                }
                ball.shape.move(move * moveStep);
                ball.setPosition();
            }
        }
    }

    return 0;
}
