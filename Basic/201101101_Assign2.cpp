#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <stdarg.h>
#include <algorithm>
#include <time.h>

#include "imageloader.h"

using namespace std;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
            0,                            //0 for now
            GL_RGB,                       //Format OpenGL uses for image
            image->width, image->height,  //Width and height
            0,                            //The border of the image
            GL_RGB, //GL_RGB, because pixels are stored in RGB format
            GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
            //as unsigned numbers
            image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function declarations
void drawScene();
void drawBox(float width , float height);
void drawBlock(float x1 , float y1 , float x2 , float y2);
void drawLine(float x1 , float y1 , float x2 , float y2);
void initRendering();
void handleResize(int w, int h);
void handleKeyPress(int key , int x , int y);
void handleKeyPress1(unsigned char key , int x , int y);
void handlePassiveMotion(int x , int y);
void handleMouseMotion(int button , int state , int x , int y);
void camera();
void init1(void);
void myinit();
void update(int t);

// Global variables
double rotate_y = 45; 
double rotate_x = 30;
int tower_view = 0;
int person_view = 0;
int t_person_view = 0;
int tile_view = 0;
int hover_view = 0;
int hel_view = 0;
int boundary = 0;
double br_x = 0;
double br_y = 0;
double br_z = 0;
double bt_x = 0;
float in_x , fin_x ;
#define BASE_HEIGHT 2 
#define BASE_RADIUS .5
#define HEAD_RADIUS .80/2
#define HAND_HEIGHT (2+1.25)/2
#define LEG_HEIGHT (2+1.25)/2
#define HANDLEG_RADIUS .5/2 
GLUquadricObj *p;
GLfloat ambient[3];
GLfloat diffuse[3];
GLfloat specular[3];
GLfloat shiness[] = {50.0f};
float theta[5]={0.0,0,0,0,0};
float xpos=1.0;
float ypos=0.0;
float zpos=-10.0;
float xlimit=15;
float zlimit=15;
float height = 0.0 , xprev = 1.0 , zprev = -10.0;
int lcount=0 , jump = 0 , h_flag = 0 , insert_value = 0 , rand_side , rcount = 0;
float z_fall = 0;
float x_tile = 1.5 , y_tile = -1.3 , z_tile = -4.5 ;
int x_prev , y_prev , first_enter = 0;
float hover_x = 3 , hover_y = 0 , hover_z = -5;
float hel_x  = 5 , hel_y = 15 , hel_z = 15;
float look_x = 5 , look_y = 0 , look_z = -5 ;
int up = 1 , block_enter = 1 , insert = 0;

//angle of rotations
float xp = 2.0 , yp = 5.0 , zp = 5.0 , xrot = 6.0 , yrot = 0.0 , angle = 0.0;

vector<int> random1;
vector<int> tile;
vector<int> block;

