#include <cstdlib>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <GL/freeglut.h>
#include "stb_image.h"
#include "getBMP.h"

GLfloat light_position[] = { 2.0, 2.0, 1.0, 1.0 }; // Posisi cahaya
GLfloat light_position2[] = { -2.0, 2.0, -1.0, 1.0 }; // Posisi cahaya
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 }; // Warna cahaya putih
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // Warna ambient light

int lastX = 0;
int lastY = 0;
bool leftMouseButtonDown = false;
bool middleMouseButtonDown = false;
bool rightMouseButtonDown = false;

float rotateX = 0.0;
float rotateY = 0.0;
float translateX = 0.0;
float translateY = -0.7;
float translateZ = -6.0; // Jarak awal kamera dari objek

//Variable Animasi
bool apress = false;
bool bpress = false;
bool qpress = false;
bool rpress = false;
bool epress = false;
float kecepatan = 0.02;
float rotasi = 0.08;
float laciAtasPositionZ = -0.84;
float laciBawahPositionZ = -0.84;
float TV = 0.0f;
float TV2 = 0.0f;

static unsigned int texture[9]; // Array of texture ids.
static int id = 0; // ID untuk Layar
static int id2 = 5; // ID untuk Kayu

void loadTextures()
{
    const char* texturePaths[] = {
        "Textures/Pens.bmp",
        "Textures/Home.bmp",
        "Textures/win7.bmp",
        "Textures/win7.bmp",
        "Textures/Yutub.bmp",
        "Textures/Wood.bmp",
        "Textures/Wood2.bmp",
        "Textures/Wood3.bmp",
        "Textures/Wood4.bmp"
    };

    // Loop through each texture
    for (int i = 0; i < 9; ++i) {
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


void updateA(int value) {
    if (apress == true && laciAtasPositionZ < 0) {
        laciAtasPositionZ += kecepatan;
        glutPostRedisplay();
        glutTimerFunc(8, updateA, 0);  // 60 FPS
    }

    if (apress == false && laciAtasPositionZ > -0.82) {
        laciAtasPositionZ -= kecepatan;
        glutPostRedisplay();
        glutTimerFunc(8, updateA, 0);  // 60 FPS
    }
}

void updateB(int value) {

    if (bpress == true && laciBawahPositionZ < 0) {
        laciBawahPositionZ += kecepatan;
        glutPostRedisplay();
        glutTimerFunc(8, updateB, 0);  // 60 FPS
    }

    if (bpress == false && laciBawahPositionZ > -0.82) {
        laciBawahPositionZ -= kecepatan;
        glutPostRedisplay();
        glutTimerFunc(8, updateB, 0);  // 60 FPS
    }
}

void updateTV(int value) {
    if (qpress == true && TV < 1.18) {
        TV += kecepatan;
        glutPostRedisplay();
        glutTimerFunc(2, updateTV, 0);
    }

    if (qpress == false && TV > 0.00001) {
        TV -= kecepatan;
        glutPostRedisplay();
        glutTimerFunc(2, updateTV, 0);
    }
}

void rotateR(int value)
{
    if (rpress == true) {
        TV2 += rotasi;
        glutPostRedisplay();
        glutTimerFunc(2, rotateR, 0);
    }
}


void rotateE(int value)
{
    if (epress == true) {
        TV2 -= rotasi;
        glutPostRedisplay();
        glutTimerFunc(2, rotateE, 0);
    }
}



void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 'a') {
        apress = !apress;
        glutTimerFunc(16, updateA, 0);  // 60 FPS
    }
    if (key == 's') {
        bpress = !bpress;
        glutTimerFunc(16, updateB, 0);  // 60 FPS
    }
    if (key == 'q') {
        qpress = !qpress;
        glutTimerFunc(4, updateTV, 0);  // 60 FPS
    }

    if (key == 'r') {
        rpress = !rpress;
        epress = false;
        glutTimerFunc(8, rotateR, 0);  // 60 FPS
    }
    if (key == 'e') {
        epress = !epress;
        rpress = false;
        glutTimerFunc(8, rotateE, 0);  // 60 FPS
    }
    if (key == 'w') {
        id++;
        if (id == 2) id = 3;
        if (id == 5) id = 0;
        loadTextures();
        glutPostRedisplay();
    }

    if (key == 'f') {
        id2++;
        if (id2 == 9) id2 = 5;
        loadTextures();
        glutPostRedisplay();
    }
    glutPostRedisplay();
}

