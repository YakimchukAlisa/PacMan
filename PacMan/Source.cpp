#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <math.h>

using namespace sf;

const int H = 35;
const int W = 30;

std::string Mase[H] = {
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




struct Pacman
{
    int x, y, nextX, nextY,score, direction, nextDirection;
} Pacman;

struct Blinky
{
    int x, y, nextX, nextY, score, direction, lastDirection;
    double minDistance;
} Blinky;

struct Pinky
{
    int x, y, nextX, nextY, score, direction, lastDirection;
} Pinky;



RenderWindow window(VideoMode(W * 25, H * 25), "Pac-Man");

void PacmanMove()
{
    if (Keyboard::isKeyPressed(Keyboard::Up) && Mase[Pacman.nextY - 1][Pacman.nextX] != 'X') {
        Pacman.nextDirection = 0;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && Mase[Pacman.nextY + 1][Pacman.nextX] != 'X') {
        Pacman.nextDirection = 1;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && (Mase[Pacman.nextY][Pacman.nextX - 1] != 'X' || (Pacman.nextY == 17 && Pacman.nextX == 0))) {
        Pacman.nextDirection = 2;
        Pacman.nextX = Pacman.x;
        Pacman.nextY = Pacman.y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && (Mase[Pacman.nextY][Pacman.nextX + 1] != 'X'|| (Pacman.nextY == 17 && Pacman.nextX == W - 1))) {
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
            if (Mase[Pacman.nextY - 1][Pacman.nextX] != 'X' && Pacman.nextY - 1 >= 0)
                Pacman.nextY--;
            break;
        case 1:
            if (Mase[Pacman.nextY + 1][Pacman.nextX] != 'X' && Pacman.nextY + 1 <= 35)
                Pacman.nextY++;
            break;
        case 2:
            if (Pacman.nextY == 17 && Pacman.nextX == 0)
                Pacman.nextX = W - 1;
            else if (Mase[Pacman.nextY][Pacman.nextX - 1] != 'X' && Pacman.nextX - 1 >= 0)
                Pacman.nextX--;
            break;
        case 3:
            if (Pacman.nextY == 17 && Pacman.nextX == W - 1)
                Pacman.nextX = 0;
            else if (Mase[Pacman.nextY][Pacman.nextX + 1] != 'X' && Pacman.nextX + 1 <= 35)
                Pacman.nextX++;
            break;
        }
        Pacman.score = 0;
    }

    if ((Mase[Pacman.nextY][Pacman.nextX] == ' ' || Mase[Pacman.nextY][Pacman.nextX] == 'o' || Mase[Pacman.nextY][Pacman.nextX] == 'O') && Pacman.nextY != 0 && Pacman.nextX != 0)
    {

        Mase[Pacman.y][Pacman.x] = ' ';
        Mase[Pacman.nextY][Pacman.nextX] = 'P';
        Pacman.x = Pacman.nextX;
        Pacman.y = Pacman.nextY;
    }
}


void MasePaint()
{
    
    RectangleShape square(Vector2f(25, 25)); // ������ ࠧ��஬ 25x25 ���ᥫ��
    square.setFillColor(Color::Blue); // ��⠭�������� ᨭ�� 梥� �����⨪�
    CircleShape circle(3); // ������ ࠧ��஬ 25x25 ���ᥫ��
    circle.setFillColor(Color::White); // ��⠭�������� ᨭ�� 梥� �����⨪�
    //circle.setOrigin(10, 10);
    CircleShape circle2(6); // ������ ࠧ��஬ 25x25 ���ᥫ��
    circle2.setFillColor(Color::White); // ��⠭�������� ᨭ�� 梥� �����⨪�
    //circle2.setOrigin(10, 10);
    RectangleShape pacman(Vector2f(25, 25)); // ������ ࠧ��஬ 25x25 ���ᥫ��
    pacman.setFillColor(Color::Yellow); // ��⠭�������� ᨭ�� 梥� �����⨪�
    for (int i = 0; i < H; i++) // 11 - ������⢮ ��ப
        for (int j = 0; j < W; j++) // �஢�ઠ ����� ��ப�
        {
            if (Mase[i][j] == 'X')
            {
                // ��⠭���� ����樨 ������ � ����ᨬ��� �� ��� ���न���
                square.setPosition(j * 25, i * 25); // ����� �������� �� ���冷� i � j
                window.draw(square); // ���㥬 ������
            }
            else if (Mase[i][j] == 'o')
            {
                // ��⠭���� ����樨 ������ � ����ᨬ��� �� ��� ���न���
                circle.setPosition(j * 25 + 8.5, i * 25 + 8.5f);
                int pacmanX = static_cast<int>(pacman.getPosition().y / 25);
                int pacmanCol = static_cast<int>(pacman.getPosition().x / 25);

                window.draw(circle); // ���㥬 ������}
            }
            else if (Mase[i][j] == 'O')
            {
                // ��⠭���� ����樨 ������ � ����ᨬ��� �� ��� ���न���
                circle2.setPosition(j * 25 + 5.5f, i * 25 + 5.5f);
                window.draw(circle2); // ���㥬 ������
            }
            else if (Mase[i][j] == 'P')
            {
                pacman.setPosition(j * 25, i * 25);
                window.draw(pacman); // ���㥬 ������
            }
        }
}

