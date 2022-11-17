#include <stdio.h>
#include <stdlib.h>
#include "mylibrary.h"
#define PlayerSize 7
#define HIGHT 20
#define WIDTH 50
#define FRAME 20
#define NULL 0
int line = 0;
int inPage = 0;
char items[3][10] = {{"play"},{"exit"}};


void backspace()
{
    if(inPage == 0)
    {
        exit(0);
    }
}
typedef struct ball
{
    int x;
    int y;
    int dir;
    int angle;
} ball;

typedef struct player
{
    short int number;
    int x;
    int y;
    int dir;
    int points;
    char draw[PlayerSize];
} player;

void draw(player *playerOne, player *playerTwo);
void movePlayer(player *playerOne, player *playerTwo, ball * mainBall);
void drawBall(ball * mainBall);
int touch(ball * mainBall, player * player);
char GTR = 2, GTL = -2, STOP = 0;
void movePlayer(player *playerOne, player *playerTwo, ball * mainBall)
{
    /**/
    char btn = 0;
    if (_kbhit())
    {
        btn =  _getch();
    }
    // player one control
    if (playerOne->x < WIDTH && playerOne->x >= 0&& playerOne->number == 1)
    {
        switch (btn)
        {
        case 54:
            //if(playerOne->x < HIGHT)
            playerOne->x += GTR;
            break;
        case 52:
            if(playerOne > 0)
            {
                playerOne->x += GTL;
            }
            break;
        default:
            playerOne->x += STOP;
            break;
        }
    }
    // player two control
    if (playerTwo->x < WIDTH && playerTwo->x >= 0 && playerTwo->number == 2)
    {
        switch (btn)
        {
        case 100:
            if(playerTwo->x < HIGHT)
            {
                playerTwo->x += GTR;
            }
            break;
        case 97:
            if(playerTwo->x > 0)
            {
                playerTwo->x += GTL;
            }
            break;
        default:
            playerTwo->x += STOP;
            break;
        }
    }
    // ball direction
    if(mainBall->y <= playerOne->y &&
            (mainBall->x >= playerOne->x && mainBall->x <= playerOne->x + PlayerSize))
    {
        mainBall->dir = 1;
    }
    else if(mainBall->y >= playerTwo->y &&
            (mainBall->x >= playerTwo->x && mainBall->x <= playerTwo->x + PlayerSize))
    {
        mainBall->dir = -1;
    }
    // ball touch player angle
    if( (mainBall->dir == 1 && playerOne->y == mainBall->y))
    {
        // angle
        if(mainBall->x >= playerOne->x && mainBall->x < playerOne->x + (PlayerSize/2))
        {
            mainBall->angle = -1;
        }
        else if(mainBall->x > playerOne->x + (PlayerSize/2) && mainBall->x <= playerOne->x + PlayerSize )
        {
            mainBall->angle = 1;
        }
        else if(mainBall->x == playerOne->x + (PlayerSize/2))
        {
            mainBall->angle = 0;
        }
    }
    else if ( (mainBall->dir == -1 && playerTwo->y == mainBall->y))
    {
        // angle
        if(mainBall->x >= playerTwo->x && mainBall->x < playerTwo->x + (PlayerSize/2))
        {
            mainBall->angle = -1;
        }
        else if(mainBall->x > playerTwo->x + (PlayerSize/2) && mainBall->x <= playerTwo->x + PlayerSize )
        {
            mainBall->angle = 1;
        }
        else if(mainBall->x == playerOne->x + (PlayerSize/2))
        {
            mainBall->angle = 0;
        }
    }
    // ball touch walls
    if(mainBall->x <= 0 && mainBall->dir == -1)
    {
        mainBall->angle = 1;
    }
    else if(mainBall->x <= 0 && mainBall->dir == 1)
    {
        mainBall->angle = 1;
    }
    else if(mainBall->x >= WIDTH && mainBall->dir == 1)
    {
        mainBall->angle = -1;
    }
    else if(mainBall->x >= WIDTH && mainBall->dir == -1)
    {
        mainBall->angle = -1;
    }


    // point to player one
    if(mainBall->y >= HIGHT)
    {
        playerOne->points++;
        mainBall->y = playerOne->y;
        mainBall->x = playerOne->x;
        mainBall->angle = 0;
        mainBall->dir = 0;
    }

    if(mainBall->y <= 0)  // point to player two
    {
        playerTwo->points++;
        mainBall->y = playerTwo->y;
        mainBall->x = playerTwo->x;
        mainBall->angle = 0;
        mainBall->dir = 0;
    }
    // make direction and angle for the ball
    mainBall->y += mainBall->dir;
    mainBall->x += mainBall->angle;
    // gotoxy and draw
    system("cls");
    gotoxy(playerOne->x, playerOne->y);
    printf("%s",playerOne->draw);
    gotoxy(playerTwo->x, playerTwo->y);
    printf("%s",playerTwo->draw);
    gotoxy(mainBall->x, mainBall->y);
    printf("*");
    gotoxy(0, HIGHT+3);
    printf("player one score : %d\nplayer two score : %d",playerOne->points,playerTwo->points);

}
int main()
{
    //menu();
    /**/
    int i = 0;
    ball mainBall;
    player playerOne, playerTwo;
    playerOne.number = 1;
    playerTwo.number = 2;
    playerOne.points = 0;
    playerTwo.points = 0;
    mainBall.dir = 1;
    draw(&playerOne, &playerTwo);
    drawBall(&mainBall);
    for (i = 0; i < PlayerSize; i++)
    {
        playerOne.draw[i]  = '=';
        playerTwo.draw[i]  = '=';
    }

    while (1)
    {
        msleep(1000/FRAME);
        movePlayer(&playerOne, &playerTwo, &mainBall);
    }
    /**/
    return 0;
}

