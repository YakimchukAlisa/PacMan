#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <math.h>

using namespace sf;


struct Map
{
    int H = 35, W = 30;
    std::string Mase[35] = {
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
}
Map;

RenderWindow window(VideoMode(Map.W * 25, Map.H * 25), "Pac-Man");

struct Pacman
{
    int x, y, nextX, nextY,score, direction, nextDirection, lifes, points;
} Pacman;

struct Ghost
{
    int x, y, nextX, nextY, score, direction, lastDirection;
    double minDistance;
};

Ghost Blinky, Pinky, Inky, Clyde;

void PacmanMove()
{
    if (Keyboard::isKeyPressed(Keyboard::Up) && Map.Mase[Pacman.nextY - 1][Pacman.nextX] != 'X') {
        Pacman.nextDirection = 0;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && Map.Mase[Pacman.nextY + 1][Pacman.nextX] != 'X') {
        Pacman.nextDirection = 1;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && (Map.Mase[Pacman.nextY][Pacman.nextX - 1] != 'X' || (Pacman.nextY == 17 && Pacman.nextX == 0))) {
        Pacman.nextDirection = 2;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && (Map.Mase[Pacman.nextY][Pacman.nextX + 1] != 'X'|| (Pacman.nextY == 17 && Pacman.nextX == Map.W - 1))) {
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
            if (Pacman.nextY == 17 && Pacman.nextX == 0)
                Pacman.nextX = Map.W - 1;
            else if (Map.Mase[Pacman.nextY][Pacman.nextX - 1] != 'X' && Pacman.nextX - 1 >= 0)
                Pacman.nextX--;
            break;
        case 3:
            if (Pacman.nextY == 17 && Pacman.nextX == Map.W - 1)
                Pacman.nextX = 0;
            else if (Map.Mase[Pacman.nextY][Pacman.nextX + 1] != 'X' && Pacman.nextX + 1 <= 35)
                Pacman.nextX++;
            break;
        }
        Pacman.score = 0;
    }

    if ((Map.Mase[Pacman.nextY][Pacman.nextX] == ' ' || Map.Mase[Pacman.nextY][Pacman.nextX] == 'o' || Map.Mase[Pacman.nextY][Pacman.nextX] == 'O') && Pacman.nextY != 0 && Pacman.nextX != 0)
    {
        if (Map.Mase[Pacman.nextY][Pacman.nextX] == 'o')
            Pacman.points += 5;
        if (Map.Mase[Pacman.nextY][Pacman.nextX] == 'O')
            Pacman.points += 10;
        Map.Mase[Pacman.y][Pacman.x] = ' ';
        Map.Mase[Pacman.nextY][Pacman.nextX] = 'P';
        Pacman.x = Pacman.nextX;
        Pacman.y = Pacman.nextY;
    }
}


void MasePaint()
{
    
    RectangleShape square(Vector2f(25, 25)); // Квадрат размером 25x25 пикселей
    square.setFillColor(Color::Blue); // Устанавливаем синий цвет квадратика
    CircleShape circle(3); // Квадрат размером 25x25 пикселей
    circle.setFillColor(Color::White); // Устанавливаем синий цвет квадратика
    //circle.setOrigin(10, 10);
    CircleShape circle2(6); // Квадрат размером 25x25 пикселей
    circle2.setFillColor(Color::White); // Устанавливаем синий цвет квадратика
    //circle2.setOrigin(10, 10);
    RectangleShape pacman(Vector2f(25, 25)); // Квадрат размером 25x25 пикселей
    pacman.setFillColor(Color::Yellow); // Устанавливаем синий цвет квадратика
    for (int i = 0; i < Map.H; i++) // 11 - количество строк
        for (int j = 0; j < Map.W; j++) // Проверка длины строки
        {
            if (Map.Mase[i][j] == 'X')
            {
                // Установка позиции квадрата в зависимости от его координат
                square.setPosition(j * 25, i * 25); // Обратите внимание на порядок i и j
                window.draw(square); // Рисуем квадрат
            }
            else if (Map.Mase[i][j] == 'o')
            {
                // Установка позиции квадрата в зависимости от его координат
                circle.setPosition(j * 25 + 8.5, i * 25 + 8.5f);
                int pacmanX = static_cast<int>(pacman.getPosition().y / 25);
                int pacmanCol = static_cast<int>(pacman.getPosition().x / 25);

                window.draw(circle); // Рисуем квадрат}
            }
            else if (Map.Mase[i][j] == 'O')
            {
                // Установка позиции квадрата в зависимости от его координат
                circle2.setPosition(j * 25 + 5.5f, i * 25 + 5.5f);
                window.draw(circle2); // Рисуем квадрат
            }
            else if (Map.Mase[i][j] == 'P')
            {
                pacman.setPosition(j * 25, i * 25);
                window.draw(pacman); // Рисуем квадрат
            }
        }
}

float distance(int pacmanX, int pacmanY, int BlinkyX, int BlinkyY)
{
    return (sqrt(pow(pacmanX - BlinkyX, 2) + pow(pacmanY - BlinkyY, 2)));
}

