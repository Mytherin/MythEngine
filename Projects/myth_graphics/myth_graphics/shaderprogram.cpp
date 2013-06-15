
#include <myth\debug\assert.h>
#include <myth\graphics\lightmanager.h>
#include <myth\graphics\shaderconstants.h>
#include <myth\graphics\shaderprogram.h>

#include <myth\io\filemanager.h>
#include <myth\io\stringext.h>

#include <myth\assets\assetmanager.h>
#include <sstream>

using namespace glm;
using namespace myth::graphics;
using namespace myth::io;
using namespace myth::assets;

ShaderProgram::ShaderProgram(myth::assets::AssetData *assetData, int package) : 
	SourceAsset(assetData,package)
{
	m_linked = false;
	m_shaderProgram = glCreateProgram();

	glBindAttribLocation(m_shaderProgram,0,"Position");
	glBindAttribLocation(m_shaderProgram,1,"TexCoord");
	glBindAttribLocation(m_shaderProgram,2,"Normal");
}

ShaderProgram::~ShaderProgram()
{
	if (m_shaderProgram) glDeleteProgram(m_shaderProgram);
}

void ShaderProgram::LoadFromSource(std::string source)
{
	std::vector<int> shaders = SplitIntegers(source,';');

	for(int i = 0; i < shaders.size(); i++)
	{
		Shader *shader = g_assetManager.GetAsset<Shader>(m_package,shaders[i]);
		AttachShader(*shader);
	}
	Link();
}

void ShaderProgram::ReloadFromSource(std::string source)
{
	Destroy();
	LoadFromSource(source);
}

void ShaderProgram::Destroy()
{
	for(int i = 0; i < m_shaders.size(); i++)
	{
		glDetachShader(m_shaderProgram,m_shaders.resources.elements[i]->id());
	}
	m_shaders.Clear();
}

bool ShaderProgram::IsLoaded()
{
	return m_shaders.size() > 0;
}

void ShaderProgram::AttachShader(Shader& shader)
{
	Assert(!m_shaders.Contains(&shader),"SHADER ATTACHING ERROR: Attempt to attach a shader that was already attached.");
	if (!shader.IsLoaded()) shader.Load();
	glAttachShader(m_shaderProgram,shader.id());
	m_shaders.Add(&shader);

	Uniforms.maxdirectionalLights = max(Uniforms.maxdirectionalLights,shader.MaxDirectionalLights());
	Uniforms.maxspotLights = max(Uniforms.maxspotLights,shader.MaxSpotLights());
	Uniforms.maxpointLights = max(Uniforms.maxpointLights,shader.MaxPointLights());
	Uniforms.samplerCount = max(Uniforms.maxdirectionalLights,shader.MaxSamplerCount());
}

void ShaderProgram::RemoveShader(Shader& shader)
{
	Assert(m_shaders.Contains(&shader),"SHADER DETACHING ERROR: Attempt to detach a shader that was not attached.");
	glDetachShader(m_shaderProgram,shader.id());
	m_shaders.Remove(&shader);
}

void ShaderProgram::Activate() const
{
	Assert(m_linked,"SHADER ACTIVATION ERROR: Attempting to activate a shading program that was not successfully linked first, call \"Link()\" before calling \"Activate()\".");

	DEBUGCODE
	{
		glValidateProgram(m_shaderProgram);

		GLint result;
		glGetProgramiv(m_shaderProgram,GL_VALIDATE_STATUS,&result);
		if (result == GL_FALSE) 
		{
			//capture the log message and print it
			GLint logLen;
			glGetProgramiv( m_shaderProgram, GL_INFO_LOG_LENGTH, &logLen );
			if( logLen > 0 )
			{
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetProgramInfoLog(m_shaderProgram, logLen, &written, log);
				printf(log);
				free(log);
			}
			Assert(result != GL_FALSE,"SHADER ACTIVATION ERROR: Program was not validated. Debug information is printed to console.");
		}
	}

	glUseProgram(m_shaderProgram);
}


void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::Link()
{
	glLinkProgram(m_shaderProgram);

	m_linked = true;

	DEBUGCODE
	{
		GLint result;
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result );


		GLint logLen;
		glGetProgramiv( m_shaderProgram, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 )
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(m_shaderProgram, logLen, &written, log);
			printf(log);
			free(log);
		}

		Assert(result != GL_FALSE,"SHADER LINKING ERROR: Failed to link the shader program!");

		m_linked = result != GL_FALSE;
	}

	GenerateUniformLocations();
}

void ShaderProgram::BindAttribLocation(GLuint location, const char *name)
{
	glBindAttribLocation(m_shaderProgram,location,name);
}

