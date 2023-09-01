
#include <ncurses.h>
#include <iostream>

using namespace std;

void input();
void setup();
void draw();
void move();

bool gameover;
int x, y, width = 30, height = 15, score, xTail[100], yTail[100], ntail, Xfruit, Yfruit, speed;

enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction dir;

void setup()
{
    initscr();
    clear();
    cbreak();
    curs_set(0);

    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    Xfruit = (rand() % width) + 1;
    Yfruit = (rand() % height) + 1;

    score = 0;
    ntail = 3;
    speed = 2;
}

void draw()
{
    clear();

    for (int i = 0; i < width + 2; i++)
    {
        printw("-");
    }
    printw("\n");

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1)
            {

                mvprintw(i, j, "+");
            }
            else if (j == 0 || j == width + 1)
            {
                mvprintw(i, j, "+");
            }
            else if (Xfruit == j && Yfruit == i)
            {
                start_color();

                init_pair(2, COLOR_RED, COLOR_YELLOW);
                attron(COLOR_PAIR(2));

                mvprintw(i, j, "Q");
                attroff(COLOR_PAIR(2));
            }

            else if (i == y && j == x)
            {
                start_color();

                init_pair(1, COLOR_BLACK, COLOR_RED);
                attron(COLOR_PAIR(1));

                mvprintw(i, j, "O");
                attroff(COLOR_PAIR(1));
            }
            else
                for (int k = 0; k < ntail; k++)
                {
                    if (i == yTail[k] && j == xTail[k])
                    {
                        start_color();

                        init_pair(1, COLOR_BLACK, COLOR_RED);
                        attron(COLOR_PAIR(1));

                        mvprintw(i, j, "o");
                        attroff(COLOR_PAIR(1));
                    }
                }
        }
    }
    printw("\n");
    printw("\n");
    start_color();

    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    printw(" Score  : %d ", score);
    attroff(COLOR_PAIR(3));
    refresh();
}

void input()
{
    keypad(stdscr, true);
    halfdelay(speed);
    if (ntail > 5)
    {
        speed = 1;
        if (ntail > 10)
        {
            speed = 0;
        }
    }

    int c = getch();
    switch (c)
    {
    case KEY_LEFT:
        dir = LEFT;

        break;
    case KEY_RIGHT:
        dir = RIGHT;

        break;
    case KEY_UP:
        dir = UP;

        break;
    case KEY_DOWN:
        dir = DOWN;

        break;
    case 'q':
        gameover = true;
        break;
    }
}

void move()
{

    int prevx = xTail[0];
    int prevy = yTail[0];
    int prev2x, prev2y;

    xTail[0] = x;
    yTail[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = xTail[i];
        prev2y = yTail[i];

        xTail[i] = prevx;
        yTail[i] = prevy;

        prevx = prev2x;
        prevy = prev2y;
    }

    switch (dir)
    {
    case UP:
        y--;

        break;
    case DOWN:
        y++;

        break;
    case LEFT:
        x--;

        break;
    case RIGHT:
        x++;

        break;
    default:
        break;
    }

    if (x > width || x < 1 || y > height || y < 1)
    {
        gameover = true;
    }

    if (ntail > 3)
    {
        for (int i = 0; i < ntail; i++)
        {
            if (xTail[i] == x && yTail[i] == y)
            {
                gameover = true;
            }
        }
    }

    if (Xfruit == x && Yfruit == y)
    {
        score += 10;
        ntail++;
        Xfruit = (rand() % width) + 1;
        Yfruit = (rand() % height) + 1;
    }
}

int main()
{
    setup();
    while (!gameover)
    {
        draw();
        input();
        move();
    }

    getch();
    endwin();

    return 0;
}