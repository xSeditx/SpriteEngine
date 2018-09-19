#include"Sprites.h"
#include<memory>

        
std::vector<Sprite *> Sprite::List;
int Sprite::Count = 0;


//=========================================================================================================================================
//_______________________________________  Frame Class ____________________________________________________________________________________
//                                                                                                                                  
//Each Frame is a UV buffer whos Index is Bound prior to rendering in accordance with the current timestep for the Animated Sprite
//=========================================================================================================================================
// I suppose I could also store the Frame Data linearly here and
// Offset to the frame that I wish to render from
// That might be the best method honestly.

Frame::Frame(Image *img, Quad f)
{
    float UnitX = (1.0f / img->Width);
    float UnitY = (1.0f / img->Height);

    Coords[0] = Vec2((float)f.x * UnitX + (float)f.Width * UnitX, (float)f.y * UnitY + (float)f.Height * UnitY);
    Coords[1] = Vec2((float)f.x * UnitX , (float)f.y * UnitY + (float)f.Height * UnitY);
    Coords[2] = Vec2((float)f.x * UnitX , (float)f.y * UnitY);
    Coords[3] = Vec2((float)f.x * UnitX + (float)f.Width * UnitX, (float)f.y * UnitY);

    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , Coords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Frame::Bind()
{
      glBindBuffer(GL_ARRAY_BUFFER, ID);      
        glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void Frame::Unbind()
{
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

//=========================================================================================================================================
//_______________________________________  State Class ____________________________________________________________________________________
//                                                                                                                                  
//   Each State is a state that an Entity can be in, Dead alive etc and is a group of frames that represents a state of the StaticSprite
//=========================================================================================================================================

State::State(Image *img, Quad srcrect, GLuint numframes)
     :TotalFrames(numframes)
{
    CurrentFrame = 0;
    Frames.reserve(numframes);
    GLuint x = srcrect.x;
    for_loop(Count, numframes)
    {
        Quad  Source(x, srcrect.y, srcrect.Width, srcrect.Height);
        Frame frame(img, Source);
        x += srcrect.Width;
       *this += frame;
    }
}
std::vector<Frame> &State::AddFrame(Frame frame)
{
	Frames.emplace_back(frame);
	return Frames;
} // Adds a frame to the State

//=========================================================================================================================================
//_______________________________________  Sprite Class ___________________________________________________________________________________
//                                                                                                                                  
// Sprite is a Collection of States which can be Enumerated or Defined so Various Animations can play our in accordance with Gameplay
//=========================================================================================================================================

Sprite::Sprite(char *name, Image *source, int numstates)
      : NumberofStates(numstates), 
        ID(Count++),   
        Name(name),
        Scale(Vec2(1)),
        CurrentState(0),
        AnimationSpeed(150),
        Picture(source),
        Position(Vec2(0))
{     

    States.reserve(numstates);
    
    for_loop(count, NumberofStates)
    {
        State temp;
        States.emplace_back(temp);
    }

    Vec3 VertexData[] = 
    {
         Vec3(0,0,0),
         Vec3(Picture->Width, 0, 0),
         Vec3(Picture->Width, Picture->Height,0),
         Vec3(0,Picture->Height, 0), 
    };

    GLuint IndexData[] = 
    {
        2,3,1,  0,1,3,
    };

    Vertices = new VertexBuffer(  &VertexData[0], 4); 
    Indices =  new IndexBuffer(   &IndexData[0], 6);

    List.push_back(this);
}
void Sprite::Render()
{
    GLuint ticks = (glfwGetTime() * 1000);
    int CF = (ticks / AnimationSpeed) % States[CurrentState].TotalFrames;

    glPushMatrix();
    Picture->Bind();
        glTranslatef(Position.x, Position.y, 0.0f);
        glScalef(Scale.x, Scale.y,0.0f);
        Vertices->Bind();
            Indices->Bind();
                States[CurrentState].Frames[CF].Bind();
                     glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
                States[CurrentState].Frames[CF].Bind();
            Indices->Unbind();
        Vertices->Unbind();
    Picture->Unbind();
    glPopMatrix();
}
// I could also probably change the Data in the UV buffer every frame update to reflect the correct position in the
// Image used to render from by providing a new Source rect everytime.