int main(int argc , char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    int i , j ;
    srand(time(NULL));
    for( i = 0 ; i < 15 ; i++)
    {
        int a = rand()%100;
        if(a == 9 || a == 90)
            i--;
        else
            random1.push_back(a);
    }
    for( i = 0 ; i < 15 ; i++)
    {
        int a = rand()%100;
        if(a == 9 || a == 90)
            i--;
        else
        {
            for(j = 0 ; j < 15 ; j++)
            {
                if(random1[j] == a)
                {
                    insert_value = 1;
                    break;
                }
            }
            if(insert_value == 0)
                 tile.push_back(a);
            else
            {
                i--;
                insert_value = 0;
            }
        }
    }
    for( i = 0 ; i < 15 ; i++)
    {
        int a = rand()%100;
        if(a == 9 || a == 90)
            i--;
        else
            block.push_back(a);
    }

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth =  (w);
    int windowHeight = (h);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Assignment-2");  // Setup the window
    initRendering();
    myinit();

    //Register callbacks
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(drawScene);
    glutSpecialFunc(handleKeyPress);
    glutIdleFunc(drawScene); 
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(handleKeyPress1);
    glutMouseFunc(handleMouseMotion);
    glutPassiveMotionFunc(handlePassiveMotion);
    glutTimerFunc(10,update,0);

    glutMainLoop();
    return 0;
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(t_person_view == 1)
    {
        if(theta[0]==0)//z
            gluLookAt(xpos,ypos+BASE_HEIGHT,zpos-8+HEAD_RADIUS/2,xpos,ypos-1.5,zpos+3-5,0,1,0);
        if(theta[0]==90 || theta[0] == -270)//x
            gluLookAt(xpos-3+HEAD_RADIUS/2,ypos+BASE_HEIGHT,zpos-5,xpos+3,ypos-1.5,zpos-5,0,1,0);
        if(theta[0]==180 || theta[0] == -180)//-z
            gluLookAt(xpos,ypos+BASE_HEIGHT,zpos-2-(HEAD_RADIUS/2),xpos,ypos-1.5,zpos-3-5,0,1,0);
        if(theta[0]==270 || theta[0] == -90)//-x
            gluLookAt(xpos+3-(HEAD_RADIUS/2),ypos+BASE_HEIGHT,zpos-5,xpos-3,ypos-1.5,zpos-5,0,1,0);

    }

    if(hover_view == 1)
    {
        gluLookAt(5,0,5,hover_x,hover_y,hover_z,0,1,0);
    }

    if(hel_view == 1)
    {
        gluLookAt(hel_x ,hel_y,hel_z-5,look_x,look_y,look_z,0,1,0);
    }
    if(person_view == 1)
    {
        if(theta[0]==0)//z
            gluLookAt(xpos,ypos+BASE_HEIGHT,zpos-5+HEAD_RADIUS/2,xpos,ypos-1.5,zpos+3-5,0,1,0);
        if(theta[0]==90 || theta[0] == -270)//x
            gluLookAt(xpos+HEAD_RADIUS/2,ypos+BASE_HEIGHT,zpos-5,xpos+3,ypos-1.5,zpos-5,0,1,0);
        if(theta[0]==180 || theta[0] == -180)//-z
            gluLookAt(xpos,ypos+BASE_HEIGHT,zpos-5-(HEAD_RADIUS/2),xpos,ypos-1.5,zpos-3-5,0,1,0);
        if(theta[0]==270 || theta[0] == -90)//-x
            gluLookAt(xpos-(HEAD_RADIUS/2),ypos+BASE_HEIGHT,zpos-5,xpos-3,ypos-1.5,zpos-5,0,1,0);
    }

    glTranslatef(0.0f,0.0,-5.0f);

    if(tile_view == 1)
    {
        gluLookAt(x_tile,y_tile,z_tile,x_tile,y_tile,z_tile-15,0,1,0);
    }

    //Camera
    if(tower_view == 1)
        camera();

    // Draw Cube
    int i , j , k , l , enter = 0 , enter_tile = 0;
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    if(person_view == 0)
        glTranslatef(0.5,-1.5,0.0);
    glPushMatrix();
    for(k = 0 ; k < 2 ; k++)
    {
        glTranslatef(0.0,-1.0,0.0);
        for(i = 0 ; i < 10 ; i++)
        {
            glTranslatef(0.0,0.0,-1.0);
            for(j = 0 ; j < 10 ; j++)
            {
                enter = 0;
                enter_tile = 0;
                block_enter = 0;
                for(l = 0 ; l < 15 ; l++)
                {
                    if(i*10 + j == random1[l])
                    {
                        if(rcount%500 == 1)
                        {
                        rand_side = rand()%4;
                        if(rand_side == 0)
                        {
                            if(random1[l]+1 != 9 and random1[l]+1 != 90)
                                random1[l] += 1;
                        }
                        else if(rand_side == 3)
                        {
                            if(random1[l]-10 != 9 and random1[l]-10 != 90)
                            random1[l] -= 10;
                        }
                        else if(rand_side == 2)
                        {
                            if(random1[l]+10 != 9 and random1[l]+10 != 90)
                            random1[l] += 10;
                        }
                        else if(rand_side == 1)
                        {
                            if(random1[l]-1 != 9 and random1[l]-1 != 90)
                            random1[l] -= 1;
                        }
                        }
                        rcount++;
                        enter = 1;
                        break;
                    }
                }
                for(l = 0 ; l < 15 ; l++)
                {
                    if(i*10 + j == tile[l])
                    {
                        enter_tile = 1;
                        break;
                    }
                }
                for(l = 0 ; l < 15 ; l++)
                {
                    if(i*10 + j == block[l])
                    {
                        block_enter = 1;
                        break;
                    }
                }
                glTranslatef(1.0,0.0,0.0);
                if(enter == 1)
                {
                    if(xpos < j+1+0.25 and xpos > j+1-0.75 and zpos > -(i+0.5)-1 and zpos < -(i+0.5))
                    {
                        glColor3f(1.0,1.0,1.0);
                        glutSolidCube(1.0);  
                        glColor3f(0.0,0.0,0.0);
                        glLineWidth(3.0f);
                        glutWireCube(1.0);
                    }
                    else
                    {
                        glColor3f(0.0,0.0,0.0);
                        glutSolidCube(1.0);  
                        glColor3f(0.0,0.0,0.0);
                        glLineWidth(3.0f);
                        glutWireCube(1.0);
                    }
                }
                else if(block_enter == 1 and k == 0 and enter_tile == 0 and enter == 0)
                {
                    glPushMatrix();
                    glTranslatef(0.0,1.0,0.0);
                    glColor3f(0.902,0.902,0.9803);
                    glutSolidCube(1.0);  
                    glColor3f(0.6902,0.7686,0.8672);
                    glLineWidth(3.0f);
                    glutWireCube(1.0);
                        if(xpos < j+1+0.50 and xpos > j+1-0.75 and zpos > -(i+0.5)-1 and zpos < -(i+0.5))
                        {
                            if(theta[0] == 0)//z
                            {
                                xpos = xprev;
                                zpos = zprev - 0.25;
                            }
                            else if(theta[0] == 180 || theta[0] == -180)//-z
                            {
                                xpos = xprev; 
                                zpos = zprev + 0.25;
                            }
                            else if(theta[0] == 270 || theta[0] == -90) //-x
                            {
                                xpos = xprev + 0.25;
                                zpos = zprev;
                            }
                            else //+x
                            {
                                xpos = xprev - 0.25;
                                zpos = zprev;
                            }
                        }
                    glPopMatrix();
                }
                else
                {
                    glPushMatrix();
                    if(enter_tile == 1 and k == 0)
                    {
                        glTranslatef(0,(height-1)/2,0);
                        glScalef(1,height,1);
                    }
                    if( i == 0 and j == 9 and k == 0)
                    {
                        glColor3f(0.5608,0.5608,0.5608);
                        glutSolidCube(1.0);  
                        glColor3f(0.6118,0.4,0.1217);
                        glLineWidth(3.0f);
                        glutWireCube(1.0);
                    }
                    else if(xpos < 9+1+0.25 and xpos > 9+1-0.75 and zpos > -(0+0.5)-1 and zpos < -(0+0.5) )
                    {
                        cout << "--------------------------" << endl;
                        cout << "  Wonderfully Played!!!!  " << endl;
                        cout << "--------------------------" << endl;
                        exit(0);
                    }
                    else
                    {
                        if(xpos < j+1+0.25 and xpos > j+1-0.75 and zpos > -(i+0.5)-1 and zpos < -(i+0.5))
                        {
                            glColor3f(1.0,1.0,1.0);
                            glutSolidCube(1.0);  
                            glColor3f(0.0,0.0,0.0);
                            glLineWidth(3.0f);
                            glutWireCube(1.0);
                        }
                        else
                        {
                            glEnable(GL_TEXTURE_2D);
                            glBindTexture(GL_TEXTURE_2D, _textureId1);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                            glColor3f(0.3,0.3,0.5);
                            glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                            glEnable(GL_TEXTURE_GEN_T);
                            glBindTexture(GL_TEXTURE_2D, _textureId1);
                            glutSolidCube(1.0);  
                            glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                            glDisable(GL_TEXTURE_GEN_T);
                            glColor3f(0.192,0.0,0.384);
                            glLineWidth(3.0f);
                            glutWireCube(1.0);
                        }
                    }
                    glPopMatrix();
                    if(enter_tile == 1 && (jump == 0 || jump == -5))
                    {
                        if(x_tile == j+1.5 and (z_tile+4.5) == (-1)*i)
                        {
                            y_tile = height - 2.0;
                        }
                        if(xpos < j+1+0.25 and xpos > j+1-0.75 and zpos > -(i+0.5)-1 and zpos < -(i+0.5))
                        {
                            if(height <= 1)
                            {
                                ypos = (height - 1);
                                xprev = xpos;
                                zprev = zpos;
                            }
                            else if(height > 1 and xpos == xprev and zpos == zprev)
                            {
                                ypos = (height - 1);
                            }
                            else
                            {
                                ypos = 0.0;
                                xpos = xprev;
                                zpos = zprev;
                            }
                        }
                    }
                    if(enter_tile == 0 && (jump == 0 || jump == -5))
                    {
                        if(xpos < j+1+0.25 and xpos > j+1-0.75 and zpos > -(i+0.5)-1 and zpos < -(i+0.5))
                        {
                            ypos = 0.0;
                        }
                    }
                    if(enter_tile == 0)
                    {
                        if(x_tile == j+1.5 and (z_tile+4.5) <= (-1)*i)
                        {
                            y_tile = -1.3;
                        }
                    }
                }
                }
                glTranslatef(-10.0,0.0,0.0);
            }
        glTranslatef(0.0,0.0,10.0);
    }

    glTranslatef(-3.0,-1.0,3.0);

    for(i = 0 ; i < 16 ; i++)
    {
        glTranslatef(0.0,0.0,-1.0);
        for(j = 0 ; j < 16 ; j++)
        {
            glTranslatef(1.0,0.0,0.0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glColor3f(0.1099,0.5255,0.9333);
            glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
            glEnable(GL_TEXTURE_GEN_T);
            glBindTexture(GL_TEXTURE_2D, _textureId);
            glutSolidCube(1.0); 
            glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
            glDisable(GL_TEXTURE_GEN_T);
        }
        glTranslatef(-16.0,0.0,0.0);
    }

    glPopMatrix();

    //robot
    glPushMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glTranslatef (xpos, ypos, zpos);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    glPushMatrix();

    ambient[0] = 1.0; ambient[1] = 0.0; ambient[2] = 0.0;
    diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 0.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);


    glScalef(0.25,0.25,0.25);
    glRotatef(-90,1,0,0);
    if(h_flag == 1)
    {
        glTranslatef(0,0,(-1)*z_fall);
    }
    gluQuadricDrawStyle(p, GLU_FILL);
    gluCylinder (p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 20, 20);
    gluDisk(p,0,BASE_RADIUS,20,20);

    glPushMatrix();
    glTranslatef(0,0,BASE_HEIGHT);
    gluDisk(p,0,BASE_RADIUS,20,20);

    glPushMatrix();//head
    glColor3f(1.0, 0.0, 0.0);
    ambient[0] = 1.0; ambient[1] = 0.0; ambient[2] = 1.0;
    diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

    glTranslatef(0,0,HEAD_RADIUS);
    gluSphere(p,HEAD_RADIUS,20,20);
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(HEAD_RADIUS/2,-HEAD_RADIUS,0);
    gluDisk(p,0,HEAD_RADIUS/2,20,20);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(-HEAD_RADIUS/2,-HEAD_RADIUS,0);
    gluDisk(p,0,HEAD_RADIUS/2,20,20);
    glPopMatrix();
    glPushMatrix();//for nose
    glTranslatef(0,-(HEAD_RADIUS+.2),0);//for nose
    glColor3f(0.0, 0.0, 1.0);
    gluSphere(p,.2,20,20);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix(); //right arm
    ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
    diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

    glTranslatef(-BASE_RADIUS-HANDLEG_RADIUS,0,0);
    glRotatef(180,1,0,0);
    glRotatef(theta[1],1,0,0);

    glColor3f(0.0, 1.0, 0.0);
    gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, HAND_HEIGHT, 20, 20);
    glPopMatrix();

    glPushMatrix(); //right arm
    ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
    diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    glTranslatef(BASE_RADIUS+HANDLEG_RADIUS,0,0);
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(180,1,0,0);
    glRotatef(theta[2],1,0,0);
    gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, HAND_HEIGHT, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix(); //right leg
    ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
    diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    glTranslatef(BASE_RADIUS/2,0,0);
    glRotatef(180,1,0,0);
    glRotatef(theta[3],1,0,0);
    gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, LEG_HEIGHT, 20, 20);
    glPushMatrix();
    glTranslatef(0,0,LEG_HEIGHT);

    glPopMatrix();
    glPopMatrix();

    glPushMatrix(); //left leg
    ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
    diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    glTranslatef(-BASE_RADIUS/2,0,0);
    glRotatef(180,1,0,0);
    glRotatef(theta[4],1,0,0);
    gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, LEG_HEIGHT, 20, 20);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    glFlush();
    glutSwapBuffers();
    angle++; //increase the angle
}

