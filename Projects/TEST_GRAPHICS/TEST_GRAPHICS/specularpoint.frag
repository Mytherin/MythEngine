
in vec3 WorldPos0;
in vec2 TexCoord0;
in vec3 Normal0;
out vec4 FragColor;
uniform sampler2D Sampler0;
void main()
{
    vec4 ambient = vec4(0.0);
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

	for(int i = 0; i < PointLights; i++)
	{
		vec3 direction =  normalize(WorldPos0 - PL[i].Location);
		float dist = length(WorldPos0 - PL[i].Location);

		vec4 ambientchange = vec4(0.0);
		vec4 diffusechange = vec4(0.0);
		vec4 specularchange = vec4(0.0);

		ambientchange = vec4(PL[i].La * Material.Ka,1.0);
		float diffuseFactor = dot(normalize(Normal0),-direction);
		if (diffuseFactor > 0)
		{
			diffusechange = vec4(diffuseFactor * PL[i].Ld * Material.Kd,1.0);
			vec3 VertexToEye = normalize(EyePos-WorldPos0);
			vec3 LightReflect = normalize(reflect(direction,Normal0));
			float specularfactor = pow(dot(LightReflect,VertexToEye),Material.SpecularPower);
			if (specularfactor > 0)
				specularchange = vec4(specularfactor * Material.SpecularIntensity * Material.Ks,1.0);
		}

		float attenuation = PL[i].Constant + PL[i].Linear * dist + PL[i].Exp * dist * dist;

		ambient += ambientchange / attenuation;
		diffuse += diffusechange / attenuation;
		specular += specularchange / attenuation;
	}

	
	
	FragColor = (ambient + diffuse + specular) * texture2D(Sampler0,TexCoord0.st);
}







