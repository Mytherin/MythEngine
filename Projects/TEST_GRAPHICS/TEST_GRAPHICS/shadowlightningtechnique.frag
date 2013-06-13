
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
	float depth = texture(Sampler[0],UV).x;

	//if the depth of this texture is deeper than the stored depth, the pixel is behind an object, return 0.5
	if (depth < (z + 0.0001))
		return 0.5;
	return 1.0;
}

void main()
{
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

	//FragColor = texture(Sampler[0],TexCoord0.st) * 0.5;

	//FragColor = vec4(LightPos.x,LightPos.y,LightPos.z,LightPos.w) / 10.0;

    FragColor = color * (0.2 + GetShadowFactor(LightPos));
	//FragColor = color * texture(Sampler[0],TexCoord0).x;
}
