#pragma once
#define _WIP_    1
#define GLEW_STATIC
// I HATE WARNINGS
#pragma warning(disable: 4244)	
#pragma warning(disable: 4005)	
#pragma warning(disable: 4305)	
#pragma warning(disable: 4996)	
#pragma warning(disable: 4099)	


#pragma warning(disable: 4715)	
#pragma warning(disable: 4800)	
#pragma warning(disable: 4018)	

//  THIS IS MY STANDARD GRAPHICS AND MULTIPURPOSE LIB I ADD TO ALMOST ALL MY FILES. JUST WINDOW MANAGEMENT, CALLBACKS FOR THE WINDOW, GUI STUFF ETC.
// ALL WINDOW STATE DATA IS RETRIEVED FROM GLFW CALLBACKS AND SENT TO THE WINDOW OBJECT

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include <ctime>


#define SCREENWIDTH       1280
#define SCREENHEIGHT      960

#define RADIANS(x)   ((x)  * 0.01745329251)
#define DEGREES(x)   ((x)  * 57.2957795131)

#define  _CALLBACK_DEBUG    0

class Image;
class Camera;

extern 
Image   *BlockTexture,
        *StoneTexture, 
        *ShadowTexture;

//const bool TRACE = true;
#define TRACE
#define FUNCTION_TRACE
//#define DEBUG


#define GetRandom( min, max )     ((rand() % (int)(((max) + 1) - (min))) + (min))  
#define RANDOM(x)                 ((rand() * (1.0 / (1.0 + RAND_MAX))) * (x))
#define RANDOM_RANGE(x)           (RANDOM(x * 2) - (x))
#define MIN(a,b)                  ((a<b) ? a : b)
#define MAX(a,b)                  ((a>b) ? a : b)
#define PICK_ONE(a,b)             ((RANDOM(1) > .5) ? a : b)
#define WaitKey                    system("PAUSE");



//======================================================================================================================================================================
//_____________________________________________________________  MACROS  _______________________________________________________________________________________________

#define Print(x)                   std::cout << x << std::endl
#define PrintXY(S,xx,yy)           COORD p = {xx, yy};\
                                   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);\
                                   Print(S);

#define LOG_CALLBACK(x)            std::cout << (x) << std::endl

/*************** DEBUG MACROS FOR DISPLAYING OPEN_GL ERRORS *****************************/
#define ASSERT(x) if(!(x)){exit(EXIT_FAILURE);}

#define ON  true
#define OFF false

const bool TEMP_DEBUGGER = OFF;
#define TEMP_DEBUG(x)   if(TEMP_DEBUGGER){ x }
 
#ifdef TRACE
      #define  _TRACE(x)  std::cout << #x << std::endl
#else
      #define _TRACE(x)
#endif

#ifdef FUNCTION_TRACE
      #define  f_TRACE(x)  std::cout << #x << std::endl
#else
      #define f_TRACE(x)
#endif


#ifdef DEBUG
#define _GL(x)           GLClearError();\
                                    (x);\
                              _TRACE(x);\
                   ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
      #define _GL(x)  x
#endif

#ifdef  DEBUG
    #define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(...))
#else
    #define GLCall(x) x
#endif
/*******************************************************************************************/

#define GL_Color(c)      (c * (.0039215686627451))

//======================================================================================================================================================================
//__________________________________________________________ USEFUL DEFINES  ___________________________________________________________________________________________

#define MOUSE_LEFT       GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT      GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_CENTER     GLFW_MOUSE_BUTTON_MIDDLE

#ifndef M_PI
#    define M_E           2.71828182845904523536
#    define M_LOG2E       1.44269504088896340736
#    define M_LOG10E      0.434294481903251827651
#    define M_LN2         0.693147180559945309417
#    define M_LN10        2.30258509299404568402
#    define M_PI          3.14159265358979323846
#    define M_PI_2        1.57079632679489661923
#    define M_PI_4        0.785398163397448309616
#    define M_1_PI        0.318309886183790671538
#    define M_2_PI        0.636619772367581343076
#    define M_2_SQRTPI1   0.12837916709551257390
#    define M_SQRT2       1.41421356237309504880
#    define M_SQRT1_2     0.707106781186547524401
#endif

#define for_loop(itr, count)          for(int(itr) = 0; itr < (count); itr++)

class  Window;
extern Window *SCREEN;