void drawLayar()
{
    // Menonaktifkan pencahayaan sementara
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[id]);  // Mengaitkan tekstur pertama

    glBegin(GL_QUADS);
    glColor3f(1.5f, 1.5f, 1.5f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, 0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);  // Unbind tekstur

    glDisable(GL_TEXTURE_2D);

    // Mengaktifkan kembali pencahayaan jika diperlukan
    glEnable(GL_LIGHTING);
}


void drawVertex()
{
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 5.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.2f, 5.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-1.0f, 0.0f, -0.2f);
    glVertex3f(-0.2f, 5.0f, -0.2f);
    glVertex3f(1.0f, 0.0f, -0.2f);
    glVertex3f(0.2f, 5.0f, -0.2f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 5.0f, 0.0f);
    glVertex3f(-0.2f, 5.0f, -0.2f);
    glVertex3f(-1.0f, 0.0f, -0.2f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.2f, 5.0f, 0.0f);
    glVertex3f(0.2f, 5.0f, -0.2f);
    glVertex3f(1.0f, 0.0f, -0.2f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-0.2f, 5.0f, 0.0f);
    glVertex3f(-0.2f, 5.0f, -0.2f);
    glVertex3f(0.2f, 5.0f, -0.2f);
    glVertex3f(0.2f, 5.0f, 0.0f);

    glEnd();
}

void drawCustomCube(float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawTorus(float innerRadius, float outerRadius, int sides, int rings) {
    glPushMatrix();
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
    glPopMatrix();
}

void drawTexturedCube(float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scaleX, scaleY, scaleZ);

    // Bind the texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[id2]);

    glBegin(GL_QUADS);
    // Front face
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top face
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Bottom face
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, -0.5f, -0.5f);

    // Right face
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.5f, -0.5f, -0.5f);

    // Left face
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void laci()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    drawTexturedCube(0.63, 0.08, 1.3, 1.0, 0.36, 0.04);//tutup
    glColor3f(0.8, 0.8, 0.8);
    drawCustomCube(0.63, -0.07, 0.8, 0.9, 0.02, 0.9);//bawah
    drawCustomCube(1.07, 0.09, 0.8, 0.03, 0.33, 0.9);//kanan
    drawCustomCube(0.19, 0.09, 0.8, 0.03, 0.33, 0.9);//kiri
    drawCustomCube(0.63, 0.09, 1.25, 0.9, 0.33, 0.12);//penutup torus
    glTranslatef(0.63, 0.18, 1.29);
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.9, 1.2);
    glutSolidTorus(0.01, 0.10, 30, 30);
    glPopMatrix();
}