void myinit() {
    p=gluNewQuadric();
}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xp,-yp,-zp); //translate the screen to the position of our camera
}

void initRendering() {

    glEnable(GL_DEPTH_TEST);       
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    Image* image = loadBMP("water.bmp");
    _textureId = loadTexture(image);
    delete image;

    Image* image1 = loadBMP("tile.bmp");
    _textureId1 = loadTexture(image1);
    delete image1;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init1(void){
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat white_light[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat lmodel_ambient[] = {1.0, 1.0, 0.0, 1.0};
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void handlePassiveMotion(int x,int y)
{
    if(hover_view == 1)
    {
        if(first_enter == 0)
        {
            first_enter = 1;
            x_prev = x;
            y_prev = y;
        }
        float diffx , diffy ;
        diffx = -(x_prev - x);
        diffy = +(y_prev - y);
        hover_x += diffx/10;
        hover_y += diffy/10;
        x_prev = x;
        y_prev = y;
    }
}
void handleMouseMotion(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            in_x = x;
        }
    }
    if(state == GLUT_UP)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            fin_x = x;
            float dx = fin_x - in_x ;
            float rot_angle = -((dx/40.0)*20.0)/180;
            float tempx = hel_x ;
            hel_x  = (hel_x )*cos(rot_angle)+(hel_z)*sin(rot_angle) ;
            hel_z = -tempx*sin(rot_angle)+(hel_z)*cos(rot_angle) ;
        }
    }
    if(button == 3)
    {
        hel_x-=0.1*(hel_x-look_x);
        hel_z-=0.1*(hel_z-look_z);
        hel_y-=0.1*(hel_y-look_y);
    }
    if(button == 4)
    {
        hel_x+=0.1*(hel_x-look_x);
        hel_z+=0.1*(hel_z-look_z);
        hel_y+=0.1*(hel_y-look_y);
    }
}
void handleKeyPress( int key, int x, int y ) {

    int i;
    if(xpos < 0.5 || xpos > 10.5 || zpos < -10.5 || zpos > -0.5)
    {
        boundary = 1;
        h_flag = 1;
    }

    if(key==GLUT_KEY_UP){
        xprev = xpos;
        zprev = zpos;
        if(h_flag == 0)
        {
        for(i = 0 ; i < 15 ; i++)
        {
            if(((int)(xpos-0.5)+(int)((abs(zpos)-0.5))*10) == random1[i]){
                h_flag = 1;
            }
        }
        xpos -= cos(90 * PI/180 + theta[0] * PI/180)/4;
        zpos += sin(90 * PI/180 + theta[0] * PI/180)/4;
        if(lcount==0){
            theta[1]=30;
            theta[2]=-30;
            theta[3]=10;
            theta[4]=-10;
            lcount=1;
        }
        else{
            theta[1]=-30;
            theta[2]=30;
            theta[3]=-10;
            theta[4]=10;
            lcount=0;
        }
        if(xpos > xlimit){
            xpos=xlimit;
        }
        if(xpos < -xlimit){
            xpos=-xlimit;
        }
        if(zpos > zlimit){
            zpos=zlimit;
        }
        if(zpos < -zlimit){
            zpos=-zlimit;
        }
        }
    }
    if(key==GLUT_KEY_DOWN){
        if(h_flag == 0)
        {
        for(i = 0 ; i < 15 ; i++)
        {
            if(((int)(xpos-0.5)+(int)((abs(zpos)-0.5))*10) == random1[i]){
                h_flag = 1;
            }
        }
        xpos += cos(90 * PI/180 + theta[0] * PI/180)/4;
        zpos -= sin(90 * PI/180 + theta[0] * PI/180)/4;
        if(lcount==0){
            theta[1]=30;
            theta[2]=-30;
            theta[3]=10;
            theta[4]=-10;
            lcount=1;
        }
        else{
            theta[1]=-30;
            theta[2]=30;
            theta[3]=-10;
            theta[4]=10;
            lcount=0;
        }
        if(xpos > xlimit){
            xpos=xlimit;
        }
        if(xpos < -xlimit){
            xpos=-xlimit;
        }
        if(zpos > zlimit){
            zpos=zlimit;
        }
        if(zpos < -zlimit){
            zpos=-zlimit;
        }
        }
    }
    if(key==GLUT_KEY_LEFT){
        theta[0]=(int)(theta[0]+90.0)%360;
    }
    if(key==GLUT_KEY_RIGHT){
        theta[0]=(int)(theta[0]-90.0)%360;
    }

    glutPostRedisplay();
}

