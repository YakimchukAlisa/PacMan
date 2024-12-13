#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <math.h>

using namespace sf;

class Food {
private:
    int count, point;
    char type;
public:
    Food(int count, int point, char type) {};
    int getCount() const { return count; }
    int getPoint() const { return point; }
    char getType() const { return type; }
    void decreaseCount() { count--; }
};

class Map {
private:
    int H, W;
    std::string Mase[100];
public:
    Map(int H, int W) {};
    int getH() const { return H; }
    int getW() const { return W; }
    char getTile(int y, int x) const { return (y >= 0 && y < H && x >= 0 && x < W) ? Mase[y][x] : 'X'; }
    void setTile(int y, int x, char tile) { if (y >= 0 && y < H && x >= 0 && x < W) Mase[y][x] = tile; }

    void createMap() {
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
            Mase[i] = tempMase[i];
        }
    }
    void MasePaint(GameSettings settings, RenderWindow& window, Food smallFood, Food bigFood) {
        RectangleShape square(Vector2f(settings.getGridSize(), settings.getGridSize()));
        square.setFillColor(settings.getSquareColor());
        CircleShape circle(3);
        circle.setFillColor(settings.getCircleColor());
        CircleShape circle2(6);
        circle2.setFillColor(settings.getCircle2Color());
        RectangleShape pacman(Vector2f(settings.getGridSize(), settings.getGridSize()));
        pacman.setFillColor(settings.getPacmanColor());
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
            {
                if (Mase[i][j] == 'X')
                {
                    square.setPosition(j * settings.getGridSize(), i * settings.getGridSize());
                    window.draw(square);
                }
                else if (Mase[i][j] == smallFood.getType())
                {
                    circle.setPosition(j * settings.getGridSize() + 8.5, i * settings.getGridSize() + 8.5f);
                    int pacmanX = static_cast<int>(pacman.getPosition().y / settings.getGridSize());
                    int pacmanCol = static_cast<int>(pacman.getPosition().x / settings.getGridSize());
                    window.draw(circle);
                }
                else if (Mase[i][j] == bigFood.getType())
                {
                    circle2.setPosition(j * settings.getGridSize() + 5.5f, i * settings.getGridSize() + 5.5f);
                    window.draw(circle2);
                }
                else if (Mase[i][j] == 'P')
                {
                    pacman.setPosition(j * settings.getGridSize(), i * settings.getGridSize());
                    window.draw(pacman);
                }
            }
    }
};

class GameSettings {
private:
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

public:
    GameSettings(int screenWidth, int screenHeight, std::string windowTitle,
        int pacmanSize, int ghostSize, int foodSize, int gridSize,
        int pacmanStartX, int pacmanStartY,
        sf::Color pacmanColor, sf::Color squareColor, sf::Color circleColor,
        sf::Color circle2Color, sf::Color blinkyColor, sf::Color pinkyColor,
        sf::Color inkyColor, sf::Color clydeColor) {}

    int getScreenWidth() const { return screenWidth; }
    int getScreenHeight() const { return screenHeight; }
    std::string getWindowTitle() const { return windowTitle; }
    int getPacmanSize() const { return pacmanSize; }
    int getGhostSize() const { return ghostSize; }
    int getFoodSize() const { return foodSize; }
    int getGridSize() const { return gridSize; }
    int getPacmanStartX() const { return pacmanStartX; }
    int getPacmanStartY() const { return pacmanStartY; }
    sf::Color getPacmanColor() const { return pacmanColor; }
    sf::Color getSquareColor() const { return squareColor; }
    sf::Color getCircleColor() const { return circleColor; }
    sf::Color getCircle2Color() const { return circle2Color; }
    sf::Color getBlinkyColor() const { return blinkyColor; }
    sf::Color getPinkyColor() const { return pinkyColor; }
    sf::Color getInkyColor() const { return inkyColor; }
    sf::Color getClydeColor() const { return clydeColor; }
};

