in vec3 TexCoord0;

out vec4 FragColor;

void main()
{
    FragColor = texture(Texture3D[0], TexCoord0);
}