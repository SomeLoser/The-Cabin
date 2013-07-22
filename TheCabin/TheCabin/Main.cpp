#include <iostream>
#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "IL\il.h"
#include "AL\al.h"
#include "AL\alut.h"
#include "Buttons.h"

#include "Buttons.h"
//#include "character.h"

using namespace std;

//functions prototypes
void initGL();
void initAL();
void initGame();
void destroyGame();

//event handlers
void display();
void keyboard(unsigned char key, int x, int y);
void mouseButton(int state, int button, int x, int y);
void mousePassive(int x, int y);
void update(int value);

void drawCharacerMenu();

//variables and constants

Buttons backButton;
Buttons forwardButton;

const int FPS = 27;
const int BOUND = 100;

GLuint texID[6]; //ID's for the textures
ALuint bgmusic; //ID for the audio

//the ID for the buffer we need (audio)

ALuint bufferID[3];

int windowWidth = 800;
int windowHeight = 800;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("The Cabin");

	//GLEW initialization

	GLenum err = glewInit();

	if(err != GLEW_OK)
	{
		cerr << "GLEW failed to load" << endl;
		cin.get();
		return 0;
	}

	//DevIL initialization

	ilInit();

	cerr << "DevIL Info:" << endl;
	cerr << " IL Version: " << endl;

	//ALUT+OpenAL initialization

	alutInit(&argc, argv);

	initGL();
	initAL();
	initGame();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(FPS, update, 0);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mousePassive);
	glutMainLoop();
	
	//this handles all of your clean up 
	destroyGame();
	return 0;
}

void initGL()
{
	//these are the current versions of OpenGL

	string versions[15] = 
	{
		"GL_VERSION_1_1",
		"GL_VERSION_1_2",
		"GL_VERSION_1_3",
		"GL_VERSION_1_4",
		"GL_VERSION_1_5",
		"GL_VERSION_2_0",
		"GL_VERSION_2_1",
		"GL_VERSION_3_0",
		"GL_VERSION_3_1",
		"GL_VERSION_3_2",
		"GL_VERSION_3_3",
		"GL_VERSION_4_0",
		"GL_VERSION_4_1",
		"GL_VERSION_4_2",
		"GL_VERSION_4_3"
	};

	//Determine which versions are safe to use

	cerr << "OpenGL+GLEW Info: " << endl;

	for(int i = 0; i < 15; ++i)
	{
		if (glewIsSupported(versions[i].c_str()))
			cerr << versions[i] << " is supported" << endl;
		else
			cerr << "ERROR: " << versions[i] << " is not supported" << endl;
	}

	cerr << endl << "OpenGL " << glGetString (GL_VERSION)
		 << " is the current OpenGL version" << endl << endl;

	glClearColor(0,0,0.25,0);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
				  GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//setup the camera

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-BOUND,BOUND,-BOUND,BOUND,-BOUND,BOUND);

	//enable access to the alpha channel

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//handle to file for loading images

	ILuint file[6];

	for(int i = 0; i < 6; ++i)
	{
	
	glGenTextures(1, &texID[i]);

	//just like OpenGL, you need to specify how many images you want to generate

	ilGenImages(1, &file[i]);

	//tie the current image DevIL is working with handle

	ilBindImage(file[i]);

	//safty check

	bool success = ilLoadImage(("Content\\tex" + std::to_string(i+1) + ".png").c_str());;

	if(success)
	{
		//convert the picel data into a usable format

		success = ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);

		if(!success)
		{
			//if an image failed to load, exit out

			cerr << "Failed to load image via DevIL" << endl;
			glutLeaveMainLoop();
			return;
		}

		glBindTexture(GL_TEXTURE_2D, texID[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

		//pull th necessary information from the image DevIL loaded and bind it to an OpenGL texture

		glTexImage2D(GL_TEXTURE_2D,0,ilGetInteger(IL_IMAGE_BPP), 
					 ilGetInteger(IL_IMAGE_WIDTH),
					 ilGetInteger(IL_IMAGE_HEIGHT),
					 0, ilGetInteger(IL_IMAGE_FORMAT),
					 GL_UNSIGNED_BYTE, ilGetData());

		//since we don't need the original image anymore, remove it from memory

		ilDeleteImages(1, &file[i]);
	}

	}
}

