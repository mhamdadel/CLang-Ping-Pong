#ifndef MYLIBRARY
#define MYLIBRARY
#include<windows.h>
#include<unistd.h>
void SetColor(int ForgC);
void textattr(int ForgC);
void clrscr();
void gotoxy(int x, int y);
int len(char arr[]);
int msleep(long tms);
#endif // MYLIBRARY
