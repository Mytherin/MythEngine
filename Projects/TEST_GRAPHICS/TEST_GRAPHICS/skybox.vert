
in vec3 Position;

out vec3 TexCoord0;

void main()
{
    vec4 MVP_Pos = MVP * vec4(Position, 1.0);
    gl_Position = MVP_Pos.xyww;
    TexCoord0 = normalize(Position);
}