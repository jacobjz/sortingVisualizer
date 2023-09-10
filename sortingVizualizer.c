#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include "GL/glut.h"
#include <math.h>
#include "algostate.h"
#define MAXWIDTH 1920

int * array;
void * font = GLUT_BITMAP_8_BY_13;

AlgorythmState status = def;
int index = 0;
int jindex = 0;
int swappedone = -1;
int swappedtwo = -1;
int greenCounter = 0;

struct {
	char* name;
	AlgorythmState state;
} AlgroythmMetaData[1];

void draw() {  	
	if(status == shuffled) {
		shuffleArray();
	}	
	if(status == sorting) {
		functionPointerArray[0]();
	}
	if(status == sorted) {
		drawSortedArray();
	}
	if(status == idle){
		drawArray();
		printf("end idle");
	}			
}

void drawArray() {
    int i = 0;
    glBegin(GL_LINES);
	glColor3f(1,1,1);
	glLineWidth(1);	
	while(i < MAXWIDTH) {
		glVertex2i(i, MAXWIDTH);
  		glVertex2i(i, MAXWIDTH-array[i]); 
  		i++;
	}
	
	glEnd();	              
}

void drawSortedArray() {
	int i=0;
	if(greenCounter < MAXWIDTH) {
		glBegin(GL_LINES);
		glLineWidth(1);	
		while(i < MAXWIDTH){
			glColor3f(1,1,1);
        	if(i <= greenCounter) {
        		glColor3f(0,1,0);  
        	}
        	if(i ==  greenCounter) {
        		glColor3f(1,0,0);
        	}
      		glVertex2i(i, MAXWIDTH);
  			glVertex2i(i, MAXWIDTH-array[i]);    					        
			i++;
		}	 
        glEnd();
        greenCounter++;        
	} else {
		status = idle;
	}	               
	glutPostRedisplay();  
}

void buttonPressed(unsigned char key, int x, int y) {
  	if(key == 'a') {
  		index = MAXWIDTH;
		status = shuffled;
  	}  	 
  	if(key == 's') {
  		index = 0;
		status = sorting;
  	}  	 
  	glutPostRedisplay();
  }
  
void shuffleArray(void) {
    srand(time(NULL));
    if(index > 0) {
		int i;
		for(i = 0; i < 10; i++) {
			int j = rand() % (index + 1);        
        	int temp = array[index];
        	array[index] = array[j];
        	array[j] = temp;
		}
    	index--;    	
    }
    drawArray();
    glutPostRedisplay();
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(void)
{
	bool swapped;
	if(index <= MAXWIDTH-1){
		swapped = false;
        for (jindex = 0; jindex < MAXWIDTH - index - 1; jindex++) {
            if (array[jindex] > array[jindex + 1]) {
                swap(&array[jindex], &array[jindex + 1]);
                swapped = true;               
				swappedone = jindex;
                swappedtwo = jindex + 1;   
            }                                             
        }
        
		index++;
		
		if (swapped == false){
			status = sorted;
			greenCounter = 0;			
		}				
		drawArray();					         	
		glutPostRedisplay();				
	}	
}

  
  void initArray() {
  	int i;
  	for (i = 0; i < MAXWIDTH; i++) {        
        array[i] = i;
    }
    
  }
  
  void init() 
  {
  	initArray();  
	glClearColor(0,0,0,0);
	gluOrtho2D(0, MAXWIDTH,MAXWIDTH,0);		
  }
  
  void display() 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    glutSwapBuffers();
  }
  
  int main(int argc, char** argv) 
  {
  	array = (int *) malloc(MAXWIDTH*sizeof(int)); 	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);    
    glutCreateWindow("Sorting Visualizer");
    glutDisplayFunc(display);
    glutKeyboardFunc(buttonPressed); 
    init();   
    glutMainLoop();
}
