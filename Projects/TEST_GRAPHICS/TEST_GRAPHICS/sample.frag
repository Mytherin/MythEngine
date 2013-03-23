#version 150

//in vec3 Position;
in vec2 TexCoord0;

out vec4 FragColor;
uniform sampler2D Sampler0;
void main()
{
    //FragColor = vec4(1,0,0,1);
    FragColor = texture2D(Sampler0,TexCoord0.st);
}


