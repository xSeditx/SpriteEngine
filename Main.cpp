#include"Window.h"
#include"Renderer.h"
#include"Sprites.h"
bool KD;
void keydown(GLushort Keycode, GLushort ScanCode, GLushort Modifier , GLubyte rep)
{
    KD = true;
}
void keyup(GLushort Keycode, GLushort ScanCode, GLushort Modifier)
{
    KD = false;
}

void main()
{
    Window GAME(0,0,SCREENWIDTH,SCREENHEIGHT, "Testing OpenGL 2D Rendering");
           GAME.SetOrthographic(SCREENWIDTH, SCREENHEIGHT);
           GAME.Callbacks.SetOnKeyDown(keydown);
           GAME.Callbacks.SetOnKeyUp(keyup);
    Image *Picture = new Image("TestAnimation.bmp"); // Image(const char *filename);
    Image *FairyPic = new Image("Fairy.bmp");

    Sprite m_Sprite("MySprite", Picture, 4);
           m_Sprite.States[0] = State(Picture, Quad(0,   0, 32, 48), 4);
           m_Sprite.States[1] = State(Picture, Quad(0,  48, 32, 48), 4);
           m_Sprite.States[2] = State(Picture, Quad(0,48*2, 32, 48), 4);
           m_Sprite.States[3] = State(Picture, Quad(0,48*3, 32, 48), 4);
           m_Sprite.Position = Vec2(100);
           m_Sprite.CurrentState = 1;
           

    Sprite Fairy("Fairy", FairyPic, 4);
           Fairy.States[0] = State(FairyPic, Quad(0,   0, 32, 32), 4);
           Fairy.States[1] = State(FairyPic, Quad(0,  32, 32, 32), 4);
           Fairy.States[2] = State(FairyPic, Quad(0,32*2, 32, 32), 4);
           Fairy.States[3] = State(FairyPic, Quad(0,32*3, 32, 32), 4);
           Fairy.Scale = Vec2(.5);
           Fairy.AnimationSpeed = 100;
           Fairy.CurrentState = 2;
           




glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(GameLoop())
    {
        CLS();
        if(KD == true)
        {
            m_Sprite.CurrentState += 1;
            m_Sprite.CurrentState %= 4;
        }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            m_Sprite.Render();
            Fairy.Render();
           // Sprite::GetByName("MySprite")->Render();
            PrintXY(SCREEN->FPS,10,10);
        SYNC();
    }
}