float distance(int pacmanX, int pacmanY, int BlinkyX, int BlinkyY)
{
    return (sqrt(pow(pacmanX - BlinkyX, 2) + pow(pacmanY - BlinkyY, 2)));
}


void BlinkyMove()
{
    float distanceUp;
    float distanceDown;
    float distanceLeft;
    float distanceRight;

    distanceUp = distance(Pacman.x, Pacman.y, Blinky.x, Blinky.y - 1);
    distanceDown = distance(Pacman.x, Pacman.y, Blinky.x, Blinky.y + 1);
    if (Blinky.y == 17 && Blinky.x == 1)
        distanceLeft = distance(Pacman.x, Pacman.y, W - 1, Blinky.y);
    else distanceLeft = distance(Pacman.x, Pacman.y, Blinky.x - 1, Blinky.y);
    if (Blinky.y == 17 && Blinky.x == W - 1)
        distanceRight = distance(Pacman.x, Pacman.y, 0, Blinky.y);
    else distanceRight = distance(Pacman.x, Pacman.y, Blinky.x + 1, Blinky.y);



    double minDistance = INFINITY;

    int change=0;

    if (distanceRight <= minDistance && Mase[Blinky.y][Blinky.x + 1] != 'X' && Blinky.lastDirection != 2) {
        minDistance = distanceRight;
        Blinky.direction = 3;
    }
    if (distanceDown <= minDistance && Mase[Blinky.y + 1][Blinky.x] != 'X' && Blinky.lastDirection != 0) {
        minDistance = distanceDown;
        Blinky.direction = 1;
    }
    if (distanceLeft <= minDistance && Mase[Blinky.y][Blinky.x - 1] != 'X' && Blinky.lastDirection != 3) {
        minDistance = distanceLeft;
        Blinky.direction = 2;
    }
    if (distanceUp <= minDistance && Mase[Blinky.y - 1][Blinky.x] != 'X' && Blinky.lastDirection != 1) {
        minDistance = distanceUp;
        Blinky.direction = 0;
    }


    Blinky.score++;
    if (Blinky.score >= 200)
    {
        change = 1;
        // ��������� � ��࠭��� ���ࠢ�����
        switch (Blinky.direction) {
        case 0: // �������� �����
            
            Blinky.y--;
            break;
        case 1: // �������� ����
            
            Blinky.y++;
            break;
        case 2: // �������� �����
            
            if (Blinky.y == 17 && Blinky.x == 1)
                Blinky.x = W - 1;
            else
                Blinky.x--;
            
            break;
        case 3: // �������� ��ࠢ�
            if (Blinky.y == 17 && Blinky.x == W - 1)
                Blinky.x = 0;
            else
                Blinky.x++;
            ;
            break;
        default:
            break; // �᫨ ��� ����㯭��� ���ࠢ�����, ��⠥��� �� ����
        }
        Blinky.score = 0;
    }
    if (Blinky.lastDirection != Blinky.direction && change)
        Blinky.lastDirection = Blinky.direction;

}

