#pragma once
#include<vector>
#include"Window.h"
#include"Shader.h"

//=========================================== DEBUG SWITCHES ==========================================================
#define _TEXTURE_DEBUG    0
#define      _UV_DEBUG    0
 //====================================================================================================================





#define VERTEX_ATTRIB     0
#define NORMAL_ATTRIB     1
#define TEXTURE_ATTRIB    2
#define COLOR_ATTRIB      3

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

#define MAX_OBJECTS    10000


using namespace std;
using namespace glm;

struct Vertex
{
    Vec3 Position;
    Vec3 Normals;
    Vec2 Uv;
};

class VertexBuffer
{
    public:
        VertexBuffer(){}
       ~VertexBuffer();
        VertexBuffer(Vec3 *Vertexdata, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 

        Vec3  *Data;

        void Bind();
        void Unbind();

        void Lock(GLenum access);
        void Unlock();

        GLfloat *Read();
        void Write(GLuint pos, GLfloat data); 

        void Rebuild();
};  
class ColorBuffer
{
   public:
        ColorBuffer(){}
       ~ColorBuffer();
        ColorBuffer(Vec3 *ColorData, GLsizei count);
        ColorBuffer(Vec4 *ColorData, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 

        Vec4 *Data;

    public:
        void Bind();
        void Unbind();
};
class NormalBuffer
{
    public:
        NormalBuffer(){}
       ~NormalBuffer();
        NormalBuffer(Vec3 *NormalData, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 
        Vec3  *Data;

    public:
        void Bind();
        void Unbind();
};
class IndexBuffer
{
    public:
        IndexBuffer(){}
       ~IndexBuffer();
        IndexBuffer(GLuint *data, GLsizei count);

        GLuint ID;
        GLuint ElementCount;
        GLuint *Data;

    public:
        void Bind();
        void Unbind();
};
class UVBuffer
{
public:
    UVBuffer();
   ~UVBuffer();
    UVBuffer(Vec2 *UVdata, GLsizei count);

    GLuint ID;
    GLuint ElementCount;

    Vec2    *Data;
public:
    void Bind();
    void Unbind();
};
class Image
{
public:
        Image();
       ~Image();
        Image(const char *filename);
        Image(GLenum param, const char *filename);
       
        GLuint ID;
       
        GLubyte header[54];
        GLuint  dataPos;
       
        GLuint  Width,
                Height,
                ImageSize;
       
        GLubyte *Data;
       
//        GLuint ElementCount;
       
        GLubyte* LoadBMP      (const char *filename); // Possibly make this Static and return an entire Image object
       
        void SetSize(float width, float height);
        void GenColorTexture(float width, float height);
        void GenDepthTexture(float width, float height);
        void Bind();
        void Unbind();
};
class TextureBuffer
{
public:
    TextureBuffer();
   ~TextureBuffer();
    TextureBuffer(Image &img, Vec2 *UVdata, GLsizei count);

    GLuint ID;
    GLuint ElementCount;

    Vec2    *Data;
    Image Picture;
public:

    void Bind();
    void Unbind();
};

class RenderBuffer
{
public:
    RenderBuffer(){}
   ~RenderBuffer();
    RenderBuffer(Shader &shader, GLuint Width, GLuint Height);
    RenderBuffer(Shader &shader ); // FUTURE AFTER RB CLASS IS FINISHED

    Shader RBShader;

    GLuint ID;

    GLuint TexCoordsID;

    void Bind();
    void Unbind();
    void Render();

    void PositionQuad(Vec3 pos);
    void RotateQuad(Vec3 rot);

private:
    void MakeTestQuad();

    GLsizei Width,Height;
    GLsizei WindowWidth,WindowHeight;

    VertexBuffer  *TestQuad;
    IndexBuffer   *TestQuadIBO;

    Vec3 Position, Rotation;
};
class FrameBuffer
{
public:

   ~FrameBuffer();
    FrameBuffer(Shader &shader, GLuint Width, GLuint Height);
    FrameBuffer(Shader &shader, RenderBuffer rendernb); // FUTURE AFTER RB CLASS IS FINISHED


    Shader FBShader;

    GLuint ID;

    Image ColorTexture;
    Image DepthTexture;

    void Bind();
    void Unbind();
    void Render();

    void PositionQuad(Vec3 pos);
    void RotateQuad(Vec3 rot);

    void AttachRenderBuffer(RenderBuffer *rbuffer);
    void AttachUVBuffer(Image *texture);
private:
    void MakeTestQuad();

    GLsizei Width,Height;
    GLsizei WindowWidth,WindowHeight;

    VertexBuffer  *TestQuad;
    IndexBuffer   *TestQuadIBO;

    GLuint TexCoordsID;
    Vec3 Position, Rotation;

    GLubyte DrawBufferCount;
};



class VAOBuffer
{
public:
       VAOBuffer();
      ~VAOBuffer(){}

       VertexBuffer *Vertices;
       IndexBuffer  *Indices;
       NormalBuffer *Normals;
       TextureBuffer     *Textures;
       ColorBuffer  *Colors;

       void Attach(VertexBuffer *vertices);
       void Attach(IndexBuffer  *indices);
       void Attach(NormalBuffer *normals);
       void Attach(TextureBuffer     *textures);
       void Attach(ColorBuffer  *color);

       void Bind();
       void Unbind();
};

// CONVERT THIS NAME TO SOMETHING LIKE IMAGE SINCE IT DOES NOT MAKE A TEXTURE BUT INSTEAD LOADS AN IMAGE
// THE TEXTUREBUFFER SHOULD EITHER BECOME TEXTURE OR PROB EVEN BETTER CALLED UV_BUFFER OR SOMETHING AND HAVE 
// A TEXTURE CLASS WHICH IS ITSELF A COMBINATION OF THE IMAGE AND THE TEXTURE COORDS SO THAT THEY CAN BE LOADED
// AND UNLOADED AT THE SAME TIME OR SEPERATELY AS NEEDED.

// ADD ALL VARIOUS BUFFERS TO A SINGLE BUFFER VERTEX, INDEX, COLOR, TEXTURE, NORMALS etc... 
// Into a single Buffer for their type, Bind each buffer than call  Draw Instances


//1.	Uniform Buffer Objects
//2.	Texture Buffer Objects
//3.	Instanced_arrays_ARB

//=============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________

//1. pbuffer extension initialization
//2. pbuffer creation
//3. pbuffer binding
//4. pbuffer destruction. 

class PBuffer
{
    PBuffer(){}
    ~PBuffer(){}
    PBuffer( GLuint width, GLuint height);



      GLuint width;
      GLuint height;
};
