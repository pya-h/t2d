#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void gotoxy(int, int);
#ifndef CONSOLE_H
  #define CONSOLE_H
#endif

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
    #include <conio.h>
    #include <windows.h>
    void gotoxy(int x, int y)
    {
        COORD c = { x, y };  
        SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
    }
    void printw(char str[], char param = 0) {
      if(param)
        printf(str, param);
      
      else
        printf(str);
      
    }
#elif defined __unix__
    #define CLEAR_SCREEN "clear"
    #include <curses.h>
    #include <ncurses.h>

    void gotoxy(int x, int y) {
      move(y, x);
      refresh();
    }
    
    WINDOW *create_newwin(int height, int width, int starty, int startx)
    {
      WINDOW *local_win = newwin(height, width, starty, startx);
      box(local_win, 0, 0);
      wrefresh(local_win);

      return (local_win);
    }
    void wgotoxy(int x, int y, WINDOW *win)
    {
      wmove(win, y, x);
    }

#elif defined __APPLE__
    #define CLEAR_SCREEN "clear"
    void gotoxy(int x, int y)
    {
      system(CLEAR_SCREEN)
        printf("%c[%d;%df", 0x1B, y, x);
    }

    int getch(void)
    {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }
    void printw(char str[], char param = 0) {
      if(param)
        printf(str, param);
      
      else
        printf(str);
      
    }
#endif
