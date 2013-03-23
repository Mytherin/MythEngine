in vec2 TexCoordOut;

out vec4 FragColor;

void main()
{
	vec4 color = texture(Sampler[0],TexCoordOut.st);

    FragColor = color;
}