void update(int t)
{
    int i;

    if(xpos < 0.5 || xpos > 10.5 || zpos < -10.5 || zpos > -0.5)
    {
        boundary = 1;
        h_flag = 1;
    }

    if(jump>=1 && jump<5)
    {
        jump++;
        xpos -= cos(90 * PI/180 + theta[0] * PI/180)/4;
        zpos += sin(90 * PI/180 + theta[0] * PI/180)/4;
        ypos+=0.3;
    }

    if(jump==5)
        jump=-1;

    if(jump<=-1 && jump>-5)
    {
        jump--;
        xpos -= cos(90 * PI/180 + theta[0] * PI/180)/4;
        zpos += sin(90 * PI/180 + theta[0] * PI/180)/4;
        ypos-=0.3;

    }

    if(h_flag == 0 and jump == -5)
    {
        for(i = 0 ; i < 15 ; i++)
        {
            if(((int)(xpos-0.5)+(int)((abs(zpos)-0.5))*10) == random1[i]){
                h_flag = 1;
            }
        }
    }
    
    if(height <= 0.2)
    {
        up = 1;
    }
    else if( height >= 2.0)
    {
        up = -1;
    }
    if(up == 1)
        height += 0.2;
    else
        height -= 0.2;

    if(h_flag == 1)
        z_fall += 0.5;
    if(z_fall >= 5.125 and boundary == 0)
    {
        cout << "---------------------------------" << endl;
        cout << "   Oops!!! BEWARE of the holes.  " << endl;
        cout << "---------------------------------" << endl;
        exit(0);
    }
    if(z_fall >= 10 and boundary == 1)
    {
        cout << "----------------------------------------------" << endl;
        cout << "   GOSH!!! I should have learnt to swim!!!!   " << endl;
        cout << "----------------------------------------------" << endl;
        exit(0);
    }

     glutPostRedisplay();
     glutTimerFunc(150,update, 0);
}

