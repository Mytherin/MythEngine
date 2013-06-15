
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec4 LightPos;
out vec3 WorldPos0;
out vec3 Normal0;
out vec2 TexCoord0;

uniform mat4 LightVP;


void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
	LightPos = Model * LightVP * vec4(Position,1.0);

	Normal0 = (Model * vec4(Normal,0.0)).xyz;
	WorldPos0 = (Model * vec4(Position,1.0)).xyz;
	TexCoord0 = TexCoord;
}