void ShaderProgram::BindFragDataLocation(GLuint location, const char *name)
{
	glBindFragDataLocation(m_shaderProgram,location,name);
}

int ShaderProgram::GetUniformLocation(const char *name) const
{
	return glGetUniformLocation(m_shaderProgram,name);
}

int ShaderProgram::GetUniformLocation(const char *start, const char *end, int index, std::stringstream& ss) const
{
	ss.str("");
	ss << start << index << end;
	return glGetUniformLocation(m_shaderProgram,ss.str().c_str());
}

bool ShaderProgram::UniformExists(const char *name) const
{
	GLint location = glGetUniformLocation(m_shaderProgram,name);
	return location >= 0;
}

void ShaderProgram::PrintAttributes() const
{
	GLint nUniforms, maxLen;
	glGetProgramiv( m_shaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,&maxLen); //get the maximum length of an attribute name
	glGetProgramiv( m_shaderProgram, GL_ACTIVE_ATTRIBUTES,&nUniforms);        //get the amount of attributes

	GLchar * name = (GLchar *) malloc( maxLen );

	GLint size, location;

	GLsizei written;
	GLenum type;
	printf(" Location | Attribute Name\n");
	printf("------------------------------------------------\n");
	for( int i = 0; i < nUniforms; ++i ) 
	{
		glGetActiveAttrib( m_shaderProgram, i, maxLen, &written,
			&size, &type, name );
		location = glGetAttribLocation(m_shaderProgram, name);
		printf(" %-8d | %s\n", location, name);
	}
	free(name);
}

