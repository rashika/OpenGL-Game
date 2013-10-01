#include <unistd.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <map>
#include <stack>
#include <string>
#include <climits>
#include <ctime>
#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <GL/glu.h>
#include "glm.cpp"
#include "imageloader.h"
using namespace std;
#define LL long long
#define ULL unsigned long long
#define LD long double
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(x) ((x)<0?-(x):(x))
#define si(n) scanf("%d",&n)
#define sf(n) scanf("%f",&n)
#define ss(n) scanf("%s",n)
#define pnl printf("\n")
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define FORR(i,n) for(int i=(n);i>=0;i--)
#define DB(x) cout<<"\n"<<#x<<" = "<<(x)<<"\n";
#define CL(a,b) memset(a,b,sizeof(a))
#define GOLD ((1+sqrt(5))/2)
const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;
void swaps (char *x,char *y){char temp;temp=*x;*x=*y;*y=temp;}
void swapi(int *a,int *b){int temp;temp=*a;*a=*b;*b=temp;}
ULL gcd(ULL a,ULL b){if(a==0)return b;if(b==0)return a;if(a==1||b==1)return 1;
if(a==b)return a;if(a>b)return gcd(b,a%b);else return gcd(a,b%a);}
int Current_Stage;
int len = 0;
int flag = 0;
class Textures
{
	public:
	GLuint loadTexture(Image*);
	GLuint grassTextureId,stoneTextureId,WaterTextureId;
	GLuint TrampolineTextureId;GLuint Coin;GLuint Teleportation;GLuint Up;GLuint Right;GLuint Left;GLuint Back;
	GLuint Front;
	GLuint Bottom;
	GLuint side;
};
Textures Aesthetics[10];
GLuint Textures :: loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId); 
	glBindTexture(GL_TEXTURE_2D, textureId); 
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels); 
	return textureId; 
}
class Ground
{
	public:
		typedef struct Tile
		{
			float x1,x2,x3,x4,z1,z2,z3,z4,h;
		}Tile;
		vector<Tile> Field;
		vector<Tile> RaisedUp;
		vector<Tile> Missing;
		vector<Tile> Falling;
		int Timer;
		int Helicopter;
		int CollectibleTimer;
		float HeliAngle;
		void HelicopterView();
		void TowerView();
		int CollectAngle;
		int Tower;
		float Helicopter_x,Helicopter_y,Helicopter_z;
		bool Rocks[1000];
		float DecrementRocks[1000];
		float Value_Rocks[1000];
		bool TilesUp[1000];
		bool Ambience;
		bool Clock;
		bool Night;
		int Dest;
		bool Tile_View;
		void TileView();
		int Here;
		bool InvisibleTiles[1000];
		bool Trampoline_Tiles[1000];
		float Raise_Value[1000];
		bool UP[1000],DOWN[1000];
		int Collectible_Position;
		float IncrementValues[1000];
		float yi;
		void JUMP(void);
		float Tile_Const;
		Tile Store_Coords;
		bool TeleportTiles[1000];
		void CreateTiles(int,int,float,float,float);
		void Tile_Coordinates(float,float,float,int,int);	
		bool Intersection();
		void RandomIteratebility();
		bool FallenUnderTheSea();
		void TilesChangeUp(int,int);
		void Initiate();
		int Cur_Tile;
		int Collide;
		void RandomFallingRocks();
		float xi,zi;
		bool OutOfTheField();
		int Num_PowerUps;
		int PowerTimer;
		void Crumbling();
		void FindRequiredTile(float x,float z);
		void Collectibles(void);
		int PowerUps(void);
		void Fallen();
		void Teleport();
		void Trampoline();
		float MIN_LIM;
		float MAX_LIM;
		float Sun_x,Sun_y,Sun_z;
		float Amb_x,Amb_y,Amb_z;
		float LIM;
		bool LIM_reached;
		int Powerup_Pos;

};
Ground Lvl1[10];
void Ground :: RandomFallingRocks()
{
	int val; 
	FOR(i,0,10)
	{
		val = (rand()%100);
		Rocks[val] = true;
		DecrementRocks[val] = (rand()%100)*1.0/500;
		Value_Rocks[val] = 2.0;
	}
	//cout<<endl;
			//cout<<Raise_Value[num]<<endl;
}
void Ground :: FindRequiredTile(float x,float z)
{
	Crumbling();
}
void Ground :: TilesChangeUp(int n,int Num_Tiles)
{
	int val;
	memset(TilesUp,false,sizeof(TilesUp));
	memset(InvisibleTiles,false,sizeof(InvisibleTiles));
	memset(Raise_Value,0,sizeof(Raise_Value));
	if(Current_Stage>=1)
	{
		FOR(i,0,Num_Tiles/2)
		{
			val = rand()%(n);
			while(val==Collectible_Position||val==0)
				val = rand()%(n);
			TilesUp[val] = true;
			Raise_Value[val] = 0.5;
		}
	}
	FOR(i,0,Num_Tiles/2)
	{
		val = rand()%(n);
		while(val==Collectible_Position||TilesUp[val]||val==0)
			val = rand()%(n);
		InvisibleTiles[val] = true;

	}
	if(Current_Stage>=1)
	{
		FOR(i,0,3)
		{
			val = rand()%(n);
			while(val==Collectible_Position||TilesUp[val]||InvisibleTiles[val]||val==0)
				val = rand()%(100);
			TeleportTiles[val] = true;
		}
		FOR(i,0,3)
		{
			val = rand()%(n);
			while(val==Collectible_Position||TilesUp[val]||InvisibleTiles[val]||val==0||TeleportTiles[val])
				val = rand()%(100);
			Trampoline_Tiles[val] = true;
		}
	}
}
void Ground :: Tile_Coordinates(float x1,float y1,float z1,int i,int j)
{
	Store_Coords.x1 = x1 + j*Tile_Const - Tile_Const/2;
	Store_Coords.x2 = x1 + j*Tile_Const + Tile_Const/2;
	Store_Coords.z1 = z1 - i*Tile_Const - Tile_Const/2;
	Store_Coords.z2 = z1 - i*Tile_Const - Tile_Const/2;
	Store_Coords.x3 = x1 + j*Tile_Const - Tile_Const/2;
	Store_Coords.x4 = x1 + j*Tile_Const + Tile_Const/2;
	Store_Coords.z3 = z1 - i*Tile_Const + Tile_Const/2;
	Store_Coords.z4 = z1 - i*Tile_Const + Tile_Const/2;
}
void Ground :: Fallen()
{
	FOR(i,0,100)
	{
		if(Rocks[i])
		{
			if(abs(Value_Rocks[i]-Field[i].h)>=0.25)
			{
				Value_Rocks[i]-=DecrementRocks[i];
			}
		}
	}
}
void Ground :: Initiate()
{
	FOR(i,0,1000)
	{
		IncrementValues[i] = ((rand()%100)*1.0)/1000;
	}
}
void Ground :: Collectibles()
{
	int val;
	val = rand()%(100);
	while(TilesUp[val]||InvisibleTiles[val])
		val = rand()%(100);
	Collectible_Position = val;
}
class Person
{
	public:
		float Cor_x,Cor_y ,Cor_z,Jump_Inc;
		typedef struct Tile
		{
			float x1,x2,x3,x4,z1,z2,z3,z4,h;
		}Tile;
		bool Jump_Limit_Reached;
		bool Kam;
		float yi;
		int Total;
		void FirstPerson();
		void ThirdPerson();
		bool Third,First;
		void SetCoordinates(float x,float y,float z,float Jump,float _an,float val);
		Tile Current_Tile;
		bool Enemy;
		float ECor_z,ECor_x;
		int iterate;
		void Exit_Status(void);
		float _angle;
		bool Trampoline_mode;
		int Score;
		int num_collide;
		void Reset();
		float Jump_Lim,Jump_LimMax;
		int Lives;
		void Enemies(void);
		bool jump_mode;
		void Current_Location(void);
		void Jump_Fun(float);
		GLMmodel* Still;
		bool UnderSpot;
		GLMmodel* Left;GLMmodel *Right;GLMmodel *Battery;
		void DefineGroups(GLMmodel* &);
		void LoadImages();
		void Kamehameha(int);
		GLvoid DrawGroup(GLMmodel* model, GLuint mode);
		void SpotLight(void);
		void Teleport(void);
};
Person Goku;
void Ground :: CreateTiles(int num_rows,int num_cols,float x1,float y1,float z1)
{
	int num = 0; 
	FOR(i,0,num_rows)
	{
		FOR(j,0,num_cols)
		{
			Tile_Coordinates(x1,y1,z1,i,j);
			Store_Coords.h = y1 + 0.5 + Raise_Value[num];
			Field.push_back(Store_Coords);
			if(InvisibleTiles[num])
			{
				Falling.push_back(Store_Coords);
				glTranslatef(Tile_Const,0.0,0.0);
				num+=1;
				continue;
			}
			if(TilesUp[num])
			{
				RaisedUp.push_back(Store_Coords);
			}
			glTranslatef(0.0,Raise_Value[num],0.0);
			glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].side);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.5, 0.0 );
			glTexCoord2f(0,0);
			glVertex3f(  Tile_Const/2, 0.25,Tile_Const/2);
			glTexCoord2f(1,0);
			glVertex3f(  Tile_Const/2,  0.5 , Tile_Const/2);
			glTexCoord2f(1,1);
			glVertex3f( -Tile_Const/2,  0.5 , Tile_Const/2);
			glTexCoord2f(0,1);
			glVertex3f( -Tile_Const/2, 0.25, Tile_Const/2);
			glEnd();
			glBegin(GL_POLYGON);
			glColor3f( 0.0,  1.0,  1.0 );
			glVertex3f(Tile_Const/2, 0.25,-Tile_Const/2 );
			glVertex3f(Tile_Const/2,  0.5 , -Tile_Const/2);
			glVertex3f(Tile_Const/2,  0.5,  Tile_Const/2);
			glVertex3f(Tile_Const/2, 0.25,  Tile_Const/2 );
			glEnd();
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  1.0,  0.0 );
			glVertex3f( -Tile_Const/2, 0.25, Tile_Const/2);
			glVertex3f(-Tile_Const/2,  0.5,  Tile_Const/2);
			glVertex3f( -Tile_Const/2,  0.5, -Tile_Const/2);
			glVertex3f( -Tile_Const/2, 0.25, -Tile_Const/2);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			if(Current_Stage>=1&&Trampoline_Tiles[num])
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].TrampolineTextureId);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			if(Current_Stage>=1&&TeleportTiles[num])
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Teleportation);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			if(!Trampoline_Tiles[num]&&!TeleportTiles[num])
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].grassTextureId);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  1.0,  1.0 );
			glTexCoord2f(0,0);
			glVertex3f(  Tile_Const/2,  0.5,  Tile_Const/2); 
			glTexCoord2f(1,0);
			glVertex3f(  Tile_Const/2,  0.5, -Tile_Const/2);
			glTexCoord2f(1,1);
			glVertex3f( -Tile_Const/2,  0.5, -Tile_Const/2);
			glTexCoord2f(0,1);
			glVertex3f( -Tile_Const/2,  0.5,  Tile_Const/2);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  1.0,  1.0 );
			glVertex3f(  Tile_Const/2, 0.25, -Tile_Const/2 );
			glVertex3f(  Tile_Const/2, 0.25,  Tile_Const/2);
			glVertex3f( -Tile_Const/2, 0.25,  Tile_Const/2);
			glVertex3f( -Tile_Const/2, 0.25, -Tile_Const/2);
			glEnd();
		/*	if(Rocks[num])
			{
				glTranslatef(0.0f,Value_Rocks[num],0.0f);
				glColor3f(1.0,1.0,1.0);
				glutSolidCube(0.25);
				glTranslatef(0.0,-Value_Rocks[num],0.0f);
			}*/
			
			if(Collectible_Position==num)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Coin);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTranslatef(0.0f,1.0 + Raise_Value[num],0.0);
				glColor3f(0.0,1.0,1.0);
				glRotatef(Lvl1[Current_Stage].CollectAngle*1.0,0,1,0);
				glBegin(GL_TRIANGLE_FAN);
				for(int i=0 ; i<360 ; i++) {
					glVertex2f(0.4*cos(i*PI/180), 0.4 * sin(i*PI/180));
				}
   				glEnd();
				glDisable(GL_TEXTURE_2D);
				glRotatef(-Lvl1[Current_Stage].CollectAngle*1.0,0,1,0);
				glTranslatef(0.0f,-(1.0 + Raise_Value[num]),0.0);
				Lvl1[Current_Stage].CollectAngle+=5;
				Lvl1[Current_Stage].CollectAngle%=360;

			}
			if(Powerup_Pos==num)
			{
				glTranslatef(0.0f,1.0 + Raise_Value[num],0.0);
				Goku.DrawGroup(Goku.Battery,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
				glTranslatef(0.0f,-(1.0 + Raise_Value[num]),0.0);
				glEnable(GL_COLOR_MATERIAL);
			}
			glTranslatef(0.0,-Raise_Value[num],0.0);
			glTranslatef(Tile_Const,0.0,0.0);
			num += 1;
		}
		glTranslatef(-Tile_Const*(num_cols), 0.0,-Tile_Const);
	}/*
	if(Goku.Collectibles>=2)
	{
		FOR(i,0,)
		{
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  0.0,  0.0 );
			glVertex3f(Tile_Const,  0.0,Tile_Const/2);
			glVertex3f(Tile_Const,  0.0, -Tile_Const/2 );
			glVertex3f(-Tile_Const,  0.0, -Tile_Const/2);
			glVertex3f(-Tile_Const,  0.0,Tile_Const/2 );
			glEnd();	
		}
		glTranslatef(0.0,0.0,-Tile_Const);
	}*/
}
bool Ground :: OutOfTheField()
{
	//cout<<Goku.Cor_z<<" "<<Goku.Cor_x<<endl;
	if(Goku.Cor_z + 6.0>-0.25)
	{
	//	cout<<"In"<<endl;
		return true;
	}
	if(Goku.Cor_x<=-5.7)
	{
		return true;
	}
	if(Goku.Cor_z<-19.2)
		return true;
	if(Goku.Cor_x>=6.98)
		return true;
	return false;
}
int Ground :: PowerUps()
{
	int val = rand()%(100);
	while(val==0||val==TilesUp[val]||val==InvisibleTiles[val]||val==Collectible_Position)
		val = rand()%(100);
	Powerup_Pos = val;
}
void Person :: Exit_Status(void)
{
	cout<<"Your Score was "<<Score + Total<<endl;
	exit(1);
}
void Ground :: JUMP()
{
	if(Goku.Cor_y<=LIM&&!(LIM_reached))
	{
		Goku.Cor_y+=0.2;
	}
	if(Goku.Cor_y>=LIM)
	{
		LIM_reached = true;
	}
	if(LIM_reached)
	{
		Goku.Cor_y-=0.2;
	}
	if(Goku.Cor_y<=Goku.yi)
	{
		Goku.Cor_y = yi;
		LIM_reached = false;
	}
}
void Ground :: Trampoline()
{
	if(Goku.Cor_y==yi)
	{
		LIM+=0.3;
	}
	if(LIM>=MAX_LIM)
		Goku.num_collide+=1;
	JUMP();
}
void Ground :: Teleport(void)
{
	int val = rand()%(100);
	while(InvisibleTiles[val]||TilesUp[val])
		val = rand()%100;
	Goku.Cor_x = Field[val].x1 + Tile_Const/2;
	Goku.Cor_z = Field[val].z1 + Tile_Const/2;
	Goku.Cor_y = Goku.yi;
}
void Person :: SpotLight(void)
{
	glEnable(GL_LIGHTING);
	GLfloat dirVector0[]={ 0.0, -1.0, 0.0, 1.0};
	GLfloat lightPos0[]={ Cor_x, Cor_y+3.0, Cor_z, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirVector0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.5);
}
void Person :: SetCoordinates(float x,float y,float z,float Jump,float _an,float val)
{
	Lvl1[Current_Stage].Sun_x = Lvl1[Current_Stage].Sun_y = Lvl1[Current_Stage].Sun_z = 0.7;
	Lvl1[Current_Stage].Amb_x = Lvl1[Current_Stage].Amb_y = Lvl1[Current_Stage].Amb_z = 0.9;
	Cor_x = x;
	Lvl1[Current_Stage].Helicopter_x = x;
	Lvl1[Current_Stage].Helicopter_y = y+3.0;
	Lvl1[Current_Stage].Helicopter_z = z;
	Lvl1[Current_Stage].HeliAngle = 90.0;
	Cor_y = y;
	Jump_Lim = 1.5;
	Jump_LimMax = 1.0;
	Cor_z = z;
	Jump_Inc = Jump;
	_angle = _an;
	num_collide = val;
	Trampoline_mode = false;
	yi = y;
	jump_mode = false;
	Jump_Limit_Reached = false;
	UnderSpot = false;
	if(Current_Stage<=1)
	Enemy = true;
	Lives = Lives==0?3:Lives;
	ECor_z = x + 0.5;
	ECor_z = z - 3.0;
	Lvl1[Current_Stage].LIM = yi;
	Lvl1[Current_Stage].MAX_LIM = 2.0;
}
void Person :: Reset()
{
	SetCoordinates(-5.0,-1.0,-7.0,0.0,90.0,0);
}
/*
void Ground :: TileView()
{
	
}*/
void Person :: Jump_Fun(float val)
{
	if(Jump_Limit_Reached)
	{
		if(Lvl1[Current_Stage].Intersection())
		{
			if(fabs(Lvl1[Current_Stage].Field[Lvl1[Current_Stage].Collide].h-Cor_y)<=0.25)
			{
				Cor_y = Lvl1[Current_Stage].Field[Lvl1[Current_Stage].Collide].h;
				jump_mode = false;
				Jump_Limit_Reached = false;
				return ;
			}
			else
			{
				Cor_y-=0.5;
				Cor_x+=(0.3)*sin(_angle*PI/180);
				Cor_z+=(0.3)*cos(_angle*PI/180);
			}
			//Cor_x+=(0.1)*sin(_angle*PI/180);
			//Cor_z+=(0.1)*cos(_angle*PI/180);
		}
		else
		{
			Cor_y-=0.5;
			Cor_x+=(0.3)*sin(_angle*PI/180);
			Cor_z+=(0.3)*cos(_angle*PI/180);
		}
	}
	if(Cor_y<yi)
	{
		Cor_y = -1.5;
		Jump_Limit_Reached = false;
		jump_mode = false;
	}
	if(!Jump_Limit_Reached)
	{
		if(Lvl1[Current_Stage].Intersection())
		{
			if(fabs(Lvl1[Current_Stage].Field[Lvl1[Current_Stage].Collide].h-Cor_y)<=0.25)
			{
				Cor_y = Lvl1[Current_Stage].Field[Lvl1[Current_Stage].Collide].h;
				jump_mode = false;
				Jump_Limit_Reached = false;
				return ;
			}
			else
			{
				Cor_y+=0.5;
				Cor_x+=(0.3)*sin(_angle*PI/180);
				Cor_z+=(0.3)*cos(_angle*PI/180);

			}
		//	Cor_x+=(0.1)*sin(_angle*PI/180);
		//	Cor_z+=(0.1)*cos(_angle*PI/180);
		}
		else
		{
			Cor_y+=0.5;
			Cor_x+=(0.3)*sin(_angle*PI/180);
			Cor_z+=(0.3)*cos(_angle*PI/180);
		}

	}
	if(abs(Cor_y - yi)>=val)
	{
		Jump_Limit_Reached = true;
	}
	iterate+=1;
}
void Person :: Current_Location()
{
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  0.0,  0.0 );
	glVertex3f(0.20,  0.0,0.20);
	glVertex3f(0.20,  0.0, -0.20 );
	glVertex3f(-0.20,  0.0, -0.20 );
	glVertex3f(-0.20,  0.0,0.20 );
	glEnd();
	if(0.5 -num_collide*0.02 <=-0.5)
	{
		Lives-=1;
		if(Lives<=0)
			Exit_Status();
		num_collide = 0;
	}
	glPushMatrix();
	glTranslatef(-0.5,1.4,0.0);
	glRotatef(90.0,0.0,1.0,0.0);
	GLUquadricObj *Keoken = gluNewQuadric();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,0.0,0.0);
	gluCylinder(Keoken,0.1,0.1,1 - (float)num_collide*0.02,32,32);
	glPopMatrix();
	/*glBegin(GL_POLYGON);	
	glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(0.50 - (num_collide*0.02),  1.5,0.0);
	glVertex3f(0.50 - (num_collide*0.02),  1.4, 0.0 );
	glVertex3f(-0.50,  1.4, 0.0 );
	glVertex3f(-0.50,  1.5,0.0 );
	glEnd();*/
        Current_Tile.x1 = Cor_x - 0.20;
	Current_Tile.x2 = Cor_x + 0.20;
	Current_Tile.z1 = Cor_z - 0.20;
	Current_Tile.z2 = Cor_z - 0.20;
        Current_Tile.x3 = Cor_x + 0.20;
	Current_Tile.x4 = Cor_x - 0.20;
	Current_Tile.z3 = Cor_z + 0.20;
	Current_Tile.z4 = Cor_z + 0.20;
	Current_Tile.h =  Cor_y + Jump_Inc;

}
void Person :: Teleport()
{
	int val = rand()%(100);
	while(Lvl1[Current_Stage].TilesUp[val]||Lvl1[Current_Stage].InvisibleTiles[val])
		val = rand()%(100);
	Goku.Cor_x = Lvl1[Current_Stage].Field[val].x1 + Lvl1[Current_Stage].Tile_Const/2;
	Goku.Cor_y = Goku.yi;
	Goku.Cor_z = Lvl1[Current_Stage].Field[val].z1 + Lvl1[Current_Stage].Tile_Const/2;
}
bool Ground :: Intersection()
{
	Collide = -1;
	FOR(i,0,RaisedUp.size())
	{
		if(Goku.Current_Tile.x1>=RaisedUp[i].x1&&RaisedUp[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z1>=RaisedUp[i].z1&&Goku.Current_Tile.z1<=RaisedUp[i].z3)
		{
			Collide = i;
			return true;
		}
		if(Goku.Current_Tile.x2>=RaisedUp[i].x1&&RaisedUp[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z2>=RaisedUp[i].z1&&Goku.Current_Tile.z1<=RaisedUp[i].z3)
		{
			Collide = i;
			return true;
		}
		if(Goku.Current_Tile.x3>=RaisedUp[i].x1&&RaisedUp[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z3>=RaisedUp[i].z1&&Goku.Current_Tile.z1<=RaisedUp[i].z3)
		{
			Collide = i;
			return true;
		}
		if(Goku.Current_Tile.x4>=RaisedUp[i].x1&&RaisedUp[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z4>=RaisedUp[i].z1&&Goku.Current_Tile.z1<=RaisedUp[i].z3)
		{
			Collide = i;
			return true;
		}
	}
}
void Ground :: Crumbling()
{
	FOR(i,0,Field.size())
	{
		if(Goku.Current_Tile.x1>=Field[i].x1&&Field[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z1>=Field[i].z1&&Goku.Current_Tile.z1<=Field[i].z3)
		{
			Cur_Tile = i;
		}
		if(Goku.Current_Tile.x2>=Field[i].x1&&Field[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z2>=Field[i].z1&&Goku.Current_Tile.z1<=Field[i].z3)
		{
			Cur_Tile = i;
		}
		if(Goku.Current_Tile.x3>=Field[i].x1&&Field[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z3>=Field[i].z1&&Goku.Current_Tile.z1<=Field[i].z3)
		{
			Cur_Tile = i;
		}
		if(Goku.Current_Tile.x4>=Field[i].x1&&Field[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z4>=Field[i].z1&&Goku.Current_Tile.z1<=Field[i].z3)
		{
			Cur_Tile = i;
		}

	}
}
bool Ground :: FallenUnderTheSea()
{
	FOR(i,0,Falling.size())
	{
		if(Goku.Current_Tile.x1>=Falling[i].x1&&Falling[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z1>=Falling[i].z1&&Goku.Current_Tile.z1<=Falling[i].z3)
		{
			return true;
		}
		if(Goku.Current_Tile.x2>=Falling[i].x1&&Falling[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z2>=Falling[i].z1&&Goku.Current_Tile.z1<=Falling[i].z3)
		{
			return true;
		}
		if(Goku.Current_Tile.x3>=Falling[i].x1&&Falling[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z3>=Falling[i].z1&&Goku.Current_Tile.z1<=Falling[i].z3)
		{
			return true;
		}
		if(Goku.Current_Tile.x4>=Falling[i].x1&&Falling[i].x2>=Goku.Current_Tile.x1&&Goku.Current_Tile.z4>=Falling[i].z1&&Goku.Current_Tile.z1<=Falling[i].z3)
		{
			return true;
		}
	}
}
void Trampoline()
{
	Goku.Jump_Fun(0.5);	
}
void Ground :: RandomIteratebility()
{
	FOR(i,0,100)
	{
		if(TilesUp[i])
		{
			if(Raise_Value[i]<=-0.3)
			{
				DOWN[i] = false;
			}
			if(Raise_Value[i]>=0.7||DOWN[i])
			{
				UP[i] = false;
				Raise_Value[i]-=IncrementValues[i];
				DOWN[i] = true;
			}
			else if(Raise_Value[i]<=-0.3||UP[i]||Raise_Value[i]<=0.7)
			{
				DOWN[i] = false;
				Raise_Value[i]+=IncrementValues[i];
				UP[i] = true;
			}
		}

	}
}
void Person :: Enemies(void)
{
	if(Cor_z!=ECor_z)
	{
		if(Cor_z>ECor_z)
		{
			ECor_z+=0.02;
		}
		else
		{
			ECor_z-=0.02;
		}
	}
	if(Cor_x!=ECor_x)
	{
		if(Cor_x>ECor_x)
		{
			ECor_x+=0.02;
		}
		else
		{
			ECor_x-=0.02;
		}
	}
}/*
void Person :: SuperRun()
{
	Cor
}*/
GLvoid Person :: DrawGroup(GLMmodel* model, GLuint mode)
{
	static GLuint i;
	static GLMgroup* group;
	static GLMtriangle* triangle;
	static GLMmaterial* material;

	assert(model);
	assert(model->vertices);
	if (mode & GLM_FLAT && !model->facetnorms) {
		printf("glmDraw() warning: flat render mode requested "
				"with no facet normals defined.\n");
		mode &= ~GLM_FLAT;
	} 
	if (mode & GLM_SMOOTH && !model->normals) {
		printf("glmDraw() warning: smooth render mode requested "
				"with no normals defined.\n");
		mode &= ~GLM_SMOOTH;
	}
	if (mode & GLM_TEXTURE && !model->texcoords) {
		printf("glmDraw() warning: texture render mode requested "
				"with no texture coordinates defined.\n");
		mode &= ~GLM_TEXTURE;
	}
	if (mode & GLM_FLAT && mode & GLM_SMOOTH) {
		printf("glmDraw() warning: flat render mode requested "
				"and smooth render mode requested (using smooth).\n");
		mode &= ~GLM_FLAT;
	}
	if (mode & GLM_COLOR && !model->materials) {
		printf("glmDraw() warning: color render mode requested "
				"with no materials defined.\n");
		mode &= ~GLM_COLOR;
	}
	if (mode & GLM_MATERIAL && !model->materials) {
		printf("glmDraw() warning: material render mode requested "
				"with no materials defined.\n");
		mode &= ~GLM_MATERIAL;
	}
	if (mode & GLM_COLOR && mode & GLM_MATERIAL) {
		printf("glmDraw() warning: color and material render mode requested "
				"using only material mode.\n");
		mode &= ~GLM_COLOR;
	}
	if (mode & GLM_COLOR)
		glEnable(GL_COLOR_MATERIAL);
	else if (mode & GLM_MATERIAL)
		glDisable(GL_COLOR_MATERIAL);
	group=model->groups;
	while(group){
		if (mode & GLM_MATERIAL) {
			material = &model->materials[group->material];
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);
		}

		if (mode & GLM_COLOR) {
			glColor3fv(material->diffuse);
		}

		glBegin(GL_TRIANGLES);
		for (i = 0; i < group->numtriangles; i++) 
		{
			triangle = &T(group->triangles[i]);

			if (mode & GLM_FLAT)
				glNormal3fv(&model->facetnorms[3 * triangle->findex]);

			if (mode & GLM_SMOOTH)
				glNormal3fv(&model->normals[3 * triangle->nindices[0]]);
			if (mode & GLM_TEXTURE)
				glTexCoord2fv(&model->texcoords[2 * triangle->tindices[0]]);
			glVertex3fv(&model->vertices[3 * triangle->vindices[0]]);

			if (mode & GLM_SMOOTH)
				glNormal3fv(&model->normals[3 * triangle->nindices[1]]);
			if (mode & GLM_TEXTURE)
				glTexCoord2fv(&model->texcoords[2 * triangle->tindices[1]]);
			glVertex3fv(&model->vertices[3 * triangle->vindices[1]]);

			if (mode & GLM_SMOOTH)
				glNormal3fv(&model->normals[3 * triangle->nindices[2]]);
			if (mode & GLM_TEXTURE)
				glTexCoord2fv(&model->texcoords[2 * triangle->tindices[2]]);
			glVertex3fv(&model->vertices[3 * triangle->vindices[2]]);

		}
		glEnd();
		group = group->next;
	}
}
void handleKeypress(int key,int x,int y)
{
    if(key==GLUT_KEY_LEFT)
    {
	Goku._angle+=-8.0;
    }
    if(key==GLUT_KEY_RIGHT)
    {
	Goku._angle+=8.0;
    }
    if(key==GLUT_KEY_DOWN)
    {
	Goku.iterate+=1;
	Goku.Cor_x-=0.25*sin(Goku._angle*PI/180);
	Goku.Cor_z-=0.25*cos(Goku._angle*PI/180);
        Goku.Current_Tile.x1=Goku.Cor_x-0.20;
	Goku.Current_Tile.x2=Goku.Cor_x+0.20;
	Goku.Current_Tile.z1=Goku.Cor_z-0.20;
	Goku.Current_Tile.z2=Goku.Cor_z-0.20;
        Goku.Current_Tile.x3=Goku.Cor_x+0.20;
	Goku.Current_Tile.x4=Goku.Cor_x-0.20;
	Goku.Current_Tile.z3=Goku.Cor_z+0.20;
	Goku.Current_Tile.z4=Goku.Cor_z+0.20;
	Goku.Current_Tile.h=Goku.Cor_y+Goku.Jump_Inc;
	if(Lvl1[Current_Stage].FallenUnderTheSea())
	{ 
		//cout<<"IN"<<endl;
	}
	else 
	if(Lvl1[Current_Stage].Intersection())
	{
		//cout<<"IN"<<endl;
		if(Lvl1[Current_Stage].RaisedUp[Lvl1[Current_Stage].Collide].h-Goku.Cor_y>=0.04)
		{
			Goku.num_collide+=1;
			Goku.Cor_x+=0.25*sin(Goku._angle*PI/180);
			Goku.Cor_z+=0.25*cos(Goku._angle*PI/180);
			Goku.Current_Tile.x1=Goku.Cor_x-0.20;
			Goku.Current_Tile.x2=Goku.Cor_x+0.20;
			Goku.Current_Tile.z1=Goku.Cor_z-0.20;
			Goku.Current_Tile.z2=Goku.Cor_z-0.20;
			Goku.Current_Tile.x3=Goku.Cor_x+0.20;
			Goku.Current_Tile.x4=Goku.Cor_x-0.20;
			Goku.Current_Tile.z3=Goku.Cor_z+0.20;
			Goku.Current_Tile.z4=Goku.Cor_z+0.20;
			Goku.Current_Tile.h=Goku.Cor_y+Goku.Jump_Inc;
		}
		else
		{
			Goku.Cor_y = Lvl1[Current_Stage].RaisedUp[Lvl1[Current_Stage].Collide].h;
		}
	}
	else
	{
		Goku.Cor_y = -1.0;
		Goku.Current_Tile.h=Goku.Cor_y+Goku.Jump_Inc;
	}
    }
    if(key==GLUT_KEY_UP)
    {
	    Goku.iterate+=1;
	Goku.Cor_x+=0.25*sin(Goku._angle*PI/180);
	Goku.Cor_z+=0.25*cos(Goku._angle*PI/180);
        Goku.Current_Tile.x1=Goku.Cor_x-0.20;
	Goku.Current_Tile.x2=Goku.Cor_x+0.20;
	Goku.Current_Tile.z1=Goku.Cor_z-0.20;
	Goku.Current_Tile.z2=Goku.Cor_z-0.20;
        Goku.Current_Tile.x3=Goku.Cor_x+0.20;
	Goku.Current_Tile.x4=Goku.Cor_x-0.20;
	Goku.Current_Tile.z3=Goku.Cor_z+0.20;
	Goku.Current_Tile.z4=Goku.Cor_z+0.20;
	Goku.Current_Tile.h=Goku.Cor_y+Goku.Jump_Inc;
	if(Lvl1[Current_Stage].FallenUnderTheSea())
	{
		//cout<<"In"<<endl;
	}
	else if(Lvl1[Current_Stage].Intersection())
	{
		//cout<<"IN"<<endl;
		if(Lvl1[Current_Stage].RaisedUp[Lvl1[Current_Stage].Collide].h-Goku.Cor_y>=0.04)
		{
			Goku.num_collide+=1;
			Goku.Cor_x-=0.25*sin(Goku._angle*PI/180);
			Goku.Cor_z-=0.25*cos(Goku._angle*PI/180);
			Goku.Current_Tile.x1=Goku.Cor_x-0.20;
			Goku.Current_Tile.x2=Goku.Cor_x+0.20;
			Goku.Current_Tile.z1=Goku.Cor_z-0.20;
			Goku.Current_Tile.z2=Goku.Cor_z-0.20;
			Goku.Current_Tile.x3=Goku.Cor_x+0.20;
			Goku.Current_Tile.x4=Goku.Cor_x-0.20;
			Goku.Current_Tile.z3=Goku.Cor_z+0.20;
			Goku.Current_Tile.z4=Goku.Cor_z+0.20;
			Goku.Current_Tile.h=Goku.Cor_y+Goku.Jump_Inc;
		}
		else
		{
			Goku.Cor_y = Lvl1[Current_Stage].RaisedUp[Lvl1[Current_Stage].Collide].h;
		}
	}
	else
	{
		Goku.Cor_y = -1.0;
		Goku.Current_Tile.h=Goku.Cor_y+Goku.Jump_Inc;
	}
    }
}
void Person :: DefineGroups(GLMmodel * &pmodel)
{
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);        
	glmVertexNormals(pmodel, 90.0);
	glmLinearTexture(pmodel);
	glmSpheremapTexture(pmodel);
}
void Person :: LoadImages()
{
	char temp[20];
	strcpy(temp,"rashika.obj");
	Still = glmReadOBJ(temp);
	if (!Still) exit(0);
	DefineGroups(Still);
	strcpy(temp,"Rashikapos1.obj");	
	Left = glmReadOBJ(temp);
	if(!Left) exit(0);
	DefineGroups(Left);
	strcpy(temp,"Rashikapos2.obj");
	Right = glmReadOBJ(temp);
	if(!Right)
		exit(0);
	DefineGroups(Right);
	strcpy(temp,"battery.obj");
	Battery= glmReadOBJ(temp);
	DefineGroups(Battery);
	if(!Battery)
		exit(0);
}/*
void Person :: ShakeEarth()
{
	Jump_Fun();
	FOR(i,0,1000)
	{
	}
}*/
void drawScene(void);
void Sound(void)
{
	pid_t  o = fork();
	if(o==0)
	{
		execlp("cvlc","cvlc","kamehameha.swf.mp3",0);
		_exit(0);
		flag = 1;
	}
	else
		usleep(3400000);
}
void Person :: Kamehameha(int val)
{
//	Sound();
	glPushMatrix();
	GLUquadricObj *Keoken = gluNewQuadric();
	int cn = 0;
	float len = 0.0;/*
	FOR(i,0,1000)
	{
		if(i%1000==0)
		{
			glColor3f(1.0,1.0,1.0);
			gluCylinder(Keoken,0.1,0.3,len,32,32);
			len+=0.01;
		}
	///	drawScene();
	}*
	FOR(i,2,1000)
	{
		glColor3f(1.0,0.0,0.0);
		gluCylinder(Keoken,0.5,0.5,i,32,32);
		usleep(4000);
	}*/
//	sleep(2);
//	sleep(1);
//	glRotatef(Goku._angle,0,1,0);
//
	//glTranslatef(-1*sin(Goku._angle),0.0,0.0);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,0.0);
	gluCylinder(Keoken,0.4,0.4,val,32,32);
	//usleep(10000);
	if((Cor_x<=ECor_x&&Cor_x+len*(cos(_angle)>=ECor_x)))
	{
		if(fabs(Cor_z-ECor_z)<=0.3&&Cor_z + len*(sin(_angle))<=ECor_z)
		{
			Goku.Enemy = true;
		}
	}
	glPopMatrix();
}
void Ground :: TileView()
{
	gluLookAt(Field[Here].x1 + Tile_Const/2,Field[Here].h+0.3,Field[Here].z1,Goku.Cor_x,Goku.Cor_y+0.5,Goku.Cor_z,0,1,0);
}
void Person :: FirstPerson()
{
	glPushMatrix();
	glRotatef(Goku._angle,0.0,1.0,0.0);
	gluLookAt(Goku.Cor_x ,Goku.Cor_y + 1.0,Goku.Cor_z,Goku.Cor_x + 1.5*sin(Goku._angle),Goku.Cor_y+1.0,Goku.Cor_z+1.5*(Goku._angle),0,1,0);
	glPopMatrix();
}

void Person :: ThirdPerson()
{

	gluLookAt(Goku.Cor_x - 0.5*sin(Goku._angle),Goku.Cor_y + 1.0,Goku.Cor_z - 0.5*cos(Goku._angle),Goku.Cor_x + 1.5*sin(Goku._angle),Goku.Cor_y-0.2,Goku.Cor_z+1.5*cos(Goku._angle),0,1,0);
}
/*
void Person :: BigBangKameha(void)
{
	FOR(i,0,10)
	{
		final+=(0.5)*sin(Goku._angle*PI/180);
		final+=(0.5)*cos(Goku._angle*PI/180);
		ofCircle(x+10, y+10, 10);
		ofCircle(x+90, y+10, 10);
		ofCircle(x+90, y+90, 10);
		ofCircle(x+10, y+90, 10);
		ofRect(x+10, y, 80, 100);
		ofRect(x, y+10, 100, 80);
	}
}
*/
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
	/*	case 'p':
			_lowSpecularity = !_lowSpecularity;
			break;
		case 'e':
			_emission = !_emission;
			break;*/
		
		case 'j':
			Goku.jump_mode = true;
			break;
		case 't':
			if(Lvl1[Current_Stage].Num_PowerUps>=1)
			{
				Goku.Teleport();
				Lvl1[Current_Stage].Num_PowerUps-=1;
				break;
			}
		case 'o':
			Goku.Trampoline_mode = true;
			break;
		case 'l':
			if(!Goku.UnderSpot)
				Goku.UnderSpot = true;
			else
				Goku.UnderSpot = false;
			break;
		case 'k':
			if(Lvl1[Current_Stage].Num_PowerUps>=3)
			{
				Sound();
			//	while(!flag);
				Goku.Kam = true;
				len = 0;
				Lvl1[Current_Stage].Num_PowerUps = 0;
			}
			else
				Goku.Kam = false;
			break;
		case 'b':
			if(!Lvl1[Current_Stage].Tile_View)
				Lvl1[Current_Stage].Tile_View = true;
			else
				Lvl1[Current_Stage].Tile_View = false;
			break;
		case 'w':
			Lvl1[Current_Stage].Here=(Lvl1[Current_Stage].Here+10)%100;
			break;
		case 'a':
			Lvl1[Current_Stage].Here=max(0,Lvl1[Current_Stage].Here-1);
			break;
		case 's':
			Lvl1[Current_Stage].Here=max(0,Lvl1[Current_Stage].Here-10);
			break;
		case 'd':
			Lvl1[Current_Stage].Here=(Lvl1[Current_Stage].Here+1)%100;
			break;
		case 'f':
			if(!Goku.First)
				Goku.First = true;
			else
				Goku.First = false;
			break;
		case 'p':
			if(!Goku.Third)
				Goku.Third = true;
			else
				Goku.Third = false;
			break;
		case 'h':
			Lvl1[Current_Stage].Helicopter^=1;
			break;
		case 'c':
			Lvl1[Current_Stage].Tower^=1;
			break;
		case '1':
			Lvl1[Current_Stage].Helicopter_x+=0.5*sin(Lvl1[Current_Stage].HeliAngle);
			Lvl1[Current_Stage].Helicopter_z+=0.5*cos(Lvl1[Current_Stage].HeliAngle);
			break;
		case '2':
			Lvl1[Current_Stage].HeliAngle-=0.8;
			break;
		case '3':
			Lvl1[Current_Stage].HeliAngle+=0.8;
			break;
		case '4':
			Lvl1[Current_Stage].Helicopter_x-=0.5*sin(Lvl1[Current_Stage].HeliAngle);
			Lvl1[Current_Stage].Helicopter_z-=0.5*cos(Lvl1[Current_Stage].HeliAngle);
			break;

		
		/*case 'c':
			ca=1;
			if(!cameramode)
				cameramode=1;
			else
				cameramode=0;
			break;
		case 'h':
			ca=2;
			if(!cameramode)
				cameramode=1;
			else
				cameramode=0;
			break;
		case 'w':
			tower_x+=(0.5)*sin(tower_angle);
			tower_z+=(0.5)*cos(tower_angle);
			break;
		case 'a':
			tower_angle-=0.01;
			break;
		case 'd':
			tower_angle+=0.01;
			break;
		case 's':
			tower_x-=(0.5)*sin(tower_angle);
			tower_z-=(0.5)*cos(tower_angle);
			break;
		case 't':
			ca=3;
			if(!cameramode)
				cameramode=1;
			else
				cameramode=0;
			break;
		case 'y':
			Tile_no=(Tile_no+1)%(Number_Tiles);
			break;
		case 'u':
			Tile_no=max(Tile_no-1,0);
			break;
		case 'v':
			ca=4;
			if(!cameramode)
				cameramode=1;
			else
				cameramode=0;
			break;
		*/


	}
}
void initRendering() 
{
	Current_Stage = 0;
	//Lvl1[Current_Stage].Collectibles();
	Lvl1[Current_Stage].TilesChangeUp(100,10);
	Lvl1[Current_Stage].Initiate();
	//Lvl1[Current_Stage].PowerUps();
	//glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
//	Lvl1[Current_Stage].RandomFallingRocks();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	Lvl1[Current_Stage].Tile_Const = 1.25;
	Lvl1[Current_Stage].Powerup_Pos = 400;
	Goku.SetCoordinates(-5.0,-1.0,-7.0,0.0,90.0,0);
	Goku.LoadImages();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	Image *Water = loadBMP("water2.bmp");
	Aesthetics[Current_Stage].WaterTextureId = Aesthetics[Current_Stage].loadTexture(Water);
	delete Water;
	Image *u = loadBMP("caveup.bmp");
	Aesthetics[0].Up = Aesthetics[0].loadTexture(u);
	Aesthetics[2].Up = Aesthetics[0].loadTexture(u);
	delete u;
	Image *u1 = loadBMP("caveright.bmp");
	Aesthetics[0].Right = Aesthetics[0].loadTexture(u1);
	Aesthetics[1].Right = Aesthetics[0].loadTexture(u1);
	Aesthetics[2].Right = Aesthetics[0].loadTexture(u1);
	delete u1;
	Image *u2 = loadBMP("caveleft.bmp");
	Aesthetics[0].Left = Aesthetics[0].loadTexture(u2);
	Aesthetics[1].Left = Aesthetics[0].loadTexture(u2);
	Aesthetics[2].Left = Aesthetics[0].loadTexture(u2);
	delete u2;
	Image *u3 = loadBMP("caveback.bmp");
	Aesthetics[0].Back = Aesthetics[0].loadTexture(u3);
	Aesthetics[1].Back = Aesthetics[0].loadTexture(u3);
	Aesthetics[2].Back = Aesthetics[0].loadTexture(u3);
	delete u3;
	Image *u4 = loadBMP("cavefront.bmp");
	Aesthetics[0].Front = Aesthetics[0].loadTexture(u4);
	Aesthetics[1].Front = Aesthetics[0].loadTexture(u4);
	Aesthetics[2].Front = Aesthetics[0].loadTexture(u4);
	delete u4;
	Image* u5 = loadBMP("cavedown.bmp");
	Aesthetics[0].Bottom = Aesthetics[0].loadTexture(u5);
	Aesthetics[1].Bottom = Aesthetics[0].loadTexture(u5);
	Aesthetics[2].Bottom = Aesthetics[0].loadTexture(u5);
	delete u5;
	Image *w1 = loadBMP("skyup.bmp");
	Aesthetics[1].Up = Aesthetics[1].loadTexture(w1);
	delete w1;
	Image *w2 = loadBMP("skydown.bmp");
	Aesthetics[1].Bottom = Aesthetics[1].loadTexture(w2);
	delete w2;
	Image *w3 = loadBMP("skyback.bmp");
	Aesthetics[1].Back = Aesthetics[1].loadTexture(w3);
	delete w3;
	Image *w4 = loadBMP("skyleft.bmp");
	Aesthetics[1].Left = Aesthetics[1].loadTexture(w4);
	delete w4;
	Image *w5 = loadBMP("skyright.bmp");
	Aesthetics[1].Right = Aesthetics[1].loadTexture(w5);
	delete w5;
	Image *w6 = loadBMP("skyfront.bmp");
	Aesthetics[1].Front = Aesthetics[1].loadTexture(w6);
	delete w6;
	Image* side = loadBMP("side.bmp");	
	Aesthetics[0].side = Aesthetics[0].loadTexture(side);
	delete side;
	Image* s1 = loadBMP("side2.bmp");	
	Aesthetics[1].side = Aesthetics[1].loadTexture(s1);
	delete s1;
	Image* s2 = loadBMP("side3.bmp");	
	Aesthetics[2].side = Aesthetics[2].loadTexture(s1);
	delete s2;
	Image *o1 = loadBMP("blood_sport512_top.bmp");
	Aesthetics[2].Up = Aesthetics[2].loadTexture(o1);
	delete o1;
	Image *o2 = loadBMP("blood_sport512_bottom.bmp");
	Aesthetics[2].Bottom = Aesthetics[2].loadTexture(o2);
	delete o2;
	Image *o3 = loadBMP("blood_sport512_back.bmp");
	Aesthetics[2].Back = Aesthetics[2].loadTexture(o3);
	delete o3;
	Image *o4 = loadBMP("blood_sport512_left.bmp");
	Aesthetics[2].Left = Aesthetics[2].loadTexture(o4);
	delete o4;
	Image *o5 = loadBMP("blood_sport512_right.bmp");
	Aesthetics[2].Right = Aesthetics[2].loadTexture(o5);
	delete o5;
	Image *o6 = loadBMP("blood_sport512_front.bmp");
	Aesthetics[2].Front = Aesthetics[2].loadTexture(o6);
	delete o6;
	/*Image *image = loadBMP("filename_stone.bmp");
	Aesthetics[Current_Stage].stoneTextureId = loadTexture(image);
	delete image;*/
	Image *face = loadBMP("tile.bmp");
	Aesthetics[0].grassTextureId = Aesthetics[0].loadTexture(face);
	delete face;
	Image *face1 = loadBMP("tile2.bmp");
	Aesthetics[1].grassTextureId = Aesthetics[1].loadTexture(face1);
	delete face1;	
	Image *face11 = loadBMP("tile3.bmp");
	Aesthetics[2].grassTextureId = Aesthetics[2].loadTexture(face11);
	delete face11;	
	Image *face2 = loadBMP("trampoline.bmp");
	Aesthetics[1].TrampolineTextureId = Aesthetics[1].loadTexture(face2);
	Aesthetics[2].TrampolineTextureId = Aesthetics[2].loadTexture(face2);
	delete face2;
	Image *face3 = loadBMP("teleport.bmp");
	Aesthetics[1].Teleportation = Aesthetics[1].loadTexture(face3);
	Aesthetics[2].Teleportation = Aesthetics[2].loadTexture(face3);
	delete face3;
	Image *face4 = loadBMP("coin.bmp");
	Aesthetics[0].Coin = Aesthetics[1].loadTexture(face4);
	Aesthetics[1].Coin = Aesthetics[1].loadTexture(face4);
	Aesthetics[2].Coin = Aesthetics[2].loadTexture(face4);
	delete face4;
	//Image* we = loadBMP("tile.bmp");
	//Aesthetics[Current_Stage][0].grassTextureId = Aesthe
	glDisable(GL_COLOR_MATERIAL);
}
void update(int value)
{
	if(!Goku.Kam)
	{
	int Num;
	if(Current_Stage>=1)
	{
		if(Lvl1[Current_Stage].Clock&&Goku.Cor_x == Lvl1[Current_Stage].xi && Goku.Cor_z == Lvl1[Current_Stage].zi)
		{
			Lvl1[Current_Stage].Timer+=1;
			if(Lvl1[Current_Stage].Timer>=200)
			{
				Lvl1[Current_Stage].FindRequiredTile(Goku.Cor_x,Goku.Cor_z);
				Lvl1[Current_Stage].TilesUp[Lvl1[Current_Stage].Cur_Tile] = false;
				Lvl1[Current_Stage].Raise_Value[Lvl1[Current_Stage].Cur_Tile]-=0.02;
				Goku.Cor_y-=0.5;
				Goku.iterate+=1;	
				if(Goku.Cor_y<=-40.0)
				{
					if(Goku.Lives<=0)
						Goku.Exit_Status();
					else
					{
						Lvl1[Current_Stage].Clock = true;
						Lvl1[Current_Stage].Raise_Value[Lvl1[Current_Stage].Cur_Tile]=0;
						Lvl1[Current_Stage].InvisibleTiles[Lvl1[Current_Stage].Cur_Tile] = false;
						Goku.Lives-=1;
						Goku.Reset();
					}
				}
			}
		}
		else if(!Lvl1[Current_Stage].Clock)
		{
			if(Lvl1[Current_Stage].Timer>0)
				Lvl1[Current_Stage].Timer-=1;
			else
			{
				Lvl1[Current_Stage].Clock = true;
				Lvl1[Current_Stage].Raise_Value[Lvl1[Current_Stage].Cur_Tile]=0;
				Lvl1[Current_Stage].InvisibleTiles[Lvl1[Current_Stage].Cur_Tile] = false;
			}
		}
		else 
		{
			Lvl1[Current_Stage].Timer = 0;
			Lvl1[Current_Stage].xi  = Goku.Cor_x;
			Lvl1[Current_Stage].zi  = Goku.Cor_z;
		}
	}
	if(Lvl1[Current_Stage].OutOfTheField())
	{
		Goku.Cor_y -= 0.5;
		if(Goku.Cor_y<=-40.0)
		{
			if(Goku.Lives<=0)
				Goku.Exit_Status();
			else
				Goku.Reset();
				Goku.Lives-=1;
		}
	}
	if(Lvl1[Current_Stage].Sun_x>=1.0||Lvl1[Current_Stage].Night)
	{
		Lvl1[Current_Stage].Sun_x -= 0.002;
		Lvl1[Current_Stage].Sun_y -= 0.002;
		Lvl1[Current_Stage].Sun_z -= 0.002;
		Lvl1[Current_Stage].Night = true;
	}
	if(!Lvl1[Current_Stage].Night)
	{
		Lvl1[Current_Stage].Sun_x += 0.002;
		Lvl1[Current_Stage].Sun_y += 0.002;
		Lvl1[Current_Stage].Sun_z += 0.002;
	}
	if(Lvl1[Current_Stage].Sun_x<=0.1)
	{
		Lvl1[Current_Stage].Sun_x += 0.002;
		Lvl1[Current_Stage].Sun_y += 0.002;
		Lvl1[Current_Stage].Sun_z += 0.002;
		Lvl1[Current_Stage].Night =false;

	}
	if(Lvl1[Current_Stage].Amb_x>=1.0||Lvl1[Current_Stage].Ambience)
	{
		Lvl1[Current_Stage].Amb_x -= 0.002;
		Lvl1[Current_Stage].Amb_y -= 0.002;
		Lvl1[Current_Stage].Amb_z -= 0.002;
		Lvl1[Current_Stage].Ambience = true;
	}
	if(!Lvl1[Current_Stage].Ambience)
	{
		Lvl1[Current_Stage].Amb_x += 0.002;
		Lvl1[Current_Stage].Amb_y += 0.002;
		Lvl1[Current_Stage].Amb_z += 0.002;
	}
	if(Lvl1[Current_Stage].Amb_x<=0.1)
	{
		Lvl1[Current_Stage].Amb_x += 0.002;
		Lvl1[Current_Stage].Amb_y += 0.002;
		Lvl1[Current_Stage].Amb_z += 0.002;
		Lvl1[Current_Stage].Ambience = false;

	}
	Lvl1[Current_Stage].Crumbling();/*
	if(Lvl1[Current_Stage].Dest[Lvl1[Current_Stage].Cur_Tile])
	{
			Current_Stage+=1;
			Lvl1[Current_Stage].Collectibles();
			Lvl1[Current_Stage].TilesChangeUp(100,10);
			Lvl1[Current_Stage].Initiate();
			Lvl1[Current_Stage].PowerUps();
			Goku.Total+=Goku.Score;
			Goku.Score = 0;
			Goku.SetCoordinates(-5.0,-1.0,-7.0,0.0,90.0,0);
			Lvl1[Current_Stage].Tile_Const = 1.25;
			if(Current_Stage>=2)
				Goku.Enemy = false;

	}*/
	if(Lvl1[Current_Stage].CollectibleTimer==100)
	{
		Lvl1[Current_Stage].Collectibles();
		Lvl1[Current_Stage].CollectibleTimer=0;
	}
	if(Lvl1[Current_Stage].Cur_Tile==Lvl1[Current_Stage].Collectible_Position)
	{
		Lvl1[Current_Stage].Collectibles();
		Goku.Score+=1;
		if(Goku.Score>=2)
		{
			Current_Stage+=1;
			Lvl1[Current_Stage].Collectibles();
			Lvl1[Current_Stage].TilesChangeUp(100,10);
			Lvl1[Current_Stage].Initiate();
			Lvl1[Current_Stage].PowerUps();
			Goku.Score = 0;
			Goku.SetCoordinates(-5.0,-1.0,-7.0,0.0,90.0,0);
			Lvl1[Current_Stage].Tile_Const = 1.25;
			if(Current_Stage>=2)
				Goku.Enemy = false;

		}
	}
	if(Current_Stage>=1)
	{
		if(Lvl1[Current_Stage].TeleportTiles[Lvl1[Current_Stage].Cur_Tile])
		{
			Lvl1[Current_Stage].Teleport();
		}
		if(Lvl1[Current_Stage].Trampoline_Tiles[Lvl1[Current_Stage].Cur_Tile])
		{
			Lvl1[Current_Stage].Trampoline();
		}
		else
		{
			Lvl1[Current_Stage].LIM = Goku.Cor_y;
		}
	}
	if(Lvl1[Current_Stage].FallenUnderTheSea())
	{
		Goku.Cor_y -= 0.5;
		if(Goku.Cor_y<=-40.0)
		{
			if(Goku.Lives<=0)
				Goku.Exit_Status();
			else
				Goku.Reset();
				Goku.Lives-=1;
		}
	}
	if(Current_Stage>=2)
		Goku.Enemies();
	if(Current_Stage>=1)
	{
		if(fabs(Goku.Cor_x-Goku.ECor_x)<=0.3&&fabs(Goku.ECor_z-Goku.Cor_z)<=0.3)
			Goku.num_collide+=1;
		if(Lvl1[Current_Stage].Intersection())
		{
			if(abs(Goku.Cor_y-Lvl1[Current_Stage].RaisedUp[Lvl1[Current_Stage].Collide].h)<0.25)
			{
				Goku.Cor_y = Lvl1[Current_Stage].RaisedUp[Lvl1[Current_Stage].Collide].h;
			}
		}
		if(Lvl1[Current_Stage].Powerup_Pos == Lvl1[Current_Stage].Cur_Tile)
		{
			Lvl1[Current_Stage].PowerTimer = 0;
			Lvl1[Current_Stage].Powerup_Pos = 600000000;
			Lvl1[Current_Stage].Num_PowerUps+=1;
			//cout<<Lvl1[Current_Stage].Num_PowerUps<<endl;
		}
		if(Lvl1[Current_Stage].PowerTimer==500)
		{
			Lvl1[Current_Stage].PowerUps();
		}
		Lvl1[Current_Stage].PowerTimer+=1;
	}
	cout<<Lvl1[Current_Stage].CollectibleTimer<<endl;
	Lvl1[Current_Stage].CollectibleTimer+=1;
	}
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}
void Ground :: HelicopterView()
{
	gluLookAt(Helicopter_x,Helicopter_y+3.0,Helicopter_z,Goku.Cor_x,Goku.Cor_y+1.0,Goku.Cor_z,0,1,0);
}
void Ground :: TowerView()
{
	gluLookAt(-5.0,18.0,-7.0,+0.7,-1,-11,0,1,0);

}
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}
void updateblocks(int value)
{
	/*if(Rising())
	{
		RaisedUp.clear();
		Missing.clear();
		TilesChangeUp(400,50);		
	}
	else
	{*/
	if(!Goku.Kam)
	{
		if(Current_Stage>=1)
		{
			Lvl1[Current_Stage].RandomIteratebility();
		}
	}
//	}
	glutPostRedisplay();
//	Lvl1[Current_Stage].Fallen();
	glutTimerFunc(100, updateblocks, 0);

}
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_COLOR_MATERIAL);	
	glPushMatrix();
	gluLookAt(0.5,6,-0.0, 0.5,-1,-9.0, 0,1,0);
	glTranslatef(-4.3, 3.7, -7.0);
	glScalef(0.2,0.2,0.2);
	FOR(i,0,Goku.Lives)
	{
		Goku.DrawGroup(Goku.Still, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
		glTranslatef(1.2,0.0,0.0);
	}
	glPopMatrix();
	if(Lvl1[Current_Stage].Tile_View)
		Lvl1[Current_Stage].TileView();
	else if(Goku.First)
	{
		//glRotatef(Goku._angle,0,1,0);
		gluLookAt(Goku.Cor_x,Goku.Cor_y + 2.0,Goku.Cor_z,Goku.Cor_x+ 1.5*cos(Goku._angle),Goku.Cor_y,Goku.Cor_z+1.5*sin(Goku._angle),0,1,0);
	}
	else if(Goku.Third)
		Goku.ThirdPerson();
	else if(Lvl1[Current_Stage].Helicopter)
		Lvl1[Current_Stage].HelicopterView();
	else if(Lvl1[Current_Stage].Tower)
		Lvl1[Current_Stage].TowerView();
	else
		gluLookAt(0.5,6,-0.0, 0.5,-1,-9.0, 0,1,0);
	if(Goku.UnderSpot)
	{
		Goku.SpotLight();
	}
	else
	{

		GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
		GLfloat sun_intensity[] = { Lvl1[Current_Stage].Sun_x, Lvl1[Current_Stage].Sun_y, Lvl1[Current_Stage].Sun_y, 1.0 };
		GLfloat ambient_intensity[] = { Lvl1[Current_Stage].Amb_x, Lvl1[Current_Stage].Amb_y,Lvl1[Current_Stage].Amb_y, 1.0 };
		glEnable(GL_LIGHTING); 
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

		glEnable(GL_LIGHT0); 
		glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	if(Goku.jump_mode)
	{
		Goku.Jump_Fun(Goku.Jump_Lim);
	}
	Lvl1[Current_Stage].Field.clear();
	Lvl1[Current_Stage].RaisedUp.clear();
	Lvl1[Current_Stage].Missing.clear();
	glPushMatrix();
	glTranslatef(Goku.ECor_x,-0.5,Goku.ECor_z);
	glScalef(0.5,0.5,0.5);
	if(!Goku.Enemy)
	{
		Goku.DrawGroup(Goku.Still,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	}/*
	else
	{
		Goku.ECor_x = -70.0;
	}*/
	glPopMatrix();
	glPushMatrix();
	FOR(i,0,Goku.Score)
	{

	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(Goku.Cor_x,Goku.Cor_y+Goku.Jump_Inc,Goku.Cor_z);
	glRotatef(Goku._angle,0,1,0);
	Goku.Current_Location();
	glTranslatef(0.0,0.5,0.0);
	if(Goku.Kam)
	{
		Goku.Kamehameha(len);
		len+=1;
		if(len>=100)
			Goku.Kam = false;
	}
	glScalef(0.6,0.6,0.6);
	if(Goku.iterate==0)
		Goku.DrawGroup(Goku.Still, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	else if((Goku.iterate&1)==1)
		Goku.DrawGroup(Goku.Left, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	else
		Goku.DrawGroup(Goku.Right, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glRotatef(180,0,1,0);
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Up);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(-5.0, 100.0, -7.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-100,-0.5,-100);
	glTexCoord2f(1,0);
	glVertex3f(100,-0.5,-100);
	glTexCoord2f(1,1);
	glVertex3f(100,-0.5,100);
	glTexCoord2f(0,1);
	glVertex3f(-100,-0.5,100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Back);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(-5.0, -1.5, -93.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-100,100,0.0);
	glTexCoord2f(1,0);
	glVertex3f(100,100,0.0);
	glTexCoord2f(1,1);
	glVertex3f(100,-100,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-100,-100,0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Front);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(-5.0, -1.5, 100.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-100,100,0.0);
	glTexCoord2f(1,0);
	glVertex3f(100,100,0.0);
	glTexCoord2f(1,1);
	glVertex3f(100,-100,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-100,-100,0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180,0,1,0);
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Bottom);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(1.7, -100, 7.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-100,-0.5,-120);
	glTexCoord2f(1,0);
	glVertex3f(100,-0.5,-120);
	glTexCoord2f(1,1);
	glVertex3f(100,-0.5,120);
	glTexCoord2f(0,1);
	glVertex3f(-100,-0.5,120);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180,1,0,0);
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Left);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(-100.0, -1.5, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(0.0,100,-100.0);
	glTexCoord2f(1,0);
	glVertex3f(0.0,100,100.0);
	glTexCoord2f(1,1);
	glVertex3f(0.0,-100,100.0);
	glTexCoord2f(0,1);
	glVertex3f(0.0,-100,-100.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180,1,0,0);
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Aesthetics[Current_Stage].Right);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(95.0, -1.5, 0.5);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(0.0,100,-100.0);
	glTexCoord2f(1,0);
	glVertex3f(0.0,100,100.0);
	glTexCoord2f(1,1);
	glVertex3f(0.0,-100,100.0);
	glTexCoord2f(0,1);
	glVertex3f(0.0,-100,-100.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.0, -1.50, -7.0);
	Lvl1[Current_Stage].CreateTiles(10,10,-5.0,-1.50,-7.0);
	glPopMatrix();
//	glPushMatrix();
//	glTranslatef(-5.0,3.0,-17.0);
	/*FOR(i,0,Goku.Score)
	{
		glColor3f(1.0,0.0,0.0);
		glutSolidCube(0.25);
		glTranslatef(0.5f,0.0,0.0);
	}
	glPopMatrix();*/
	glutSwapBuffers();
}
int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 800);
	glutCreateWindow("The 3D - Game");
	initRendering();
	glutDisplayFunc(drawScene);
	glutSpecialFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutTimerFunc(100, updateblocks, 0);
	glutKeyboardFunc(handleKeypress);
	glutMainLoop();
	return 0;
}