void initAL()
{
    //for the current sound, create a position
    ALfloat listenerPos[3] = {0,0,0};
    
    //and the velocity of the sound (for doplar effects)
    ALfloat listenerVel[3] = {0,0,0};

    //first 3 arguments: the "At" vector 
    //(forward direction of listener)
    //second 3 arguments: the "Up" vector 
    //(perpendicular vector to "At")
    ALfloat listenerDirection[6] = 
    { 0.0, 0.0, 0.0,  0.0, 1.0, 0.0 };

	//Set the source and listener to the same location
    //set the values here for AL_POSITION, 
    //AL_VELOCITY, and AL_ORIENTATION
    alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerDirection);

	for(int i = 0; i < 3; ++i)
	{
    //load the wav file into memory
    bufferID[i] = alutCreateBufferFromFile(("Content\\sound" + std::to_string(i + 1) + ".wav").c_str());
    
    // Create sound buffer and source
    alGenSources(1, &bgmusic);
    alSourcei(bgmusic, AL_BUFFER, bufferID[i]);

    alSourcei(bgmusic, AL_REFERENCE_DISTANCE, 1.0);
    alSourcei(bgmusic, AL_SOURCE_RELATIVE, AL_TRUE);     
    alSourcefv(bgmusic, AL_POSITION, listenerPos);

    //to play sound
	//alSourcePlay(bgmusic[3]);

    //the major function calls to play sound are:
    //alSourcePlay(bgmusic);    //plays a sound
    //alSourcePause(bgmusic);   //pauses the sound
    //alSourceStop(bgmusic);    //stops playback of sound
    //alSourceRewind(bgmusic);  //sets playback position to beginning
	}
}

void drawCharacerMenu()
{
	int x = 0;
	int y = 0;

	float w = BOUND;
	float h = BOUND;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texID[0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(-w + x, h + y);
		glTexCoord2f(0,1); glVertex2f(-w + x, -h + y);
		glTexCoord2f(1,1); glVertex2f(w + x, -h + y);
		glTexCoord2f(1,0); glVertex2f(w + x, h + y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-BOUND,BOUND,-BOUND,BOUND,-BOUND,BOUND);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawCharacerMenu();

	glutSwapBuffers();
}

void initGame()
{
	//game initializations
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: glutLeaveMainLoop(); break;
	case 'h': cerr << "help menu here" << endl;
	
	default: break;
	}
	glutPostRedisplay();
}

void destroyGame()
{
	for(int i = 0; i < 6; ++i)
	{
	//unload the textures form memory 
	glDeleteTextures(1,&texID[i]);
	}

	for(int j = 0; j < 3; ++j)
	{
	//remove the buffer from memory
	alDeleteBuffers(1,&bufferID[j]);
	//remove the sound from memory 
	alDeleteSources(1,&bgmusic);
	//allows ALUT to perform a clean exit
	}
	alutExit();
}

void update(int value)
{

	glutTimerFunc(FPS, update, 0);

	glutPostRedisplay();
}

void mouseButton(int state, int button, int x, int y)
{
	x = -1 * ((windowWidth / 2) - x - 1);
	y = ((windowHeight / 2) -y -1);

	x = (x / (windowWidth / 2.0)) *100;
	y = (y / (windowHeight / 2.0)) *100;

	button = (1 << button);


}

void mousePassive(int x, int y)
{
	x = -1 * ((windowWidth / 2) - x - 1);
	y = ((windowHeight / 2) - y - 1);

	x = (x / (windowWidth / 2.0)) *100;
	y = (y / (windowHeight / 2.0)) *100;

	//if()
	//{

	//}
	//else
	//{

	//}

	glutPostRedisplay();
}

