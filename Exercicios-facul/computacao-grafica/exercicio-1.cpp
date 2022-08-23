#include <GL/glut.h>
#include <stdlib.h>
static int i = 1;
static int control = 1;
 
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
 
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (200, 200);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Desenha uma reta composta de pontos...");
    
    init( );
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop( );
}
 
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho (0, 256, 0, 256, -1 ,1);
}
 
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    
    int m =  (20 - 100) / (100 - 20);
    for(int i = 20; i < 100; i++ ) {
        glPointSize(3);
        int y = -m * i + 20;
        glBegin(GL_POINTS);
        glVertex2i(i, y);
        glEnd();
    }
    glFlush( );
}
void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27:
            exit(0);
        break;
    }
}