void GhostMove(Ghost& ghost, int x, int y)
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

    if (distanceRight <= minDistance && Map.Mase[ghost.y][ghost.x + 1] != 'X' && ghost.x + 1 != Map.W - 1 && ghost.lastDirection != 2) {
        minDistance = distanceRight;
        ghost.direction = 3;
    }
    if (distanceUp <= minDistance && Map.Mase[ghost.y - 1][ghost.x] != 'X' && ghost.lastDirection != 1) {
        minDistance = distanceUp;
        ghost.direction = 0;
    }
    if (distanceLeft <= minDistance && Map.Mase[ghost.y][ghost.x - 1] != 'X' && ghost.x - 1 != 0 && ghost.lastDirection != 3) {
        minDistance = distanceLeft;
        ghost.direction = 2;
    }
    if (distanceDown <= minDistance && Map.Mase[ghost.y + 1][ghost.x] != 'X' && ghost.lastDirection != 0) {
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
                ghost.x = Map.W - 1;
            else
                ghost.x--;
            break;
        case 3: // Движение вправо
            if (ghost.y == 17 && ghost.x == Map.W - 1)
                ghost.x = 0;
            else
                ghost.x++;
            break;
        default:
            break; // Если нет доступного направления, остаемся на месте
        }
        ghost.score = 0;
    }

    if (ghost.lastDirection != ghost.direction && change)
        ghost.lastDirection = ghost.direction;
}

void BlinkyMove()
{

    GhostMove(Blinky, Pacman.x, Pacman.y);

}

void PinkyMove()
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

    GhostMove(Pinky, x, y);
}

void InkyMove()
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
    y = 2*(y-Blinky.y);


    GhostMove(Inky, x, y);
}

void ClydeMove()
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
    GhostMove(Clyde, x, y);
}



int Lose()
{
    int f = 1;
    if (Pacman.x == Blinky.x && Pacman.y == Blinky.y)
        Pacman.lifes--;
    else if (Pacman.x == Pinky.x && Pacman.y == Pinky.y)
        Pacman.lifes--;
    else if (Pacman.x == Inky.x && Pacman.y == Inky.y)
        Pacman.lifes--;
    else if (Pacman.x == Clyde.x && Pacman.y == Clyde.y)
        Pacman.lifes--;
    else f = 0;
    return f;
}


int main()
{




    RectangleShape blinky(Vector2f(25, 25));
    blinky.setFillColor(Color::Red); 
    blinky.setPosition(13 * 25 + 3.0f, 14 * 25 + 3.0f);
    RectangleShape pinky(Vector2f(25, 25)); 
    pinky.setFillColor(sf::Color(255, 185, 193));
    pinky.setPosition(14 * 25 + 3.0f, 14 * 25 + 3.0f);
    RectangleShape inky(Vector2f(25, 25));
    inky.setFillColor(Color::Cyan); 
    inky.setPosition(15 * 25 + 3.0f, 14 * 25 + 3.0f);
    RectangleShape clyde(Vector2f(25, 25)); 
    clyde.setFillColor(sf::Color(255, 165, 0));  
    clyde.setPosition(15 * 25 + 3.0f, 14 * 25 + 3.0f);
    Pacman.direction = 3;
    Pacman.nextDirection = 3;


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


    Pacman.lifes = 3;
    Pacman.nextX = 0;
    Pacman.nextY = 0;
    Pacman.x = 14;
    Pacman.y = 26;
    Pacman.score = 300;


    Blinky.x = 13;
    Blinky.y = 14;

    Pinky.x = 14;
    Pinky.y = 14;

    Inky.x = 15;
    Inky.y = 14;

    Clyde.x = 16;
    Clyde.y = 14;

    do
    {
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color::Black);

            


            MasePaint();
            PacmanMove();

            BlinkyMove();
            PinkyMove();
            InkyMove();
            ClydeMove();


            pointsText.setString("Points " + std::to_string(Pacman.points));
            livesText.setString("Lifes " + std::to_string(Pacman.lifes));
            window.draw(pointsText);
            window.draw(livesText);

            window.draw(blinky);
            pinky.setPosition(Pinky.x * 25, Pinky.y * 25);
            blinky.setPosition(Blinky.x * 25, Blinky.y * 25);
            inky.setPosition(Inky.x * 25, Inky.y * 25);
            clyde.setPosition(Clyde.x * 25, Clyde.y * 25);
            window.draw(blinky);
            window.draw(pinky);
            window.draw(inky);
            window.draw(clyde);
            if (Lose()) {
                Blinky.x = 13;
                Blinky.y = 14;

                Pinky.x = 14;
                Pinky.y = 14;

                Inky.x = 15;
                Inky.y = 14;

                Clyde.x = 16;
                Clyde.y = 14;
                Pacman.direction = -1;
                Pacman.nextDirection = -1;

                Map.Mase[Pacman.nextY][Pacman.nextX] = ' ';
                Map.Mase[26][14] = 'P';
                Pacman.nextX = 0;
                Pacman.nextY = 0;
                Pacman.x = 14;
                Pacman.y = 26;


                Pacman.score = 0;

            }

            window.display();
        }
    } while (Pacman.lifes);
    return 0;
}