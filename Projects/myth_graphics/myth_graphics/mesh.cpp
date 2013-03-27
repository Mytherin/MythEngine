
#include <myth\debug\assert.h>
#include <myth\graphics\mesh.h>

using namespace myth::graphics;

Mesh::Mesh(myth::assets::FilePath *assetData, int package) :
	FileAsset(assetData,package),m_meshes(0),m_textures(0),m_materials(0)
{

}


Mesh::~Mesh()
{
	Destroy();
}


void Mesh::LoadFromFile(std::string filepath)
{
	bool success = false;
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filepath.c_str(), aiProcess_Triangulate);

	if (scene) 
	{
		InitFromScene(scene, filepath);
	}
	else
	{
		printf("MESH LOAD ERROR: Error loading mesh '%s': '%s'\n", filepath.c_str(), importer.GetErrorString());
	}
}

void Mesh::ReloadFromFile(std::string filepath)
{
	Destroy();
	LoadFromFile(filepath);
}

void Mesh::Destroy()
{
	if (m_meshes) delete [] m_meshes;
	if (m_textures) delete [] m_textures;
	if (m_materials) delete [] m_materials;

	m_meshes = 0;
	m_textures = 0;
	m_materials = 0;
}

bool Mesh::IsLoaded()
{
	return (m_meshes);
}

bool Mesh::InitFromScene(const aiScene* scene, const std::string& filename)
{  
	m_meshCount = scene->mNumMeshes;
	m_materialCount = scene->mNumMaterials;
	m_meshes = new ModelMesh[m_meshCount];
	m_textures = new Texture[m_materialCount];
	m_materials = new Material[m_materialCount];

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0 ; i < m_meshCount; ++i) 
	{
		const aiMesh* aiMesh = scene->mMeshes[i];
		InitMesh(i, aiMesh);
	}

	return InitMaterials(scene, filename);
}

void Mesh::InitMesh(unsigned int index, const aiMesh* aiMesh)
{
	float *positions = new float[aiMesh->mNumVertices*3];
	float *texCoords = new float[aiMesh->mNumVertices*2];
	float *normals = new float[aiMesh->mNumVertices*3];
	unsigned short *indices = new unsigned short[aiMesh->mNumFaces*3];

	const aiVector3D Zero(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0 ; i < aiMesh->mNumVertices; ++i) 
	{
		const aiVector3D* pos      = &(aiMesh->mVertices[i]);
		const aiVector3D* tex = aiMesh->HasTextureCoords(0) ? &(aiMesh->mTextureCoords[0][i]) : &Zero;
		const aiVector3D* norm   = &(aiMesh->mNormals[i]);

		positions[i*3+0] = pos->x;
		positions[i*3+1] = pos->y;
		positions[i*3+2] = pos->z;

		texCoords[i*2+0] = tex->x;
		texCoords[i*2+1] = tex->y;

		normals[i*3+0] = norm->x;
		normals[i*3+1] = norm->y;
		normals[i*3+2] = norm->z;
	}

	for (unsigned int i = 0 ; i < aiMesh->mNumFaces; ++i) 
	{
		const aiFace& Face = aiMesh->mFaces[i];

		Assert(Face.mNumIndices == 3,"MESH LOAD ERROR: Encountered a face that did not have 3 vertices, please convert all quads and n-gons to triangles prior to using the model, these are not supported.");

		indices[i*3] = Face.mIndices[0];
		indices[i*3+1] = Face.mIndices[1];
		indices[i*3+2] = Face.mIndices[2];
	}

	m_meshes[index].Initialize(positions,texCoords,normals,indices,aiMesh->mNumVertices,aiMesh->mNumFaces*3);
}

bool Mesh::InitMaterials(const aiScene* scene, const std::string& filename)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) 
	{
		Dir = ".";
	}
	else if (SlashIndex == 0) 
	{
		Dir = "/";
	}
	else 
	{
		Dir = filename.substr(0, SlashIndex);
	}

	bool success = true;

	// Initialize the materials
	for (unsigned int i = 0 ; i < scene->mNumMaterials ; ++i) 
	{
		const aiMaterial* pMaterial = scene->mMaterials[i];

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
		{
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
			{
				std::string FullPath = Dir + "/" + Path.data;
				m_textures[i] = Texture2D(new myth::assets::FilePath(FullPath),0);

				m_textures[i].Load();

				if (!m_textures[i].IsLoaded()) 
				{
					printf("TEXTURE LOADING ERROR: Error loading texture '%s', loading default texture.\n", FullPath.c_str());
					// Load an error texture in case the model does not include its own texture
					m_textures[i] = Texture2D(new myth::assets::FilePath("error.png"),0);

					m_textures[i].Load();
					success = false;
				}
				else 
				{
					printf("Loaded texture '%s'\n", FullPath.c_str());
				}
			}
		}

		aiColor3D mcolor(0.0f,0.0f,0.0f);
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE,mcolor))
			m_materials[i].Diffuse_Color = Vector3F(mcolor.r,mcolor.g,mcolor.b);
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_SPECULAR,mcolor))
			m_materials[i].Specular_Color = Vector3F(mcolor.r,mcolor.g,mcolor.b);
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_AMBIENT,mcolor))
			m_materials[i].Ambient_Color = Vector3F(mcolor.r,mcolor.g,mcolor.b);

		aiString mstring = aiString();
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_NAME,mstring))
			m_materials[i].Name = std::string(mstring.C_Str());

		bool mbool;
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_TWOSIDED,mbool))
			m_materials[i].Twosided = mbool;

		float mfloat;
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_OPACITY,mfloat))
			m_materials[i].Opacity = mfloat;
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_SHININESS,mfloat))
			m_materials[i].Shininess = mfloat;
		if (AI_SUCCESS == pMaterial->Get(AI_MATKEY_SHININESS_STRENGTH,mfloat))
			m_materials[i].Shininess_Strength = mfloat;
	}

	return success;
}

void Mesh::Render(ShaderProgram& program)
{
	program.BindMaterial(m_materials[0]);
	for(unsigned int i = 0; i < m_meshCount;++i)
	{
		m_meshes[i].Render();
	}
}
