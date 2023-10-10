#include <GL/glut.h>
#include <math.h>

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX = 0;
int lastMouseY = 0;

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
{

    glColor3f(1, 1, 1);
    int i;
    int triangleAmount = 20;

    GLfloat twicePi = 2.0f * 3.15;

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(x, y, z); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawDadu()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.4f, 1.0f, 0.3f);	//tampak depan
    glVertex3f(0.0f, 1.0f, 0.0f);	//titik atas
    glVertex3f(-1.0f, -1.0f, 1.0f);	//titik kiri alas
    glVertex3f(1.0f, -1.0f, 1.0f);	//titik kanan alas
    glEnd();

    // 1 poin
    glPushMatrix();
    glTranslatef(0.0f, -0.28f, 0.68f);
    glRotatef(30.0f, -1.0f, 0.0f, 0.0f);
    drawFilledCircle(0, 0, 0, 0.13);
    glPopMatrix();
    //***

    glBegin(GL_TRIANGLES);
    glColor3f(0.4f, 1.0f, 0.3f);	//tampak belakang
    glVertex3f(0.0f, 1.0f, 0.0f);	//titik atas
    glVertex3f(-1.0f, -1.0f, -1.0f);//titik kiri alas
    glVertex3f(1.0f, -1.0f, -1.0f);	//titik kanan alas
    glEnd();

    // 5 poin
    glPushMatrix();
    glTranslatef(0.0f, -0.28f, -0.68f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, -0.3, 0, 0.13);
    drawFilledCircle(0.3, -0.3, 0, 0.13);
    drawFilledCircle(0, 0, 0, 0.13);
    glPopMatrix();
    //**


    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.9f, 0.6f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    // 4 poin
    glPushMatrix();
    glTranslatef(-0.68f, -0.28f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(30.0f, 0.5f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, -0.3, 0, 0.13);
    drawFilledCircle(0.3, -0.3, 0, 0.13);
    glPopMatrix();
    //***


    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.9f, 0.6f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    // 8 poin
    glPushMatrix();
    glTranslatef(0.68f, -0.28f, 0.0f);
    glRotatef(90.0f, 0.0f, -2.0f, 0.0f);
    glRotatef(30.0f, 0.5f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.3, 0, 0.13);
    drawFilledCircle(0.3, 0, 0, 0.13);
    drawFilledCircle(0.3, -0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0, 0, 0.13);
    drawFilledCircle(-0.3, -0.3, 0, 0.13);
    drawFilledCircle(0, 0.15, 0, 0.13);
    drawFilledCircle(0, -0.15, 0, 0.13);
    glPopMatrix();

    //***
    //bagian bawah
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.7f, 0.4f);
    glVertex3f(0.0f, -3.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    // 6 poin
    glPushMatrix();
    glTranslatef(0.0f, -1.5f, 0.8f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.3, 0, 0.13);
    drawFilledCircle(0.3, 0, 0, 0.13);
    drawFilledCircle(0.3, -0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0, 0, 0.13);
    drawFilledCircle(-0.3, -0.3, 0, 0.13);
    glPopMatrix();

    //***
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.7f, 0.4f);
    glVertex3f(0.0f, -3.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    // 2 poin
    glPushMatrix();
    glTranslatef(0.0f, -1.5f, -0.8f);
    glRotatef(30.0f, -1.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.3, 0.3, 0, 0.13);
    drawFilledCircle(0.3, -0.3, 0, 0.13);
    glPopMatrix();

    //***
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 1.0f, 0.9f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, -3.0f, 0.0f);
    glEnd();

    // 7 poin
    glPushMatrix();
    glTranslatef(-0.8f, -1.5f, 0.0f);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glRotatef(30.0f, 0.5f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.3, 0, 0.13);
    drawFilledCircle(0.3, 0, 0, 0.13);
    drawFilledCircle(0.3, -0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0.3, 0, 0.13);
    drawFilledCircle(-0.3, 0, 0, 0.13);
    drawFilledCircle(-0.3, -0.3, 0, 0.13);
    drawFilledCircle(0, 0, 0, 0.13);

    glPopMatrix();

    //***
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 1.0f, 0.9f);
    glVertex3f(0.0f, -3.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    // 3 poin
    glPushMatrix();
    glTranslatef(0.8f, -1.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.3, 0, 0.13);
    drawFilledCircle(0, 0, 0, 0.13);
    drawFilledCircle(-0.3, -0.3, 0, 0.13);
    glPopMatrix();

    glutSwapBuffers();
}

void display_dadu()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 1.0f, -6.0f);
    glRotatef(angleX, 0.0f, 15.0f, 0.0f);
    glRotatef(angleY, -15.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    drawDadu();
    glDisable(GL_DEPTH_TEST);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

void motion(int x, int y)
{
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;
    lastMouseX = x;
    lastMouseY = y;

    angleX += deltaX * 0.1f;
    angleY += deltaY * 0.1f;

    glutPostRedisplay();
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;

    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Dadu Artama Mail");

    glutDisplayFunc(display_dadu);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glutMainLoop();

    return 0;
}