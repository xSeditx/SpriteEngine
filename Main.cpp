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

           Sleep(153);
    Sprite m_Sprite2("MySprite", Picture, 4);
           m_Sprite2.States[0] = State(Picture, Quad(0,   0, 32, 48), 4);
           m_Sprite2.States[1] = State(Picture, Quad(0,  48, 32, 48), 4);
           m_Sprite2.States[2] = State(Picture, Quad(0,48*2, 32, 48), 4);
           m_Sprite2.States[3] = State(Picture, Quad(0,48*3, 32, 48), 4);
           m_Sprite2.Position = Vec2(200);
           m_Sprite2.CurrentState = 1;

    TileMap TileSet(new Image("TestTiles.bmp"), Quad(0,0,15,15));                 

    Shader TileShader("TileShader.vert", "TileShader.frag");


    for_loop(x, 86)
    {
        for_loop(y , 64)
        {
            TileSet.SpawnTile(Vec2(x * 15,y * 15), (int)(y * .5));
        }
    }
 //for_loop(D, 1000)
 //{
 //    TileSet.DestroyTile(1);
 //}
 //
    TileSet.BatchUpdate();
    TileSet.SetShader(TileShader);

    while(GameLoop())
    {
        CLS(0x0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
          //for(auto& B:TileSet.BatchedTiles)
          //{
          //  B->Position.x += RANDOM(2)- 1;
          //  B->Position.y += RANDOM(2)- 1;
          //}
            TileSet.BatchUpdate();
            TileSet.Render();

            if(TileSet.BatchedTiles.size() > 0){TileSet.DestroyTile((int)rand()%TileSet.BatchedTiles.size());}
            m_Sprite.Render();
           

           PrintXY(SCREEN->FPS << "  ",1, 2);
        SYNC();
    }
}