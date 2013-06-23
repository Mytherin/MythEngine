
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
in vec3 Tangent;

out vec3 WorldPos0;
out vec2 TexCoord0;
out vec3 Normal0;
out vec3 Tangent0;

void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
	TexCoord0   = TexCoord;
	Normal0     = (Model * vec4(Normal,0.0)).xyz;
	WorldPos0   = (Model * vec4(Position,1.0)).xyz;
	Tangent0    = (Model * vec4(Tangent,0.0)).xyz;
}

