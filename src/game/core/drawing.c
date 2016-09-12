#include "drawing.h"

void begin_drawing(struct window * window)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void end_drawing(struct window * window)
{
    glfwSwapBuffers(window->handle);
    glDisable(GL_BLEND);
}

void clear_background(struct color color)
{
    glClearColor(color.red, color.green, color.blue, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_texture_adv(struct vertex vertices[4], struct texture *texture, struct color color)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture->id );

    glPushMatrix();

    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glColor4ub(color.red, color.green, color.blue, color.alpha);

    // Top Left
    glTexCoord2f( 0.f, 0.f );
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

    // Bottom Left
    glTexCoord2f( 0.f, 1.f );
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    // Bottom Right
    glTexCoord2f( 1.f, 1.f );
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

    // Top Right
    glTexCoord2f( 1.f, 0.f );
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_texture(struct rectangle rect, struct texture *texture, struct color color)
{
    struct vertex vertices[4] = {
        {rect.x - rect.width / 2, rect.y - rect.height / 2, -1.0f},
        {rect.x - rect.width / 2, rect.y + rect.height / 2, -1.0f},
        {rect.x + rect.width / 2, rect.y + rect.height / 2, -1.0f},
        {rect.x + rect.width / 2, rect.y - rect.height / 2, -1.0f}
    };

    draw_texture_adv(vertices, texture, color);
}

void begin_3d(struct window * window)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, window->width, window->height, 0, -1000.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void end_3d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); 
}
