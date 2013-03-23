#version 150

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec2 TexCoord0;
out vec3 Normal0;

uniform vec3 EyeDir;
uniform vec3 EyePos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 VP;

void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	Normal0 = (Model * vec4(Normal,1.0)).xyz;
}

