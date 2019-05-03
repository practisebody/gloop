#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class PmxObjObject : public Group
{
public:
	PmxObjObject* Data(const std::string& name)
	{
		if (size_t pos = name.find_last_of("/\\"); pos != std::string::npos)
			m_sPath = name.substr(0, pos + 1);
		std::ifstream file(name, std::fstream::in | std::fstream::binary);
		assert(file);
		
		// two stage, first all the vertex data
		float x, y, z;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		while (GetLine(file)) {
			// comment
			if (starts_with("#"))
				continue;
			// position
			else if (starts_with("v "))
			{
				sscanf_s(line + 2, "%f%f%f", &x, &y, &z);
				positions.emplace_back(glm::vec3(x, y, z));
			}
			else if (starts_with("vt "))
			{
				sscanf_s(line + 3, "%f%f", &x, &y);
				texCoords.emplace_back(glm::vec2(x, y));
			}
			else if (starts_with("vn "))
			{
				sscanf_s(line + 3, "%f%f%f", &x, &y, &z);
				normals.emplace_back(glm::vec3(x, y, z));
			}
			else if (starts_with("f ") || starts_with("usemtl ") || starts_with("s "))
			{
				RevertLine();
				break;
			}
			else if (starts_with("mtllib "))
			{
				ParseMtl(line + 7);
			}
#ifdef _DEBUG
			else if (strlen(line))
			{
				fprintf(stderr, "Unrecognized line in obj file: \"%s\"\n", line);
			}
#endif
		}
		
		// TODO
		// currently every vbo is using the whole obj vertices, which can be simplified
		//std::shared_ptr<VBO> vboPos = Make<VBO(GLuint)>(0, positions);
		//std::shared_ptr<VBO> vboTexCoord = Make<VBO(GLuint)>(1, texCoords);
		//std::shared_ptr<VBO> vboNormal = Make<VBO(GLuint)>(2, normals);
		std::shared_ptr<PmxMaterial> curr;
		std::vector<glm::uvec3> indices;
		size_t a, b, c;
		// then faces
		const std::function<void()> addObject = [&]()
		{
			//AddObject(Make<VAO(DRAW_MODE)>(DRAW_MODE::TRIANGLES, Make<IBO>(indices), vboPos, vboTexCoord, vboNormal)
			AddObject(Make<VAO(DRAW_MODE)>(DRAW_MODE::TRIANGLES, Make<IBO>(indices), positions, texCoords, normals)
				->AddAttribute(progPmxMaterial)
				->AddAttribute(curr)
				->QED());
		};

		while (GetLine(file)) {
			if (starts_with("f "))
			{
				sscanf_s(line + 2, "%d/%*d/%*d%d/%*d/%*d%d/%*d/%*d",
					&a, &b, &c);
				indices.emplace_back(glm::uvec3(a - 1, b - 1, c - 1));
			}
			else if (starts_with("usemtl "))
			{
				if (indices.size())
				{
					addObject();
					indices.clear();
				}
				curr = m_materials.find(line + 7)->second;
			}
#ifdef _DEBUG
			else
			{
				fprintf(stderr, "Unrecognized line in obj file: \"%s\"", line);
			}
#endif
		}
		addObject();
		file.close();
		EL_PSY_CONGROO;
	}

protected:
	bool starts_with(const char* prefix)
	{
		return strncmp(line, prefix, strlen(prefix)) == 0;
	}

	bool IsAbsPath(const std::string& path)
	{
		return path[0] == '/' || path.find_first_of(":") != std::string::npos;
	}

	bool GetLine(std::istream& s)
	{
		if (m_bFetchNewLine)
		{
			bool ret = static_cast<bool>(s.getline(line, BUFFER_SIZE));
			int len = static_cast<int>(strlen(line));
			for (int i = len - 1; i >= 0; --i)
			{
				if (isspace(line[i]))
					line[i] = '\0';
				else
					break;
			}
			return ret;
		}
		else
		{
			m_bFetchNewLine = true;
			return true;
		}
	}

	void RevertLine()
	{
		m_bFetchNewLine = false;
	}

	void ParseMtl(std::string name)
	{
		if (IsAbsPath(name) == false)
			name = m_sPath + name;
		else
			;//m_sPath = ;
		std::ifstream file(name, std::ios::binary);
		assert(file);
		std::shared_ptr<PmxMaterial> curr;
		std::map<std::string, std::shared_ptr<Texture2D>> textures;
		float r, g, b;
		float v;

		while (GetLine(file)) {
			// comment
			if (starts_with("#"))
				continue;
			else if (starts_with("newmtl "))
			{
				curr = m_materials.emplace(
					std::make_pair(line + 7, Make<PmxMaterial(std::string)>("m"))).first->second;
			}
			else if (starts_with("map_Kd "))
			{
				std::map<std::string, std::shared_ptr<Texture2D>>::iterator it = textures.find(line + 7);
				if (it == textures.end())
					it = textures.emplace(std::make_pair(line + 7, Make<BMPTexture>((m_sPath + (line + 7)).c_str()))).first;
				curr->SetTexDiffuse(it->second);
			}
			else if (starts_with("Ka "))
			{
				sscanf_s(line + 3, "%f%f%f", &r, &g, &b);
				curr->SetAmbient(glm::vec4(r, g, b, 1.0f));
			}
			else if (starts_with("Kd "))
			{
				sscanf_s(line + 3, "%f%f%f", &r, &g, &b);
				curr->SetDiffuse(glm::vec4(r, g, b, 1.0f));
			}
			else if (starts_with("Ks "))
			{
				sscanf_s(line + 3, "%f%f%f", &r, &g, &b);
				curr->SetSpecular(glm::vec4(r, g, b, 1.0f));
			}
			else if (starts_with("Ns "))
			{
				sscanf_s(line + 3, "%f", &v);
				curr->SetSpecularExponent(v);
			}
			else if (starts_with("d "))
			{
				sscanf_s(line + 2, "%f", &v);
				curr->SetDissolve(v);
			}
#ifdef _DEBUG
			else if (strlen(line))
			{
				fprintf(stderr, "Unrecognized line in mtl file: \"%s\"", line);
			}
#endif
		}
		file.close();
	}

	// TODO fix
	inline static constexpr int BUFFER_SIZE = 1024;
	inline static char line[1024] {};
	bool m_bFetchNewLine = true;

	std::string m_sPath;
	std::map<std::string, std::shared_ptr<PmxMaterial>> m_materials;
};
_PREFAB_END
_GL_END