#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>

class SnakeGame {
public:
    SnakeGame(int width, int height)
        : width(width), height(height), gameOver(false), score(0) {
        srand(static_cast<unsigned>(time(0)));
        initializeSnake();
        spawnFruit();
    }

    void runGame() {
        while (!gameOver) {
            draw();
            input();
            move();
            checkCollision();
            checkFruit();
            Sleep(100); // Windows için bekleme fonksiyonu
        }
        std::cout << "Oyun bitti! Toplam puan: " << score << std::endl;
    }

private:
    const int width;
    const int height;
    bool gameOver;
    int score;

    struct Point {
        int x;
        int y;
    };

    enum Direction {
        STOP = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Direction dir;
    Point head;
    Point fruit;

    void initializeSnake() {
        dir = STOP;
        head.x = width / 2;
        head.y = height / 2;
    }

    void spawnFruit() {
        fruit.x = rand() % width;
        fruit.y = rand() % height;
    }

    void draw() {
        system("cls"); // Ekranı temizle (Windows için)

        for (int i = 0; i < width + 2; i++)
            std::cout << "#";
        std::cout << std::endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    std::cout << "#"; // Duvar başlangıcı
                if (i == head.y && j == head.x)
                    std::cout << "O"; // Yılan başı
                else if (i == fruit.y && j == fruit.x)
                    std::cout << "F"; // Meyve
                else {
                    bool isBodyPart = false;
                    for (int k = 0; k < tail.size(); k++) {
                        if (tail[k].x == j && tail[k].y == i) {
                            std::cout << "o"; // Yılanın vücut kısmı
                            isBodyPart = true;
                        }
                    }
                    if (!isBodyPart)
                        std::cout << " ";
                }

                if (j == width - 1)
                    std::cout << "#"; // Duvar sonu
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width + 2; i++)
            std::cout << "#";
        std::cout << std::endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void move() {
        Point prev = tail.empty() ? head : tail.back();
        for (int i = tail.size() - 1; i > 0; i--)
            tail[i] = tail[i - 1];
        if (!tail.empty())
            tail[0] = head;

        switch (dir) {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        }
    }

    void checkCollision() {
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            gameOver = true;

        for (const auto& part : tail) {
            if (part.x == head.x && part.y == head.y)
                gameOver = true;
        }
    }

    void checkFruit() {
        if (head.x == fruit.x && head.y == fruit.y) {
            score += 10;
            spawnFruit();
            tail.push_back({ 0, 0 }); // Yılanın kuyruğuna yeni bir parça ekle
        }
    }

    // Windows için Sleep fonksiyonu eklenmiştir.
    void Sleep(unsigned milliseconds) {
        std::clock_t start = std::clock();
        while ((std::clock() - start) / (double)CLOCKS_PER_SEC * 1000.0 < milliseconds)
            ;
    }

    std::vector<Point> tail;
};

int main() {
    const int width = 20;
    const int height = 10;

    SnakeGame snakeGame(width, height);
    snakeGame.runGame();

    return 0;
}
