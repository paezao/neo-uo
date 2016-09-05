#include "misc.h"

void Begin3dOrthoMode()
{
    rlglDraw();

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();

    float right = 1.0f;
    float top = 1.0f;

    rlOrtho(0, GetScreenWidth(), GetScreenHeight(), 0, -1000.0f, 1000.0f);

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    rlEnableDepthTest();
}

void DrawLand(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Color tint)
{
    rlEnableTexture(texture.id);

    rlPushMatrix();

    rlScalef(1.0f, 1.0f, 1.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rlTexCoord2f(0,0);
    rlVertex3f((destRec.x - destRec.width / 2) + 0.5f, (destRec.y - destRec.height / 2) + 0.5f, -10.0f);

    rlTexCoord2f(0,1);
    rlVertex3f((destRec.x - destRec.width / 2) + 0.5f, (destRec.y + destRec.height / 2) + 0.5f, -10.0f);
    
    rlTexCoord2f(1,1);
    rlVertex3f((destRec.x + destRec.width / 2) + 0.5f, (destRec.y + destRec.height / 2) + 0.5f, -10.0f);

    rlTexCoord2f(1,0);
    rlVertex3f((destRec.x + destRec.width / 2) + 0.5f, (destRec.y - destRec.height / 2) + 0.5f, -10.0f);

    rlEnd();
    rlPopMatrix();

    rlDisableTexture();
}

void DrawTexMap(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Color tint)
{
    rlEnableTexture(texture.id);

    rlPushMatrix();

    rlScalef(1.0f, 1.0f, 1.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    // Bottom-left corner for texture and quad
    // Bottom Tip
    rlTexCoord2f((float)sourceRec.x / texture.width, (float)sourceRec.y / texture.height);
    rlVertex3f(destRec.x, destRec.y + destRec.height / 2, -10.0f);

    // Bottom-right corner for texture and quad
    // Right Tip
    rlTexCoord2f((float)sourceRec.x / texture.width, (float)(sourceRec.y + sourceRec.height) / texture.height);
    rlVertex3f(destRec.x + destRec.width / 2, destRec.y, -10.0f);

    // Top-right corner for texture and quad
    // Top Tip
    rlTexCoord2f((float)(sourceRec.x + sourceRec.width) / texture.width, (float)(sourceRec.y + sourceRec.height) / texture.height);
    rlVertex3f(destRec.x, destRec.y - destRec.width / 2, -10.0f);

    // Top-left corner for texture and quad
    // Left Tip
    rlTexCoord2f((float)(sourceRec.x + sourceRec.width) / texture.width, (float)sourceRec.y / texture.height);
    rlVertex3f(destRec.x - destRec.width / 2, destRec.y, -10.0f);

    rlEnd();
    rlPopMatrix();

    rlDisableTexture();
}
