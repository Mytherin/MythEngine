#version 150

in vec2 TexCoord0;

out vec4 FragColor;

uniform sampler2D Sampler0;

void main()
{
   FragColor = texture2D(Sampler0,TexCoord0.st);
}






