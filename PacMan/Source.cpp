#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <math.h>

using namespace sf;



struct Food
{
    int count, point;
    char type;
};

struct Map
{
    int H, W, countFood;
    Food bigFood, smallFood;
    std::string Mase[100];
};

struct GameSettings {
    int screenWidth;
    int screenHeight;
    std::string windowTitle;
    int pacmanSize;
    int ghostSize;
    int foodSize;
    sf::Color pacmanColor;
    sf::Color squareColor;
    sf::Color circleColor;
    sf::Color circle2Color;
    sf::Color blinkyColor; 
    sf::Color pinkyColor;
    sf::Color inkyColor;
    sf::Color clydeColor;
    int gridSize; 
    int pacmanStartX;
    int pacmanStartY;
};

GameSettings* gameSettingsPtr = nullptr;


struct Pacman
{
    int x, y, nextX, nextY,score, nextDirection, lives, points;
};

struct Ghost
{
    int x, y, nextX, nextY, score, direction, lastDirection;
};


void PacmanMove(Pacman& Pacman, Map& Map)
{
    if (Keyboard::isKeyPressed(Keyboard::Up) && Map.Mase[Pacman.nextY - 1][Pacman.nextX] != 'X' && !(Pacman.nextY == 17 && Pacman.nextX == 0 || Pacman.nextY == 17 && Pacman.nextX == Map.W-1)) {
        Pacman.nextDirection = 0;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && Map.Mase[Pacman.nextY + 1][Pacman.nextX] != 'X' && !(Pacman.nextY == 17 && Pacman.nextX == 0 || Pacman.nextY == 17 && Pacman.nextX == Map.W - 1)) {
        Pacman.nextDirection = 1;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && (Map.Mase[Pacman.nextY][Pacman.nextX - 1] != 'X' )) {
        Pacman.nextDirection = 2;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && (Map.Mase[Pacman.nextY][Pacman.nextX + 1] != 'X')) {
        Pacman.nextDirection = 3;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }

    Pacman.score++;
    if (Pacman.score >= 200)
    {
        switch (Pacman.nextDirection)
        {
        case 0:
            if (Map.Mase[Pacman.nextY - 1][Pacman.nextX] != 'X' && Pacman.nextY - 1 >= 0)
                Pacman.nextY--;
            break;
        case 1:
            
            if (Map.Mase[Pacman.nextY + 1][Pacman.nextX] != 'X' && Pacman.nextY + 1 <= 35)
                Pacman.nextY++;
            break;
        case 2:
            if (Pacman.nextY == 17 && Pacman.nextX == 1)
                Pacman.nextX = Map.W - 2;
            else if (Map.Mase[Pacman.nextY][Pacman.nextX - 1] != 'X' && Pacman.nextX - 1 >= 0)
                Pacman.nextX--;
            break;
        case 3:
            if (Pacman.nextY == 17 && Pacman.nextX == Map.W - 2)
                Pacman.nextX = 1;
            else if (Map.Mase[Pacman.nextY][Pacman.nextX + 1] != 'X' && Pacman.nextX + 1 <= 35)
                Pacman.nextX++;
            break;
        }
        Pacman.score = 0;
    }

    if ((Map.Mase[Pacman.nextY][Pacman.nextX] == ' ' || Map.Mase[Pacman.nextY][Pacman.nextX] ==  Map.smallFood.type || Map.Mase[Pacman.nextY][Pacman.nextX] == Map.bigFood.type) && Pacman.nextY != 0 && Pacman.nextX != 0)
    {
        if (Map.Mase[Pacman.nextY][Pacman.nextX] == Map.smallFood.type)
        {
            Pacman.points += Map.smallFood.point;
            Map.smallFood.count--;
        }
        if (Map.Mase[Pacman.nextY][Pacman.nextX] == Map.bigFood.type)
        {
            Pacman.points += Map.bigFood.point;
            Map.bigFood.count--;
        }
        Map.Mase[Pacman.y][Pacman.x] = ' ';
        Map.Mase[Pacman.nextY][Pacman.nextX] = 'P';
        Pacman.x = Pacman.nextX;
        Pacman.y = Pacman.nextY;
    }
}


