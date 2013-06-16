
in vec2 TexCoord0;

out vec4 FragColor;

void main()
{
    float Depth = texture(Texture2D[0], TexCoord0).x;
    Depth = 1.0 - (1.0 - Depth) * 25.0;
    FragColor = vec4(Depth);
}