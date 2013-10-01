
#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include "glm.cpp"

using namespace std;
 float RADIUS = 4.0f; //The radius of the sphere
int cnt=1;
#define PI 3.14159265
float _angle=0.0f;
float cor_y=0.0f;
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
GLMmodel* pmodel1 = NULL;
GLMmodel* pmodel2 = NULL;

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
    while(group){
	if((cnt&1)==1)
	{
		if(!strcmp(group->name," upper_left"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);	
		}
		if(!strcmp(group->name," lower_left"))
    		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);	

		}
		if(!strcmp(group->name," upper_right"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_lower"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_shoe"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(-20.0,1.0,0.0,0.0);

		}
		if(!strcmp(group->name," left_shoe"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
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
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_shoe"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);

		}
		if(!strcmp(group->name," left_shoe"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
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
	//	    cout<<"In"<<endl;
	//	    cout<<group->name<<endl;
		    glRotatef(-20.0,1.0,0.0,0.0);	
	    }
	    if(!strcmp(group->name," lower_left"))
	    {
	//	    cout<<"In"<<endl;
	//	    cout<<group->name<<endl;
		    glRotatef(-20.0,1.0,0.0,0.0);	

	    }
	    if(!strcmp(group->name," upper_right"))
	    {
	//	    cout<<"In"<<endl;
	//	    cout<<group->name<<endl;
		    glRotatef(20.0,1.0,0.0,0.0);
	    }
	    if(!strcmp(group->name," right_lower"))
	    {
//		    cout<<"In"<<endl;
//		    cout<<group->name<<endl;
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
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);	
		}
		if(!strcmp(group->name," lower_left"))
    		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);	

		}
		if(!strcmp(group->name," upper_right"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_lower"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(-20.0,1.0,0.0,0.0);
		}
		if(!strcmp(group->name," right_shoe"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(-20.0,1.0,0.0,0.0);

		}
		if(!strcmp(group->name," left_shoe"))
		{
	//		cout<<"In"<<endl;
	//		cout<<group->name<<endl;
			glRotatef(20.0,1.0,0.0,0.0);
		}
	}
	//cnt+=1;
        group = group->next;
    }
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
		case 's':
			_highShininess = !_highShininess;
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
			if(!ca)
				ca=1;
			else
				ca=0;
	}
}
void camera()
{
	gluLookAt(0.0,0.0,-10,cor_x,cor_y,cor_z,0,-1,0);
}
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
	_angle+=-1.0;
    }
    if(key==GLUT_KEY_RIGHT)
    {
	 if(keypressright==0)
		 cnt=1;
	keypressright=1;
	_angle+=1.0;
    }
    if(key==GLUT_KEY_DOWN)
    {
	 if(keypressdown==0)
		 cnt=1;
	cnt+=1;
	//cout<<_angle<<endl;
	cor_x-=0.5*sin(_angle*PI/180);
	cor_z-=0.5*cos(_angle*PI/180);
	keypressdown=1;
    }
    if(key==GLUT_KEY_UP)
    {
	 if(keypressup==0)
		 cnt=1;
	cnt+=1;
	//cout<<_angle<<endl;
	cor_x+=0.5*sin(_angle*PI/180);
	cor_z+=0.5*cos(_angle*PI/180);
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

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
		cor_x+=0.05*sin(_angle*PI/180);
		cor_z+=0.05*cos(_angle*PI/180);
		
	}
	if(jump2)
	{
		inc-=0.2;
		cor_x+=0.05*sin(_angle*PI/180);
		cor_z+=0.05*cos(_angle*PI/180);
	}
	if(inc-0<0.0001)
	{
		jump2=0;
		inc=0.0;
	}
	
	cout<<cor_x<<" "<<cor_y<<" "<<cor_z<<endl;
	if(ca)
	{
		gluLookAt(cor_x,cor_y+inc,cor_z-2,cor_x+(0.5)*sin(_angle),cor_y-1,cor_z+(0.5)*cos(_angle),0.0,1.0,0.0);
	}
	glPushMatrix();
	glTranslatef(cor_x, cor_y+inc, cor_z);
	//cout<<_angle<<endl;
	glRotatef(_angle,0,1,0);
/*	if(keypressright)
	{
		glRotatef(90,0,1,0);
		//DrawGroup(pmodel1,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL,left_lower);
		//DrawGroup(pmodel1,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL,right_upper);
	}*/
//	glRotatef(_angle, 0, 1, 0);
	
	/*
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos[] = {1.5f * RADIUS, 2 * RADIUS, 1.5 * RADIUS, 1.0f};
	//Diffuse (non-shiny) light component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	//Specular (shiny) light component
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	*/

	/*
	//Determine the specularity, emissivity, and shininess parameters, based on
	//variables that can be toggled with keystrokes
	float specularity;
	if (_lowSpecularity) {
		specularity = 0.3f;
	}
	else {
		specularity = 1;
	}
	
	float emissivity;
	if (_emission) {
		emissivity = 0.05f;
	}
	else {
		emissivity = 0;
	}
	
	float shininess;
	if (_highShininess) {
		shininess = 25;
	}
	else {
		shininess = 12;
	}
	
	//The color of the sphere
	GLfloat materialColor[] = {0.2f, 0.2f, 1.0f, 1.0f};
	//The specular (shiny) component of the material
	GLfloat materialSpecular[] = {specularity, specularity, specularity, 1.0f};
	//The color emitted by the material
	GLfloat materialEmission[] = {emissivity, emissivity, emissivity, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); //The shininess parameter
	
	//Draw the sphere
	glutSolidSphere(RADIUS, 150, 80);
	*/
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
	DrawGroup(pmodel1, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
//	gluLookAt(cor_x, cor_y, cor_z,cor_x, cor_y,  cor_z,0.0f, 1.0f,  0.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -2.5, -15);	
	//gluLookAt(0, 1.5,0, 0,  0,0, 0.0f,1.0f,  0.0f);
	glScalef(6,6,6);
	if (!pmodel2) 
	{
		// this is the call that actualy reads the OBJ and creates the model object
		char *temp = new char[20];
		strcpy(temp, "groundfinal.obj");
		pmodel2 = glmReadOBJ(temp);	
		if (!pmodel2) exit(0);
		glmUnitize(pmodel2);
		glmFacetNormals(pmodel2);        
		glmVertexNormals(pmodel2, 90.0);
                glmLinearTexture(pmodel2);
                glmSpheremapTexture(pmodel2);
	}
	ran=rand()%13;
	DrawGroup(pmodel2, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	glPopMatrix();
	//glPushMatrix();
	//camera();
	//glPopMatrix();
	glScalef(0.1,0.1,0.1);
	glutSwapBuffers();
}
void update(int value) {
	
//	_angle += 1.5f;
//	if (_angle > 360) {
//		_angle -= 360;
//	}
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("Materials - videotutorialsrock.com");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutSpecialFunc(handleKeypress);
	glutMainLoop();
	return 0;
}	