void MasePaint(Map Map, RenderWindow& window)
{
    RectangleShape square(Vector2f(gameSettingsPtr->gridSize, gameSettingsPtr->gridSize));
    square.setFillColor(gameSettingsPtr->squareColor);
    CircleShape circle(3); 
    circle.setFillColor(gameSettingsPtr->circleColor);
    CircleShape circle2(6);
    circle2.setFillColor(gameSettingsPtr->circle2Color);
    RectangleShape pacman(Vector2f(gameSettingsPtr->gridSize, gameSettingsPtr->gridSize));
    pacman.setFillColor(gameSettingsPtr->pacmanColor);
    for (int i = 0; i < Map.H; i++) 
        for (int j = 0; j < Map.W; j++) 
        {
            if (Map.Mase[i][j] == 'X')
            {
                square.setPosition(j * gameSettingsPtr->gridSize, i * gameSettingsPtr->gridSize);
                window.draw(square);
            }
            else if (Map.Mase[i][j] == Map.smallFood.type)
            {
                circle.setPosition(j * gameSettingsPtr->gridSize + 8.5, i * gameSettingsPtr->gridSize + 8.5f);
                int pacmanX = static_cast<int>(pacman.getPosition().y / gameSettingsPtr->gridSize);
                int pacmanCol = static_cast<int>(pacman.getPosition().x / gameSettingsPtr->gridSize);
                window.draw(circle); 
            }
            else if (Map.Mase[i][j] == Map.bigFood.type)
            {
                circle2.setPosition(j * gameSettingsPtr->gridSize + 5.5f, i * gameSettingsPtr->gridSize + 5.5f);
                window.draw(circle2);
            }
            else if (Map.Mase[i][j] == 'P')
            {
                pacman.setPosition(j * gameSettingsPtr->gridSize, i * gameSettingsPtr->gridSize);
                window.draw(pacman); 
            }
        }
}

float distance(int pacmanX, int pacmanY, int ghostX, int ghostY)
{
    return (sqrt(pow(pacmanX - ghostX, 2) + pow(pacmanY - ghostY, 2)));
}

void GhostMove(Ghost& ghost, int x, int y, Map Map)
{

    float distanceUp;
    float distanceDown;
    float distanceLeft;
    float distanceRight;

    distanceUp = distance(x, y, ghost.x, ghost.y - 1);
    distanceDown = distance(x, y, ghost.x, ghost.y + 1);
    if (ghost.y == 17 && ghost.x == 1)
        distanceLeft = distance(x, y, Map.W - 1, ghost.y);
    else distanceLeft = distance(x, y, ghost.x - 1, ghost.y);
    if (ghost.y == 17 && ghost.x == Map.W - 1)
        distanceRight = distance(x, y, 0, ghost.y);
    else distanceRight = distance(x, y, ghost.x + 1, ghost.y);
    double minDistance = INFINITY;
    int change = 0;

    if (distanceRight <= minDistance && Map.Mase[ghost.y][ghost.x + 1] != 'X'   && ghost.lastDirection != 2) {
        minDistance = distanceRight;
        ghost.direction = 3;
    }
    if (distanceUp <= minDistance && Map.Mase[ghost.y - 1][ghost.x] != 'X' && ghost.lastDirection != 1 && !(ghost.y==17 && ghost.x==0 || ghost.y == 17 && ghost.x == Map.W  - 1)) {
        minDistance = distanceUp;
        ghost.direction = 0;
    }
    if (distanceLeft <= minDistance && Map.Mase[ghost.y][ghost.x - 1] != 'X' && ghost.lastDirection != 3) {
        minDistance = distanceLeft;
        ghost.direction = 2;
    }
    if (distanceDown <= minDistance && Map.Mase[ghost.y + 1][ghost.x] != 'X' && ghost.lastDirection != 0 && !(ghost.y == 17 && ghost.x == 0 || ghost.y == 17 && ghost.x == Map.W - 1)) {
        minDistance = distanceDown;
        ghost.direction = 1;
    }

    ghost.score++;
    if (ghost.score >= 200)
    {
        change = 1;
        // Двигаемся в выбранном направлении
        switch (ghost.direction) {
        case 0: // Движение вверх
            ghost.y--;
            break;
        case 1: // Движение вниз
            ghost.y++;
            break;
        case 2: // Движение влево
            if (ghost.y == 17 && ghost.x == 1)
                ghost.x = Map.W - 2;
            else
                ghost.x--;
            break;
        case 3: // Движение вправо
            if (ghost.y == 17 && ghost.x == Map.W - 2)
                ghost.x = 1;
            else
                ghost.x++;
            break;
        default:
            break; 
        }
        ghost.score = 0;
    }

    if (ghost.lastDirection != ghost.direction && change)
        ghost.lastDirection = ghost.direction;
}

