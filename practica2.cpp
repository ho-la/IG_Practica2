/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   practica2.cpp
 * Author: odopaon
 *
 * Created on 23 de octubre de 2016, 20:56
 */
//https://github.com/ho-la/IG_Practica2.git
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <cstdlib>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawTriangulo(char color);
void funKeyboard(int key, int x, int y);
void raton (int button, int state, int x, int y);
void destroyFunc();
void funIdle();

void glDrawSphere(char color,float radio);
void tarea1();
void tarea2();
void tarea3();
void tarea4();
void drawPieza();

// Variables globales
int w = 800;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;

//Si gira de 4h en 4h
GLfloat anio = (360.0/365.0)/6; //365*24 horas
GLfloat dia = (360.0/6.0); //24 horas
GLfloat mes= anio*12*4;  // Luna gira 12 veces sobre a Tierra en un año



GLboolean girar=true;
GLfloat inclinaTierra = -30.0f;
GLfloat inclinaLuna = 45.0f;

GLfloat RAnio = 0.0f;
GLfloat RDia = 0.0f;
GLfloat RMes=0.0f;
GLboolean anima=true;
GLboolean hacerZoom=true;
GLfloat zoom = -10.0f;
GLfloat giroVertical=0.0f;
GLfloat T4Girar=0.0f;
GLfloat T4Dezplazar=0.0f;
GLboolean esTarea4=true;
int main(int argc, char** argv) {
    
 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("QiaoLang Chen y Alexey Sorokin");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones específicas
    initFunc();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
	glutMouseFunc(raton);
    glutIdleFunc(funIdle);  
    
 // Bucle principal
    glutMainLoop();
    
 // Destrucción de objetos
    destroyFunc();
    
    return(0);
}


void initFunc() {
    
 // Configuracion de etapas del cauce
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    
}

void destroyFunc() {
    
}

void funReshape(int wnew, int hnew) {
    
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    
    w = wnew;
    h = hnew;
}

void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    // Proyeccion Ortogonal: 
    //GLfloat left=-4.0, right=4.0, bottom=-4.0, top=4.0, nplane=1.0, fplane=10.0;
    //glOrtho(left, right, bottom, top, nplane, fplane);
  
    //Proyeccion en Frustum
    //GLfloat left=-2.0, right=2.0, bottom=-2.0, top=2.0, nplane=3.0, fplane=10.0;
    //glFrustum(left, right, bottom, top, nplane, fplane);

    //En perspectiva
    /**/
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 30.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    /**/ 
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    
 // Dibujamos los objetos (M)
    //glTranslatef(0.0f, 0.0f, desZ);
    //glTranslatef(0.0f, 0.0f, -5.0f);
    if (hacerZoom)
        glTranslatef(0.0f,0.0f, zoom);
    //tarea1();
    //tarea2();
    tarea3();
    //tarea4();
 // Intercambiamos los buffers
    glutSwapBuffers();
}

