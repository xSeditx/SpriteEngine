
#include "Window.h"
#include "Sprites.h"
#include "Renderer.h"

extern const int WorldWidth;
extern const int WorldHeight;
extern int WorldData[];

class World
{
public:
    World();
    World(int *data, int w, int h);
    Vec2 Size;
    Vec2 TileSize;
    int *Data;


    TileMap TileRender;
    std::vector<Vec2>   UVBatch;
    std::vector<Vec3>   VertexBatch;
    std::vector<GLuint> IndexBatch;
    //std::vector<Tile*>  BatchedTiles;

    UVBuffer     *UVCoords;
    VertexBuffer *Vertices;
    IndexBuffer  *Indices;

    int UVCount;    
    int IndexCount; 
    int VertexCount;

    int  GetXY(int x, int y);
    int  WorldtoGrid(Vec2 pos);
    void RenderTile(int TileIndex, int x, int y);

    VAOBuffer WindowBuffer;

    class Player
    {
        public:
            Player()
                :Position(0), Size(0){}
            Player(Vec2 pos, Vec2 size);

            Vec2 Position,
                 ScreenPosition,
                 Size;

            Vec2 TileSize;
            Sprite PlayerSprite;
  
            int PlayerState;
            
            bool Grounded;
            bool Jumping;
            bool Forward;


            class Viewport
            {
                public:
                    Viewport()
                        :Position(0), Size(0){}
                    Viewport(Vec2 pos, Vec2 size);

	                void MoveLeft(float amount);
	                void MoveRight(float amount);
	                void MoveUp(float amount);
	                void MoveDown(float amount);
	                void ZoomIn(float amount);
	                void ZoomOut(float amount);
                    
	                void CameraCenter(int x, int y);
	                void CameraGoto(int x, int y);
	                void Update();
                    void Render();
	                //private:
	                Vec2  Position,
	                	  Target,
	                   	  Size;
                    
	                float Zoom,
	                	  Speed;

                    

            }Camera;

        void MoveLeft(float amount);
        void MoveRight(float amount);
        void MoveUp(float amount);
        void MoveDown(float amount);
        void Update();
        void Render();

    }Player1;


    void Update();
    void Render();
};