void handleKeyPress1( unsigned char key, int x, int y ) {

    if(key == 27)
    {
        cout << "----------------------------" << endl;
        cout << "   Thanks for playing!!!!   " << endl;
        cout << "----------------------------" << endl;
        exit(0);
    }
    if(key == 'b')
    {
        if(tile_view == 0)
        {
            rotate_x = 0;
            rotate_y = 0;
            tile_view = 1;
        }
        else
        {
            rotate_x = 30;
            rotate_y = 45;
            tile_view = 0;
        }
    }
    if(tile_view == 1)
    {
            if(key == 'd')
            {
                if(x_tile < 10.5)
                     x_tile += 1.0;
            }
            if(key == 'a')
            {
                if(x_tile > 1.5)
                   x_tile -= 1.0;
            }
            if(key == 'w')
            {
                if(z_tile > -13.5)
                z_tile -= 1.0;
            }
            if(key == 'x')
            {
                if(z_tile < -4.5)
                z_tile += 1.0;
            }
    }
    if(key == 'v')
    {
        if(hover_view == 0)
        {
            rotate_x = 30;
            rotate_y = 45;
            hover_view = 1;
        }
        else
        {
            rotate_x = 30;
            rotate_y = 45;
            hover_view = 0;
        }
    }
    if(key == 'h')
    {
        if(hel_view == 0)
        {
            rotate_x = 0;
            rotate_y = 0;
            hel_view = 1;
        }
        else
        {
            rotate_x = 30;
            rotate_y = 45;
            hel_view = 0;
        }
    }
    if(key == 'f')
    {
        if(person_view == 0)
        {
            rotate_x = 0;
            rotate_y = 0;
            person_view = 1;
        }
        else
        {
            rotate_x = 30;
            rotate_y = 45;
            person_view = 0;
        }
    }
    if(key == 'p')
    {
        if(t_person_view == 0)
        {
            rotate_x = 0;
            rotate_y = 0;
            t_person_view = 1;
        }
        else
        {
            rotate_x = 30;
            rotate_y = 45;
            t_person_view = 0;
        }
    }
    if(key == 'j')
    {
        if(h_flag == 1)
            jump = 0;
        else
            jump = 1;
    }
    if(key == 't')
    {
        if(tower_view == 0)
        {
            rotate_x = 55;
            rotate_y = 30;
            tower_view = 1;
        }
        else 
        {
            tower_view = 0;
            rotate_x = 30;
            rotate_y = 45;
        }
    }
    if(tower_view == 1)
    {
        if (key=='q')
        {
            xrot += 1;
            if (xrot > 360) xrot -= 360;
        }

        if (key=='z')
        {
            xrot -= 1;
            if (xrot < -360) xrot += 360;
        }

        if (key=='w')
        {
            float xrotrad, yrotrad;
            {
                yrotrad = (yrot / 180 * PI);
                xrotrad = (xrot / 180 * PI);
                xp += float(sin(yrotrad)) ;
                zp -= float(cos(yrotrad)) ;
                yp -= float(sin(xrotrad)) ;
            }
        }

        if (key=='s')
        {
            float xrotrad, yrotrad;
            yrotrad = (yrot / 180 * PI);
            xrotrad = (xrot / 180 * PI);
            xp -= float(sin(yrotrad));
            zp += float(cos(yrotrad)) ;
            yp += float(sin(xrotrad));
        }

        if (key=='d')
        {
            yrot += 1;
            if (yrot > 360) yrot -= 360;
        }

        if (key=='a')
        {
            yrot -= 1;
            if (yrot < -360)yrot += 360;
        }
    }
}

void drawBlock(float x1 , float y1 , float x2 , float y2)
{
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void drawLine(float x1 , float y1 , float x2 , float y2)
{
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}
