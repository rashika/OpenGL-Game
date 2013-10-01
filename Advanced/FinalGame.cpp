#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "glm.cpp"
#include<vector>
#include<cstdlib>
#include<cmath>
bool giri=false;
using namespace std;
float RADIUS = 4.0f; //The radius of the sphere
int cnt=1;
#define PI 3.14159265
float _angle=0.0f;
float cor_y=0.1f;
float cor_x=0.0f;
float inc=0.0;
int ca=0;
int jump2=0,jump=0;
float cor_z=-10.0f;
int ran=0;
bool _highShininess = false; //Whether the shininess parameter is high
bool _lowSpecularity = false; //Whether the specularity parameter is high
bool _emission = false; //Whether the emission parameter is turned on
int keypressup;
int keypressright;
int keypressleft;
int keypressdown;
int counter;
bool flagblock=false;
float tower_angle=0.0f;
float tower_x=cor_x,tower_y=cor_y+5.0,tower_z=cor_z;
struct tile
{
	float x1,x2,x3,x4,z1,z2,z3,z4,h;
};
vector <struct tile > tilesup;
vector <struct tile> tiles;
vector <struct tile> Ground;
struct tile current_tile;
struct tile elem;
GLMmodel* pmodel1 = NULL;
GLMmodel* pmodel2 = NULL;
float stones_x1=-2.5f,stones_y1=10.0,stones_z1=-7.0f;
bool random_2[100];
float random_1[100];
bool random_11[100];
bool flag[100];
bool intersection()
{
	for(int i=0;i<tilesup.size();i++)
	{
		if(current_tile.x1>=tilesup[i].x1&&tilesup[i].x2>=current_tile.x1&&current_tile.z1>=tilesup[i].z1&&current_tile.z1<=tilesup[i].z4)
			return true;
		if(current_tile.x2>=tilesup[i].x1&&tilesup[i].x2>=current_tile.x1&&current_tile.z2>=tilesup[i].z1&&current_tile.z1<=tilesup[i].z4)
			return true;
			if(current_tile.x3>=tilesup[i].x1&&tilesup[i].x2>=current_tile.x1&&current_tile.z3>=tilesup[i].z1&&current_tile.z1<=tilesup[i].z4)
			return true;
		if(current_tile.x4>=tilesup[i].x1&&tilesup[i].x2>=current_tile.x1&&current_tile.z4>=tilesup[i].z1&&current_tile.z1<=tilesup[i].z4)
			return true;

	}
	return false;
}
bool girna()
{
	for(int i=0;i<tiles.size();i++)
	{
		if(current_tile.x1>=tiles[i].x1&&tiles[i].x2>=current_tile.x1&&current_tile.z1>=tiles[i].z1&&current_tile.z1<=tiles[i].z4)
			return true;
		if(current_tile.x2>=tiles[i].x1&&tiles[i].x2>=current_tile.x1&&current_tile.z2>=tiles[i].z1&&current_tile.z1<=tiles[i].z4)
			return true;
		if(current_tile.x3>=tiles[i].x1&&tiles[i].x2>=current_tile.x1&&current_tile.z3>=tiles[i].z1&&current_tile.z1<=tiles[i].z4)
			return true;
		if(current_tile.x4>=tiles[i].x1&&tiles[i].x2>=current_tile.x1&&current_tile.z4>=tiles[i].z1&&current_tile.z1<=tiles[i].z4)
			return true;

	}
	return false;

}

