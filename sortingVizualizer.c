#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include "GL/glut.h"
#include <math.h>
#define MAXWIDTH 1080
#define MAXHEIGHT 1080
  
void * font = GLUT_BITMAP_8_BY_13; //font used	
int globalArray[MAXWIDTH];
int n=0;
int index = 0;
int jindex = 0;
int swappedone = -1;
int swappedtwo = -1;
int sortedThreshold = -1;
int greenCounter = 0;
bool sorted = true;
bool sortingAlgorythmEnded = false;
void bubbleSort(void);
typedef void (*FunctionPtr)(void);
FunctionPtr functionPointerArray[] = {bubbleSort};

struct {
	char* name;
	bool sorted;
	bool ended;
	bool shuffle;
} AlgroythmMetaData[1];

  void draw() {
	drawArray();
	if(sortingAlgorythmEnded) {
		drawSortedArray();
	}  	      
    if(!sorted) {
    	functionPointerArray[0]();    	
    }   
}

void drawArray() {
	int n = sizeof(globalArray) / sizeof(globalArray[0]);
    int i;
        for (i = 0; i < n; i++){
        	glColor3f(1,1,1);  
			if(i == swappedone || i == swappedtwo) {
				glColor3f(1,0,0);  
			}  		             	
			if(sorted) {
				glColor3f(1,1,1);  	
			}
			glBegin(GL_LINES);
			glLineWidth(1);
      		glVertex2i(i, MAXWIDTH);
  			glVertex2i(i, MAXWIDTH-globalArray[i]);  
        }		
        glEnd();
}

void drawSortedArray() {
	int i;
	if(greenCounter < n) {
		glBegin(GL_LINES);
		glLineWidth(1);
		for (i = 0; i < n; i++){
			glColor3f(1,1,1);  
        	if(i <= greenCounter) {
        		glColor3f(0,1,0);  
        	}
        	if(i ==  greenCounter) {
        		glColor3f(1,0,0);
        	}
      		glVertex2i(i, MAXWIDTH);
  			glVertex2i(i, MAXWIDTH-globalArray[i]);    					        
        }
        glEnd();
        greenCounter++;
        glutPostRedisplay(); 
	} else {
		sortingAlgorythmEnded = false;
	}	                
}

void buttonPressed(unsigned char key, int x, int y) {
  	if(key == 'a') {
  		sorted = false;
  		sortingAlgorythmEnded = false;
  	}  	
  	if(key == 's') {
  		n = sizeof(globalArray) / sizeof(globalArray[0]);
  		sorted = false;
  		sortingAlgorythmEnded = false;
  		index = 0;
  		jindex = 0;
  		shuffleArray();
  	}
  	glutPostRedisplay();
  }
  
  void display() 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    glutSwapBuffers();
  }

  void initArray() {
  	int i;
  	for (i = 0; i < MAXWIDTH; i++) {
        globalArray[i] = i;
    }
    
  }
  
void shuffleArray() {
    srand(time(NULL));
    
    int i;
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        
        int temp = globalArray[i];
        globalArray[i] = globalArray[j];
        globalArray[j] = temp;
    }
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
	if(index <= n-1){
		swapped = false;
        for (jindex = 0; jindex < n - index - 1; jindex++) {
            if (globalArray[jindex] > globalArray[jindex + 1]) {
                swap(&globalArray[jindex], &globalArray[jindex + 1]);
                swapped = true;               
				swappedone = jindex;
                swappedtwo = jindex + 1;   
            }                                             
        }
		
		if (swapped == false){
			sorted = true;
			sortingAlgorythmEnded = true;			
		}            
		
		index++;
		glutPostRedisplay();
	}	
}

void printArray()
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", globalArray[i]);
	printf("\n");        
}

  void init() 
  {
  	initArray();  		
	glClearColor(0,0,0,0);
	gluOrtho2D(0, MAXWIDTH,MAXHEIGHT,0);		
  }

  int main(int argc, char** argv) 
  {
  	n = sizeof(globalArray) / sizeof(globalArray[0]);  	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);    
    glutCreateWindow("Sorting Visualizer");
    glutDisplayFunc(display);
    glutKeyboardFunc(buttonPressed);
    init();   
    glutMainLoop();    
}