class Pacman {
private:
    int x, y, nextX, nextY, score, nextDirection, lives, points;
public:
    Pacman(int x, int y, int NextX, int nextY, int score, int nextDirection, int lives, int points) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getPoints() const { return points; }
    int getLives() const { return lives; }
    int getNextDirection() const { return nextDirection; }
    void loseLife() { lives--; }
    void move(Map map, Food smallFood, Food bigFood) {
        if (Keyboard::isKeyPressed(Keyboard::Up) && map.getTile(nextY - 1, nextX) != 'X' && !(nextY == 17 && nextX == 0 || nextY == 17 && nextX == map.getW() - 1)) {
        nextDirection = 0;
        nextX = x;
        nextY = y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && map.getTile(nextY + 1, nextX) != 'X' && !(nextY == 17 && nextX == 0 || nextY == 17 && nextX == map.getW() - 1)) {
        nextDirection = 1;
        nextX = x;
        nextY = y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && (map.getTile(nextY,nextX - 1) != 'X')) {
        nextDirection = 2;
        nextX = x;
        nextY =y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && (map.getTile(nextY,nextX + 1) != 'X')) {
        nextDirection = 3;
        nextX = x;
        nextY = y;
    }

    score++;
    if (score >= 200)
    {
        switch (nextDirection)
        {
        case 0:
            if (map.getTile(nextY - 1,nextX) != 'X' && nextY - 1 >= 0)
                nextY--;
            break;
        case 1:

            if (map.getTile(nextY + 1,nextX) != 'X' && nextY + 1 <= 35)
                nextY++;
            break;
        case 2:
            if (nextY == 17 && nextX == 1)
                nextX = map.getW() - 2;
            else if (map.getTile(nextY,nextX - 1) != 'X' && nextX - 1 >= 0)
                nextX--;
            break;
        case 3:
            if (nextY == 17 && nextX == map.getW() - 2)
                nextX = 1;
            else if (map.getTile(nextY,nextX + 1) != 'X' && nextX + 1 <= 35)
                nextX++;
            break;
        }
        score = 0;
    }

    if ((map.getTile(nextY, nextX) == ' ' || map.getTile(nextY, nextX) == smallFood.getType() || map.getTile(nextY, nextX) == bigFood.getType()) && nextY != 0 && nextX != 0)
    {
        if (map.getTile(nextY,nextX) == smallFood.getType())
        {
            points += smallFood.getPoint();
            smallFood.decreaseCount();
        }
        if (map.getTile(nextY,nextX) == bigFood.getType())
        {
            points += bigFood.getType();
            bigFood.decreaseCount();
        }
        map.setTile(y, x, ' ');
        map.setTile(nextY, nextX,'P');
        x = nextX;
        y = nextY;
    }
}

    int Lose(Ghost blinky, Ghost pinky, Ghost inky, Ghost clyde)
    {
        int f = 1;
        if (x == blinky.getX() && y == blinky.getY() || x + 1 == blinky.getX() && y== blinky.getY() || x - 1 == blinky.getX() && y == blinky.getY() || x == blinky.getX() && y + 1 == blinky.getY() || x == blinky.getX() && y - 1 == blinky.getX())
            loseLife();
        else if (x == pinky.getX() && y == pinky.getY() || x + 1 == pinky.getX() && y == pinky.getY() || x - 1 == pinky.getX() && y == pinky.getY() || x == pinky.getX() && y + 1 == pinky.getY() || x == pinky.getX() && y - 1 == pinky.getY())
            loseLife();
        else if (x == inky.getX() && y == inky.getY() || x + 1 == inky.getX() && y == inky.getY() || x - 1 == inky.getX() && y == inky.getY() || x == inky.getX() && y + 1 == inky.getY() || x == inky.getX() && y - 1 == inky.getY())
            loseLife();
        else if (x == clyde.getX() && y == clyde.getY() || x + 1 == clyde.getX() && y == clyde.getY() || x - 1 == clyde.getX() && y == clyde.getY() || x == clyde.getX() && y + 1 == clyde.getY() || x == clyde.getX() && y - 1 == clyde.getY())
            loseLife();
        else f = 0;
        return f;
    }

    int WonOrLost(Food smallFood, Food bigFood, Text& Result)
    {
        int f = 1;
        if (smallFood.getCount() == 0 && bigFood.getCount() == 0)
            Result.setString("You won! ");
        else if (!lives)
            Result.setString("You lost! ");
        else f = 0;
        return f;
    }
};

