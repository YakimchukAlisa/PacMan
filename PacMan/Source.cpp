#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <math.h>

using namespace sf;

struct Food
{
    int count, point;
};

struct Map
{
    int H, W, countFood;
    Food bigFood, smallFood;
    std::string Mase[100];

};

RenderWindow window(VideoMode(30 * 25, 35 * 25), "Pac-Man");

struct Pacman
{
    int x, y, nextX, nextY,score, direction, nextDirection, lives, points;
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

    if ((Map.Mase[Pacman.nextY][Pacman.nextX] == ' ' || Map.Mase[Pacman.nextY][Pacman.nextX] == 'o' || Map.Mase[Pacman.nextY][Pacman.nextX] == 'O') && Pacman.nextY != 0 && Pacman.nextX != 0)
    {
        if (Map.Mase[Pacman.nextY][Pacman.nextX] == 'o')
        {
            Pacman.points += Map.smallFood.point;
            Map.smallFood.count--;
        }
        if (Map.Mase[Pacman.nextY][Pacman.nextX] == 'O')
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


void MasePaint(Map Map)
{
    RectangleShape square(Vector2f(25, 25)); 
    square.setFillColor(Color::Blue); 
    CircleShape circle(3); 
    circle.setFillColor(Color::White); 
    CircleShape circle2(6);
    circle2.setFillColor(Color::White); 
    RectangleShape pacman(Vector2f(25, 25));
    pacman.setFillColor(Color::Yellow); 
    for (int i = 0; i < Map.H; i++) 
        for (int j = 0; j < Map.W; j++) 
        {
            if (Map.Mase[i][j] == 'X')
            {
                square.setPosition(j * 25, i * 25); 
                window.draw(square);
            }
            else if (Map.Mase[i][j] == 'o')
            {
                circle.setPosition(j * 25 + 8.5, i * 25 + 8.5f);
                int pacmanX = static_cast<int>(pacman.getPosition().y / 25);
                int pacmanCol = static_cast<int>(pacman.getPosition().x / 25);
                window.draw(circle); 
            }
            else if (Map.Mase[i][j] == 'O')
            {
                circle2.setPosition(j * 25 + 5.5f, i * 25 + 5.5f);
                window.draw(circle2);
            }
            else if (Map.Mase[i][j] == 'P')
            {
                pacman.setPosition(j * 25, i * 25);
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
    Pacman.nextX = 0;
    Pacman.nextY = 0;
    Pacman.direction = 3;
    Pacman.nextDirection = 3;
    Pacman.score = 0;
    Pacman.lives = 3;
    Pacman.points = 0;
}

void createBlinky(Ghost& ghost)
{
    ghost.x = 13;
    ghost.y = 14;
    ghost.score = 0;
}

void createPinky(Ghost& ghost)
{
    ghost.x = 14;
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
    ghost.x = 16;
    ghost.y = 14;
    ghost.score = 0;
}

void createMap(Map& map)
{
    map.H = 35;
    map.W = 30;
    map.smallFood.count = 200;
    map.bigFood.point = 10;
    map.bigFood.count = 4;
    map.smallFood.point = 5;
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

int main()
{
    Pacman Pacman;
    Ghost Blinky, Pinky, Inky, Clyde;
    Map Map;
    RectangleShape blinky(Vector2f(25, 25));
    blinky.setFillColor(Color::Red); 
 
    RectangleShape pinky(Vector2f(25, 25)); 
    pinky.setFillColor(sf::Color(255, 185, 193));
 
    RectangleShape inky(Vector2f(25, 25));
    inky.setFillColor(Color::Cyan); 

    RectangleShape clyde(Vector2f(25, 25)); 
    clyde.setFillColor(sf::Color(255, 165, 0));  
 
    sf::Font font;
    if (!font.loadFromFile("Unformital Medium.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(2*25, 1*25);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(40);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(22*25, 1*25);

    sf::Text Result;
    Result.setFont(font);
    Result.setCharacterSize(80);
    Result.setFillColor(sf::Color::White);
    Result.setPosition(5 * 25, 10 * 25);
  
    createMap(Map);
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
            MasePaint(Map);
            if (Pacman.lives && Map.smallFood.count && Map.bigFood.count)
            {
                PacmanMove(Pacman, Map);
                BlinkyMove(Pacman, Blinky, Map);
                PinkyMove(Pacman, Pinky, Map);
                InkyMove(Pacman, Inky, Blinky, Map);
                ClydeMove(Pacman, Clyde, Map);
                pointsText.setString("Points " + std::to_string(Pacman.points));
                livesText.setString("Lives " + std::to_string(Pacman.lives));
                window.draw(pointsText);
                window.draw(livesText);
                pinky.setPosition(Pinky.x * 25, Pinky.y * 25);
                blinky.setPosition(Blinky.x * 25, Blinky.y * 25);
                inky.setPosition(Inky.x * 25, Inky.y * 25);
                clyde.setPosition(Clyde.x * 25, Clyde.y * 25);
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
                    Pacman.x = 14;
                    Pacman.y = 26;
                    Pacman.score = 0;
                    Pacman.nextDirection = 3;
                }
                if (!(Map.smallFood.count+Map.bigFood.count))
                {
                    Result.setString("You won! ");
                    sf::FloatRect textBounds = Result.getLocalBounds();
                    sf::Vector2u windowSize = window.getSize();
                    Result.setPosition((windowSize.x - textBounds.width) / 2, (windowSize.y - textBounds.height) / 2 - 50);
                    window.draw(Result);
                }
                if (!Pacman.lives)
                {
                    Result.setString("You lost! ");
                    sf::FloatRect textBounds = Result.getLocalBounds();
                    sf::Vector2u windowSize = window.getSize();
                    Result.setPosition((windowSize.x - textBounds.width) / 2, (windowSize.y - textBounds.height) / 2 -50);
                    window.draw(Result);
                }
                window.display();
            }
        }
    return 0;
}