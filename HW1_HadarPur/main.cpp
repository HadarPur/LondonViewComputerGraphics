//
//  main.cpp
//  HW1_HadarPur
//
//  Created by Hadar Pur on 16/07/2018.
//  Copyright © 2018 Hadar Pur. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14
#define MAX_HEIGHT 0.8
#define MIN_HEIGHT 0.6
#define BUILDING_WIDTH 0.1
#define BUILD_START_X -1
#define BUILD_END_X -0.7
#define MAX_X 1
#define BUILD_START_TOWER_X -0.8
#define BUILD_START_TOWER_X1 -0.35
#define BUILD_END_TOWER_X -0.2
#define BUILD_END_TOWER_X1 -0.55
#define FIRST_FLOOR 0.02
#define WINDOW_HEIGHT 0.03
#define WINDOW_START_WIDTH 0.02
#define WINDOW_END_WIDTH 0.01
#define WINDOW_WIDTH 0.01
#define FLOOR_SPACE 0.02
#define ROOF_HEIGHT 0.15

#define BUILD_START_BRIDGE -0.4
#define BUILD_START_BRIDGE_X1 -0.15
#define BUILD_END_BRIDGE_X1 0
#define BUILD_START_BRIDGE_X2 0.6
#define BUILD_END_BRIDGE_X2 0.75
#define BUILD_END_BRIDGE 1

#define START_X -1
#define END_X 1
#define START_Y -1
#define END_Y 1
#define MIDDLE 0

const int NUM_STARS = 500;
const int NUM_OF_BUILDINGS = 30;
const int NUM_OF_WINDOWS = 150;

double stars[2][NUM_STARS];
double buildings[2][NUM_OF_BUILDINGS];
double windows[NUM_OF_WINDOWS][NUM_OF_WINDOWS];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// init methods //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initStars()
{
    for (int i = 0; i < NUM_STARS; i++)
    {
        // random value in [-1, 1]
        stars[0][i] =-1 + 2*(rand() % 1000)/1000.0;
        
        // random value in [0.5, 1]
        stars[1][i] = 0.5 + (rand() % 1000) / 1000.0;
    }
}

void initWindows()
{
    for(int i = 0; i < NUM_OF_WINDOWS ; i++)
    {
        for(int j=0 ; j < NUM_OF_WINDOWS ; j++)
        {
            windows[i][j] = (rand() % 100) / 100.0;
        }
    }
}

void initBuildings()
{
    int j = 0;
    double y;
    double random;
    
    for (double x = BUILD_START_X ; x <= MAX_X ;  x += BUILDING_WIDTH)
    {
        y = 0.8*sin(10*x)*sin(10 * x);
        random = ((float) rand()) / (float) RAND_MAX;

        //random between [0.2,0.5]
        buildings[0][j] = (MAX_HEIGHT-MIN_HEIGHT)*random + MIN_HEIGHT;
        // random roof
        buildings[1][j] =  (rand()%2)+1;

        j++;
    }
}

void init()
{
    // sets window background color
    glClearColor(0.0,0.0,0,0);

    //init stars
    initStars();
    
    //init buildings
    initBuildings();

    //init windows
    initWindows();
    
    //define cubic of the drawing world - definition of the origins points
    glOrtho(-1, 1, -1, 1, -1, 1); // sets the range of the points location
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// sky drawing methods //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawUpperMoon()
{
    int num = 40;
    double rad = 0.1;
    glLoadIdentity();
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 1, 0.8);
    glVertex2d(-0.6, 0.8);
    for (int i=0; i<= num; i++)
    {
        glColor3d(0, 0, 0.4);
        glVertex2d(rad*cos((i*PI*2)/num)-0.6, rad*sin((i*PI*2)/num)+0.8);
    }
    glEnd();
}

void drawReflactionMoon()
{

    int num =40;
    double rad = 0.1;
    glLoadIdentity();
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 1, 0.8);
    glVertex2d(-0.6, -0.8);
    for (int i=0; i<= num; i++)
    {
        glColor3d(0, 0, 0.3);
        glVertex2d(rad*cos((i*PI*2)/num)-0.6, rad*sin((i*PI*2)/num)-0.8);
    }
    glEnd();
}

void drawUpperSky()
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.4);
    glVertex2d(START_X, END_Y);
    glVertex2d(END_X, END_Y);
    glColor3d(0.5, 0.1, 0.6);
    glVertex2d(END_X, MIDDLE);
    glVertex2d(START_X, MIDDLE);
    glEnd();
}

