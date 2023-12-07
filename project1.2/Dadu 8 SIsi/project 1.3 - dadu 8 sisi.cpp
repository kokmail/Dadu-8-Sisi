#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <ctime> 
#include "stb_image.h"
#include "getBMP.h"

float angleX = 0.0f;
float angleY = 0.0f;
float rotationSpeed = 0.0f;  // Initial rotation speed
float rotationX = 220.0f;
float rotationY = 180.0f;

int lastMouseX = 0;
int lastMouseY = 0;

static unsigned int texture[1];
static int logo = 0;

void loadTextures()
{
    const char* texturePaths[] = {
        //"Textures/pens.bmp",
        "E:/Kuli yah/Semester 3/Grafika Komputer/OpenGLwrappers/ExperimenterSource/Dadu 8 SIsi/Textures/pens.bmp"
    };

    // Loop through each texture
    for (int i = 0; i < 1; ++i) {
        int width, height, channels;

        // Load image using stb_image
        unsigned char* image = stbi_load(texturePaths[i], &width, &height, &channels, STBI_rgb_alpha);

        if (image == nullptr) {
            std::cerr << "Failed to load image: " << texturePaths[i] << std::endl;
            continue;  // Move to the next iteration if loading fails
        }

        // Generate texture object
        glGenTextures(1, &texture[i]);

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, texture[i]);

        // Specify image data for the currently active texture object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        // Free the image data
        stbi_image_free(image);

        // Set texture parameters for wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set texture parameters for filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}

void drawDotPutih(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
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
    drawDotPutih(0, 0, 0, 0.13);
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
    drawDotPutih(0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, -0.3, 0, 0.13);
    drawDotPutih(0.3, -0.3, 0, 0.13);
    drawDotPutih(0, 0, 0, 0.13);
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
    drawDotPutih(0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, -0.3, 0, 0.13);
    drawDotPutih(0.3, -0.3, 0, 0.13);
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
    drawDotPutih(0.3, 0.3, 0, 0.13);
    drawDotPutih(0.3, 0, 0, 0.13);
    drawDotPutih(0.3, -0.3, 0, 0.13);
    drawDotPutih(-0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, 0, 0, 0.13);
    drawDotPutih(-0.3, -0.3, 0, 0.13);
    drawDotPutih(0, 0.15, 0, 0.13);
    drawDotPutih(0, -0.15, 0, 0.13);
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
    drawDotPutih(0.3, 0.3, 0, 0.13);
    drawDotPutih(0.3, 0, 0, 0.13);
    drawDotPutih(0.3, -0.3, 0, 0.13);
    drawDotPutih(-0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, 0, 0, 0.13);
    drawDotPutih(-0.3, -0.3, 0, 0.13);
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
    drawDotPutih(-0.3, 0.3, 0, 0.13);
    drawDotPutih(0.3, -0.3, 0, 0.13);
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
    drawDotPutih(0.3, 0.3, 0, 0.13);
    drawDotPutih(0.3, 0, 0, 0.13);
    drawDotPutih(0.3, -0.3, 0, 0.13);
    drawDotPutih(-0.3, 0.3, 0, 0.13);
    drawDotPutih(-0.3, 0, 0, 0.13);
    drawDotPutih(-0.3, -0.3, 0, 0.13);
    drawDotPutih(0, 0, 0, 0.13);

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
    drawDotPutih(0.3, 0.3, 0, 0.13);
    drawDotPutih(0, 0, 0, 0.13);
    drawDotPutih(-0.3, -0.3, 0, 0.13);
    glPopMatrix();


    //glutSwapBuffers();
}

void drawTable() {
    //glEnable(GL_TEXTURE_2D);

    // Atas meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.0f, 0.8f);
    glVertex3f(-0.8f, 0.0f, 0.8f);
    glEnd();


    glEnable(GL_TEXTURE_2D);

    // Depan meja
    glBegin(GL_QUADS);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[0]);  // Mengaitkan tekstur pertama
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.8f, 0.9f, 0.7f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.8f, 0.9f, 0.7f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.8f, 0.0f, 0.7f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.8f, 0.0f, 0.7f);
    glColor3f(.7f, 0.4f, 0.1f); // Warna coklat karamel
    glVertex3f(-0.8f, 0.9f, 0.7f);
    glVertex3f(0.8f, 0.9f, 0.7f);
    glVertex3f(0.8f, 0.0f, 0.7f);
    glVertex3f(-0.8f, 0.0f, 0.7f);
    glPopMatrix();
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Atas depan meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.1f, 0.8f);
    glVertex3f(0.8f, 0.1f, 0.8f);
    glVertex3f(0.8f, 0.0f, 0.8f);
    glVertex3f(-0.8f, 0.0f, 0.8f);
    glEnd();

    // Bawah depan meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.7f, 0.8f, 0.8f);
    glVertex3f(0.7f, 0.8f, 0.8f);
    glVertex3f(0.7f, 0.9f, 0.8f);
    glVertex3f(-0.7f, 0.9f, 0.8f);
    glEnd();

    // Depan bawah meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.8f, 0.9f, 0.7f);
    glVertex3f(-0.8f, 0.9f, 0.7f);
    glVertex3f(-0.8f, 0.9f, 0.8f);
    glVertex3f(0.8f, 0.9f, 0.8f);
    glEnd();

    // Atas belakang meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.1f, -0.8f);
    glVertex3f(0.8f, 0.1f, -0.8f);
    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(-0.8f, 0.0f, -0.8f);
    glEnd();


    // Kaki meja ke 1
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.0f, -0.8f);
    glVertex3f(-0.7f, 0.0f, -0.8f);
    glVertex3f(-0.7f, 1.3f, -0.8f);
    glVertex3f(-0.8f, 1.3f, -0.8f);
    glEnd();

    // Kiri kaki meja ke 1
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.0f, -0.7f);
    glVertex3f(-0.8f, 0.0f, -0.8f);
    glVertex3f(-0.8f, 1.3f, -0.8f);
    glVertex3f(-0.8f, 1.3f, -0.7f);
    glEnd();

    // Kanan kaki meja ke 1
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.0f, -0.7f);
    glVertex3f(0.8f, 1.3f, -0.7f);
    glVertex3f(0.8f, 1.3f, -0.8f);
    glEnd();

    // Bawah kaki meja ke 1
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 1.3f, 0.8f);
    glVertex3f(-0.7f, 1.3f, 0.8f);
    glVertex3f(-0.7f, 1.3f, -0.8f);
    glVertex3f(-0.8f, 1.3f, -0.8f);
    glEnd();

    // Atas kiri meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.1f, 0.8f);
    glVertex3f(-0.8f, 0.0f, 0.8f);
    glVertex3f(-0.8f, 0.0f, -0.8f);
    glVertex3f(-0.8f, 0.1f, -0.8f);
    glEnd();

    // Atas kanan meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.8f, 0.1f, 0.8f);
    glVertex3f(0.8f, 0.0f, 0.8f);
    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.1f, -0.8f);
    glEnd();

    // Bawah kiri meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 1.3f, 0.8f);
    glVertex3f(-0.8f, 1.2f, 0.8f);
    glVertex3f(-0.8f, 1.2f, -0.8f);
    glVertex3f(-0.8f, 1.3f, -0.8f);
    glEnd();

    // Bawah kanan meja
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.8f, 1.3f, 0.8f);
    glVertex3f(0.8f, 1.2f, 0.8f);
    glVertex3f(0.8f, 1.2f, -0.8f);
    glVertex3f(0.8f, 1.3f, -0.8f);
    glEnd();


    // Kaki meja ke 2
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.7f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 1.3f, -0.8f);
    glVertex3f(0.7f, 1.3f, -0.8f);
    glEnd();

    // Kaki meja ke 3
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.7f, 0.0f, 0.8f);
    glVertex3f(0.8f, 0.0f, 0.8f);
    glVertex3f(0.8f, 1.3f, 0.8f);
    glVertex3f(0.7f, 1.3f, 0.8f);
    glEnd();

    // Kanan kaki meja ke 3
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.7f, 0.0f, 0.8f);
    glVertex3f(0.8f, 0.0f, 0.7f);
    glVertex3f(0.8f, 1.3f, 0.7f);
    glVertex3f(0.7f, 1.3f, 0.8f);
    glEnd();

    // Bawah kaki meja ke 3
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(0.7f, 1.3f, -0.8f);
    glVertex3f(0.8f, 1.3f, -0.8f);
    glVertex3f(0.8f, 1.3f, 0.8f);
    glVertex3f(0.7f, 1.3f, 0.8f);
    glEnd();

    // Kaki meja ke 4
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.0f, 0.8f);
    glVertex3f(-0.7f, 0.0f, 0.8f);
    glVertex3f(-0.7f, 1.3f, 0.8f);
    glVertex3f(-0.8f, 1.3f, 0.8f);
    glEnd();

    // Kiri kaki meja ke 4 
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f); // Warna putih
    glVertex3f(-0.8f, 0.0f, 0.7f);
    glVertex3f(-0.7f, 0.0f, 0.8f);
    glVertex3f(-0.7f, 1.3f, 0.8f);
    glVertex3f(-0.8f, 1.3f, 0.7f);
    glEnd();
  
    //glDisable(GL_TEXTURE_2D);

}

