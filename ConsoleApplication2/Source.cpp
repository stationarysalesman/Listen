#include <gl/glut.h>
#include <stdio.h>
#include "audio.h"
#include "audio2.h"
#include "MyAudioSink.h"
void init();
void display(void);
void centerOnScreen();
void drawObject();
HANDLE mutex; /* mutex for shared buffer */
HANDLE captureThread; /* a thread */
DWORD ThreadID; /* hold threadid */
float input[1024]; /* Shared buffer for audio data */



//  define the window position on screen
int window_x;
int window_y;
 
//  variables representing the window size
int window_width = 960;
int window_height = 540;
 
//  variable representing the window title
char *window_title = "dicks out for Harambe";

/* Thread entry point for audio capture thread */
void get_audio()
{
	/* Record some audio */
	MyAudioSink pMySink(input);
	RecordAudioStream(&pMySink);
}

/* Thread entry point for graphic display thread
	Currently also the main/calling thread */
void display_audio()
{

}
/*	Main entry point.

	Split off into two threads, one for capturing audio, 
	and one for processing that audio data and displaying it on 
	the screen.

*/
int main(int argc, char **argv)
{
	/* Initialize the mutex and give it to me
	(the caller/processing and graphics thread) */
	mutex = CreateMutex(NULL, TRUE, NULL);
	if (mutex == NULL) 
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	/* Initialize the audio capture thread */
	captureThread = CreateThread(
					NULL,	/* security attributes */
					0,		/* default stack size */
					(LPTHREAD_START_ROUTINE) get_audio,
					NULL,	/* no thread function arguments */
					0,		/* default creation flag */
					&ThreadID);

	

    //  Connect to the windowing system + create a window
    //  with the specified dimensions and position
    //  + set the display mode + specify the window title.
    glutInit(&argc, argv);
    //centerOnScreen();
	window_x = 0;
	window_y = 0;
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(window_x, window_y);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(window_title);
 
    //  Set OpenGL program initial state.
    init();
 
    // Set the callback functions
    glutDisplayFunc(display);
 
    //  Start GLUT event processing loop
    glutMainLoop();
}
 
//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init()
{
    //  Set the frame buffer clear color to black. 
    glClearColor(0.0, 0.0, 0.0, 0.0);
}
 
//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//  OpenGL contents on the window.
//-------------------------------------------------------------------------
void display(void)
{
    //  Clear the window or more specifically the frame buffer...
    //  This happens by replacing all the contents of the frame
    //  buffer by the clear color (black in our case)
    glClear(GL_COLOR_BUFFER_BIT);
 
    //  Draw object
    drawObject();
 
    //  Swap contents of backward and forward frame buffers
    glutSwapBuffers();
}
 
//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------
void drawObject()
{
    //  Draw sphere
	glutWireTeapot(.3);
	glutWireTeapot(.2);
	glutWireTeapot(.4);
}
 
//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen()
{
    window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
    window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}