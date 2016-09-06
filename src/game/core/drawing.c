#include "drawing.h"

void begin_drawing(struct Window * window)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void end_drawing(struct Window * window)
{
    glfwSwapBuffers(window->handle);
}

void clear_background(Color color)
{
    glClearColor(color.red, color.green, color.blue, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_rectangle(Point2D position, float width, float height, Color color)
{
    glBegin(GL_QUADS);

    glColor4ub(color.red, color.green, color.blue, color.alpha);

    // Top Left
    glVertex3f(position.x - width / 2, position.y - height / 2, 0.0f);

    // Top Right
    glVertex3f(position.x + width / 2, position.y - height / 2, 0.0f);

    // Bottom Right
    glVertex3f(position.x + width / 2, position.y + height / 2, 0.0f);

    // Bottom Left
    glVertex3f(position.x - width / 2, position.y + height / 2, 0.0f);

    glEnd();
}

void begin_3d(struct Window * window)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, window->viewport_width, window->viewport_height, 0, -1000.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
}

void end_3d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); 
}
