//
//  main.cpp
//  Project3_CSCI368
//
//  Created by Madushani Lekam Wasam Liyanage on 11/12/17.
//  Copyright © 2017 Madushani Lekam Wasam Liyanage. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
using namespace std;

GLint vert[100][2];
GLint points[100][2];

int width=400,height=600,n=0,s=0,k=0,t=0, type = GL_LINE_STRIP,v,pi=3.14;
int numberOfVertices = 0;
GLint dist[10];
bool antialiasing=false, flag=true, isPolygon=false,color=false;
bool colorArr[100];

void keyboard(unsigned char key,int x, int y){
    switch(key){
        case 'a': antialiasing = !antialiasing;
            if(antialiasing){
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
            }
            else{
                glDisable(GL_BLEND);
                glDisable(GL_LINE_SMOOTH);
            }
            break;
        case 'c': type=GL_LINE_LOOP; flag=false;isPolygon=true;break;
        case 'l': type=GL_LINE_STRIP; break;
        case 'r': n=0;t=0;type=GL_LINE_STRIP;flag=true;isPolygon=false;
            numberOfVertices = 0; break;
        case 'v': type=GL_POINTS; break;
    }
    glutPostRedisplay();
}

bool isInside(int x, int y) {
    int arrSize = numberOfVertices;
    float theta = 0.0;
    /*
     cout<<arrSize<<" :array Size";
     cout<<x<<" :x";
     cout<<y<<" :y";
    */
    
    for (int i = 0; i<arrSize; i++) {
        int index = (i+1)%arrSize;
        float x1 = vert[i][0];
        float y1 = vert[i][1];
        float x2 = vert[index][0];
        float y2 = vert[index][1];
        float xx1 = (x1-x);
        float yy1 = (y1-y);
        float xx2 = (x2-x);
        float yy2 = (y2-y);
        
        float xx1_squared = pow(xx1,2);
        float yy1_squared = pow(yy1,2);
        float xx2_squared = pow(xx2,2);
        float yy2_squared = pow(yy2,2);
        
        float dist1 = sqrt(xx1_squared+yy1_squared);
        float dist2 = sqrt(xx2_squared+yy2_squared);
        
        cout << acos((xx1*xx2+yy1*yy2)/(dist1*dist2))<<" \n";
        cout << x<<" x:"<<" \n";
        theta += acos((xx1*xx2+yy1*yy2)/(dist1*dist2)) * 180/pi;
    }
   // cout<<theta<<" :theta";
    if (theta >= 300.0) {
        return true;
    }
    return false;
}

void changeColor(bool change){
    if(change){
        glColor3f(0, 1, 0);
    }
    else{
        glColor3f(1, 0, 0);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(n==1 && (type==GL_LINE_STRIP || type==GL_LINE_LOOP)){
        glBegin(GL_POINTS);
        glVertex2iv(vert[0]);
        glEnd();
    }
    glBegin(type);
    glColor3f(1, 1, 0);
    for(int i=0;i<n;i++){
        glVertex2iv(vert[i]);
    }
    glEnd();
    if(isPolygon){
        glBegin(GL_POINTS);
        for(int i=0;i<t;i++){
            changeColor(colorArr[i]);
            glVertex2iv(points[i]);
            
        }
        glEnd();
    }
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state ==GLUT_DOWN){
                if(flag&& !isPolygon){
                    numberOfVertices++;
                    v=n++;
                    vert[v][0]=x;
                    vert[v][1]=height-1-y;
                    glutPostRedisplay();
                }
                if(isPolygon){
                    k=t++;
                    points[k][0]=x;
                    points[k][1]=height-1-y;
                    if (isInside(x, y)) {
                        colorArr[t-1] = true;
                    }
                    else {
                        colorArr[t-1] = false;
                    }
                    glutPostRedisplay();
                }
            }else
                break;
        case GLUT_RIGHT_BUTTON:
            break;
    }
}

int main(int argc, char** argv) {
    numberOfVertices = 0;
    n = 0;
    v = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("project3");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width,0,height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    
}