void PinkyMove()
{
    int x=Pacman.x, y=Pacman.y;
    switch (Pacman.direction)
    {
    case 0:
        y = y - 4;
        break;
    case 1:
        y = y + 1;
        break;
    case 2:
        x = x - 4;
        break;
    case 3:
        x = x + 4;
        break;


    }

    float distanceUp;
    float distanceDown;
    float distanceLeft;
    float distanceRight;

    distanceUp = distance(x, y, Pinky.x, Pinky.y - 1);
    distanceDown = distance(x, y, Pinky.x, Pinky.y + 1);
    if (Pinky.y == 17 && Pinky.x == 1)
        distanceLeft = distance(x, y, W - 1, Pinky.y);
    else distanceLeft = distance(x, y, Blinky.x - 1, Pinky.y);
    if (Pinky.y == 17 && Pinky.x == W - 1)
        distanceRight = distance(x, y, 0, Pinky.y);
    else distanceRight = distance(x, y, Pinky.x + 1, Pinky.y);



    double minDistance = INFINITY;
    int change = 0;



    if (distanceRight <= minDistance && Mase[Pinky.y][Pinky.x + 1] != 'X' && Pinky.lastDirection != 2) {
        minDistance = distanceRight;
        Pinky.direction = 3;
    }
    if (distanceUp <= minDistance && Mase[Pinky.y - 1][Pinky.x] != 'X' && Pinky.lastDirection != 1) {
        minDistance = distanceUp;
        Pinky.direction = 0;
    }
    if (distanceLeft <= minDistance && Mase[Pinky.y][Pinky.x - 1] != 'X' && Pinky.lastDirection != 3) {
        minDistance = distanceLeft;
        Pinky.direction = 2;
    }
    if (distanceDown <= minDistance && Mase[Pinky.y + 1][Pinky.x] != 'X' && Pinky.lastDirection != 0) {
        minDistance = distanceDown;
        Pinky.direction = 1;
    }



    Pinky.score++;
    if (Pinky.score >= 200)
    {
        change = 1;
        // ��������� � ��࠭��� ���ࠢ�����
        switch (Pinky.direction) {
        case 0: // �������� �����
            Pinky.y--;
            break;
        case 1: // �������� ����
            Pinky.y++;
            break;
        case 2: // �������� �����
            if (Pinky.y == 17 && Pinky.x == 1)
                Pinky.x = W - 1;
            else
                Pinky.x--;
            break;
        case 3: // �������� ��ࠢ�
            if (Pinky.y == 17 && Pinky.x == W - 1)
                Pinky.x = 0;
            else
                Pinky.x++;
            break;
        default:
            break; // �᫨ ��� ����㯭��� ���ࠢ�����, ��⠥��� �� ����
        }
        Pinky.score = 0;
    }

    if (Pinky.lastDirection != Pinky.direction && change)
        Pinky.lastDirection = Pinky.direction;

}


int main()
{
   
   
    RectangleShape blinky(Vector2f(25, 25)); // ������ ࠧ��஬ 25x25 ���ᥫ��
    blinky.setFillColor(Color::Red); // ��⠭�������� ᨭ�� 梥� �����⨪�
    blinky.setPosition(13 * 25 + 3.0f, 14 * 25 + 3.0f);
    RectangleShape pinky(Vector2f(25, 25)); // ������ ࠧ��஬ 25x25 ���ᥫ��
    pinky.setFillColor(Color::Magenta); // ��⠭�������� ᨭ�� 梥� �����⨪�
    pinky.setPosition(13 * 25 + 3.0f, 14 * 25 + 3.0f);
    Pacman.direction = -1;
    Pacman.nextDirection = -1;


    Pacman.nextX = 0;
    Pacman.nextY = 0;
    Pacman.x = 14;
    Pacman.y = 26;
    Pacman.score = 0;


    Blinky.x = 13;
    Blinky.y = 14;
    Blinky.score = 0;
    Blinky.direction = -1;
    Blinky.lastDirection = -1;


    Pinky.x = 14;
    Pinky.y = 14;

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

                window.draw(blinky); // ���㥬 �����

              




               
                pinky.setPosition(Pinky.x * 25, Pinky.y * 25);


                blinky.setPosition(Blinky.x * 25, Blinky.y * 25);

                window.draw(blinky); // ���㥬 ������
                window.draw(pinky);






                window.display(); // ������塞 ����
            }
        return 0;
    }