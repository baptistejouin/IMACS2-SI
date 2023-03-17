#include "draw_scene.h"
#include "3D_tools.h"

void drawBase()
{
    glPushMatrix();
    glScalef(3.0, 3.0, 1.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCircle();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0, 2.0, 10.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCone();
    glPopMatrix();
}

void drawArm()
{
    glPushMatrix();
    glScalef(1.6, 1.6, 1.6);
    glColor3f(0.92, 0.81, 0.20);
    drawSphere();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0., 1, 0);
    glScalef(1, 1, 10.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCone();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0., -1, 0);
    glScalef(1, 1, 10.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCone();
    glPopMatrix();
}

void drawPan()
{
    glPushMatrix();
    glScalef(3.0, 3.0, 5.0);
    glColor3f(0.33, 0.45, 0);
    drawCircle();
    glPopMatrix();

    glPushMatrix();

    glBegin(GL_LINES);

    glColor3f(1, 0., 0);
    glVertex3f(0., 0., 5.);
    glVertex3f(cos(M_PI * 2) * 3, sin(M_PI * 2) * 3, 0);

    glVertex3f(0., 0., 5.);
    glVertex3f(cos(M_PI * 2 / 3) * 3, sin(M_PI * 2 / 3) * 3, 0);

    glVertex3f(0., 0., 5.);
    glVertex3f(-cos(M_PI * 2 / 6) * 3, -sin(M_PI * 2 / 6) * 3, 0);
    glEnd();

    glPopMatrix();
}

void drawFrame()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0., 0., 0.);
    glVertex3f(1, 0., 0.);

    glColor3f(0, 1, 0);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 1, 0.);

    glColor3f(0, 0, 1);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., 1);

    glEnd();
}

int rotation = 0;
int rotation2 = 0;
int loopRotation = 0;

void draw()
{

    glPushMatrix();
    glScalef(8.0, 8.0, 8.0);
    drawFrame();
    glPopMatrix();

    drawBase();

    glPushMatrix();
    glRotatef(rotation, 0., 0., 5.);

    glTranslatef(0., 0., 10.);
    glRotatef(rotation2, 0., 1., 0.);
    drawArm();

    glTranslatef(10., 0., -5.);
    drawPan();

    glTranslatef(-20., 0., 0.);
    drawPan();

    glRotatef(rotation, 0., 0., 5.);
    glRotatef(rotation2, 0., 1., 0.);

    glPopMatrix();

    rotation = rotation >= 360 ? 0 : rotation + 1;
    rotation2 += loopRotation ? -1 : 1;

    if (rotation2 <= -15 || rotation2 >= 15)
        loopRotation = !loopRotation;
}