typedef RECT Rect;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GLM COMPATIBILITY                                                                                                                       
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "C:\Users\Curt\Documents\Visual Studio 2012\Libraries\glm-0.9.2.7\glm\glm.hpp"
#include "C:\Users\Curt\Documents\Visual Studio 2012\Libraries\glm-0.9.2.7\glm\gtc\type_ptr.hpp"
#include "C:\Users\Curt\Documents\Visual Studio 2012\Libraries\glm-0.9.2.7\glm\gtc\matrix_transform.hpp"


typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

typedef glm::mat4 Matrix;

typedef glm::vec3 RGBf;
typedef glm::vec4 RGBAf;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           CALLBACK CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CallBack
{
    public:
        CallBack()
        {
                
            CallBackOnInputFocus     = NULL;
            CallBackOnInputBlur      = NULL;

            CallBackOnKeyDown        = NULL;
            CallBackOnKeyUp          = NULL;
            CallBackOnKeyHold        = NULL;

            CallBackOnMouseFocus     = NULL;
            CallBackOnMouseBlur      = NULL;
            CallBackOnMouseMove      = NULL;
            CallBackOnMouseWheel     = NULL;
                                     
            CallBackOnLButtonDown    = NULL;
            CallBackOnLButtonUp      = NULL;
            CallBackOnRButtonDown    = NULL;
            CallBackOnRButtonUp      = NULL;
            CallBackOnMButtonDown    = NULL;
            CallBackOnMButtonUp      = NULL;
                                   
            CallBackOnMinimize       = NULL;
            CallBackOnRestore        = NULL;
            CallBackOnResize         = NULL;
            CallBackOnExpose         = NULL;
            CallBackOnExit           = NULL;
            CallBackOnUser           = NULL;

        };

        ~CallBack(){};

       void (*CallBackOnInputFocus)           ();
       void (*CallBackOnInputBlur)            ();

       void (*CallBackOnKeyDown)              (GLushort Keycode, GLushort ScanCode, GLushort Modifier , GLubyte rep);                                                    //(SDL_Keysym sym, int mod, Uint16 unicode);
       void (*CallBackOnKeyUp)                (GLushort Keycode, GLushort ScanCode, GLushort Modifier);   
       void (*CallBackOnKeyHold)              (GLushort Keycode, GLushort ScanCode, GLushort Modifier);

       void (*CallBackOnMouseFocus)           ();
       void (*CallBackOnMouseBlur)            ();
       void (*CallBackOnMouseMove)            (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
       void (*CallBackOnMouseWheel)           (bool Up, bool Down); 
                                             
       void (*CallBackOnLButtonDown )         (int mX, int mY);
       void (*CallBackOnLButtonUp  )          (int mX, int mY);
       void (*CallBackOnRButtonDown)          (int mX, int mY);
       void (*CallBackOnRButtonUp )           (int mX, int mY);
       void (*CallBackOnMButtonDown)          (int mX, int mY);
       void (*CallBackOnMButtonUp   )         (int mX, int mY);

       void (*CallBackOnMinimize)             ();
       void (*CallBackOnRestore)              ();
       void (*CallBackOnResize)               (int w,int h);
       void (*CallBackOnExpose)               ();
       void (*CallBackOnExit)                 ();
       void (*CallBackOnUser)                 (GLubyte type, int code, void* data1, void* data2);

       void SetOnInputFocus();
       void SetOnInputBlur();
       
       void SetOnKeyDown(void (*f)   (GLushort Keycode, GLushort ScanCode, GLushort Modifier , GLubyte rep)) {CallBackOnKeyDown     = f;}
       void SetOnKeyUp  (void (*f)   (GLushort Keycode, GLushort ScanCode, GLushort Modifier ))            {CallBackOnKeyUp       = f;}
       void SetOnKeyHold(void (*f)   (GLushort Keycode, GLushort ScanCode, GLushort Modifier ))            {CallBackOnKeyHold       = f;}

       void SetOnMouseFocus                   ();
       void SetOnMouseBlur                    ();
       void SetOnMouseMove(void (*f) (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle))  {CallBackOnMouseMove = f;}
       void SetOnMouseWheel                   (bool Up, bool Down);    
       
       void SetOnLButtonDown(void (*f)        (int, int))                                            {CallBackOnLButtonDown = f;}
       void SetOnLButtonUp(void (*f)          (int, int))                                            {CallBackOnLButtonUp   = f;}
       void SetOnRButtonDown(void (*f)        (int, int))                                            {CallBackOnRButtonDown = f;}
       void SetOnRButtonUp(void (*f)          (int, int))                                            {CallBackOnRButtonUp   = f;}
       void SetOnMButtonDown(void (*f)        (int, int))                                            {CallBackOnMButtonDown = f;}
       void SetOnMButtonUp(void (*f)          (int, int))                                            {CallBackOnMButtonUp   = f;}
       
       void SetOnMinimize                     ();
       void SetOnRestore                      ();
       void SetOnResize                       (int w,int h);
       void SetOnExpose                       ();
       void SetOnExit                         ();
       void SetOnUser                         (GLubyte type, int code, void* data1, void* data2);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    WINDOWS CAMERA CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Cam
{
public:
    Cam(){}
#if 1
    Cam(Vec3 position, Vec3 Rotation)
    { 
            FOV = 45.0;
            AspectRatio = 640.0f / 480.0f;
            Near = 0.1f;
            Far  = 10000.0f;

            Speed = 2.0;

            Position = position;

            horizontalAngle=0;
            verticalAngle=0;

            Forward =  Vec3(0.0f, 0.0f, 1.0f);
            Up      =  Vec3(0.0f, 1.0f, 0.0f);
            
            ProjectionMatrix  = glm::perspective((FOV),  AspectRatio, Near, Far);
            View = GetViewProjection();
    }

    float    FOV, 
             AspectRatio, 
             Near,
             Far;
             
    Vec3     Position,
             Rotation,
             Forward,
             Right,
             Up;
             
    Matrix   ProjectionMatrix;
    Matrix   View;

    float horizontalAngle,
          verticalAngle;


    float Speed;
//    std::vector<Matrix> MatrixStack;
//=======================================================================================================================================================
// FUNCTIONS FOR THE CAMERA CLASS
//=======================================================================================================================================================

    void Update()
    {
           // ClampCamera();
           Forward = Vec3(cos(verticalAngle) * sin(horizontalAngle),
	                    sin(verticalAngle),
		                cos(verticalAngle) * cos(horizontalAngle));

	       Right = Vec3(sin(horizontalAngle - 3.14f / 2.0f),
	                    0,
	                    cos(horizontalAngle - 3.14f / 2.0f));
 
           Up    = glm::normalize(glm::cross(Right, Forward));
    }
 // Direction : Spherical coordinates to Cartesian coordinates conversion
//glm::vec3 direction(
//    cos(verticalAngle) * sin(horizontalAngle),
//    sin(verticalAngle),
//    cos(verticalAngle) * cos(horizontalAngle)
//);
//   

    Matrix GetViewProjection()
    {
        View = glm::lookAt(Position, Position + Forward, Up);
        return ProjectionMatrix;
    }
        
    void Rotate(float pitch, float yaw)
    {
        Rotation.y += yaw;
        Rotation.x += pitch;

        horizontalAngle += .05 * pitch;
	    verticalAngle   += .05 * yaw;
    }
    void MoveForward(float speed)
    { 
            Position -= (Speed * Forward);
            View = glm::translate(glm::mat4(1.0f), Position);
    }
    void MoveBack(float speed)
    {
            Position += (Speed * Forward);
            View = glm::translate(glm::mat4(1.0f), Position);
    }
    void StrifeLeft(float speed)
    {
            Position -= Right * Speed; // glm::normalize(glm::cross(Forward,Up)) * Speed;
            View = glm::translate(glm::mat4(1.0f), Position);
    }
    void StrifeRight(float speed)
    {
            Position += Right * Speed; //Position += glm::normalize(glm::cross(Forward,Up)) * Speed;
            View = glm::translate(glm::mat4(1.0f), Position);
    }
//=======================================================================================================================================================

    void ClampCamera()
    {
      if ( Rotation.x > 90)  Rotation.x =  90;
      if ( Rotation.x < -90) Rotation.x = -90;
      if ( Rotation.y < .0)    Rotation.y  += 360.0f;
      if ( Rotation.y > 360.0f)  Rotation.y  -= 360.0f;
    }

    Matrix RotateX(GLfloat Angle)
    {
        Matrix ret;
            
        return ret;
    }
    Matrix RotateY(GLfloat Angle)
    {
        Matrix ret;
            
        return ret;
    }
    Matrix RotateZ(GLfloat Angle)
    {
        Matrix ret;
            
        return ret;
    }
#endif

};


class Camera2D
{
public:
    Camera2D(){};
    Camera2D(Vec2 position, float width, float height)
    {
        Position = position;
        Zoom = 1.0f;
        Rotation = 0.0f;
        Width = width;
        Height = height;
        CAM_Z = Zoom;

        GLfloat FF_PROJECTION[16];
        glGetFloatv(GL_PROJECTION_MATRIX,  &FF_PROJECTION[0]) ;
        
        ProjectionMatrix[0][0] = FF_PROJECTION[0];
        ProjectionMatrix[0][1] = FF_PROJECTION[1];
        ProjectionMatrix[0][2] = FF_PROJECTION[2];
        ProjectionMatrix[0][3] = FF_PROJECTION[3];
                  
        ProjectionMatrix[1][0] = FF_PROJECTION[4];
        ProjectionMatrix[1][1] = FF_PROJECTION[5];
        ProjectionMatrix[1][2] = FF_PROJECTION[6];
        ProjectionMatrix[1][3] = FF_PROJECTION[7];
                  
        ProjectionMatrix[2][0] = FF_PROJECTION[8];
        ProjectionMatrix[2][1] = FF_PROJECTION[9];
        ProjectionMatrix[2][2] = FF_PROJECTION[10];
        ProjectionMatrix[2][3] = FF_PROJECTION[11];
                  
        ProjectionMatrix[3][0] = FF_PROJECTION[12];
        ProjectionMatrix[3][1] = FF_PROJECTION[13];
        ProjectionMatrix[3][2] = FF_PROJECTION[14];
        ProjectionMatrix[3][3] = FF_PROJECTION[15];

        glGetFloatv(GL_MODELVIEW_MATRIX,  &FF_PROJECTION[0]) ;

        ViewMatrix[0][0] = FF_PROJECTION[0];
        ViewMatrix[0][1] = FF_PROJECTION[1];
        ViewMatrix[0][2] = FF_PROJECTION[2];
        ViewMatrix[0][3] = FF_PROJECTION[3];
        ViewMatrix[1][0] = FF_PROJECTION[4];
        ViewMatrix[1][1] = FF_PROJECTION[5];
        ViewMatrix[1][2] = FF_PROJECTION[6];
        ViewMatrix[1][3] = FF_PROJECTION[7];
        ViewMatrix[2][0] = FF_PROJECTION[8];
        ViewMatrix[2][1] = FF_PROJECTION[9];
        ViewMatrix[2][2] = FF_PROJECTION[10];
        ViewMatrix[2][3] = FF_PROJECTION[11];
        ViewMatrix[3][0] = FF_PROJECTION[12];
        ViewMatrix[3][1] = FF_PROJECTION[13];
        ViewMatrix[3][2] = FF_PROJECTION[14];
        ViewMatrix[3][3] = FF_PROJECTION[15];

    }

    ~Camera2D(){}

   Vec2 Position;
   Vec2 Origin;
   float Rotation;

   Matrix ProjectionMatrix, ModelMatrix, ViewMatrix;


   float CAM_Z;

   inline float GetZoom()
   {
       return Zoom;
   }
   inline void  SetZoom(const float zoom)
   {
       Zoom = zoom;
   }


   void CreateTransform()   {}

   float Width, Height;

   Matrix GetViewMatrix()
   {
       Matrix view;
       Vec2 midOffset = Vec2(this->Width * 0.5, this->Height * 0.5);
   
       view = glm::translate(view, glm::vec3(midOffset, 0.0));
       view = glm::rotate(view, -this->Rotation, Vec3(0.0, 0.0, 1.0));
       view = glm::translate(view, Vec3(-midOffset, 0.0));
       view = glm::translate(view, Vec3(-this->Position, CAM_Z));
   
       return view;
   }

   inline Matrix GetTransform();	


   	struct Transformation
	{
		Matrix       ViewMatrix;
		Vec2         LastPosition;
		float        LastZoom;
		Vec2         LastOrigin;
		float        LastRotation;
		void Update(const Vec2& p, const Vec2& origin, const float zoom, const float rotation)
        {
            LastPosition = p;
            LastOrigin = origin; 
            LastZoom = zoom; 
            LastRotation = rotation;	
        }
	};


private:

   Transformation Transform;
   float Zoom;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         WINDOW CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Window
{
public:
        Window(){}
        ~Window(){glfwTerminate();}
        Window(int,int,int,int,char*);
	    
        int     X,     Y,
            WIDTH,HEIGHT;

        HWND            Hwnd;       // HWND
        char           *TITLE;
        GLFWwindow     *glCONTEXT;   
        
        unsigned  long  TIMER;
        unsigned   int  FRAME_COUNT;
        unsigned   int  FPS;

        struct FrameBuffer
        {
            int WIDTH,
                HEIGHT;
           GLuint NAME;
        }FRAME_BUFFER;
        
        struct MouseProperties
        {
            bool Button[5];      
            int  Action,
                 Modifications;
            double  X,
                    Y;
            int  OldX,Oldy;
            int  MouseMoveX, 
                 MouseMoveY;
            inline bool IsButtonPressed (int button){ return Button[button]; }
            inline void HIDE(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
            inline void SHOW(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL);} 
        }MOUSE;
        
        
        struct Key_Board
        {
             int Key, 
                 Scancode,  
                 Action, 
                 Modifications;
            bool KEY_STATES[350];
          inline bool IsKeyPressed (int keycode)  { return KEY_STATES[keycode];}		
        }KEY_BOARD;
        
        CallBack Callbacks;

        Camera2D Camera;

private:
    unsigned short SyncRATE;
    int           FrameRate;


public:
               int GetFPS()
               { 
                   return FrameRate;
               }


              void Destroy ();

              void SetSyncRate (unsigned short);
    unsigned short GetSyncRate ();

       inline Vec2 GetPosition ();
       inline void SetPosition (GLFWwindow *,int x, int y) ;
       inline void Show() { glfwShowWindow(this->glCONTEXT); }
       inline void Hide() { glfwHideWindow(this->glCONTEXT); }


       void SetOrthographic(int width, int height);

private:	

  static void Error_callback           ( int,    const char*);
  static void Resize_Callback          ( GLFWwindow *window,int,int);
  static void Window_close_callback    ( GLFWwindow *window);
  static void KeyBoard_Callback        ( GLFWwindow *window,    int,    int, int, int);
  static void Mouse_Callback           ( GLFWwindow *window,    int,    int, int);
  static void MouseMove_Callback       ( GLFWwindow *window, double, double);
  static void DropFile_callback        ( GLFWwindow *window,    int, const char**);
  static void Window_Size_Callback     ( GLFWwindow *window,    int,    int);
  
};
 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          HELPER FUNCTIONS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void SYNC();
extern void CLS();
extern void CLS(unsigned long color);
extern bool GameLoop();
extern bool Set_Window_Focus  (Window *);

extern const  char *GetClipBoard();
extern        void  SetClipBoard(char*);

extern GLvoid* BufferObjectPtr( unsigned int idx);

extern void GLClearError();
extern void GLCheckError();
extern bool GLLogCall(const char *function, const char *file, int line);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
extern void *GetAnyGLFuncAddress(const char *name);
extern float WrapAngle(float angle);
// SCREEN RAYCASTER TO GET THE MOUSE XY Position in 3D SPACE
//    http://antongerdelan.net/opengl/raycasting.html


extern Matrix MatCast(float arr[16]);

extern inline float Max(float p1,float p2);
extern inline float Min(float p1, float p2);

extern inline float Squared(float x);
extern inline float GetDistance(Vec3 p1, Vec3 p2);


//
////In a header somewhere.

//PFNGLUSEPROGRAMPROC glUseProgram;
//
////In an initialization routine
//glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");


//PFNGLUSEPROGRAMPROC EXT_compiled_vertex_array;
//GL_ARB_vertex_buffer_object();
//    multi draw arrays
// ARB   pixel buffer object
//  ARB  draw buffers
//  GL EXT draw range elements
//
//  glBindBufferARB();

//#define GL_ARRAY_BUFFER_ARB 0x8892
//#define GL_STATIC_DRAW_ARB 0x88E4
//typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
//typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
//typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
//typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);
// 
//// VBO Extension Function Pointers
//PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;                  // VBO Name Generation Procedure
//PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;                  // VBO Bind Procedure
//PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;                  // VBO Data Loading Procedure
//PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;                // VBO Deletion Procedure












//void CAM_moveCamera(Camera *cam, GLfloat dir)
//{
//  GLfloat rad= (cam->camYaw + dir) * (M_PI/180.0);
//
//  cam->camX -= sin(rad) * cam->moveVel;
//  cam->camZ -= cos(rad) * cam->moveVel;
//}


//int foo()
//{
//        glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
//        glm::mat4 Model = glm::mat4(1.0);
//        Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
//        glm::vec4 Transformed = Model * Position;
//        return 0;
//}
//

