#version 110
uniform sampler2D tex;
uniform vec3 Color;
void main()
{
vec4 texelColor0 = texture2D(tex, gl_TexCoord[0].xy);
gl_FragColor = texelColor0 * .5;
}