class Ghost: public Pacman {
private:
    int x, y, score, direction, lastDirection;
public:
    Ghost(int x, int y, int score, int direction, int lastDirection) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    int getDirection() const { return direction; }
    int getLAstDirection() const { return lastDirection; }

    float distance(int x1, int y1, int x2, int y2) {
        return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    }

    void move(Map map, int goalX, int goalY) {
        float distanceUp, distanceDown, distanceLeft, distanceRight;
        double minDistance = INFINITY;
        int change = 0;

        distanceUp = distance(goalX, goalY, x, y - 1);
        distanceDown = distance(goalX, goalY, x, y + 1);
        if (y == 17 && x == 1)
            distanceLeft = distance(goalX, goalY, map.getW() - 1, y);
        else distanceLeft = distance(goalX, goalY, x - 1, y);
        if (y == 17 && x == map.getW() - 1)
            distanceRight = distance(goalX, goalY, 0, y);
        else distanceRight = distance(goalX, goalY, x + 1, y);

        if (distanceRight <= minDistance && map.getTile(y, x + 1) != 'X' && lastDirection != 2) {
            minDistance = distanceRight;
            direction = 3;
        }
        if (distanceUp <= minDistance && map.getTile(y - 1, x) != 'X' && lastDirection != 1 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
            minDistance = distanceUp;
            direction = 0;
        }
        if (distanceLeft <= minDistance && map.getTile(y, x - 1) != 'X' && lastDirection != 3) {
            minDistance = distanceLeft;
            direction = 2;
        }
        if (distanceDown <= minDistance && map.getTile(y + 1, x) != 'X' && lastDirection != 0 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
            minDistance = distanceDown;
            direction = 1;
        }

        score++;
        if (score >= 200)
        {
            change = 1;
            // Двигаемся в выбранном направлении
            switch (direction) {
            case 0: // Движение вверх
                y--;
                break;
            case 1: // Движение вниз
                y++;
                break;
            case 2: // Движение влево
                if (y == 17 && x == 1)
                    x = map.getW() - 2;
                else
                    x--;
                break;
            case 3: // Движение вправо
                if (y == 17 && x == map.getW() - 2)
                    x = 1;
                else
                    x++;
                break;
            default:
                break;
            }
            score = 0;
        }

        if (lastDirection != direction && change)
            lastDirection = direction;
    }

    void BlinkyMove(Pacman pacman, Map map) {
        move(map, pacman.getX(), pacman.getY());
    }

    void PinkyMove(Pacman pacman, Map map) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
        {
        case 0:
            b = b - 4;
            break;
        case 1:
            b = b + 4;
            break;
        case 2:
            a = a - 4;
            break;
        case 3:
            a = a + 4;
            break;
        }
        move(map, a, b);
    }

    void InkyMove(Pacman pacman, Map map, Ghost blinky) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
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
        a = blinky.getX() + 2 * (a - blinky.getX());
        b = blinky.getY() + 2 * (b - blinky.getY());
        move(map, a, b);
    }

    void ClydeMove(Pacman pacman, Map map) {
        int a, b;
        float mainDistance = distance(pacman.getX(), pacman.getY(), x, y);
        if (mainDistance > 8)
        {
            a = pacman.getX();
            b = pacman.getY();
        }
        else
        {
            a = 0;
            b = map.getH();
        }
        move(map, a, b);
    }
};

  
 





int main()
{
    GameSettings settings(800, 600, "Pac-Man", 20, 20, 10, 25, 14, 26,sf::Color::Yellow, sf::Color::Blue, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color(255, 185, 193), sf::Color::Cyan, sf::Color(255, 165, 0));
    Map map(35, 30);
    Pacman pacman(14, 26, 14, 26, 0, 3, 3, 0);
    Ghost Blinky(11, 14, 0, 3, 3), Pinky(13, 14, 0, 3, 3), Inky(15, 14, 0, 3, 3), Clyde(17, 14, 0, 3, 3);
    Food smallFood(240, 5, 'o'), bigFood(4, 10, 'O');
    RenderWindow window(VideoMode(settings.getScreenWidth(), settings.getScreenHeight()), settings.getWindowTitle());
    return 0;
}