void drawMainTV() 
{
    glPushMatrix();
    glTranslatef(1.0, 0.53, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.3, 0.05, 0.3);
    drawVertex();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, 0.53, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.3, 0.05, 0.3);
    drawVertex();
    glPopMatrix();

    //TV
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    drawCustomCube(0.0, 1.45, 0.0, 2.3, 1.35, 0.05);
    glPopMatrix();

    //Layar TV
    glPushMatrix();
    glTranslatef(0.0, 1.48, 0.03);
    glRotatef(180, 0.0, 0.0, 1.0);
    glScalef(-2.2, TV, 0.045);
    drawLayar();
    glPopMatrix();

    // Gambar papan meja
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    drawTexturedCube(0.0, 0.515, 0.0, 2.5, 0.05, 1.35);//atas
    drawTexturedCube(0.0, -0.02, -0.5, 2.3, 0.9, 0.05);//belakang
    drawTexturedCube(0.63, 0.35, 0.46, 1.0, 0.15, 0.04);//atas laci
    glColor3f(1.3, 1.3, 1.3);
    drawCustomCube(0.0, 0.47, 0.4, 2.4, 0.05, 0.05);
    drawCustomCube(0.0, 0.47, -0.4, 2.4, 0.05, 0.05);
    glPopMatrix();

    // Gambar Kaki meja
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    drawCustomCube(1.17, -0.175, 0.5, 0.1, 1.25, 0.07);
    drawCustomCube(1.17, -0.175, -0.5, 0.1, 1.25, 0.07);
    drawCustomCube(1.17, 0.415, 0.0, 0.1, 0.07, 1.0);
    drawCustomCube(1.17, -0.765, 0.0, 0.1, 0.07, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    drawTexturedCube(1.17, -0.2, 0.0, 0.03, 1.2, 0.5);
    glPopMatrix();

    // Gambar Kaki meja yang satunya
    glPushMatrix();
    glScalef(-1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    drawCustomCube(1.17, -0.175, 0.5, 0.1, 1.25, 0.07);
    drawCustomCube(1.17, -0.175, -0.5, 0.1, 1.25, 0.07);
    drawCustomCube(1.17, 0.415, 0.0, 0.1, 0.07, 1.0);
    drawCustomCube(1.17, -0.765, 0.0, 0.1, 0.07, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    drawTexturedCube(1.17, -0.2, 0.0, 0.03, 1.2, 0.5);
    glPopMatrix();

    //Belakang laci
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    drawCustomCube(0.63, -0.021, 0.0, 1.0, 0.9, 0.9);
    glPopMatrix();

    //Laci atas
    glPushMatrix();
    glTranslatef(0.0, -0.0, laciAtasPositionZ);
    laci();
    glPopMatrix();

    //Laci bawah
    glPushMatrix();
    glTranslatef(0.0, -0.37, laciBawahPositionZ);
    laci();
    glPopMatrix();
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)720 / 720, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);

    // Gambar teks di dalam mode proyeksi
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 720, 0, 720);  // Sesuaikan ukuran proyeksi dengan ukuran jendela
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(10, 700);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned const char*)"Q : Menyalakan Layar\nW : Mengganti Gambar\nA : Membuka Laci Atas\nS : Membuka Laci Bawah\nE/R : Merotasi Objek");
    glRasterPos2f(300, 700);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned const char*)"LMB  : Menggerakkan Kamera\nRMB  : Zoom In/Out\nMMB : Menggeser Kamera\nF : Mengganti Teksture Meja");
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Menetapkan pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white_light);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);

    //Objek TV
    glPushMatrix();
    glRotatef(TV2, 0.0, 1.0, 0.0);
    drawMainTV();
    glPopMatrix();
 
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    lastX = x;
    lastY = y;

    if (button == GLUT_LEFT_BUTTON) {
        leftMouseButtonDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_MIDDLE_BUTTON) {
        middleMouseButtonDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        rightMouseButtonDown = (state == GLUT_DOWN);
    }
}

void motion(int x, int y) {
    int deltaX = x - lastX;
    int deltaY = y - lastY;

    if (leftMouseButtonDown) {
        rotateX += deltaY * 0.5;
        rotateY += deltaX * 0.5;

        if (rotateX > 360.0) rotateX = 360.0;
        if (rotateX < -360.0) rotateX = -360.0;
    }
    else if (middleMouseButtonDown) {
        translateX += deltaX * 0.01;
        translateY -= deltaY * 0.01;
    }
    else if (rightMouseButtonDown) {
        translateZ += deltaY * 0.03;
    }
    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(720, 720);
    glutCreateWindow("Meja Lab");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutKeyboardFunc(keyboardFunc);
    loadTextures();
    glutMainLoop();
    return 0;
}
