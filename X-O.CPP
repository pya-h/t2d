// #include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console.h"
#define X 0
#define O 1
#define EMPTY 0

int x,y,shift,ax,ay;

char t[3][3];
void display_table();
void check_table(char);
void show_winner(char,int,int,char);
void Xmove(char);
void Omove();
void random(int&,int&);
void writeO(int,int);
void freerand(bool&);
bool find_two_O();
bool find_another_O(int,int);
void placeO(int,int);
void denote_winner(int&,int&,char&);
void attack_for_avoid_attack();
void move_in_table(int,int);
void movefree(bool&);
int zero_to_two();
int nofs = 0;

WINDOW *win;
int main()
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();

   srand(time(0));
   shift = X;
   x = 29;
   y = 8;
   ax = 0;
   ay = 0;
	display_table();
   gotoxy(x,y);
   // refresh();
   char ch;
   while(1)
   {
      if(shift == X)
      {
         ch = getch();
			Xmove(ch);
      }
      else
      	Omove();
      gotoxy(x,y);
      if(nofs >= 9)
      	show_winner('d',x,y,'d');
   }
   endwin();
   return 0;
}
void display_table()
{
   gotoxy(25,17);
	printw("         |         |         \n");
   gotoxy(25,8);
   printw("         |         |         \n");
   gotoxy(25,9);
   printw("         |         |         \n");
   gotoxy(25,10);
   printw("---------|---------|---------\n");
   gotoxy(25,11);
   printw("         |         |         \n");
   gotoxy(25,12);
   printw("         |         |         \n");
   gotoxy(25,13);
   printw("         |         |         \n");
   gotoxy(25,14);
   printw("---------|---------|---------\n");
   gotoxy(25,15);
   printw("         |         |         \n");
   gotoxy(25,16);
   printw("         |         |         \n");
   gotoxy(25,17);
   printw("         |         |         \n");
   // refresh();
}

