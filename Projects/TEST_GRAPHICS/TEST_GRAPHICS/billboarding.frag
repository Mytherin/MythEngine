
in vec2 TexCoord;
out vec4 FragColor;

void main()
{
    FragColor = texture2D(Texture2D[0], TexCoord);

    if (FragColor.r == 0 && FragColor.g == 0 && FragColor.b == 0) 
	{
        discard;
    }
}