void draw(player *playerOne, player *playerTwo)
{
    int x;
    x = (WIDTH/2)-(PlayerSize/2);
    playerOne->x = x;
    playerOne->y = 1;

    playerTwo->x = x;
    playerTwo->y = HIGHT-1;

    gotoxy(playerOne->x, playerOne->y);
    printf("%s",playerOne->draw);

    gotoxy(playerTwo->x, playerTwo->y);
    printf("%s",playerTwo->draw);
}
void drawBorder()
{
    int i = 0, j=0;
    for(i=1; i<=WIDTH; i++)
    {
        for(j=1; j<=WIDTH; j++)
        {
            if(i==1 || i==WIDTH || j==1 || j==WIDTH)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void drawBall(ball * mainBall)
{
    int x;
    x = (WIDTH/2);
    mainBall->x = x;
    mainBall->y = 2;
    gotoxy(mainBall->x, mainBall->y);
    printf("*");
}

int touch(ball * mainBall, player * player)
{
    if(mainBall->x >= player->x && mainBall->x <= player->x + PlayerSize &&
            ((mainBall->y == player->y + 1 && player->number == 1) ||
             (mainBall->y == player->y - 1 && player->number == 2))
      )
    {
        printf("%d", player->number);
        return player->number;
    }
}


void menu()
{
    int i;
    system("cls");
    printf("line : %d\n", line);
    for(i=0; i<3; i++)
    {
        if(line == i+1)
        {
            printf("\033[0;31m {%s} \033[0m\n", items[i]);
        }
        else
        {
            printf("%s\n", items[i]);
        }
    }

    char n = getch();
    do
    {
        if(n == -32) //extended key
        {
            switch (getch())
            {
            case 72: // up
                if(line == 0)
                {
                    line = 3;
                }
                else if(line == 1)
                {
                    line = 3;
                }
                else
                {
                    line--;
                }
                menu();
                break;
            case 80: // down
                if(line == 0)
                {
                    line = 1;
                }
                else if(line == 3)
                {
                    line = 1;
                }
                else
                {
                    line++;
                }
                menu();
                break;
            case 13 :
                if(line != 0)
                {
                    if(line == 1) break;
                    else if (line == 2) exit(0);
                }
                break;
            case 8 :
                menu();
                backspace();
                break;
            }
        }
    }
    while(n != 13 || inPage != 3);
}
