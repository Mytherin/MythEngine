
#define MaxSpotLights 1

in vec4 LightPos;
in vec3 WorldPos0;
in vec3 Normal0;
in vec2 TexCoord0;

out vec4 FragColor;

float GetShadowFactor(vec4 lightPosition)
{
	//convert the position to the projection coordinates 
	vec3 proj = lightPosition.xyz / lightPosition.w;

	//projection coordinates are [-1..1], texture coordinates are [0..1], simply convert them so we can get the values from the shadow map
	vec2 UV;
	UV.x = proj.x * 0.5 + 0.5;
	UV.y = proj.y * 0.5 + 0.5;
	float z = proj.z * 0.5 + 0.5;

	//obtain the depth from the depth texture
	float depth = texture(Texture2D[0],UV).y;

	//if the depth of this texture is deeper than the stored depth, the pixel is behind an object, return 0.5
	if (depth < z - 0.00001)
		return 0.5;
	return 1.0;
}

void main()
{
    vec4 ambient = vec4(0.0);
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);
    for(int i = 0; i < SpotLights; i++)
	{
        vec3 dirToObj =  normalize(WorldPos0 - SL[i].Location);
        float dist = length(WorldPos0 - SL[i].Location);

        float spotlightFactor = 0;

        float directionMatch = dot(normalize(SL[i].Direction),dirToObj);


        if (directionMatch > SL[i].InnerAngle) spotlightFactor = 1;
        else if (directionMatch > SL[i].OuterAngle) spotlightFactor = (directionMatch - SL[i].OuterAngle) / (SL[i].InnerAngle - SL[i].OuterAngle);
		
		
        vec4 ambientchange = vec4(0.0);
        vec4 diffusechange = vec4(0.0);
        vec4 specularchange = vec4(0.0);
        ambientchange = vec4(SL[i].La * Material.Ka,1.0);
        float diffuseFactor = dot(normalize(Normal0),SL[i].Direction);
        if (diffuseFactor > 0)
		{
            diffusechange = vec4(diffuseFactor * SL[i].Ld * Material.Kd,1.0);
            vec3 VertexToEye = normalize(EyePos-WorldPos0);
            vec3 LightReflect = normalize(reflect(SL[i].Direction,Normal0));
            float specularfactor = pow(dot(LightReflect,VertexToEye),Material.SpecularPower);
            if (specularfactor > 0)
				specularchange = vec4(specularfactor * Material.SpecularIntensity * Material.Ks,1.0);
        }


		float attenuation = SL[i].Constant + SL[i].Linear * dist + SL[i].Exp * dist * dist;

        ambient += spotlightFactor * ambientchange / attenuation;
        diffuse += spotlightFactor * diffusechange / attenuation;
        specular += spotlightFactor * specularchange / attenuation;
	}

	//FragColor = texture2D(Texture2D[0],TexCoord0);
	FragColor = /*(ambient+diffuse + specular) **/ vec4(1) * GetShadowFactor(LightPos);// * texture2D(Texture2D[1],TexCoord0.st);
}
