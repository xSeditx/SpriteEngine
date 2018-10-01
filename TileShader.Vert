#version 110
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 Color;
uniform sampler2D tex;
void main()
{
gl_TexCoord[0] = gl_MultiTexCoord0;
gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