void BlinkyMove(Pacman Pacman, Ghost& Blinky, Map Map)
{
    GhostMove(Blinky, Pacman.x, Pacman.y, Map);
}

void PinkyMove(Pacman Pacman, Ghost& Pinky, Map Map)
{
    int x=Pacman.x, y=Pacman.y;
    switch (Pacman.nextDirection)
    {
    case 0:
        y = y - 4;
        break;
    case 1:
        y = y + 4;
        break;
    case 2:
        x = x - 4;
        break;
    case 3:
        x = x + 4;
        break;
    }
    GhostMove(Pinky, x, y, Map);
}

void InkyMove(Pacman Pacman, Ghost& Inky, Ghost& Blinky, Map Map)
{
    int x = Pacman.x, y = Pacman.y;
    switch (Pacman.nextDirection)
    {
    case 0:
        y = y - 2;
        break;
    case 1:
        y = y + 2;
        break;
    case 2:
        x = x - 2;
        break;
    case 3:
        x = x + 2;
        break;
    }
    x = Blinky.x+2*(x-Blinky.x);
    y = Blinky.y+2*(y-Blinky.y);
    GhostMove(Inky, x, y, Map);
}

void ClydeMove(Pacman Pacman, Ghost& Clyde, Map Map)
{
    int x, y;
    float mainDistance = distance(Pacman.x, Pacman.y, Clyde.x, Clyde.y);
    if (mainDistance > 8)
    {
        x = Pacman.x; 
        y = Pacman.y;
    }
    else
    {
        x = 0;
        y = Map.H;
    }
    GhostMove(Clyde, x, y, Map);
}

int Lose(Pacman& Pacman, Ghost Blinky, Ghost& Pinky, Ghost& Inky, Ghost& Clyde)
{
    int f = 1;
    if (Pacman.x == Blinky.x && Pacman.y == Blinky.y)
        Pacman.lives--;
    else if (Pacman.x == Pinky.x && Pacman.y == Pinky.y)
        Pacman.lives--;
    else if (Pacman.x == Inky.x && Pacman.y == Inky.y)
        Pacman.lives--;
    else if (Pacman.x == Clyde.x && Pacman.y == Clyde.y)
        Pacman.lives--;
    else f = 0;
    return f;
}

void createPacman(Pacman& Pacman) {
    Pacman.x = 14;
    Pacman.y = 26;
    Pacman.nextX = 14;
    Pacman.nextY = 26;
    Pacman.nextDirection = 0;
    Pacman.score = 0;
    Pacman.lives = 3;
    Pacman.points = 0;
}

void createBlinky(Ghost& ghost)
{
    ghost.x = 11;
    ghost.y = 14;
    ghost.score = 0;
}

void createPinky(Ghost& ghost)
{
    ghost.x = 13;
    ghost.y = 14;;
    ghost.score = 0;
}

void createInky(Ghost& ghost)
{
    ghost.x = 15;
    ghost.y = 14;
    ghost.score = 0;
}

void createClyde(Ghost& ghost)
{
    ghost.x = 17;
    ghost.y = 14;
    ghost.score = 0;
}