GLvoid
DrawGroup(GLMmodel* model, GLuint mode)
{
    static GLuint i;
    static GLMgroup* group;
    static GLMtriangle* triangle;
    static GLMmaterial* material;
    
    assert(model);
    assert(model->vertices);
    
    /* do a bit of warning */
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
  //  glTranslatef(cor_x,cor_y+inc,cor_z);
    while(group){
	if((cnt&1)==1)
	{
		if(!strcmp(group->name," upper_left"))
		{
			glRotatef(20.0,1.0,0.0,0.0);	
		}
		if(!strcmp(group->name," lower_left"))
    		{
			glRotatef(20.0,1.0,0.0,0.0);	

		}
		if(!strcmp(group->name," upper_right"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_lower"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_shoe"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);

		}
		if(!strcmp(group->name," left_shoe"))
		{
			glRotatef(20.0,1.0,0.0,0.0);
		}
	}
	else 
	{
		if(!strcmp(group->name," upper_left"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);	
		}
		if(!strcmp(group->name," lower_left"))
    		{
			glRotatef(-20.0,1.0,0.0,0.0);	

		}
		if(!strcmp(group->name," upper_right"))
		{
			glRotatef(20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_lower"))
		{
			glRotatef(20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_shoe"))
		{
			glRotatef(20.0,1.0,0.0,0.0);

		}
		if(!strcmp(group->name," left_shoe"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);
		}
	}
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
        for (i = 0; i < group->numtriangles; i++) {
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
    if((cnt&1)==1)
    {       
	    if(!strcmp(group->name," upper_left"))
	    {
		    glRotatef(-20.0,1.0,0.0,0.0);	
	    }
	    if(!strcmp(group->name," lower_left"))
	    {
		    glRotatef(-20.0,1.0,0.0,0.0);	

	    }
	    if(!strcmp(group->name," upper_right"))
	    {
		    glRotatef(20.0,1.0,0.0,0.0);
	    }
	    if(!strcmp(group->name," right_lower"))
	    {
		    glRotatef(20.0,1.0,0.0,0.0);
	    }
	    if(!strcmp(group->name," right_shoe"))
	    {
//		    cout<<"In"<<endl;
//		    cout<<group->name<<endl;
		    glRotatef(20.0,1.0,0.0,0.0);

	    }
	    if(!strcmp(group->name," left_shoe"))
	    {
	//	    cout<<"In"<<endl;
	//	    cout<<group->name<<endl;
		    glRotatef(-20.0,1.0,0.0,0.0);
	    }
	}
	else
	{
		if(!strcmp(group->name," upper_left"))
		{
			glRotatef(20.0,1.0,0.0,0.0);	
		}
		if(!strcmp(group->name," lower_left"))
    		{
			glRotatef(20.0,1.0,0.0,0.0);	

		}
		if(!strcmp(group->name," upper_right"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_lower"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_shoe"))
		{
			glRotatef(-20.0,1.0,0.0,0.0);

		}
		if(!strcmp(group->name," left_shoe"))
		{
			glRotatef(20.0,1.0,0.0,0.0);
		}
	}
        group = group->next;
    }
}
int cameramode=0;
int Number_Tiles=30;
int Tile_no=0;
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
		case 'p':
			_lowSpecularity = !_lowSpecularity;
			break;
		case 'e':
			_emission = !_emission;
			break;
		case 'j':
			jump=1;
			break;
		case 'c':
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


	}
}
bool person_on_block(void);
void handleKeypress(int key,int x,int y)
{
   // keypressright=0;
    //keypressleft=0;
    //keypressup=0;
    //keypressdown=0;
    if(key==GLUT_KEY_LEFT)
    {
//    cout<<cnt<<endl;
	 if(keypressleft==0)
		 cnt=1;
	keypressleft=1;
	_angle+=-0.01;
    }
    if(key==GLUT_KEY_RIGHT)
    {
	 if(keypressright==0)
		 cnt=1;
	keypressright=1;
	_angle+=0.01;
    }
    if(key==GLUT_KEY_DOWN)
    {
	 if(keypressdown==0)
		 cnt=1;
	cnt+=1;
	//if(checkdown()){
	cor_x-=0.75*sin(_angle*PI/180);
	cor_z-=0.75*cos(_angle*PI/180);
        current_tile.x1=cor_x-0.25;
	current_tile.x2=cor_x+0.25;
	current_tile.z1=cor_z-0.5;
	current_tile.z2=cor_z-0.5;
        current_tile.x3=cor_x-0.25;
	current_tile.x4=cor_x+0.25;
	current_tile.z3=cor_z+0.5;
	current_tile.z4=cor_z+0.5;
	current_tile.h=cor_y-1.0;
	if(person_on_block())
	{
		cout<<"IN"<<endl;
	}
	else if(intersection())
	{
		//cout<<"IN"<<endl;
		cor_x+=0.75*sin(_angle*PI/180);
		cor_z+=0.75*cos(_angle*PI/180);
		current_tile.x1=cor_x-0.25;
		current_tile.x2=cor_x+0.25;
		current_tile.z1=cor_z-0.5;
		current_tile.z2=cor_z-0.5;
		current_tile.x3=cor_x-0.25;
		current_tile.x4=cor_x+0.25;
		current_tile.z3=cor_z+0.5;
		current_tile.z4=cor_z+0.5;
		current_tile.h=cor_y-1.0;
	}
	else
	{
		cor_y=0.1;
		current_tile.h=cor_y-1.0;
	}
	keypressdown=1;
    }
    if(key==GLUT_KEY_UP)
    {
	 if(keypressup==0)
		 cnt=1;
	cnt+=1;
	cor_x+=0.75*sin(_angle*PI/180);
	cor_z+=0.75*cos(_angle*PI/180);
        current_tile.x1=cor_x-0.25;
	current_tile.x2=cor_x+0.25;
	current_tile.z1=cor_z-0.5;
	current_tile.z2=cor_z-0.5;
        current_tile.x3=cor_x-0.25;
	current_tile.x4=cor_x+0.25;
	current_tile.z3=cor_z+0.5;
	current_tile.z4=cor_z+0.5;
	if(person_on_block())
	{
		cout<<"IN"<<endl;
	}
	else if(intersection())
	{

		cor_x-=0.75*sin(_angle*PI/180);
		cor_z-=0.75*cos(_angle*PI/180);
		current_tile.x1=cor_x-0.25;
		current_tile.x2=cor_x+0.25;
		current_tile.z1=cor_z-0.5;
		current_tile.z2=cor_z-0.5;
		current_tile.x3=cor_x-0.25;
		current_tile.x4=cor_x+0.25;
		current_tile.z3=cor_z+0.5;
		current_tile.z4=cor_z+0.5;
		current_tile.h=cor_y-1.0;
	}
	else
	{
		cor_y=0.2;
		current_tile.h=cor_y-1.0;
	}
	keypressup=1;
    }
}

void initRendering() {
	//glColor3f(1.0,1.0,1.0);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//Disable color materials, so that glMaterial calls work
	glDisable(GL_COLOR_MATERIAL);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}
void collisions_select(int n,int num_tiles)
{
	memset(random_1,0,sizeof(random_1));
	memset(random_2,false,sizeof(random_2));
	memset(random_11,false,sizeof(random_11));
	memset(flag,false,sizeof(flag));
	random_11[0]=1;
	random_1[0]=0.2;
	//cout<<n<<endl;
	for(int i=0;i<n;i++)
	{
		int val=(int)rand()%(num_tiles);
		if(i<2)
		{
			if(!random_11[val])
			{
				random_2[val]=true;
			}
		}
		else{
			if(!random_2[val])
			{
				random_1[val]=0.2;
				random_11[val]=true;
			}
		}
	}

}
void current_tile_coordinates()
{
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  0.0,  0.0 );
	glVertex3f(0.25,  -1.01, 0.5);
	glVertex3f(0.25,  -1.01, -0.5 );
	glVertex3f(-0.25,  -1.01, -0.5 );
	glVertex3f(-0.25,  -1.01, 0.5 );
	glEnd();
        current_tile.x1=cor_x-0.25;
	current_tile.x2=cor_x+0.25;
	current_tile.z1=cor_z-0.5;
	current_tile.z2=cor_z-0.5;
        current_tile.x3=cor_x-0.25;
	current_tile.x4=cor_x+0.25;
	current_tile.z3=cor_z+0.5;
	current_tile.z4=cor_z+0.5;
	current_tile.h=cor_y-1.0;

}
void Tile_Coordinates(float x1,float y1,float z1,int i,int j)
{
	elem.x1=x1+j*1.50-0.75;
	elem.x2=x1+j*1.50+0.75;
	elem.z1=z1-i*1.50-0.75;
	elem.z2=z1-i*1.50-0.75;
	elem.x3=x1+j*1.50-0.75;
	elem.x4=x1+j*1.50+0.75;
	elem.z3=z1-i*1.50+0.75;
	elem.z4=z1-i*1.50+0.75;
//	return elem;
}
void CreateTiles(int num_rows,int num_cols,float x1,float y1,float z1)
{
	float x2,y2,z2;
	float inc1=0.0,inc2=0.0;
	int cnv=0;
	for(int i=0;i<num_rows;i++)
	{
		inc2=0.0;
		for(int j=0;j<num_cols;j++)
		{
			Tile_Coordinates(x1,y1,z1,i,j);
			elem.h=y1+0.75;
			Ground.push_back(elem);
			if(random_11[cnv])
			{
				elem.h=y1+0.75+random_1[cnv];
				tilesup.push_back(elem);
			}
			else if(random_2[cnv])
			{
				tiles.push_back(elem);
				glTranslatef(1.50,0.0,0.0);
				cnv+=1;
				continue;

			}
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  1.0, 1.0 );
			glVertex3f(  0.75, -0.75, 0.75 );
			glVertex3f(  0.75,  0.75+random_1[cnv], 0.75 );
			glVertex3f( -0.75,  0.75+random_1[cnv], 0.75 );
			glVertex3f( -0.75, -0.75, 0.75 );
			glEnd();
			glBegin(GL_POLYGON);
			glColor3f( 1.0,  0.0,  1.0 );
			glVertex3f(0.75, -0.75,-0.75 );
			glVertex3f(0.75,  0.75+random_1[cnv], -0.75 );
			glVertex3f(0.75,  0.75+random_1[cnv],  0.75 );
			glVertex3f(0.75, -0.75,  0.75 );
			glEnd();
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  1.0,  0.0 );
			glVertex3f( -0.75, -0.75, 0.75 );
			glVertex3f(-0.75,  0.75+random_1[cnv],  0.75 );
			glVertex3f( -0.75,  0.75+random_1[cnv], -0.75 );
			glVertex3f( -0.75, -0.75, -0.75 );
			glEnd();
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  0.0,  1.0 );
			glVertex3f(  0.75,  0.75+random_1[cnv],  0.75 );
			glVertex3f(  0.75,  0.75+random_1[cnv], -0.75 );
			glVertex3f( -0.75,  0.75+random_1[cnv], -0.75 );
			glVertex3f( -0.75,  0.75+random_1[cnv],  0.75 );
			glEnd();
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.0,  0.0 );
			glVertex3f(  0.75, -0.75, -0.75 );
			glVertex3f(  0.75, -0.75,  0.75 );
			glVertex3f( -0.75, -0.75,  0.75 );
			glVertex3f( -0.75, -0.75, -0.75 );
			glEnd();
			glTranslatef(1.50,0.0,0.0);	
			cnv+=1;
		}
		glTranslatef(-1.5*num_cols, 0.0,-1.50);

	}/*
	for(int i=0;i<30;i++)
	{
		cout<<random_1[i]<<" ";
	}
	cout<<endl;*/

}
void camera()
{
	if(ca==1)
	{
		gluLookAt(cor_x,cor_y+inc+1.0,cor_z,cor_x+(1.5)*sin(_angle),cor_y-0.5,cor_z+(1.5)*cos(_angle),0.0,1.0,0.0);
	}
	if(ca==2)
	{
		gluLookAt(tower_x,tower_y,tower_z,cor_x,cor_y+inc+1.0,cor_z,1.0,0.0,0.0);
	}
	if(ca==3)
	{
		float x1_1,y1_1,z1_1;
		cout<<Tile_no<<endl;
		cout<<Ground.size()<<endl;
	        x1_1 = (Ground[Tile_no].x1+Ground[Tile_no].x2)/2;	
	        z1_1 = (Ground[Tile_no].z1+Ground[Tile_no].z4)/2;	
		gluLookAt(x1_1,Ground[Tile_no].h,z1_1,cor_x,cor_y+inc+1.0,cor_z,0.0,1.0,0.0);
	}
}
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
      //  glTranslatef(0.0,0.0,-8.0);
	if(jump)
	{
		if(inc>1.0)
		{
			inc-=0.2;
			jump=0;
			jump2=1;
		}
		else
		{
			inc+=0.2;
		}
		cor_x+=0.2*sin(_angle*PI/180);
		cor_z+=0.2*cos(_angle*PI/180);	
	}
	if(jump2)
	{
		inc-=0.2;
		cor_x+=0.2*sin(_angle*PI/180);
		cor_z+=0.2*cos(_angle*PI/180);
	}
	if(inc-0<0.0001)
	{
		jump2=0;
		inc=0.0;
	}
	if(inc<0.0)
		inc=0.0;
	if(cameramode)
	{
		camera();
	}
	glPushMatrix();
	glTranslatef(cor_x, cor_y+inc, cor_z);
	glRotatef(_angle,0,1,0);
	if (!pmodel1) 
	{
		// this is the call that actualy reads the OBJ and creates the model object
		char *temp = new char[20];
		strcpy(temp, "mard.obj");
		pmodel1 = glmReadOBJ(temp);	
		if (!pmodel1) exit(0);
		glmUnitize(pmodel1);
		glmFacetNormals(pmodel1);        
		glmVertexNormals(pmodel1, 90.0);
                glmLinearTexture(pmodel1);
                glmSpheremapTexture(pmodel1);
	}
	glScalef(0.75,0.75,0.75);
	DrawGroup(pmodel1, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	current_tile_coordinates();
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	tiles.clear();
	tilesup.clear();
	glTranslatef(-2.5, -1.5, -7.0);
	CreateTiles(6,5,-2.5,-1.5,-7.0);                    // To Create Tiles for the Game	
	glPopMatrix();/*
	glPushMatrix();	
	if(stones_y1<-0.5)
		stones_y1=-0.5;
	glTranslatef(-1.5, stones_y1, -8.5);
	glScalef(0.1,0.1,0.1);
	for(int i=0;i<5;i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(   1.0,  1.0, 1.0 );
		glVertex3f(  0.75, -0.75, 0.75 );
		glVertex3f(  0.75,  0.75, 0.75 );
		glVertex3f( -0.75,  0.75, 0.75 );
		glVertex3f( -0.75, -0.75, 0.75 );
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(  1.0,  0.0,  1.0 );
		glVertex3f( 0.75, -0.75,-0.75 );
		glVertex3f(0.75,  0.75, -0.75 );
		glVertex3f( 0.75,  0.75,  0.75 );
		glVertex3f( 0.75, -0.75,  0.75 );
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(   0.0,  1.0,  0.0 );
		glVertex3f( -0.75, -0.75, 0.75 );
		glVertex3f(-0.75,  0.75,  0.75 );
		glVertex3f( -0.75,  0.75, -0.75 );
		glVertex3f( -0.75, -0.75, -0.75 );
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(   0.0,  0.0,  1.0 );
		glVertex3f(  0.75,  0.75,  0.75 );
		glVertex3f(  0.75,  0.75, -0.75 );
		glVertex3f( -0.75,  0.75, -0.75 );
		glVertex3f( -0.75,  0.75,  0.75 );
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(   1.0,  0.0,  0.0 );
		glVertex3f(  0.75, -0.75, -0.75 );
		glVertex3f(  0.75, -0.75,  0.75 );
		glVertex3f( -0.75, -0.75,  0.75 );
		glVertex3f( -0.75, -0.75, -0.75 );
		glEnd();
		glTranslatef(10.25,0.0,10.25);
		
	}
	glPopMatrix();*/
	glutSwapBuffers();
}
bool person_on_block()
{
	for(int i=0;i<tilesup.size();i++)
	{
		cout<<"Gussna"<<endl;
		cout<<current_tile.h<<" "<<tilesup[i].h<<" "<<cor_y<<endl;
		cout<<"Andar"<<endl;
		if(intersection()&&((abs(current_tile.h-tilesup[i].h)<=0.25)||flagblock))
		{
			current_tile.h=tilesup[i].h;
			cor_y=current_tile.h+1.0;
			flagblock=true;
			return true;
		}
	}
	flagblock=false;
	return false;
}
void update(int value) {
	stones_y1-=0.25;/*
	if(giri&&inc==0.0)
	{
		cor_y-=0.20f;
		cnt+=1;
	}
	if(girna()&&inc==0.0)
	{
		giri=true;
		cor_y-=0.20f;
		cnt+=1;
	}*//*
	if(person_on_block())
	{
		cout<<"IN"<<endl;
	}
	else
	{
		cor_y=0.2;
		current_tile.h=cor_y-1.0;
	}*/
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}
bool CheckTilesUp()
{
	for(int i=0;i<100;i++)
	{
		if(random_11[i])
			return false;
	}
	return true;
}
void IterateTilesup()
{
	for(int i=0;i<100;i++)
	{
		if(random_11[i])
		{
			if(random_1[i]>=2.0||flag[i])
			{
				random_1[i]-=0.2;
				flag[i]=true;
			}	
			else if(random_1[i]<=2.0&&random_1[i]>0.0)
				random_1[i]+=0.2;
			if(random_1[i]<=0.0)
			{
				random_11[i]=false;
				flag[i]=false;
				random_1[i]=0;
			}
		}
	}
}
void updateblocks(int value)
{
        glEnable(GL_COLOR_MATERIAL);
	//resets();                                                // TO create tiles and blocks;
	/*if(CheckTilesUp())
	{
		tilesup.clear();
		tiles.clear();
		random_11[0]=1;
		collisions_select(6,30);
	}
	else
	{
		IterateTilesup();
	}
	if(person_on_block())
	{
		cout<<"IN"<<endl;
	}
	else
	{
		cor_y=0.2;
		current_tile.h=cor_y-1.0;
	}*/
	glutPostRedisplay();
	glutTimerFunc(100, updateblocks, 0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	
	glutCreateWindow("Materials - videotutorialsrock.com");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutTimerFunc(10, updateblocks, 0);
	glutSpecialFunc(handleKeypress);
	glutMainLoop();
	return 0;
}	