void drawReflactionSky()
{
    glBegin(GL_POLYGON);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(END_X,MIDDLE);
    glVertex2d(START_X, MIDDLE);
    glColor3d(0, 0, 0.3);
    glVertex2d(START_X, START_Y);
    glVertex2d(END_X, START_Y);
    glEnd();
    
}

void drawUpperStars()
{
    // add stars
    glColor3d(1, 1, 0);//yellow
    for (int i = 0; i < NUM_STARS ; i++)
    {
        glPointSize(rand() % 2 + 0.5);
        glBegin(GL_POINTS);
        glVertex2d(stars[0][i], stars[1][i]);
        glVertex2d(stars[0][i], -stars[1][i]);

        glEnd();
    }
}

void drawMiddleLineSeperation()
{
    glLineWidth(0.02);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0.4);
    glVertex2d(-1, 0);
    glVertex2d(1, 0);
    glEnd();
}

void drawSky()
{
    //draw upper sky
    drawUpperSky();
    //draw reflaction sky
    drawReflactionSky();
    
    //draw moon
    drawUpperMoon();
    //draw reflaction moon
    drawReflactionMoon();
    
    //draw stars
    drawUpperStars();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// buildings drawing methods ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// roofs drawing methods ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void drawRoof(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.4);
    glVertex2d(x, y);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(x + 1.7*BUILDING_WIDTH/2 , y+ROOF_HEIGHT);
    glColor3d(0, 0, 0.2);
    glVertex2d(x + 1.7*BUILDING_WIDTH, y);
    glEnd();
}

void drawReflactionRoof(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, y);
    glVertex2d(x + 1.7*BUILDING_WIDTH/2 , y - ROOF_HEIGHT);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(x + 1.7*BUILDING_WIDTH, y);
    glEnd();
    
}

void drawLowerRoof(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, y);
    glColor3d(0.4, 0.4, 0.5);
    glVertex2d(x + BUILDING_WIDTH , y + ROOF_HEIGHT/3);
    glColor3d(0, 0, 0.1);
    glVertex2d(x + BUILDING_WIDTH, y);
    glEnd();
}


void drawReflactionLowerRoof(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, y);
    glVertex2d(x + BUILDING_WIDTH, y - ROOF_HEIGHT/3);
    glColor3d(0.4, 0.4, 0.5);
    glVertex2d(x + BUILDING_WIDTH, y);
    glEnd();
    
}

void drawTowerOfLondonRoof(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, y);
    glColor3d(0.2, 0.2, 0.6);
    glVertex2d(x + BUILDING_WIDTH/4 , y + ROOF_HEIGHT);
    glColor3d(0, 0, 0.2);
    glVertex2d(x + BUILDING_WIDTH/2, y);
    glEnd();
}

void drawBridgeRoof(double x, double y, double half)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0);
    glVertex2d(x, y);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(x + BUILDING_WIDTH/4 , y + ROOF_HEIGHT/half);
    glColor3d(0, 0, 0);
    glVertex2d(x + BUILDING_WIDTH/2, y);
    glEnd();
}

void drawReflactionTowerOfLondonRoof(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, y);
    glVertex2d(x + BUILDING_WIDTH/4 , y - ROOF_HEIGHT);
    glColor3d(0.2, 0.2, 0.6);
    glVertex2d(x + BUILDING_WIDTH/2, y);
    glEnd();
}

void drawBridgeReflactionRoof(double x, double y, double half)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.1);
    glVertex2d(x, y);
    glVertex2d(x + BUILDING_WIDTH/4 , y - ROOF_HEIGHT/half);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(x + BUILDING_WIDTH/2, y);
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// windows drawing methods //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void drawWindow(double startX, double startY, int i, int j)
{
    glColor3d(windows[i][j], windows[i][j], 0);
    glBegin(GL_POINTS);
    glVertex2d(startX, startY);
    glEnd();
}

void draReflactionwWindow(double startX, double startY, int i, int j)
{
    glColor3d(windows[i][j]/2, windows[i][j]/2, 0);
    glBegin(GL_POINTS);
    glVertex2d(startX, startY);
    glEnd();
}

void drawWindow(double startX, double startY)
{
    glPointSize(2);
    glColor3d(0.5, 0.5, 0);
    glBegin(GL_POINTS);
    glVertex2d(startX, startY);
    glEnd();
}

