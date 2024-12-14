#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <math.h>

using namespace sf;

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
    GameSettings() {};
    GameSettings(int screenWidth, int screenHeight, std::string windowTitle,
        int pacmanSize, int ghostSize, int foodSize, int gridSize,
        int pacmanStartX, int pacmanStartY,
        sf::Color pacmanColor, sf::Color squareColor, sf::Color circleColor,
        sf::Color circle2Color, sf::Color blinkyColor, sf::Color pinkyColor,
        sf::Color inkyColor, sf::Color clydeColor) :screenWidth(screenWidth), screenHeight(screenHeight), windowTitle(windowTitle), pacmanSize(pacmanSize), ghostSize(ghostSize), foodSize(foodSize), gridSize(gridSize),
        pacmanStartX(pacmanStartX), pacmanStartY(pacmanStartY), pacmanColor(pacmanColor), squareColor(squareColor), circleColor(circleColor), circle2Color(circle2Color), blinkyColor(blinkyColor), pinkyColor(pinkyColor), 
        inkyColor(inkyColor), clydeColor(clydeColor) {};

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


class Food {
private:
    int count;
    int point;
    char type;
public:
    Food() {};
    Food(int count, int point, char type) : count(count), point(point), type(type) {};
    int getCount() { return count; }
    int getPoint()  { return point; }
    char getType() { return type; }
    void decreaseCount() { count--; }
};

class Map {
private:
    int H, W;
    std::string Mase[100];
public:
    Map(int H, int W) : H(H), W(W) {};
    int getH() const { return H; }
    int getW() const { return W; }
    char getTile(int y, int x) const { return  Mase[y][x]; }
    void setTile(int y, int x, char tile) { Mase[y][x] = tile; }

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
        for (int i = 0; i < H; ++i) {
            Mase[i] = tempMase[i];
        }
    }

    void MasePaint(GameSettings& settings, RenderWindow& window, Food& smallFood, Food& bigFood) {
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

class Pacman {
private:
    int x, y, nextX, nextY, score, nextDirection, lives, points;
public:
    Pacman() {};
    Pacman(int x, int y, int nextX, int nextY, int score, int nextDirection, int lives, int points) : x(x), y(y), nextX(nextX), nextY(nextY), score(score), nextDirection(nextDirection), lives(lives), points(points) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getStartX() const { return 14; }
    int getStartY() const { return 26; }
    int getPoints() const { return points; }
    int getLives() const { return lives; }
    int getNextDirection() const { return nextDirection; }
    void setX(int a) { x = a; }
    void setY(int a) { y = a; }
    void setNextX(int a) { nextX = a; }
    void setNextY(int a) { nextY = a; }
    void setScore(int a) { score = a; }
    void setNextDirection(int a) { nextDirection = a; }
    void loseLife() { lives--; }
    void addPoints(int p) { points += p; }

    void move(Map &map, Food& smallFood, Food& bigFood) {
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
            addPoints(smallFood.getPoint());
            smallFood.decreaseCount();
        }
        if (map.getTile(nextY,nextX) == bigFood.getType())
        {
            addPoints(bigFood.getPoint());
            bigFood.decreaseCount();
        }
        map.setTile(y, x, ' ');
        map.setTile(nextY, nextX,'P');
        x = nextX;
        y = nextY;
    }
}

    int WonOrLost(Food smallFood, Food bigFood, Text& Result)
    {
        int f = 1;
        if (smallFood.getCount() == 0 && bigFood.getCount() == 0)
            Result.setString("You won! ");
        else if (!getLives())
            Result.setString("You lost! ");
        else f = 0;
        return f;
    }
};

class Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    Ghost() {};
    Ghost(int x, int y, int score, int direction, int lastDirection): x(x), y(y), score(score), direction(direction),lastDirection(lastDirection) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    int getDirection() const { return direction; }
    int getLAstDirection() const { return lastDirection; }
    void setAll(int a, int b, int c, int d, int e) { x = a, y = b, score = c, d = direction, e = lastDirection; }

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
};

