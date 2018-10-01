#pragma once
#include "Renderer.h"

struct Quad
{
    Quad(){};
    Quad(int X, int Y, int W, int H) 
        : x(X), y(Y), Width(W), Height(H){}
    Quad(Vec2 pos, Vec2 size) 
        : x(pos.x), y(pos.y), Width(size.x), Height(size.y){}

    int x,y;
    int Height,Width;
};

class Frame
{
public:
    Frame(){}
    Frame(Image*img, Quad f);

    Vec2 Coords[4];
    GLuint ID;

    void Bind();
    void Unbind();
};
class State
{
public:
	    State(){}
	   ~State(){}

	    State(Image *img, Quad sourcerect,uint numframes);

	    std::vector<Frame> Frames;

	    uint TotalFrames;
	    uint CurrentFrame;

        State operator +=(Frame newframe)
        { 
            this->AddFrame(newframe);  
            return *this;
        }
        State operator +=(State newstate)
        {
            for_loop(count, newstate.TotalFrames)
            {
                this->AddFrame(newstate.Frames[count]); 
                this->TotalFrames++;
            }
            return *this;
        }
        
private:
		std::vector<Frame>& AddFrame(Frame frame);
};
class Sprite
{
public:
	    Sprite(){}
       ~Sprite(){}

        Sprite(char *name, Image *source, int numstates);

        int ID;

        Vec2 Position;
        Vec2 Size;
        Vec2 Scale; // Possibly one in the same;

        Matrix ModelMatrix;

	    GLuint CurrentState;
        GLint  AnimationSpeed;

        std::vector<State> States;
        GLuint NumberofStates;

        Image        *Picture;
        VertexBuffer *Vertices;
        IndexBuffer  *Indices;
        int Lifetime;
public:

        void Render();
        void Update();

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC METHODS FOR MANAGING SPRITE ASSETS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        char *Name;

    static Sprite *GetByName(char *name)
    {
        for_loop(Index, Count)
        {
            if(List[Index]->Name == name)
            {
                return List[Index];
            }
        }
      return nullptr;
    }
    static std::vector<Sprite *> List;
    static int Count;
};
 


class TileMap;
class Tile
{
public:
    Tile(TileMap* source, Quad area);

    Vec2 Position;
    Vec2 Size;
    Vec2 Scale;

    uint ID;

    Image        *Picture;

    UVBuffer     *UVCoords;
    VertexBuffer *Vertices;
    IndexBuffer  *Indices;

    void Render();
    void Render(Vec2 pos);
};
class TileMap
{
public:
    TileMap(Image *img, Quad f);

    Image *FullMap;


    int BorderX,
        BorderY;

    std::vector<Tile*> Tiles;
    std::vector<Tile*> BatchedTiles;

    int  SpawnTile(Vec2 pos, GLuint tileindex);
    void DestroyTile(GLuint tileindex);
    void SetShader(Shader &renderer){ Renderer = &renderer;}

    GLuint NumberOfTiles;

    Shader *Renderer;

    UVBuffer     *UVCoords;
    VertexBuffer *Vertices;
    IndexBuffer  *Indices;

    GLuint IndexCount, VertexCount, UVCount;
    std::vector< Vec2> UnionPos;

    std::vector<Vec2>   UVBatch;
    std::vector<Vec3>   VertexBatch;
    std::vector<GLuint> IndexBatch;
    
    void BatchUpdate();
    void Render();
};
