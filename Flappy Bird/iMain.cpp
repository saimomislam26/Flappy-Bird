#include "iGraphics.h"
#include <stdio.h>
#include <time.h>
#include<stdlib.h>


int random(int low, int high)
{
	return rand() % (high - low + 1) + low;
}
struct buttonCoordinate
{
	int x;
	int y;

}bcoordinate[2];
int posx,posy;
char button[10][30]={"playB.bmp","highscore.bmp"};
char homemenu[20]="menu.bmp";
char play[20]="play.bmp";
char highscore[30]="score.bmp";
//char ins[25]="ins.bmp";


struct background
{
	int x,y;

}bnd[20];

int backGroundTimer = 0;
int birdTimer;
int birdX = 250,birdY = 300;
int speed = 8;
int jump = 80;
int currentPosition;
int destination;
bool birdUp , firstClick = false;

char bg[20][20] ={
				   "bg//1.bmp",
				   "bg//2.bmp",
				   "bg//3.bmp",
				   "bg//4.bmp",
				   "bg//5.bmp",
				   "bg//6.bmp",
				   "bg//7.bmp",
				   "bg//8.bmp",
				   "bg//9.bmp",
				   "bg//10.bmp",
				   "bg//11.bmp",
				   "bg//12.bmp",
				   "bg//13.bmp",
				   "bg//14.bmp",
				   "bg//15.bmp",
				   "bg//16.bmp",
				   "bg//17.bmp",
				   "bg//18.bmp",
				   "bg//19.bmp",
				   "bg//20.bmp"
};

bool birdHitsPiller();

struct piller {
	int x;
	int y;
	int height;
	int lenght;
}piller[10], pillerUp[10];


void setPiller()
{

	for (int i = 0, dx = 0; i < 10; i++, dx += 200)
	{
		piller[i].x = 500 + dx;
		piller[i].y = 0;
		piller[i].lenght = 30;
		piller[i].height = random (150, 250);
	}
	for (int i = 0; i < 10; i++)
	{
		pillerUp[i].height = 500 - piller[i].height;
		pillerUp[i].x = piller[i].x;
		pillerUp[i].y = 700 - pillerUp[i].height;
		pillerUp[i].lenght = 30;
	}
}

void resetPiller()
{
	for (int i = 0; i < 10; i++)
	{
		if (piller[i].x <= -piller[i].lenght)
		{
			piller[i].x = 2000 - piller[i].lenght;
		}
	}
}

void movePiller()
{
	for (int i = 0; i < 10; i++)
	{
		piller[i].x -= 5;
		pillerUp[i].x = piller[i].x;
	}
	resetPiller();
}
bool birdHitsPiller();
int score=0;
int s = 15;
void showPiller()
{
	int i;
	
	for ( i = 0; i < 10; i++)
	{
		iSetColor(13, 255, 12);
		iFilledRectangle(piller[i].x, piller[i].y, piller[i].lenght, piller[i].height);
		iFilledRectangle(pillerUp[i].x, pillerUp[i].y, pillerUp[i].lenght, pillerUp[i].height);
		
		if (birdX >= piller[i].x + piller[i].lenght && birdX <= piller[i].x + piller[i].lenght + 4)
		{
			
			if (i != s)
			{
				score++;
				s = i;
			}
		}
		
	}
	
	
}

bool menu = true;

bool birdHitsPiller()
{
	for (int i = 0; i < 10; i++)
	{
		if (birdX + 70 >= piller[i].x && birdX - 10 <= piller[i].x + piller[i].lenght)
		{
			if (birdY +12 <= piller[i].height || birdY + 48 >= pillerUp[i].y)
			{
				return true;
				break;
			}
		}
		
	}
	return false;
}


int gamestart =-1;
void iDraw()
{
	iClear();
	if(gamestart =-1)
	{
	iShowBMP(0,0,homemenu);
	for(int i=0;i<2;i++)
	{
		iShowBMP2(bcoordinate[i].x,bcoordinate[i].y,button[i],0);
	}
	}
	else if(gamestart==0)
	{
		iShowBMP(0,0,play);
	}
	else if(gamestart==1)
	{
		iShowBMP(0,0,highscore);
	}
	//else if(gamestart==2)
	//{
		//iShowBMP(0,0,ins);
	//}
	else
	{

	}
	birdHitsPiller();
	if(birdHitsPiller())
	{
		menu = false;
	}

	if(menu)
	{
		for(int i = 0; i < 20; i++)
		{
			iShowBMP(bnd[i].x,bnd[i].y,bg[i]);
		}
		char strscore[40];
		sprintf(strscore,"score:%d",score);
		iSetColor(0,0,0);
		iText(300,550,strscore,GLUT_BITMAP_HELVETICA_18);

		iShowBMP2(birdX,birdY,"flappy.bmp",255);

		showPiller();
	}
	else
	{
		iSetColor(255,0,0);
		iText(500,500,"Game Over");
		//iShowBMP2(0,0,"bb.bmp", 0);
	}
}

void iMouseMove(int mx, int my){}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for(int i=0;i<2;i++)
		{
			if(mx>=bcoordinate[i].x && mx<=bcoordinate[i].x+100 && my>=bcoordinate[i].y && my<=bcoordinate[i].y+34)

			{
				gamestart=i;
			}
		}
		if(firstClick == false)
		{
			firstClick = true;
			iResumeTimer(birdTimer);
			iResumeTimer(backGroundTimer);
		}
		currentPosition = birdY;
		birdUp = true;
		destination = currentPosition + jump;

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void iPassiveMouseMove(int mx,int my) {}

void iKeyboard(unsigned char key)
{
	if(key == 'q'){}
}

void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
}

void backGroundMove()
{
	for(int i = 0; i < 20; i++)
	{
		bnd[i].x -= 32;

		if(bnd[i].x < 0 )
			bnd[i].x = 608;
	}
}

void birdMove()
{
	if(birdUp == true)
	{
		birdY += speed;
		if(birdY > destination)
			birdUp = false;
	}
	if(birdUp == false)
	{
		birdY -= speed;
	}
}

int main()
{
	srand(time(0));
	int j=50;
	for(int i=1;i>=0;i--)
	{
		bcoordinate[i].x=200;
		bcoordinate[i].y=j;
		j+=100;
	}
	setPiller();
	int sum = 0;
	for(int i = 0; i < 20 ; i++)
	{
		bnd[i].y = 0;
		bnd[i].x += sum;
		sum += 32;
	}
	

	backGroundTimer = iSetTimer(100, backGroundMove);
	//iPauseTimer(backGroundTimer);
	iSetTimer(30, movePiller);
	birdTimer = iSetTimer(50, birdMove);
	//iPauseTimer(birdTimer);
	
	

	iInitialize(608, 700, "Flappy Bird");
	return 0;
}
