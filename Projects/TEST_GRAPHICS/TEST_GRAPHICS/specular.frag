#version 150

in vec3 WorldPos0;
in vec2 TexCoord0;
in vec3 Normal0;

out vec4 FragColor;

struct MaterialProperties
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float SpecularIntensity;
	float SpecularPower;
};

uniform MaterialProperties Material;

uniform vec3 EyeDir;
uniform vec3 EyePos;
uniform float Ambient;
uniform float Diffuse;
uniform vec3 Direction;
uniform sampler2D Sampler0;

void main()
{
    vec4 ambient = vec4(Ambient * Material.Ka,1.0);
	vec4 diffuse = vec4(0.0);
	vec4 specular = vec4(0.0);

    float diffuseFactor = dot(normalize(Normal0),-Direction);
    if (diffuseFactor > 0)
	{
        diffuse = vec4(diffuseFactor * Diffuse * Material.Kd,1.0);

		vec3 VertexToEye = normalize(EyePos-WorldPos0);
		vec3 LightReflect = normalize(reflect(Direction,Normal0));
		float specularfactor = pow(dot(LightReflect,VertexToEye),Material.SpecularPower);

		if (specularfactor > 0)
			specular = vec4(specularfactor * Material.SpecularIntensity * Material.Ks,1.0);
    }

   FragColor = (ambient + diffuse + specular) * texture2D(Sampler0,TexCoord0.st);
}