void drawReflactionWindow(double startX, double startY)
{
    glPointSize(2);
    glColor3d(0.25, 0.25, 0);
    glBegin(GL_POINTS);
    glVertex2d(startX, startY);
    glEnd();
}

void drawUpperWindows(double x, double y, double xx, double yy)
{
    glPointSize(2);
    
    // windows
    double startY, startX;
    
    int i = rand() % NUM_OF_WINDOWS;
    int j = rand() % NUM_OF_WINDOWS;
    // pick any matrix element and change it
    windows[i][j] = (rand() % 100) / 100.0;

    i=0;
    for (startY = y + FIRST_FLOOR  ; startY < yy - FLOOR_SPACE; startY += FLOOR_SPACE, i++)
    {
        j=0;
        for(startX = x ; startX < xx - WINDOW_END_WIDTH ; startX += WINDOW_WIDTH, j++)
        {
            drawWindow(startX, startY, i, j);
        }
    }
}

void drawReflactionWindows(double x, double y, double xx, double yy)
{
    glPointSize(2);
    // windows
    double startY, startX;
    
    int i = rand() % NUM_OF_WINDOWS;
    int j = rand() % NUM_OF_WINDOWS;
    // pick any matrix element and change it
    windows[i][j] = (rand() % 100) / 100.0;
    
    i=0;
    for (startY = y - FIRST_FLOOR  ; startY >= yy + FLOOR_SPACE ; startY -= FLOOR_SPACE, i++)
    {
        j=0;
        for(startX = x ; startX < xx - WINDOW_END_WIDTH ; startX += WINDOW_WIDTH, j++)
        {
            draReflactionwWindow(startX, startY, i, j);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// buildings drawing methods /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void drawUpperBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.4);
    glVertex2d(x, yy);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(xx, yy);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, y);
    glEnd();
}

void drawUpperReflactionBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, y);
    glVertex2d(x, y);
    glEnd();
}


void drawUpperLowerBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, yy);
    glColor3d(0.4, 0.4, 0.5);
    glVertex2d(xx, yy);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0.1);
    glVertex2d(x, y);
    glEnd();
}

void drawUpperLowerReflactionBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, y);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonTowerBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glColor3d(0.2, 0.2, 0.6);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonTowerReflactionBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.3);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, y);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonBridgeBuilding(double x, double y, double xx, double yy)
{

    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0);
    glVertex2d(x, yy);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(xx, yy);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0);
    glVertex2d(x, y);
    glEnd();
    
}
void drawLondonBridgeReflactionBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.1);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, y);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonBridgeSidesSectionReflactionBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.1);
    glVertex2d(x, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, yy);
    glVertex2d(xx, y);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonBridgeUpperReflactionBuilding(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.1);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glVertex2d(xx, y);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonHalfBridge(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0);
    glVertex2d(x, yy);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0);
    glVertex2d(xx, yy);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(x, y);
    glEnd();
}

void drawLondonHalfReflactionBridge(double x, double y, double xx, double yy)
{
    glBegin(GL_POLYGON);
    glColor3d(0, 0, 0.1);
    glVertex2d(x, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0.1);
    glVertex2d(xx, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(x, y);
    glEnd();
}

void drawTowerBuildingBorder(double x, double y, double xx, double yy)
{
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, yy);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(xx, yy);
    glVertex2d(xx, y);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, y);
    glEnd();
}

void drawTowerBuildingReflactionBorder(double x, double y, double xx, double yy)
{
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3d(0, 0, 0.2);
    glVertex2d(x, yy);
    glVertex2d(xx, yy);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(xx, y);
    glVertex2d(x, y);
    glEnd();
}

void drawTowerBuildingLine(double x, double y, double xx, double yy)
{
    glBegin(GL_LINE_STRIP);
    glColor3d(0, 0, 0.4);
    glVertex2d(x, y);
    glColor3d(0.4, 0.4, 0.6);
    glVertex2d(xx, yy);
    glEnd();
}

void drawTowerBuildingReflactionLine(double x, double y, double xx, double yy)
{
    glBegin(GL_LINE_STRIP);
    glColor3d(0.5, 0.2, 0.6);
    glVertex2d(x, y);
    glColor3d(0, 0, 0.3);
    glVertex2d(xx, yy);
    glEnd();
}

