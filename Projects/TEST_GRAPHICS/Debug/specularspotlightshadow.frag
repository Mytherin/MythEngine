in vec2 TexCoordOut;

out vec4 FragColor;

void main()
{
	vec4 color = texture(Sampler[0],TexCoordOut.st);

    //Depth = 1.0 - (1.0 - Depth) * 25.0;
    FragColor = color;
}