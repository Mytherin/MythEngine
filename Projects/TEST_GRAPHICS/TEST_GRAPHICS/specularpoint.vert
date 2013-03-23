
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec3 WorldPos0;
out vec2 TexCoord0;
out vec3 Normal0;

void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	//Normal0 = Normal;
	//Normal0 = Normal/2+0.5;
	Normal0 = (Model * vec4(Normal,0.0)).xyz;
	WorldPos0 = (Model * vec4(Position,1.0)).xyz;
}