void createsmallFood(Food& smallFood)
{
    smallFood.count = 240;
    smallFood.point = 5;
    smallFood.type = 'o';
}

void createbigFood(Food& bigFood)
{
    bigFood.count = 4;
    bigFood.point = 10;
    bigFood.type = 'O';
}

void createMap(Map& map, Food smallFood, Food bigFood)
{
    map.H = 35;
    map.W = 30;
    map.smallFood = smallFood;
    map.bigFood = bigFood;
    std::string tempMase[100] = {
        "                              ",
            "                              ",
            "                              ",
            " XXXXXXXXXXXXXXXXXXXXXXXXXXXX ",
            " XooooooooooooXXooooooooooooX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XOXXXXoXXXXXoXXoXXXXXoXXXXOX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XooooooooooooooooooooooooooX ",
            " XoXXXXoXXoXXXXXXXXoXXoXXXXoX ",
            " XoXXXXoXXoXXXXXXXXoXXoXXXXoX ",
            " XooooooXXooooXXooooXXooooooX ",
            " XXXXXXoXXXXX XX XXXXXoXXXXXX ",
            "      XoXXXXX XX XXXXXoX      ",
            "      XoXX          XXoX      ",
            "      XoXX XXXXXXXX XXoX      ",
            " XXXXXXoXX X      X XXoXXXXXX ",
            "       o   X      X   o       ",
            " XXXXXXoXX X      X XXoXXXXXX ",
            "      XoXX XXXXXXXX XXoX      ",
            "      XoXX          XXoX      ",
            "      XoXX XXXXXXXX XXoX      ",
            " XXXXXXoXX XXXXXXXX XXoXXXXXX ",
            " XooooooooooooXXooooooooooooX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XOooXXoooooooPooooooooXXooOX ",
            " XXXoXXoXXoXXXXXXXXoXXoXXoXXX ",
            " XXXoXXoXXoXXXXXXXXoXXoXXoXXX ",
            " XooooooXXooooXXooooXXooooooX ",
            " XoXXXXXXXXXXoXXoXXXXXXXXXXoX ",
            " XoXXXXXXXXXXoXXoXXXXXXXXXXoX ",
            " XooooooooooooooooooooooooooX ",
            " XXXXXXXXXXXXXXXXXXXXXXXXXXXX ",
            "                              ",
    };
    for (int i = 0; i < 100; ++i) {
        map.Mase[i] = tempMase[i];
    }
}

void createGameSettings()
{
    gameSettingsPtr = new GameSettings;
    gameSettingsPtr->screenWidth = 800;
    gameSettingsPtr->screenHeight = 600;
    gameSettingsPtr->windowTitle = "Pac-Man";
    gameSettingsPtr->pacmanSize = 20;
    gameSettingsPtr->ghostSize = 18;
    gameSettingsPtr->foodSize = 10;
    gameSettingsPtr->pacmanColor = sf::Color::Yellow;
    gameSettingsPtr->squareColor = sf::Color::Blue;
    gameSettingsPtr->circleColor = sf::Color::White;
    gameSettingsPtr->circle2Color = sf::Color::White;
    gameSettingsPtr->blinkyColor = sf::Color::Red;
    gameSettingsPtr->pinkyColor = sf::Color(255, 185, 193);
    gameSettingsPtr->inkyColor = sf::Color::Cyan;
    gameSettingsPtr->clydeColor = sf::Color(255, 165, 0);
    gameSettingsPtr->gridSize = 25; 
    gameSettingsPtr->pacmanStartX = 14;
    gameSettingsPtr->pacmanStartY = 26;
}

int WonOrLost(Pacman Pacman, Map Map, Text& Result)
{
    int f = 1;
    if (!(Map.smallFood.count + Map.bigFood.count))
        Result.setString("You won! ");
    else if ((!Pacman.lives))
        Result.setString("You lost! ");
    else f = 0;
    return f;
}

