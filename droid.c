#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
int  MAX_X=80;
int  MAX_Y=24;
int key,c;
int high_score=0;
int speed=0;
int kbhit(void);
int gotoxy(int,int);
int intro(int,int);
int game_logo(int,int);
int game_menu();
int instruction();
int scoreboard(int,int);
int boundary(void);
int road(int,int);
int droid(int,int);
int car(int,int);
int reset(void);
int endgame(int,int);
int clean(void);
int main(void)
{	
	printf("\e[8;24;80t");// resizes terminal using xterm inbuilt escape sequence code
	boundary();
	intro(10,5);
	clean();
	boundary();
	game_logo(20,5);
	game_menu();
	clean();
	key=getchar();
	instruction();
	int i,j,lost,sleep,decrease;
	again:
	clean();
	gotoxy(2,2);
	printf("HIGH SCORE::%d\n",high_score);
	printf(" MAX SPEED::%d",speed);
	decrease=2500;
	j=14;
	i=67;
	lost=0;
	sleep=55000;
	boundary();
	scoreboard(60,2);
	droid(15,14);
	road(2,23);
	car(66,20);
	while(lost==0)
	{	
		while(!kbhit())
		{		
			if(i<=24 && i>=6 && j>=14)
			{
				lost=1;
				break;
			}
			high_score=high_score+2;
			scoreboard(60,2);
			if(i==2)
			{
				reset();
				i=66;
			}
			i--;
			car(i,20);
			usleep(sleep);
		}
		if(lost==0)
		{	
			key=getchar();
			if(key==81 || key==113)
			{
				goto end;
			}
		}
		if(lost==0)	
		{
			while(j!=2)
			{	
				if(i<=24 && i>=6 && j>=14)
				{
					lost=1;
					break;
				}
				high_score=high_score+2;
				scoreboard(60,2);
				j--;
				droid(15,j);
				if(i==2)
				{
					reset();
					i=66;
				}
				i--;
				car(i,20);
				usleep(sleep);
			}	
			while(j!=14)
			{	
				if(i<=24 && i>=6 && j>=14)
				{
					lost=1;
					break;
				}
				high_score=high_score+2;
				scoreboard(60,2);
				j++;
				droid(15,j);
				if(i==2)
				{	
					reset();
					i=66;
				}
				i--;
				car(i,20);
				usleep(sleep);
			}
			road(2,23);
			if(sleep!=30000)
			{
				sleep=sleep-decrease;
				speed++;
			}
		}
	}
	endgame(20,10);
	if(key==89 || key==121)
	{
		goto again;
	}
	end:
	gotoxy(0,81);
	return 0;
}
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}
int gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
	return 0;
}
int boundary()
{
	int i;
	for(i=0;i<=MAX_Y;i++)
	{
		gotoxy(0,i);
		printf("#");
		gotoxy(84,i);
		printf("#");
	}	
	for(i=1;i<MAX_X;i++)
	{	
		gotoxy(i,0);
		printf("#");
		gotoxy(i,84);
		printf("#");
	}	
	return 0;
}
int intro(int x,int y)
{	
	int p,q;
	p=x;
	q=y;
	gotoxy(p,q);
	printf("A MINI PROJECT DEVELOPED BY");
	q=q+2;
	gotoxy(p,q);
	printf("RRRR   OOO  H  H III TTTTTT\n");
	q=q+1;
	gotoxy(p,q);
	printf("R   R O   O H  H  I    TT\n"); 
	q=q+1;
	gotoxy(p,q);
	printf("RRRR  O   O HHHH  I    TT\n");  
	q=q+1;
	gotoxy(p,q);   
	printf("R R   O   O H  H  I    TT\n");     
	q=q+1;
	gotoxy(p,q);  
	printf("R  RR  OOO  H  H III   TT\n"); 
	q=q+2;      
	gotoxy(p,q);
	printf(" SSS  RRRR  III V     V  AA   SSS  TTTTTT  AA  V     V\n");
	q=q+1;
	gotoxy(p,q);
	printf("S     R   R  I  V     V A  A S       TT   A  A V     V \n");
	q=q+1;
	gotoxy(p,q);
	printf(" SSS  RRRR   I   V   V  AAAA  SSS    TT   AAAA  V   V  \n");
	q=q+1;
	gotoxy(p,q);
	printf("    S R R    I    V V   A  A     S   TT   A  A   V V   \n");
	q=q+1;
	gotoxy(p,q);
	printf("SSSS  R  RR III    V    A  A SSSS    TT   A  A    V    \n");                                                                                                        
	sleep(4);
	return 0;
}
int game_logo(int x,int y)
{
	int p,q;
	p=x;
	q=y;
	gotoxy(p,q);
	printf(" _|_|_|    _|_|_|      _|_|    _|_|_|  _|_|_|\n");
	q=q+1;
	gotoxy(p,q);
	printf(" _|    _|  _|    _|  _|    _|    _|    _|    _|\n");  
	q=q+1;
	gotoxy(p,q);  
	printf(" _|    _|  _|_|_|    _|    _|    _|    _|    _|\n");    
	q=q+1;
	gotoxy(p,q);
	printf(" _|    _|  _|    _|  _|    _|    _|    _|    _|\n");    
	q=q+1;
	gotoxy(p,q);
	printf(" _|_|_|    _|    _|    _|_|    _|_|_|  _|_|_|\n"); 
	return 0;                                
}
int game_menu()
{
		int choice;
		gotoxy(20,18);
		printf("1.START NEW GAME");
		gotoxy(20,21);
		printf("2.QUIT");
		gotoxy(20,23);
		printf("Enter your choice:");
		scanf("%d",&choice);
		if(choice==2)
		{
			exit(0);
		}
		return 0;
}
int instruction()
{ 
	boundary();
	scoreboard(60,2);
	droid(15,14);
	road(2,23);
	car(66,20);
	gotoxy(34,5);
	printf(" INSTRUCTIONS ");
	gotoxy(34,6);
	printf("--------------");
	gotoxy(7,7);
	printf("press any key to make the droid jump to avoid collison with the car.");
	gotoxy(15,8);
	printf("The speed of car will increase with the progress.");
	gotoxy(25,9);
	printf("(press 'Q' to quit any time)");
	gotoxy(30,10);
	printf("------------------------");
	gotoxy(30,11);
	printf("(press any key to Start)");
	while(!kbhit())
	{
	}
	return 0;
}
int scoreboard(int x,int y)
{
	int p,q;
	p=x;
	q=y;
	gotoxy(p,q);
	printf("SCORE::%d",high_score);
	q=q+1;
	gotoxy(p,q);
	printf("SPEED::%d",speed);
	return 0;
}
int road(int x,int y)
{
	int i,p,q;
	p=x;
	q=y;
	gotoxy(p,q);
	for(i=2;i<80;i++)
	{
		printf("!");
	}
	return 0;
}	
int droid(int x,int y)
{
	int p,q;
	p=x;
	q=y;
	gotoxy(p,q);
	printf("             ");
	q=q+1;
	gotoxy(p,q);
	printf("   ╲    ╱\n");
	q=q+1;
	gotoxy(p,q);
	printf("   ╱▔▔▔▔╲   ");
	q=q+1;
	gotoxy(p,q);
	printf("  ┃┈▇┈┈▇┈┃  ");
	q=q+1;
	gotoxy(p,q);
	printf("╭╮┣━━━━━━┫╭╮ ");
	q=q+1;
	gotoxy(p,q);
	printf("┃┃┃┈┈┈┈┈┈┃┃┃  ");
	q=q+1;
	gotoxy(p,q);
	printf("╰╯┃┈┈┈┈┈┈┃╰╯ ");
	q=q+1;
	gotoxy(p,q);
	printf("  ╰┓┏━━┓┏╯  ");
	q=q+1;
	gotoxy(p,q);
	printf("   ╰╯┈┈╰╯\n");
	q=q+1;
	gotoxy(p,q);
	printf("                ");
	return 0;
}
int car(int x,int y)
{
	int p,q;
	p=x;
	q=y;
	gotoxy(p,q);
	printf("   .--.    ");
	q=q+1;
	gotoxy(p,q);
	printf(".--'   '--. ");
	q=q+1;
	gotoxy(p,q);   
	printf("'-()---()-' ");
	return 0;
}
int reset()
{
	int i,j;
	j=22;
	for(i=0;i<=3;i++)
	{
		gotoxy(2,j-i);
		printf("            ");
	}
	return 0;
		
}
int endgame(int x,int y)
{	
	int p,q,i;
	i=10;
	p=x;
	q=y;
	gotoxy(p,q);
	printf("YOU LOST");
	q=q+1;
	gotoxy(p,q);
	printf("PLAY AGAIN:Y/N?::");
	q=q+1;
	while(!kbhit())
	{
		i--;
		gotoxy(p,q);
		printf("(game will automatically close in %d seconds)",i);
		usleep(1000000);
		if(i==0)
		{
			break;
		}
	}
	if(i!=0 )
	{
		key=getchar();
	}
	return 0;
}
int clean(void)
{
	int i;
	gotoxy(0,0);
	for(i=0;i<1920;i++)
	{
		printf(" ");
	}
	return 0;
}





