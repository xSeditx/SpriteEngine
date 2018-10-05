
#include"World.h"


const int WorldWidth  = 100;
const int WorldHeight = 20;

int WorldData[] = {
    01,02,03,04,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,01,01,01,00,00,00,02,02,02,02,02,00,00,03,03,03,00,00,04,04,04,04,04,04,04,04,04,00,00,05,05,05,05,05,05,05,05,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,00,00,02,00,00,00,00,00,00,03,00,00,03,00,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,00,00,02,00,00,00,00,00,00,03,00,00,00,03,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,02,00,00,00,00,00,00,03,00,00,00,03,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,01,01,00,00,00,00,00,02,02,02,02,00,00,00,03,00,00,00,03,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,01,01,00,00,00,02,00,00,00,00,00,00,03,00,00,00,03,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01,00,00,02,00,00,00,00,00,00,03,00,00,00,03,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,00,00,02,00,00,00,00,00,00,03,00,00,00,03,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,00,00,02,00,00,00,00,00,00,03,00,00,03,00,00,00,00,00,04,00,00,00,00,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,01,01,01,00,00,00,02,02,02,02,02,00,00,03,03,03,00,00,04,04,04,04,04,04,04,04,04,00,00,00,00,00,00,05,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,
};


World::World(int *data, int w, int h)
     :Size(w,h),
      Data(new int[w * h]),
      Player1(Vec2(300,300), Vec2(64,64)),
      TileRender(new Image("TestTiles.bmp"), Quad(0,0,15,15)),
      TileSize(15,15)        
{
    Data = data;

    UVCount     = 0;
    IndexCount  = 0;
    VertexCount = 0;
    Vec3   *Vdata  = new Vec3(0);
    Vec2   *UVData = new Vec2(0);
    GLuint *IData  = new GLuint(0);

    Vertices = new VertexBuffer(Vdata,1);
    UVCoords = new UVBuffer(UVData,1);
    Indices  = new IndexBuffer(IData,1);
}


int  World::GetXY(int x, int y)
{
	return Data[x + (int)Size.x * y];
}
int  World::WorldtoGrid(Vec2 pos)
{
	Vec2 Test(0);

	Test.x = (pos.x / (float)(TileSize.x * Player1.Camera.Zoom));
	Test.y = (pos.y / (float)(TileSize.y * Player1.Camera.Zoom));

	if (Test.x < 0) Test.x = 0;
	if (Test.x >= WorldWidth) Test.x = WorldWidth - 1;

	if (Test.y < 0) Test.y = 0;
	if (Test.y >= WorldHeight) Test.y = WorldHeight - 1;

	return GetXY((int)Test.x,
		         (int)Test.y );
}

void World::Update()
{
    Player1.Update();
    VertexBatch.clear();
    UVBatch.clear();
    IndexBatch.clear();
 
          UVCount     = 0;
          IndexCount  = 0;
          VertexCount = 0;
//=====================================================================================================
//                        UPDATE THE VERTICES FOR THE WINDOW                                                                                                             
//=====================================================================================================

	Vec2 Offset = Vec2((int)(Player1.Camera.Position.x) % (int)(TileSize.x * Player1.Camera.Zoom),
	                   (int)(Player1.Camera.Position.y) % (int)(TileSize.y * Player1.Camera.Zoom));

	float DrawX = 0 - Offset.x,
		  DrawY = 0 - Offset.y;

	for (float y = 0; y <= SCREENHEIGHT; y += (TileSize.y * Player1.Camera.Zoom))
	{
		for (float x = 0; x <= SCREENWIDTH; x += (TileSize.x * Player1.Camera.Zoom))
		{
			float positionx = ((x - Offset.x) + (Player1.Camera.Position.x));
			float positiony = ((y - Offset.y) + (Player1.Camera.Position.y));

			int TileIndex = WorldtoGrid(Vec2(positionx, positiony));

			//if (TileIndex > 0)
			//{
			RenderTile(TileIndex, DrawX , DrawY);
			//}
			DrawX += TileSize.x * Player1.Camera.Zoom;
		}
		DrawY += TileSize.y * Player1.Camera.Zoom;
		DrawX =  -Offset.x;
	}
	Player1.PlayerSprite.CurrentState = Player1.PlayerState;
	Player1.Render();

}
void World::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, Vertices->ID);
        glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vec3), &VertexBatch[0], GL_DYNAMIC_DRAW) ; 

    glBindBuffer(GL_ARRAY_BUFFER, UVCoords->ID); // Update UVBuffer
    UVCoords->ElementCount = VertexCount;
        glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vec2),  &UVBatch[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Indices->ID); // Update IndexBuffer
    Indices->ElementCount = IndexCount;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(GLuint), &IndexBatch[0], GL_DYNAMIC_DRAW);

    Player1.Render();
        TileRender.FullMap->Bind();
            UVCoords->Bind();
                Vertices->Bind();
                    Indices->Bind();
                        glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
}
void World::RenderTile(int tileindex, int x, int y)
{
    //le *PushTile = new Tile(*TileRender.Tiles[tileindex]);
     //  PushTile->Position = Vec2(x,y);

    for_loop(VIndex, TileRender.Tiles[tileindex]->Vertices->ElementCount)
    {
        VertexBatch.push_back((TileRender.Tiles[tileindex]->Vertices->Data[VIndex] * Player1.Camera.Zoom) + Vec3(x, y, 0));
    }
    for_loop(Counter, TileRender.Tiles[tileindex]->Indices->ElementCount)
    {
        IndexBatch.push_back(TileRender.Tiles[tileindex]->Indices->Data[Counter] + VertexCount);
    }
    for_loop(Counter, TileRender.Tiles[tileindex]->UVCoords->ElementCount)
    {
        UVBatch.push_back(TileRender.Tiles[tileindex]->UVCoords->Data[Counter]);
    }
    
    UVCount     += TileRender.Tiles[tileindex]->UVCoords->ElementCount;
    IndexCount  += TileRender.Tiles[tileindex]->Indices->ElementCount;
    VertexCount += TileRender.Tiles[tileindex]->Vertices->ElementCount;
    
  //  BatchedTiles.push_back(PushTile);
}




