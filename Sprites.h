#pragma once
#include "Renderer.h"

struct Quad
{
    Quad(){};
    Quad(int X, int Y, int W, int H) 
        : x(X), y(Y), Width(W), Height(H){}
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

	    GLuint CurrentState;
        GLint  AnimationSpeed;

        std::vector<State> States;
        GLuint NumberofStates;

        Image        *Picture;
        VertexBuffer *Vertices;
        IndexBuffer  *Indices;
public:

        void  Render();

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
        