void sinusRight()
{
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    double x, y;

    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0.4, 0.4, 0.6);
        glVertex2d(x, -y + MAX_HEIGHT-0.2);
        
    }
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0.4, 0.4, 0.6);
        glVertex2d(x, -y + MAX_HEIGHT-0.2);
        glVertex2d(x, 0.15);

    }
    glEnd();
}

void sinusLeft()
{
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    double x, y;
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0.4, 0.4, 0.6);
        glVertex2d(1-x+BUILD_START_BRIDGE, -y + MAX_HEIGHT-0.2);
        
    }
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0.4, 0.4, 0.6);
        glVertex2d(1-x+BUILD_START_BRIDGE, -y + MAX_HEIGHT-0.2);
        glVertex2d(1-x+BUILD_START_BRIDGE, 0.15);
        
    }
    glEnd();
}



void sinusReflactionRight()
{
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    double x, y;
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glVertex2d(x, y - MAX_HEIGHT+0.2);
        glColor3d(0, 0, 0.3);
    }
    
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0, 0, 0.3);
        glVertex2d(x, y - MAX_HEIGHT+0.2);
        glColor3d(0.5, 0.2, 0.6);
        glVertex2d(x, -0.15);
        
    }
    glEnd();
}

void sinusReflactionLeft()
{
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    double x, y;
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0, 0, 0.3);
        glVertex2d(1-x+BUILD_START_BRIDGE, y - MAX_HEIGHT+0.2);
        
    }
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    
    for (x=BUILD_END_BRIDGE_X2; x<BUILD_END_BRIDGE; x+=0.01)
    {
        y = fabs(0.4*cos(2*PI*x));
        glColor3d(0, 0, 0.3);
        glVertex2d(1-x+BUILD_START_BRIDGE, y - MAX_HEIGHT+0.2);
        glColor3d(0.5, 0.2, 0.6);
        glVertex2d(1-x+BUILD_START_BRIDGE, -0.15);
        
    }
    glEnd();
}

void drawWheel()
{
    glLineWidth(2);
    int num = 400;
    double rad = 0.4;
    
    glBegin(GL_LINE_STRIP);
    glColor3d(0.6,0, 0.3);
    glVertex2d(0.8, 0.45);
    for (int i=0; i<= num; i++)
    {
        glVertex2d(rad*cos((i*PI*2)/num)+0.8, rad*sin((i*PI*2)/num)+0.45);
    }
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3d(0.6,0, 0.3);
    for (int i=0; i<= num; i+=10)
    {
        glVertex2d(rad*cos((i*PI*2)/num)+0.8, rad*sin((i*PI*2)/num)+0.45);
        glVertex2d(0.8, 0.45);
    }
    glEnd();
}