void display()
{

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0f, -0.2f, -5.0f);
    glRotatef(rotationX, 0.0f, 15.0f, 0.0f);
    glRotatef(rotationY, 1.0f, 0.0f, 0.0f);
    drawTable();
    glPopMatrix();

    //************
    glPushMatrix();
    //angleX += rotationSpeed;
    //angleY += rotationSpeed;

    glTranslatef(0.0f, 5.0f, -30.0f);  //kanan-kiri, atas-bawah, ukuran
    glRotatef(angleX, 0.0f, 15.0f, 0.0f);
    drawDadu();

    /*if (rotationSpeed > 0.0f)
    {
        rotationSpeed -= 0.0005f; // Adjust the value for the desired deceleration rate
        glutPostRedisplay();  // Trigger a redraw
    }
    */

    glPopMatrix();

    glDisable(GL_DEPTH_TEST);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, aspect, 0.5f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };  // Directional light from the top-right
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_FLAT);  // You can also use GL_SMOOTH for smooth shading
}

/*void randomizeRotationSpeed()
{
    // Generate a random rotation speed between 1 and 10
    rotationSpeed = (rand() % 3 + 1) * 0.7;
}
*/
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
    case 'R':
    angleY: 0.1f;
        glutPostRedisplay();  // Trigger a redraw
        break;
    }
    switch (key)
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'w':
        rotationY += 5.0f;
        glutPostRedisplay();
        break;
    case 's':
        rotationY -= 5.0f;
        glutPostRedisplay();
        break;
    }
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

    rotationX += deltaX * 0.1f;

    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    srand(static_cast<unsigned>(time(nullptr)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Dadu Artama Mail");


    glutDisplayFunc(display);
    initLighting();  // Call the lighting initialization function
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);  // Set the keyboard function

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearDepth(1.0f);
    loadTextures();
    glutMainLoop();

    return 0;
}
