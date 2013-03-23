
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec2 TexCoordOut;

void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
    TexCoordOut = TexCoord;
}