void drawReflactionWheel()
{
    glLineWidth(2);
    int num = 400;
    double rad = 0.4;
    
    glBegin(GL_LINE_STRIP);
    glColor3d(0.4, 0.1, 0.4);
    glVertex2d(0.8, -0.45);
    for (int i=0; i<= num; i++)
    {
        glVertex2d(rad*cos((i*PI*2)/num)+0.8, rad*sin((i*PI*2)/num)-0.45);
    }
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3d(0.4, 0.1, 0.4);
    for (int i=0; i<= num; i+=10)
    {
        glVertex2d(rad*cos((i*PI*2)/num)+0.8, rad*sin((i*PI*2)/num)-0.45);
        glVertex2d(0.8, -0.45);
    }
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////// buildings drawing methods ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void drawUpperBuildings()
{
    double x = 0;
    int counter = 0;
    
    // upper part
    for (x = BUILD_START_X ; x < BUILD_END_X; x += BUILDING_WIDTH, counter++)
    {
        drawUpperBuilding(x, MIDDLE, x + 1.7*BUILDING_WIDTH, buildings[0][counter]);
        drawUpperWindows(x + WINDOW_START_WIDTH, MIDDLE , x + 1.7*BUILDING_WIDTH, buildings[0][counter]);
        
        //reflaction
        drawUpperReflactionBuilding(x, MIDDLE, x + 1.7*BUILDING_WIDTH, MIDDLE-buildings[0][counter]);
        drawReflactionWindows(x + WINDOW_START_WIDTH, MIDDLE , x + 1.7*BUILDING_WIDTH, MIDDLE-buildings[0][counter]);

        if (buildings[1][counter] != 1)
        {
            drawRoof(x, buildings[0][counter]);
            drawReflactionRoof(x, MIDDLE-buildings[0][counter]);
        }
        else
        {
            drawUpperBuilding(x + BUILDING_WIDTH/4, buildings[0][counter], x + 1.7*BUILDING_WIDTH - BUILDING_WIDTH/4 , buildings[0][counter] + BUILDING_WIDTH);
            drawUpperWindows(x + BUILDING_WIDTH/4 + WINDOW_START_WIDTH, buildings[0][counter] , x + 1.7*BUILDING_WIDTH - BUILDING_WIDTH/4, buildings[0][counter] + BUILDING_WIDTH*1.2);
            drawUpperBuilding(x + BUILDING_WIDTH/4, MIDDLE - buildings[0][counter], x + 1.7*BUILDING_WIDTH - BUILDING_WIDTH/4 , MIDDLE - buildings[0][counter]- BUILDING_WIDTH);
            drawReflactionWindows(x + BUILDING_WIDTH/4 + WINDOW_START_WIDTH, MIDDLE - buildings[0][counter], x + 1.7*BUILDING_WIDTH - BUILDING_WIDTH/4, MIDDLE - buildings[0][counter] - BUILDING_WIDTH);
        }
    }
}

void drawUpperLowerBuildings()
{
    double x = 0;
    int counter = 0;
    
    // upper part
    for (x = BUILD_START_X+BUILDING_WIDTH/2; x < BUILD_START_BRIDGE-BUILDING_WIDTH/2 ; x += BUILDING_WIDTH/2, counter++)
    {
        drawUpperLowerBuilding(x, MIDDLE, x + BUILDING_WIDTH, buildings[0][counter]/2);
        drawUpperWindows(x + WINDOW_START_WIDTH, MIDDLE , x + BUILDING_WIDTH, buildings[0][counter]/2);
        
        //reflaction
        drawUpperLowerReflactionBuilding(x, MIDDLE, x + BUILDING_WIDTH, MIDDLE-buildings[0][counter]/2);
        drawReflactionWindows(x + WINDOW_START_WIDTH, MIDDLE , x + BUILDING_WIDTH, MIDDLE-buildings[0][counter]/2);
        
        if (buildings[1][counter] != 1)
        {
            drawLowerRoof(x , buildings[0][counter]/2);
            drawReflactionLowerRoof(x, MIDDLE-buildings[0][counter]/2);
        }
    }
}

void drawBridge()
{
    double startRoof;
    int i, j;
    //left roofs
    startRoof = BUILD_START_BRIDGE_X1;
    for (int x = 0 ; x < 3 ; x++)
    {
        if (x != 1)
        {
            drawBridgeRoof(startRoof, MAX_HEIGHT-0.1, 2);
            drawBridgeReflactionRoof(startRoof, MIDDLE-MAX_HEIGHT+0.1, 2);
        }
        else
        {
            drawBridgeRoof(startRoof, MAX_HEIGHT-0.1, 1);
            drawBridgeReflactionRoof(startRoof, MIDDLE-MAX_HEIGHT+0.1, 1);
            
        }
        startRoof += BUILDING_WIDTH/2;
    }
    
    //right roofs
    startRoof = BUILD_START_BRIDGE_X2;
    for (int x = 0 ; x < 3 ; x++)
    {
        if (x != 1)
        {
            drawBridgeRoof(startRoof, MAX_HEIGHT-0.1, 2);
            drawBridgeReflactionRoof(startRoof, MIDDLE-MAX_HEIGHT+0.1, 2);
        }
        else
        {
            drawBridgeRoof(startRoof, MAX_HEIGHT-0.1, 1);
            drawBridgeReflactionRoof(startRoof, MIDDLE-MAX_HEIGHT+0.1, 1);

        }
        startRoof += BUILDING_WIDTH/2;
    }
    
    //draw bridge's ropes
    sinusRight();
    sinusLeft();
    
    //draw reflaction bridge's ropes
    sinusReflactionRight();
    sinusReflactionLeft();
    
    //draw the towers
    drawLondonBridgeBuilding(BUILD_START_BRIDGE_X1, MIDDLE, BUILD_END_BRIDGE_X1, MAX_HEIGHT-0.1);
    drawLondonBridgeBuilding(BUILD_START_BRIDGE_X2, MIDDLE, BUILD_END_BRIDGE_X2, MAX_HEIGHT-0.1);
    
    //draw the reflaction towers
    drawLondonBridgeReflactionBuilding(BUILD_START_BRIDGE_X1, MIDDLE, BUILD_END_BRIDGE_X1, -MAX_HEIGHT+0.1);
    drawLondonBridgeReflactionBuilding(BUILD_START_BRIDGE_X2, MIDDLE, BUILD_END_BRIDGE_X2, -MAX_HEIGHT+0.1);
    
    // left tower
    i=0;
    for (double startY = MIDDLE + 2*FIRST_FLOOR ; startY < MAX_HEIGHT-0.1 ; startY += 3*FLOOR_SPACE, i++)
    {
        j=0;
        for(double startX = BUILD_START_BRIDGE_X1+WINDOW_START_WIDTH ; startX <BUILD_END_BRIDGE_X1 - WINDOW_END_WIDTH ; startX += 2.5*WINDOW_WIDTH, j++)
        {
            drawWindow(startX, startY);
            drawReflactionWindow(startX, -startY);
        }
    }
    
    // right tower
    i=0;
    for (double startY = MIDDLE + 2*FIRST_FLOOR ; startY < MAX_HEIGHT-0.1 ; startY += 3*FLOOR_SPACE, i++)
    {
        j=0;
        for(double startX = BUILD_START_BRIDGE_X2+WINDOW_START_WIDTH ; startX <BUILD_END_BRIDGE_X2 - WINDOW_END_WIDTH ; startX += 2.5*WINDOW_WIDTH, j++)
        {
            drawWindow(startX, startY);
            drawReflactionWindow(startX, -startY);
        }
    }
    
    //draw upper section
    drawLondonBridgeBuilding(BUILD_START_BRIDGE_X1 + 1.5*BUILDING_WIDTH, 0.6, BUILD_END_BRIDGE_X2 - 1.5*BUILDING_WIDTH, MAX_HEIGHT - 0.15);
    
    //draw upper section reflaction
    drawLondonBridgeUpperReflactionBuilding(BUILD_START_BRIDGE_X1 + 1.5*BUILDING_WIDTH, -0.6, BUILD_END_BRIDGE_X2 - 1.5*BUILDING_WIDTH, -MAX_HEIGHT + 0.15);

    for(double startX = BUILD_START_BRIDGE_X1 + 1.5*BUILDING_WIDTH+WINDOW_START_WIDTH ; startX <BUILD_END_BRIDGE_X2 - 1.5*BUILDING_WIDTH - WINDOW_END_WIDTH ; startX += 2.5*WINDOW_WIDTH)
    {
        drawWindow(startX, 0.62);
        drawReflactionWindow(startX, -0.62);
    }

    //draw sides section
    drawLondonBridgeBuilding(BUILD_END_BRIDGE_X2 , 0.1, BUILD_END_BRIDGE, 0.15);
    drawLondonBridgeBuilding(BUILD_START_BRIDGE , 0.1, BUILD_START_BRIDGE_X1, 0.15);
    //draw sides section reflaction
    drawLondonBridgeSidesSectionReflactionBuilding(BUILD_END_BRIDGE_X2 , -0.1, BUILD_END_BRIDGE, -0.15);
    drawLondonBridgeSidesSectionReflactionBuilding(BUILD_START_BRIDGE , -0.1, BUILD_START_BRIDGE_X1, -0.15);
    
    //draw half
    drawLondonHalfBridge(BUILD_START_BRIDGE_X1 + 1.5*BUILDING_WIDTH , 0.05, BUILD_END_BRIDGE_X2-1.5*BUILDING_WIDTH, 0.15);
    drawLondonHalfReflactionBridge(BUILD_START_BRIDGE_X1 + 1.5*BUILDING_WIDTH , -0.05, BUILD_END_BRIDGE_X2-1.5*BUILDING_WIDTH, -0.15);

}

void drawFerrisWheel()
{
    drawWheel();
    drawReflactionWheel();
}

void drawTowerOfLondon()
{
    double startRoof;
    int i = 0, j = 0;

    //left roofs
    startRoof = BUILD_START_TOWER_X;
    for (int x= 0 ; x < 3 ; x++)
    {
        drawTowerOfLondonRoof(startRoof, MIN_HEIGHT);
        drawReflactionTowerOfLondonRoof(startRoof, MIDDLE-MIN_HEIGHT);
        startRoof += BUILDING_WIDTH/2;
    }
    
    //right roofs
    startRoof = BUILD_START_TOWER_X1;
    for (int x= 0 ; x < 3 ; x++)
    {
        drawTowerOfLondonRoof(startRoof, MIN_HEIGHT);
        drawReflactionTowerOfLondonRoof(startRoof, MIDDLE-MIN_HEIGHT);
        startRoof += BUILDING_WIDTH/2;
    }
    
    //draw the reflaction tower
    drawLondonTowerReflactionBuilding(BUILD_START_TOWER_X, MIDDLE, BUILD_END_TOWER_X,MIDDLE-MIN_HEIGHT);
    
    drawTowerBuildingReflactionBorder(BUILD_START_TOWER_X, MIDDLE, BUILD_END_TOWER_X, MIDDLE - MIN_HEIGHT);
    drawTowerBuildingReflactionLine(BUILD_START_TOWER_X + 1.5*BUILDING_WIDTH, MIDDLE, BUILD_START_TOWER_X + 1.5*BUILDING_WIDTH, MIDDLE - MIN_HEIGHT);
    drawTowerBuildingReflactionLine(BUILD_END_TOWER_X - 1.5*BUILDING_WIDTH, MIDDLE,BUILD_END_TOWER_X - 1.5*BUILDING_WIDTH, MIDDLE - MIN_HEIGHT);
    
    //draw the tower
    drawLondonTowerBuilding(BUILD_START_TOWER_X, MIDDLE, BUILD_END_TOWER_X, MIN_HEIGHT);
    
    drawTowerBuildingBorder(BUILD_START_TOWER_X, MIDDLE, BUILD_END_TOWER_X, MIN_HEIGHT);
    drawTowerBuildingLine(BUILD_START_TOWER_X + 1.5*BUILDING_WIDTH, MIDDLE, BUILD_START_TOWER_X + 1.5*BUILDING_WIDTH, MIN_HEIGHT);
    drawTowerBuildingLine(BUILD_END_TOWER_X - 1.5*BUILDING_WIDTH, MIDDLE,BUILD_END_TOWER_X - 1.5*BUILDING_WIDTH, MIN_HEIGHT);

    // left section
    i=0;
    for (double startY = MIDDLE + FIRST_FLOOR/2 ; startY < MIN_HEIGHT ; startY += FLOOR_SPACE, i++)
    {
        j=0;
        for(double startX = BUILD_START_TOWER_X+WINDOW_START_WIDTH ; startX <= BUILD_START_TOWER_X + 1.5*BUILDING_WIDTH - WINDOW_END_WIDTH ; startX += 2.6*WINDOW_WIDTH, j++)
        {
            drawWindow(startX, startY);
            drawReflactionWindow(startX, -startY);
        }
    }
    
    //right section
    i=0;
    for (double startY = MIDDLE + FIRST_FLOOR/2  ; startY <MIN_HEIGHT ; startY += FLOOR_SPACE, i++)
    {
        j=0;
        for(double startX = BUILD_END_TOWER_X - 1.5*BUILDING_WIDTH + WINDOW_START_WIDTH; startX <= BUILD_END_TOWER_X - WINDOW_END_WIDTH ; startX += 2.6*WINDOW_WIDTH, j++)
        {
            drawWindow(startX, startY);
            drawReflactionWindow(startX, -startY);
        }
    }
    
    // middle section
    i=0;
    for (double startY = MIDDLE + FIRST_FLOOR/2  ; startY <MIN_HEIGHT ; startY += FLOOR_SPACE, i++)
    {
        j=0;
        for(double startX = BUILD_START_TOWER_X + 1.5*BUILDING_WIDTH + WINDOW_END_WIDTH + WINDOW_START_WIDTH ; startX <= BUILD_END_TOWER_X - 1.5*BUILDING_WIDTH - WINDOW_END_WIDTH; startX += 2.6*WINDOW_WIDTH, j++)
        {
            drawWindow(startX, startY);
            drawReflactionWindow(startX, -startY);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// all buildings drawing methods ////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void drawBuildings()
{
    drawFerrisWheel();
    drawTowerOfLondon();
    drawBridge();
    drawUpperBuildings();
    drawUpperLowerBuildings();
    //seprate btween
    drawMiddleLineSeperation();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// openGL drawing methods ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // loads background color

    //draw all pic
    
    drawSky();
    drawBuildings();
    
    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay(); // indirect call to display
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("London view - Hadar Pur");
    
    glutDisplayFunc(display); //display all pic
    glutIdleFunc(idle); // for glowing effects
    init();
    glutMainLoop();
    
    return 0;
}
