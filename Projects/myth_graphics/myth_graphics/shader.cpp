
#include <myth\debug\assert.h>
#include <myth\generic\numerics.h>
#include <myth\graphics\shader.h>
#include <myth\graphics\shaderprogram.h>
#include <myth\io\parser.h>
#include <sstream>

using namespace myth::graphics;
using namespace myth::io;

Shader::Shader(GLenum shaderType,myth::assets::AssetData *assetData, int package) :
	SourceAsset(assetData,package), m_shaderType(shaderType),m_shaderHandle(0)
{
}

Shader::~Shader()
{
	Destroy();
}

void Shader::LoadFromSource(std::string source)
{
	GLuint shader = Create(m_shaderType,source);

	if (shader)
	{
		m_shaderHandle = shader;
	}
}

void Shader::ReloadFromSource(std::string source)
{
	Destroy();

	LoadFromSource(source);
}

bool Shader::IsLoaded()
{
	return m_shaderHandle;
}

void Shader::Destroy()
{
	if (m_shaderHandle)
	{	
		glDeleteShader(m_shaderHandle);
	}
	m_shaderHandle = 0;
}

GLuint Shader::Create(GLenum type, std::string source)
{
	GLuint shader = glCreateShader(type);

	Assert(shader, "SHADER CREATION ERROR: Could not create a shader of the specified shader type.");

	KeyValueMap map = Parser::ParseAssignments(source, String("#define %n %v") + Parser::LineEnd(), false, true);

	//parse shader source to find max lights, if the information is not there, add the default information
	

	m_maxdirectionalLights = map.count("MaxDirectionalLights")       ? Int::ParseString(map["MaxDirectionalLights"]) : DefaultDirectionalLights;
	m_maxpointLights       = map.count("MaxPointLights")             ? Int::ParseString(map["MaxPointLights"])       : DefaultPointLights;
	m_maxspotLights        = map.count("MaxSpotLights")              ? Int::ParseString(map["MaxSpotLights"])        : DefaultSpotLights;
	m_sampler2DCount       = map.count("MaxSampler2D")               ? Int::ParseString(map["MaxSampler2D"])         : DefaultSampler2DCount;
	m_sampler3DCount       = map.count("MaxSampler3D")               ? Int::ParseString(map["MaxSampler3D"])         : DefaultSampler3DCount;
	
	//prepend uniform variables used in the shader (matrices, samplers, light information)
	std::stringstream ss;
	ss << "#version 150 \n";
	ss << "#define MaxDirectionalLights "   << m_maxdirectionalLights <<   "\n"; 
	ss << "#define MaxPointLights "         << m_maxpointLights       <<   "\n";
	ss << "#define MaxSpotLights "          << m_maxspotLights        <<   "\n";
	ss << "#define MaxSampler2D "           << m_sampler2DCount       <<   "\n";
	ss << "#define MaxSampler3D "           << m_sampler3DCount       <<   "\n";
	ss << 
		"uniform int DirectionalLights;                                \n"
		"uniform int PointLights;                                      \n"
		"uniform int SpotLights;                                       \n"
		"uniform mat4 Model;                                           \n"
		"uniform mat4 View;                                            \n" 
		"uniform mat4 Projection;                                      \n" 
		"uniform mat4 MVP;                                             \n" 
		"uniform mat4 MV;                                              \n"
		"uniform mat4 VP;                                              \n" 
		"struct MaterialProperties                                     \n" 
		"{                                                             \n"
		"	vec3 Ka;                                                   \n"
		"	vec3 Kd;                                                   \n"
		"	vec3 Ks;                                                   \n" 
		"	float SpecularIntensity;                                   \n"
		"	float SpecularPower;                                       \n"
		"};                                                            \n"
		"uniform MaterialProperties Material;                          \n"
		"struct DirectionalLight                                       \n"
		"{                                                             \n"
		"	vec3 La;                                                   \n"
		"	vec3 Ld;                                                   \n"
		"	vec3 Direction;                                            \n"
		"};                                                            \n";
	if (m_maxdirectionalLights > 0)
		ss << "uniform DirectionalLight DL[MaxDirectionalLights];      \n";
	ss << 
		"struct PointLight                                             \n"
		"{                                                             \n"
		"	vec3 La;                                                   \n"
		"	vec3 Ld;                                                   \n"
		"	vec3 Location;                                             \n"
		"	float Constant;                                            \n"
		"	float Linear;                                              \n"
		"	float Exp;                                                 \n"
		"};                                                            \n";
	if (m_maxpointLights > 0)
		ss << 	"uniform PointLight PL[MaxPointLights];                \n";
	ss <<
		"struct SpotLight                                              \n"
		"{                                                             \n"
		"	vec3 La;                                                   \n"
		"	vec3 Ld;                                                   \n"
		"	vec3 Location;                                             \n"
		"	vec3 Direction;                                            \n"
		"	float InnerAngle;                                          \n"
		"	float OuterAngle;                                          \n"
		"	float Constant;                                            \n"
		"	float Linear;                                              \n"
		"	float Exp;                                                 \n"
		"};                                                            \n";
	if (m_maxspotLights > 0)
		ss << 	"uniform SpotLight SL[MaxSpotLights];                  \n";
	ss << 		
		"uniform vec3 EyePos;                                          \n"
		"uniform vec3 EyeDir;                                          \n";
	ss << 
		"uniform sampler2D Texture2D[" << m_sampler2DCount << "];      \n";
	ss << 
		"uniform samplerCube Texture3D[" << m_sampler3DCount << "];    \n";
	std::string str = ss.str();

	const GLchar *codeArray[] = {str.c_str(), source.c_str()};
	
	glShaderSource(shader,2,codeArray,NULL);

	glCompileShader(shader);

	//check if the shader compiled properly
	GLint result;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&result);
	if (result == GL_FALSE) 
	{
		//capture the log message and print it
		GLint logLen;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 )
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			printf("SHADER CREATION ERROR LOG:\n ");
			printf(log);
			free(log);
		}
		Assert(0,"SHADER CREATION ERROR: Shader compilation failed.");
		return 0;
	}

	return shader;
}
