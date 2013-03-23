#version 150

in vec2 TexCoord0;
in vec3 Normal0;
out vec4 FragColor;
uniform float Ambient;
struct DiffuseLight
{
    float Diffuse;
    vec3 Direction;
};
uniform DiffuseLight Lights[2];
uniform int LightCount;
uniform float Diffuse;
uniform vec3 Direction;
uniform sampler2D Sampler0;
void main()
{
    vec4 color = vec4(0,0,0,0);

    for(int i = 0; i < LightCount; i++)
	{
        vec4 ambient = vec4(Ambient);
        float diffuseFactor = dot(normalize(Normal0),-Lights[i].Direction);
        vec4 diffuse;
        if (diffuseFactor > 0)
		{
            diffuse = diffuseFactor * Lights[i].Diffuse * vec4(1,1,1,1);        
		}
		else
		{
            diffuse = vec4(0,0,0,0);
        }

		color = color + ambient + diffuse;
    }

    FragColor = color * texture2D(Sampler0,TexCoord0.st);
}