class Blinky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    Blinky() {};
    ~Blinky() {};
    Blinky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void BlinkyMove(Pacman pacman, Map map, GameSettings settings, RenderWindow &window) {
        move(map, pacman.getX(), pacman.getY());
        RectangleShape blinkyShape(Vector2f(settings.getGridSize(), settings.getGridSize()));
        blinkyShape.setFillColor(settings.getBlinkyColor());
        blinkyShape.setPosition(getX() * settings.getGridSize(), getY() * settings.getGridSize());
        window.draw(blinkyShape);
    }
};

class Pinky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    Pinky() {};
    ~Pinky() {};
    Pinky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void PinkyMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window) {
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
        RectangleShape pinkyShape(Vector2f(settings.getGridSize(), settings.getGridSize()));
        pinkyShape.setFillColor(settings.getPinkyColor());
        pinkyShape.setPosition(getX() * settings.getGridSize(), getY() * settings.getGridSize());
        window.draw(pinkyShape);
    }
};

class Inky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    Inky() {};
    ~Inky() {};
    Inky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void InkyMove(Pacman pacman, Map map, Ghost blinky, GameSettings settings, RenderWindow &window) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
        {
        case 0:
            b = b - 2;
            break;
        case 1:
            b = b + 2;
            break;
        case 2:
            a = a - 2;
            break;
        case 3:
            a = a + 2;
            break;
        }
        a = blinky.getX() + 2 * (a - blinky.getX());
        b = blinky.getY() + 2 * (b - blinky.getY());
        move(map, a, b);
        RectangleShape inkyShape(Vector2f(settings.getGridSize(), settings.getGridSize()));
        inkyShape.setFillColor(settings.getInkyColor());
        inkyShape.setPosition(getX() * settings.getGridSize(), getY() * settings.getGridSize());
        window.draw(inkyShape);
    }
};

class Clyde : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    Clyde() {};
    ~Clyde() {};
    Clyde(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void ClydeMove(Pacman pacman, Map map, GameSettings settings, RenderWindow &window) {
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
        RectangleShape clydeShape(Vector2f(settings.getGridSize(), settings.getGridSize()));
        clydeShape.setFillColor(settings.getClydeColor());
        clydeShape.setPosition(getX() * settings.getGridSize(), getY() * settings.getGridSize());
        window.draw(clydeShape);
    }

    int Lose(Pacman& pacman, Blinky& blinky, Pinky& pinky, Inky& inky)
    {
        int result = 1;
        if (pacman.getX() == blinky.getX() && pacman.getY() == blinky.getY()) {
            pacman.loseLife();
            result = 0;
        }
        if (pacman.getX() == pinky.getX() && pacman.getY() == pinky.getY()) {
            pacman.loseLife();
            result = 0;
        }
        if (pacman.getX() == inky.getX() && pacman.getY() == inky.getY()) {
            pacman.loseLife();
            result = 0;
        }
        if (pacman.getX() == getX() && pacman.getY()  == getY()) {
            pacman.loseLife();
            result = 0;
        }
        switch (pacman.getNextDirection()) {
        case 0:
            if (pacman.getX() == blinky.getX() && pacman.getY() - 1 == blinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() == pinky.getX() && pacman.getY() - 1 == pinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() == inky.getX() && pacman.getY() - 1 == inky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() == getX() && pacman.getY() - 1 == getY()) {
                pacman.loseLife();
                result = 0;
            }
            break;
        case 1:
            if (pacman.getX() == blinky.getX() && pacman.getY() + 1 == blinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() == pinky.getX() && pacman.getY() + 1 == pinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() == inky.getX() && pacman.getY() + 1 == inky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() == getX() && pacman.getY() + 1 == getY()) {
                pacman.loseLife();
                result = 0;
            }
            break;
        case 2:
            if (pacman.getX() -1 == blinky.getX() && pacman.getY() == blinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() -1 == pinky.getX() && pacman.getY() == pinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX()-1 == inky.getX() && pacman.getY() == inky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX() - 1 == getX() && pacman.getY() == getY()) {
                pacman.loseLife();
                result = 0;
            }
            break;
        case 3:
            if (pacman.getX()+1 == blinky.getX() && pacman.getY() == blinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX()+1 == pinky.getX() && pacman.getY() == pinky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX()+1 == inky.getX() && pacman.getY() == inky.getY()) {
                pacman.loseLife();
                result = 0;
            }
            if (pacman.getX()+1 == getX() && pacman.getY() == getY()) {
                pacman.loseLife();
                result = 0;
            }
            break;
        }
        return result;
    }
};