void ShaderProgram::PrintUniforms() const
{
	GLint nUniforms, maxLen;
	glGetProgramiv( m_shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv( m_shaderProgram, GL_ACTIVE_UNIFORMS, &nUniforms);
	GLchar * name = (GLchar *) malloc( maxLen );

	GLint size, location;

	GLsizei written;
	GLenum type;
	printf(" Location | Index | Uniform Name                                 | Size\n");
	printf("--------------------------------------------------------------------------------\n");
	for( int i = 0; i < nUniforms; ++i ) 
	{
		glGetActiveUniform( m_shaderProgram, i, maxLen, &written,
			&size, &type, name );
		location = glGetUniformLocation(m_shaderProgram, name);
		printf(" %-9d | %-5d | %-44s | %d \n", location,i, name,size);
	}
	free(name);
}

void ShaderProgram::PrintUniformValues() const
{
	GLint nUniforms, maxLen;
	glGetProgramiv( m_shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv( m_shaderProgram, GL_ACTIVE_UNIFORMS, &nUniforms);
	GLchar * name = (GLchar *) malloc( maxLen );

	GLint size, location;

	GLsizei written;
	GLenum type;

	std::stringstream ss;

	printf(" Location | Uniform Name                            | Value\n");
	printf("--------------------------------------------------------------------------------\n");
	for( int i = 0; i < nUniforms; ++i ) 
	{
		glGetActiveUniform( m_shaderProgram, i, maxLen, &written, &size, &type, name );
		location = glGetUniformLocation(m_shaderProgram, name);

		ss.str("");
		int count = 0;
		switch (type)
		{
		case GL_FLOAT:      count = count == 0 ? 1 : count;
		case GL_FLOAT_VEC2: count = count == 0 ? 2 : count;
		case GL_FLOAT_VEC3: count = count == 0 ? 3 : count;
		case GL_FLOAT_VEC4: count = count == 0 ? 4 : count;
			float floats[4];
			glGetUniformfv(m_shaderProgram,location,floats);
			ss << "(";
			for(int i = 0; i < count; i++)
			{
				ss << floats[i];
				if (i != count-1) ss << ",";
			}
			ss << ")";
			break;
		case GL_INT:               count = count == 0 ? 1 : count;
		case GL_INT_VEC2:          count = count == 0 ? 2 : count;
		case GL_INT_VEC3:          count = count == 0 ? 3 : count;
		case GL_INT_VEC4:          count = count == 0 ? 4 : count;
		case GL_UNSIGNED_INT:      count = count == 0 ? 1 : count;
		case GL_UNSIGNED_INT_VEC2: count = count == 0 ? 2 : count;
		case GL_UNSIGNED_INT_VEC3: count = count == 0 ? 3 : count;
		case GL_UNSIGNED_INT_VEC4: count = count == 0 ? 4 : count;
			int ints[4];
			glGetUniformiv(m_shaderProgram,location,ints);
			ss << "(";
			for(int i = 0; i < count; i++)
			{
				ss << ints[i];
				if (i != count-1) ss << ",";
			}
			ss << ")";
			break;
		case GL_DOUBLE:      count = count == 0 ? 1 : count;
		case GL_DOUBLE_VEC2: count = count == 0 ? 2 : count;
		case GL_DOUBLE_VEC3: count = count == 0 ? 3 : count;
		case GL_DOUBLE_VEC4: count = count == 0 ? 4 : count;
			double doubles[4];
			glGetUniformdv(m_shaderProgram,location,doubles);
			ss << "(";
			for(int i = 0; i < count; i++)
			{
				ss << doubles[i];
				if (i != count-1) ss << ",";
			}
			ss << ")";
			break;
		}

		printf(" %-9d | %-38s | %s \n", location, name,ss.str().c_str());
	}
	free(name);
}



void ShaderProgram::BindCamera(const Camera& camera)
{
	m_linkedCamera = &camera;
	SetUniform(Uniforms.View,camera.ViewMatrix());
	SetUniform(Uniforms.Projection,camera.ProjectionMatrix());
	SetUniform(Uniforms.VP,camera.ViewProjectionMatrix());
	SetUniform(Uniforms.EyePos,camera.Position());
	SetUniform(Uniforms.EyeDir,camera.Direction());
}

void ShaderProgram::BindModel(glm::mat4 Model)
{
	SetUniform(Uniforms.Model,Model);
	if (Uniforms.MV >= 0) SetUniform(Uniforms.MV, m_linkedCamera->ViewMatrix() * Model);
	if (Uniforms.MVP >= 0) SetUniform(Uniforms.MVP,m_linkedCamera->ViewProjectionMatrix() * Model);
}

void ShaderProgram::BindMaterial(const Material& material)
{
	SetUniform(Uniforms.Ka,material.Ambient_Color);
	SetUniform(Uniforms.Kd,material.Diffuse_Color);
	SetUniform(Uniforms.Ks,material.Specular_Color);
	SetUniform(Uniforms.SpecularIntensity,material.Shininess);
	SetUniform(Uniforms.SpecularPower,material.Shininess_Strength);
}

inline int min(int x, int y)
{
	if (x < y) return x;
	return y;
}

void ShaderProgram::BindLights()
{
	DirectionalLight *d;
	int directionalLights = min(Uniforms.maxdirectionalLights,g_lightManager.DirectionalLights.Count());
	SetUniform(Uniforms.DirectionalLights,directionalLights);
	for(int i = 0; i < directionalLights; i++)
	{
		d = g_lightManager.DirectionalLights.elements[i];

		SetUniform(Uniforms.directionalLight[i].Direction  ,d->direction);
		SetUniform(Uniforms.directionalLight[i].La         ,d->ambientColor);
		SetUniform(Uniforms.directionalLight[i].Ld         ,d->diffuseColor);
	}

	PointLight *p;
	int pointLights = min(Uniforms.maxpointLights,g_lightManager.PointLights.Count());
	SetUniform(Uniforms.PointLights,pointLights);
	for(int i = 0; i < pointLights; i++)
	{
		p = g_lightManager.PointLights.elements[i];

		SetUniform(Uniforms.pointLight[i].Location             ,p->location);
		SetUniform(Uniforms.pointLight[i].La                   ,p->ambientColor);
		SetUniform(Uniforms.pointLight[i].Ld                   ,p->diffuseColor);
		SetUniform(Uniforms.pointLight[i].Constant             ,p->Constant);
		SetUniform(Uniforms.pointLight[i].Linear               ,p->Linear);
		SetUniform(Uniforms.pointLight[i].Exp                  ,p->Exp);
	}

	SpotLight *s;
	int spotLights = min(Uniforms.maxspotLights,g_lightManager.SpotLights.Count());
	SetUniform(Uniforms.SpotLights,spotLights);
	for(int i = 0; i < spotLights; i++)
	{
		s = g_lightManager.SpotLights.elements[i];

		SetUniform(Uniforms.spotLight[i].Location             ,s->location);
		SetUniform(Uniforms.spotLight[i].Direction            ,s->direction);
		SetUniform(Uniforms.spotLight[i].InnerAngle           ,s->innerangle);
		SetUniform(Uniforms.spotLight[i].OuterAngle           ,s->outerangle);
		SetUniform(Uniforms.spotLight[i].La                   ,s->ambientColor);
		SetUniform(Uniforms.spotLight[i].Ld                   ,s->diffuseColor);
		SetUniform(Uniforms.spotLight[i].Constant             ,s->Constant);
		SetUniform(Uniforms.spotLight[i].Linear               ,s->Linear);
		SetUniform(Uniforms.spotLight[i].Exp                  ,s->Exp);
	}
}

void ShaderProgram::BindTexture(GLuint texture, int index)
{
	Assert(index <= Uniforms.samplerCount,"Attempted to bind a texture to a texture index that was out of range of the valid texture indices of the shaderprogram.");
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D,texture);
	SetUniform(Uniforms.Sampler[index],index);
}

void ShaderProgram::GenerateUniformLocations()
{
	//matrices
	Uniforms.Model = GetUniformLocation("Model");
	Uniforms.View = GetUniformLocation("View");
	Uniforms.Projection = GetUniformLocation("Projection");
	Uniforms.MVP = GetUniformLocation("MVP");
	Uniforms.MV = GetUniformLocation("MV");
	Uniforms.VP = GetUniformLocation("VP");
	//camera properties
	Uniforms.EyeDir = GetUniformLocation("EyeDir");
	Uniforms.EyePos = GetUniformLocation("EyePos");
	//material properties
	Uniforms.Ka = GetUniformLocation("Material.Ka");
	Uniforms.Kd = GetUniformLocation("Material.Kd");
	Uniforms.Ks = GetUniformLocation("Material.Ks");
	Uniforms.SpecularIntensity = GetUniformLocation("Material.SpecularIntensity");
	Uniforms.SpecularPower = GetUniformLocation("Material.SpecularPower");
	//light properties
	std::stringstream ss;
	if (Uniforms.maxdirectionalLights > 0)
	{
		Uniforms.DirectionalLights = GetUniformLocation("DirectionalLights");
		Uniforms.directionalLight = new DirectionalLightUL[Uniforms.maxdirectionalLights];
		for(int i = 0; i < Uniforms.maxdirectionalLights; ++i)
		{
			Uniforms.directionalLight[i].Direction = GetUniformLocation("DL[","].Direction",i,ss);
			Uniforms.directionalLight[i].La        = GetUniformLocation("DL[","].La",i,ss);
			Uniforms.directionalLight[i].Ld        = GetUniformLocation("DL[","].Ld",i,ss);
		}
	}

	if (Uniforms.maxpointLights > 0)
	{
		Uniforms.PointLights = GetUniformLocation("PointLights");
		Uniforms.pointLight = new PointLightUL[Uniforms.maxpointLights];
		for(int i = 0; i < Uniforms.maxpointLights; ++i)
		{
			Uniforms.pointLight[i].Location                = GetUniformLocation("PL[","].Location",i,ss);
			Uniforms.pointLight[i].La                      = GetUniformLocation("PL[","].La",i,ss);
			Uniforms.pointLight[i].Ld                      = GetUniformLocation("PL[","].Ld",i,ss);
			Uniforms.pointLight[i].Constant                = GetUniformLocation("PL[","].Constant",i,ss);
			Uniforms.pointLight[i].Linear                  = GetUniformLocation("PL[","].Linear",i,ss);
			Uniforms.pointLight[i].Exp                     = GetUniformLocation("PL[","].Exp",i,ss);
		}
	}

	if (Uniforms.maxspotLights > 0)
	{
		Uniforms.SpotLights = GetUniformLocation("SpotLights");
		Uniforms.spotLight = new SpotLightUL[Uniforms.maxspotLights];
		for(int i = 0; i < Uniforms.maxspotLights; ++i)
		{
			Uniforms.spotLight[i].Location                = GetUniformLocation("SL[","].Location",i,ss);
			Uniforms.spotLight[i].Direction               = GetUniformLocation("SL[","].Direction",i,ss);
			Uniforms.spotLight[i].La                      = GetUniformLocation("SL[","].La",i,ss);
			Uniforms.spotLight[i].Ld                      = GetUniformLocation("SL[","].Ld",i,ss);
			Uniforms.spotLight[i].InnerAngle              = GetUniformLocation("SL[","].InnerAngle",i,ss);
			Uniforms.spotLight[i].OuterAngle              = GetUniformLocation("SL[","].OuterAngle",i,ss);
			Uniforms.spotLight[i].Constant                = GetUniformLocation("SL[","].Constant",i,ss);
			Uniforms.spotLight[i].Linear                  = GetUniformLocation("SL[","].Linear",i,ss);
			Uniforms.spotLight[i].Exp                     = GetUniformLocation("SL[","].Exp",i,ss);
		}
	}


	if (Uniforms.samplerCount > 0)
	{
		Uniforms.Sampler = new int[Uniforms.samplerCount];
		for(int i = 0; i < Uniforms.samplerCount; i++)
		{
			Uniforms.Sampler[i] = GetUniformLocation("Sampler[","]",i,ss);
		}
	}
}