void funKeyboard(int key, int x, int y) {
    if(esTarea4){
        switch(key){
            case GLUT_KEY_UP:
                T4Girar += 0.1f;
                break;
            case GLUT_KEY_DOWN:
                T4Girar  -= 0.1f;
                break;
            case GLUT_KEY_RIGHT:
                T4Dezplazar += 0.1f;
                break;
            case GLUT_KEY_LEFT:
                T4Dezplazar -= 0.1f;
                break;
            default:
                T4Girar = 0.0f;
                T4Dezplazar = 0.0f;
        }
    }
    else{
    //F1 detener/arrancar animación
    //Con la animación detenida, rotar de forma independiente la Tierra y la Luna mediante las teclas de las Flechas.
        if(anima==true)
         switch(key) {
             case GLUT_KEY_F1:
                 anima = false;
                 break;
        }    
        else{
            switch(key){
                case GLUT_KEY_F1:
                    anima = true;
                    break;
                case GLUT_KEY_RIGHT:
                    //rotY -= 5.0f;
                    RAnio--;
                    RDia -= 365;
                    RMes -= 12;
                    break;
                case GLUT_KEY_LEFT:
                    //rotY += 5.0f;
                    RAnio++;
                    RDia += 365;
                    RMes +=12;
                    break;
            }
        }    
    }
    glutPostRedisplay();
    
}
void raton (int button, int state, int x, int y){
    //2.1 y 2.2):Zoom con rueda del raton, establecer limites para que no se vea demasiados pequeños o grandes
    /*3.1)  Modificar la posición de la cámara (controlada con la función gluLookAt) para que la
        podamos desplazar verticalmente, manteniendo el punto hacia el que mira en el centro del
        sistema solar.
    */        
    //3.2):Dezplazar camara verticarmente, controlar el dezplazamiento con la tecla izq del raton
    if(!esTarea4){
        switch(button){
            case GLUT_LEFT_BUTTON:
                if(state==GLUT_DOWN)
                    giroVertical -= 6.0f;
                break; 
            //Rueba arriba
            case 3:
                if (zoom>-17)
                    zoom-=1;
                break;
            //Rueda abajo    
            case 4:
                if (zoom<-7)
                    zoom+=1;
                break;
        }        
    }
    glutPostRedisplay();
}
void glDrawSphere(char color,float radio){
    switch(color) {
        //White
        case 'w':
            glColor3f(1.0f, 1.0f, 1.0f);
            break;
        //Yellow    
        case 'y':
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        //Red
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        //Green
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        //Blue
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        //White
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    glutWireSphere(radio,20,20); 
    //(GLdouble radius,GLint slices, GLint stacks); (number of lines)
}
void funIdle() {
    if(anima){
        RAnio++;
        RDia += 365;
        RMes +=12;
    }   
    Sleep(10);   
    glutPostRedisplay();  
}
void tarea1(){
    glPushMatrix();
        //Dibujar sol
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('y',2.0f);
        glPopMatrix();
        //Dibujar tierra
        glRotatef(RAnio,0.0f,1.0f,0.0f);
        glTranslatef(4.0f,0.0f,0.0f);
        glRotatef(RDia,0.0f,1.0f,0.0f);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('b',0.5f);
        glPopMatrix();
        glRotatef(-RDia,0.0f,1.0f,0.0f);
        //Dibujar luna
        glRotatef(RMes,0.0f,1.0f,0.0f);
        glTranslatef(1.5,0.0,0.0);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('w',0.1f);
        glPopMatrix();
    glPopMatrix();
    esTarea4=false;
}
void tarea2(){
    glPushMatrix();
        //Dibujar sol
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('y',2.0f);
        glPopMatrix();
        //Dibujar tierra
        glRotatef(-30,0.0f,0.0f,1.0f);
        glRotatef(RAnio,0.0f,1.0f,0.0f);
        glTranslatef(4.0f,0.0f,0.0f);
        glRotatef(RDia,0.0f,1.0f,0.0f);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('b',0.5f);
        glPopMatrix();
        glRotatef(-RDia,0.0f,1.0f,0.0f);
        //Dibujar luna
        glRotatef(45,0.0f,0.0f,1.0f);
        glRotatef(RMes,0.0f,1.0f,0.0f);
        glTranslatef(1.5,0.0,0.0);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('w',0.1f);
        glPopMatrix();
    glPopMatrix();
    esTarea4=false;
}
void tarea3(){
    //F1 detener/arrancar animación
    //Con la animación detenida, rotar de forma independiente la Tierra y la Luna mediante las teclas de las Flechas.
    //2):Zoom con rueda del raton, establecer limites
    //3):Dezplazar camara verticarmente, controlar el dezplazamiento con la tecla izq del raton
    glPushMatrix();
        glRotatef(giroVertical,1.0f,0.0f,0.0f);
        //Dibujar sol
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('y',2.0f);
        glPopMatrix();
        //Dibujar tierra
        glRotatef(RAnio,0.0f,1.0f,0.0f);
        glTranslatef(4.0f,0.0f,0.0f);
        glRotatef(RDia,0.0f,1.0f,0.0f);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('b',0.5f);
        glPopMatrix();
        glRotatef(-RDia,0.0f,1.0f,0.0f);
        //Dibujar luna
        glRotatef(RMes,0.0f,1.0f,0.0f);
        glTranslatef(1.5,0.0,0.0);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('w',0.1f);
        glPopMatrix();
    glPopMatrix();
    esTarea4 = false;
}
void tarea4(){
    glPushMatrix();
        glTranslatef(2.5f,0.0f,0.0f);
        glRotatef(T4Girar,0.0f,0.0f,1.0f);
        glRotatef(-90,0.0f,0.0f,1.0f);
        glPushMatrix();
            glTranslatef(-0.5f,-0.5f,0.0f);
            glColor3f(1.0f, 0.0f, 1.0f);
            drawPieza();
        glPopMatrix();
        glPushMatrix();
            glRotatef(90,0.0f,0.0f,1.0f);
            glTranslatef(T4Dezplazar,0.0f,0.0f);
            glTranslatef(2.5f,0.25f,0.0f);
            glScalef(0.5f,0.5f,1.0f);
            glRotatef(-90,0.0f,0.0f,1.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            drawPieza();
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.5f,0.5f,0.0f);
        glRotatef(-90,0.0f,0.0f,1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        drawPieza();
    glPopMatrix();
    esTarea4=true;
}
void drawPieza(){
    glBegin(GL_QUADS);
        glVertex3f( 0.0, 0.0, 0.0);
        glVertex3f( 1.0, 0.0, 0.0);        
        glVertex3f( 1.0, 3.0, 0.0);
        glVertex3f( 0.0, 3.0, 0.0);
    glEnd();
}