int main()
{
    Food smallFood(240, 5, 'o');
    Food bigFood(4, 10, 'O');
    GameSettings settings(750, 875, "Pac-Man", 20, 20, 10, 25, 14, 26,sf::Color::Yellow, sf::Color::Blue, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color(255, 185, 193), sf::Color::Cyan, sf::Color(255, 165, 0));
    Map map(35, 30);
    map.createMap();
    Pacman pacman(14, 26, 14, 26, 0, 3, 3, 0);
    Blinky blinky(11, 14, 0, 3, 3);
    Pinky pinky(13, 14, 0, 3, 3);
    Inky inky(15, 14, 0, 3, 3);
    Clyde clyde(17, 14, 0, 3, 3);
    sf::Font font;
    if (!font.loadFromFile("Unformital Medium.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(2 * settings.getGridSize(), 1 * settings.getGridSize());

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(40);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(22 * settings.getGridSize(), 1 * settings.getGridSize());

    sf::Text Result;
    Result.setFont(font);
    Result.setCharacterSize(80);
    Result.setFillColor(sf::Color::White);
    Result.setPosition(5 * settings.getGridSize(), 10 * settings.getGridSize());

    RenderWindow window(VideoMode(settings.getScreenWidth(), settings.getScreenHeight()), settings.getWindowTitle());
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::Black);
        if (!(pacman.WonOrLost(smallFood, bigFood, Result)))
        {
            map.MasePaint(settings, window, smallFood, bigFood);
            blinky.BlinkyMove(pacman, map, settings, window);
            pinky.PinkyMove(pacman, map, settings, window);
            inky.InkyMove(pacman, map, blinky, settings, window);
            clyde.ClydeMove(pacman, map, settings, window);
            window.draw(pointsText);
            window.draw(livesText);
            if (!(clyde.Lose(pacman, blinky, pinky, inky)))
            {
                blinky.setAll(11, 14, 0, 3, 3);
                pinky.setAll(13, 14, 0, 3, 3);
                inky.setAll(15, 14, 0, 3, 3);
                clyde.setAll(17, 14, 0, 3, 3);
                map.setTile(pacman.getY(), pacman.getX(), ' ');
                map.setTile(26, 14, 'P');
                pacman.setX(pacman.getStartX());
                pacman.setY(pacman.getStartY());
                pacman.setNextX(pacman.getStartX());
                pacman.setNextY(pacman.getStartY());
                pacman.setScore(0);
                pacman.setNextDirection(3);
            }
            pacman.move(map, smallFood, bigFood);
            if (pacman.WonOrLost(smallFood, bigFood, Result))
            {
                sf::FloatRect textBounds = Result.getLocalBounds();
                sf::Vector2u windowSize = window.getSize();
                Result.setPosition((windowSize.x - textBounds.width) / 2, (windowSize.y - textBounds.height) / 2 - 50);
                window.draw(Result);
            }
            pointsText.setString("Points " + std::to_string(pacman.getPoints()));
            livesText.setString("Lives " + std::to_string(pacman.getLives()));
            window.display();
        }
    }
    return 0;
}