void check_table(char s)
{
   int xx = 0,yy = 0;
	for(;yy <= 2;yy++)
   	if(t[xx][yy] == t[xx+1][yy] && t[xx+1][yy] == t[xx+2][yy] && t[xx+2][yy] != EMPTY)
      	show_winner(s,xx,yy,'x');
   for(xx = 0,yy = 0;xx <= 2;xx++)
   	if(t[xx][yy] == t[xx][yy+1] && t[xx][yy+1] == t[xx][yy+2] && t[xx][yy+2] != EMPTY)
      	show_winner(s,xx,yy,'y');
   if(t[0][0] == t[1][1] && t[1][1] == t[2][2] && t[2][2] != EMPTY)
   	show_winner(s,-1,-1,'\\');
   if(t[2][0] == t[1][1] && t[1][1] == t[0][2] && t[0][2] != EMPTY)
      show_winner(s,-1,-1,'/');
}
void show_winner(char w,int x2,int y2,char wm)
{

   denote_winner(x2,y2,wm);
	gotoxy(1,1);
   if(w == 'd')
   	printw("Draw!\nAny Key To Exit...");
   else
   	printw("%c Won!\nAny Key To Exit...",w);
   // refresh();
   getch();
   exit(1);
}
void Xmove(char ch)
{
	switch(ch)
   {
   	case '\r':
      case '\n':
      	if(t[ax][ay] == 'X' || t[ax][ay] == 'O')	break;
         printw("X");
         // refresh();
         t[ax][ay] = 'X';
         check_table('X');
         shift = O;
         nofs++;
         break;
      case 'd':
      case 'D':
      	if(x <= 39)
         {
         	x += 10;
				ax++;
         }
         else
         {
         	x -= 20;
            ax = 0;
         }
         break;
      case 's':
      case 'S':
      	if(y <= 12)
         {
         	y += 4;
         	ay++;
         }
         else
         {
         	y -= 8;
            ay = 0;
         }
         break;
      case 'w':
      case 'W':
      	if(y >= 12)
         {
         	y -= 4;
            ay--;
         }
         else
         {
         	y += 8;
            ay = 2;
         }
         break;
      case 'a':
      case 'A':
      	if(x >= 39)
         {
         	x -= 10;
            ax--;
         }
         else
         {
         	x += 20;
            ax = 2;
			}
			break;
	}
}
void writeO(int ax,int ay)
{
	move_in_table(ax,ay);
   printw("O");
   // refresh();
   gotoxy(x,y);
   nofs++;
}
void random(int& xxx,int& yyy)
{
	xxx = rand() % 3;
   yyy = rand() % 3;
}
void movefree(bool& moved)
{
	int xx,yy;
   if(t[1][1] == 'X' && nofs == 1)
   {
      switch(rand() % 4)
      {
      	case 0:
         	placeO(0,0);
            return;
         case 1:
         	placeO(0,2);
            return;
         case 2:
         	placeO(2,0);
            return;
         case 3:
         	placeO(2,2);
            return;
      }
   }
   else if(nofs == 3)
   {
   	if((t[2][0] == 'X' && t[0][2] == 'X'))
   	{
   		attack_for_avoid_attack();
      	return;
   	}
      else if(t[0][0] == 'X')
      {
      	if(t[2][2] == 'X')
        	{
   			attack_for_avoid_attack();
      		return;
   		}
         else if(t[1][2] == 'X')
   		{
            switch(zero_to_two())
            {
               case 0:
   					placeO(0,2);return;
               case 1:
               	placeO(2,1);return;
               case 2:
               	placeO(2,1);return;
            }
   		}
         else if(t[2][1] == 'X')
   		{
            switch(zero_to_two())
            {
               case 0:
   					placeO(2,0);return;
               case 1:
               	placeO(1,0);return;
               case 2:
               	placeO(1,2);return;
            }
   		}
		}
      else if(t[2][0] == 'X')
      {
      	if(t[1][2] == 'X')
         {
            switch(zero_to_two())
            {
               case 0:
   					placeO(2,2);return;
               case 1:
               	placeO(0,1);return;
               case 2:
               	placeO(2,1);return;
            }
         }
         else if(t[0][1] == 'X')
         {
            switch(zero_to_two())
            {
               case 0:
   					placeO(0,0);return;
               case 1:
               	placeO(1,2);return;
               case 2:
               	placeO(1,0);return;
            }
         }
      }
      else if(t[0][2] == 'X')
      {
      	if(t[1][0] == 'X')
         {
            switch(zero_to_two())
            {
               case 0:
   					placeO(0,0);return;
               case 1:
               	placeO(0,1);return;
               case 2:
               	placeO(2,1);return;
            }
         }
         else if(t[2][1] == 'X')
         {
            switch(zero_to_two())
            {
               case 0:
   					placeO(2,2);return;
               case 1:
               	placeO(1,0);return;
               case 2:
               	placeO(1,2);return;
            }
         }
      }
      else if(t[2][2] == 'X')
      {
      	if(t[1][0] == 'X')
         {
            switch(zero_to_two())
            {
               case 0:
   					placeO(2,0);return;
               case 1:
               	placeO(0,1);return;
               case 2:
               	placeO(2,1);return;
            }
         }
         else if(t[0][1] == 'X')
         {
            switch(zero_to_two())
            {
               case 0:
   					placeO(0,2);return;
               case 1:
               	placeO(1,2);return;
               case 2:
               	placeO(1,0);return;
            }
         }
      }
   }
   else if(t[1][0] == 'X' && t[0][0] == EMPTY && (t[0][1] == 'X' || t[2][1] == 'X'))
   {
   	placeO(0,0);
      return;
   }
   else if(t[1][2] == 'X' && t[0][2] == EMPTY && (t[0][1] == 'X' || t[2][1] == 'X'))
   {
   	placeO(0,2);
      return;
   }
   xx = yy = 1;
   while(t[xx][yy] != EMPTY)
    	random(xx,yy);
   t[xx][yy] = 'O';
   writeO(xx,yy);
   moved = true;
}
void Omove()
{
   bool moved = false;
   moved = find_two_O();
   if(moved == false)
   {
   	int x2,y2;
      int nox = 0;
      for(y2 = 0;y2 <= 2 && moved == false;y2++)
      {
      	for(x2 = 0;x2 <= 2;x2++)
         {
         	if(t[x2][y2] == 'X')
            	nox++;
            if(nox == 2)
            {
            	int x3;
               for(x3 = 0;x3 <= 2;x3++)
               	if(t[x3][y2] == EMPTY || t[x3][y2] == 'O')
                  	break;
               if(t[x3][y2] == EMPTY)
               {
               	placeO(x3,y2);
                  moved = true;
               }
            }
         }
         nox = 0;
      }
   }
   if(moved == false)
   {
   	int x2,y2;
      int nox = 0;
      for(x2 = 0;x2 <= 2 && moved == false;x2++)
      {
      	for(y2 = 0;y2 <= 2;y2++)
         {
         	if(t[x2][y2] == 'X')
            	nox++;
            if(nox == 2)
            {
            	int y3;
               for(y3 = 0;y3 <= 2;y3++)
               	if(t[x2][y3] == EMPTY || t[x2][y3] == 'O')
                  	break;
               if(t[x2][y3] == EMPTY)
               {
               	placeO(x2,y3);
                  moved = true;
               }
            }
         }
         nox = 0;
      }
   }
   if(moved == false)
   {
      moved = true;
		if(t[0][0] == t[1][1] && t[0][0] != EMPTY && t[2][2] == EMPTY)
      	placeO(2,2);
		else if(t[0][0] == t[2][2] && t[2][2] != EMPTY && t[1][1] == EMPTY)
      	placeO(1,1);
		else if(t[1][1] == t[2][2] && t[2][2] != EMPTY && t[0][0] == EMPTY)
      	placeO(0,0);
		else if(t[2][0] == t[1][1] && t[1][1] != EMPTY && t[0][2] == EMPTY)
      	placeO(0,2);
		else if(t[0][2] == t[1][1] && t[1][1] != EMPTY && t[2][0] == EMPTY)
      	placeO(2,0);
		else if(t[0][2] == t[2][0] && t[2][0] != EMPTY && t[1][1] == EMPTY)
      	placeO(1,1);
      else
      	moved = false;
   }
   if(moved == false)
   	movefree(moved);
   shift = X;
   check_table('O');
}
bool find_two_O()
{
	int x2,y2;
   for(y2 = 0;y2 <= 2;y2++)
   	for(x2 = 0;x2 <= 2;x2++)
      	if(t[x2][y2] == 'O' && find_another_O(x2,y2) == true)
         	return true;
   return false;
}
bool find_another_O(int x2,int y2)
{
	switch(x2)
   {
   	case 0:
      	if(t[1][y2] == 'O' && t[2][y2] == EMPTY)
         {
         	placeO(2,y2);
            return true;
         }
         else if(t[2][y2] == 'O' && t[1][y2] == EMPTY)
         {
         	placeO(1,y2);
            return true;
         }
         break;
   	case 1:
      	if(t[2][y2] == 'O' && t[0][y2] == EMPTY)
         {
         	placeO(0,y2);
            return true;
         }
         else if(t[0][y2] == 'O' && t[2][y2] == EMPTY)
         {
         	placeO(2,y2);
            return true;
         }
         break;
   	case 2:
      	if(t[1][y2] == 'O' && t[0][y2] == EMPTY)
         {
         	placeO(0,y2);
            return true;
         }
         else if(t[0][y2] == 'O' && t[1][y2] == EMPTY)
         {
         	placeO(1,y2);
            return true;
         }
         break;
   }
   switch(y2)
   {
   	case 0:
      	if(t[x2][1] == 'O' && t[x2][2] == EMPTY)
         {
         	placeO(x2,2);
            return true;
         }
         else if(t[x2][2] == 'O' && t[x2][1] == EMPTY)
         {
         	placeO(x2,1);
            return true;
         }
         else if(x2 == 0 && t[1][1] == 'O' && t[2][2] == EMPTY)
         {
         	placeO(2,2);
            return true;
         }
         else if(x2 == 2 && t[1][1] == 'O' && t[0][2] == EMPTY)
         {
         	placeO(0,2);
            return true;
         }
         break;
   	case 1:
      	if(t[x2][0] == 'O' && t[x2][2] == EMPTY)
         {
         	placeO(x2,2);
            return true;
         }
         else if(t[y2][2] == 'O' && t[x2][0] == EMPTY)
         {
         	placeO(x2,0);
            return true;
         }
         else if(x2 == 1)
         {
         	if(t[0][0] == 'O' && t[2][2] == EMPTY)
         	{
         		placeO(2,2);
            	return true;
         	}
            else if(t[2][2] == 'O' && t[0][0] == EMPTY)
         	{
         		placeO(0,0);
            	return true;
         	}
            else if(t[0][2] == 'O' && t[2][0] == EMPTY)
         	{
         		placeO(2,0);
            	return true;
         	}
            else if(t[2][0] == 'O' && t[0][2] == EMPTY)
         	{
         		placeO(0,2);
            	return true;
         	}
         }
         break;
   	case 2:
      	if(t[x2][1] == 'O' && t[x2][0] == EMPTY)
         {
         	placeO(x2,0);
            return true;
         }
         else if(t[x2][0] == 'O' && t[x2][1] == EMPTY)
         {
         	placeO(x2,1);
            return true;
         }
         else if(x2 == 0 && t[1][1] == 'O' && t[2][0] == EMPTY)
         {
         	placeO(0,2);
            return true;
         }
         else if(x2 == 2 && t[1][1] == 'O' && t[0][0] == EMPTY)
         {
         	placeO(0,0);
            return true;
         }
         break;
   }
   return false;
}
void placeO(int x2,int y2)
{
	t[x2][y2] = 'O';
   writeO(x2,y2);
}
void denote_winner(int& x2,int& y2,char& wm)
{
	switch(wm)
   {
   	case '\\':
      	move_in_table(0,0);
         printw("\\");
      	// refresh();
         move_in_table(1,1);
         printw("\\");
      	// refresh();
         move_in_table(2,2);
         printw("\\");
         // refresh();
         break;
      case '/':
      	move_in_table(2,0);
         printw("/");
      	// refresh();
         move_in_table(1,1);
         printw("/");
      	// refresh();
         move_in_table(0,2);
         printw("/");
         // refresh();
         break;
      case 'x':
      	move_in_table(x2,y2);
         printw("--");
      	// refresh();
         move_in_table(x2 + 1,y2);
         printw("--");
      	// refresh();
         move_in_table(x2 + 2,y2);
         printw("--");
         // refresh();
         break;
      case 'y':
      	move_in_table(x2,y2);
         printw("|");
      	// refresh();
         move_in_table(x2,y2 + 1);
         printw("|");
      	// refresh();
         move_in_table(x2,y2 + 2);
         printw("|");
         // refresh();
         break;
      case 'd':
      	break;
   }
}
void move_in_table(int ax,int ay)
{
	int tx = 29;
   int ty = 8;
   int i;
   for(i = 0;i < ax;i++)
   	tx += 10;
   for(i = 0;i < ay;i++)
   	ty += 4;
   gotoxy(tx,ty);
   // refresh();
}
void attack_for_avoid_attack()
{
	int rnd = rand() % 4;
   switch(rnd)
   {
   	case 0:
      	placeO(1,0);
         return;
   	case 1:
      	placeO(0,1);
         return;
   	case 2:
      	placeO(2,1);
         return;
   	case 3:
      	placeO(1,2);
         return;
   }
}
int zero_to_two()
{
	return rand() % 3;
}