World::Player::Player(Vec2 pos, Vec2 size)
     : Position(pos) ,
       Size(size),
       Camera((pos),Vec2(1280.f,960.f)),
       PlayerState(0),
       Forward(true),
       Grounded(true)
{
}
void World::Player::MoveLeft(float amount)
{
	Position.x -= amount;
}
void World::Player::MoveRight(float amount)
{
	Position.x += amount;
}
void World::Player::MoveUp(float amount)
{
	Position.y -= amount;
}
void World::Player::MoveDown(float amount)
{
	Position.y += amount;
}
void World::Player::Update()
{
	if (SCREEN->KEY_BOARD.IsKeyPressed(GLFW_KEY_RIGHT))
	{
		  Forward = true;
		  MoveRight(2);
	}
	if (SCREEN->KEY_BOARD.IsKeyPressed(GLFW_KEY_LEFT))
	{
		  Forward = false;
		  MoveLeft(2);
	}
	if (SCREEN->KEY_BOARD.IsKeyPressed(GLFW_KEY_DOWN))
	{
	      MoveDown(2);
	}
	if (SCREEN->KEY_BOARD.IsKeyPressed(GLFW_KEY_UP))
	{
		  MoveUp(2);
	}

	if (SCREEN->KEY_BOARD.IsKeyPressed(GLFW_KEY_SPACE))
    {
        Camera.Zoom += .01;
    }
	if (SCREEN->KEY_BOARD.IsKeyPressed(GLFW_KEY_Z))
    {
        Camera.Zoom -= .01;
    }

	Camera.CameraCenter(Position.x, Position.y);
	Camera.Update();

	Print("Player" << Position.x << " : " << Position.y);
	Print("Camera" << Camera.Position.x << " : " << Camera.Position.y);

	ScreenPosition = Position - Camera.Position;
 
}
void World::Player::Render()
{
    //PlayerSprite.Render();
}


World::Player::Viewport::Viewport(Vec2 pos, Vec2 size)
     : Position(pos),
       Size(size),
       Speed(.5),
       Zoom(1.0f)
{
}

void World::Player::Viewport::Update()
{
	
	float x, y, Distance;
	float Vx, Vy, V;

	x = (float)(Target.x - Position.x);
	y = (float)(Target.y - Position.y);

	if (Squared(x) + Squared(y) <= 1)
	{
		Position = Target;
	}
	else
	{
		Distance = sqrt(Squared(x) + Squared(y));
		V = (Distance * Speed / 60);
		if (V < 1.0f)
		{
		    V = 1.0f;
	    }
		Vx = x * (V / Distance);
		Vy = y * (V / Distance);

		Position.x += Vx;
		Position.y += Vy;
	}
}
void World::Player::Viewport::Render()
{
}

void World::Player::Viewport::CameraCenter(int x, int y)
{
	x = x - (Size.x / 2);
	y = y - (Size.y / 2);
	Target.x = (float)x * Zoom;
	Target.y = (float)y * Zoom;
}
void World::Player::Viewport::CameraGoto(int x, int y)
{
	Target.x = (float)x * Zoom;
	Target.y = (float)y * Zoom ;
}
void World::Player::Viewport::MoveLeft(float amount)
{
	CameraGoto(Position.x - amount* Zoom , Position.y);
}
void World::Player::Viewport::MoveRight(float amount)
{
	CameraGoto(Position.x + amount* Zoom , Position.y);
}
void World::Player::Viewport::MoveUp(float amount)
{
	CameraGoto(Position.x, Position.y - amount* Zoom );
}
void World::Player::Viewport::MoveDown(float amount)
{
	CameraGoto(Position.x, Position.y + amount* Zoom );
}
void World::Player::Viewport::ZoomIn(float amount)
{
	Zoom += amount;
}
void World::Player::Viewport::ZoomOut(float amount)
{
	Zoom -= amount;
}