int main()
{
    createGameSettings();
    RenderWindow window(VideoMode(30 * gameSettingsPtr->gridSize, 35 * gameSettingsPtr->gridSize), "Pac-Man");
    Pacman Pacman;
    Ghost Blinky, Pinky, Inky, Clyde;
    Map Map;
    Food bigFood, smallFood;

    RectangleShape blinky(Vector2f(gameSettingsPtr->gridSize, gameSettingsPtr->gridSize));
    blinky.setFillColor(gameSettingsPtr->blinkyColor);
 
    RectangleShape pinky(Vector2f(gameSettingsPtr->gridSize, gameSettingsPtr->gridSize));
    pinky.setFillColor(gameSettingsPtr->pinkyColor);
 
    RectangleShape inky(Vector2f(gameSettingsPtr->gridSize, gameSettingsPtr->gridSize));
    inky.setFillColor(gameSettingsPtr->inkyColor);

    RectangleShape clyde(Vector2f(gameSettingsPtr->gridSize, gameSettingsPtr->gridSize));
    clyde.setFillColor(gameSettingsPtr->clydeColor);
 
    sf::Font font;
    if (!font.loadFromFile("Unformital Medium.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(2* gameSettingsPtr->gridSize, 1* gameSettingsPtr->gridSize);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(40);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(22* gameSettingsPtr->gridSize, 1* gameSettingsPtr->gridSize);

    sf::Text Result;
    Result.setFont(font);
    Result.setCharacterSize(80);
    Result.setFillColor(sf::Color::White);
    Result.setPosition(5 * gameSettingsPtr->gridSize, 10 * gameSettingsPtr->gridSize);
  
    createbigFood(bigFood);
    createsmallFood(smallFood);
    createMap(Map, smallFood, bigFood);
    createPacman(Pacman);
    createBlinky(Blinky);
    createPinky(Pinky);
    createInky(Inky);
    createClyde(Clyde);
    
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color::Black);
            MasePaint(Map, window);
            if (!(WonOrLost(Pacman, Map, Result)))
            {
                BlinkyMove(Pacman, Blinky, Map);
                PinkyMove(Pacman, Pinky, Map);
                InkyMove(Pacman, Inky, Blinky, Map);
                ClydeMove(Pacman, Clyde, Map);
                pointsText.setString("Points " + std::to_string(Pacman.points));
                livesText.setString("Lives " + std::to_string(Pacman.lives));
                window.draw(pointsText);
                window.draw(livesText);
                pinky.setPosition(Pinky.x * gameSettingsPtr->gridSize, Pinky.y * gameSettingsPtr->gridSize);
                blinky.setPosition(Blinky.x * gameSettingsPtr->gridSize, Blinky.y * gameSettingsPtr->gridSize);
                inky.setPosition(Inky.x * gameSettingsPtr->gridSize, Inky.y * gameSettingsPtr->gridSize);
                clyde.setPosition(Clyde.x * gameSettingsPtr->gridSize, Clyde.y * gameSettingsPtr->gridSize);
                window.draw(blinky);
                window.draw(pinky);
                window.draw(inky);
                window.draw(clyde);
                if (Lose(Pacman, Blinky, Pinky, Inky, Clyde))
                {
                    createBlinky(Blinky);
                    createPinky(Pinky);
                    createInky(Inky);
                    createClyde(Clyde);
                    Map.Mase[Pacman.y][Pacman.x] = ' ';
                    Map.Mase[26][14] = 'P';
                    Pacman.nextX = 0;
                    Pacman.nextY = 0;
                    Pacman.x = gameSettingsPtr->pacmanStartX;
                    Pacman.y = gameSettingsPtr->pacmanStartY;
                    Pacman.score = 0;
                    Pacman.nextDirection = 3;
                }
                if (WonOrLost(Pacman, Map, Result))
                {
                    sf::FloatRect textBounds = Result.getLocalBounds();
                    sf::Vector2u windowSize = window.getSize();
                    Result.setPosition((windowSize.x - textBounds.width) / 2, (windowSize.y - textBounds.height) / 2 -50);
                    window.draw(Result);
                }
                PacmanMove(Pacman, Map);
                window.display();
            }
        }
        delete gameSettingsPtr;
        gameSettingsPtr = nullptr;
    return 0;
}