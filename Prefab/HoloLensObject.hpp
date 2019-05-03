#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class HoloLensObject : public Group
{
public:
	HoloLensObject* Data(const std::string& name)
	{
		std::ifstream file(name, std::fstream::in | std::fstream::binary);
		assert(file);
		
		// two stage, first all the vertex data
		float x, y, z;
		std::vector<glm::vec3> positions;
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
			else if (starts_with("f ") || starts_with("usemtl ") || starts_with("s "))
			{
				RevertLine();
				break;
			}
		}
		
		// TODO
		// currently every vbo is using the whole obj vertices, which can be simplified
		//std::shared_ptr<VBO> vboPos = Make<VBO(GLuint)>(0, positions);
		//std::shared_ptr<VBO> vboTexCoord = Make<VBO(GLuint)>(1, texCoords);
		//std::shared_ptr<VBO> vboNormal = Make<VBO(GLuint)>(2, normals);
		std::vector<glm::uvec3> indices;
		size_t a, b, c;
		// then faces
		const std::function<void()> addObject = [&]()
		{
			//AddObject(Make<VAO(DRAW_MODE)>(DRAW_MODE::TRIANGLES, Make<IBO>(indices), vboPos, vboTexCoord, vboNormal)
			AddObject(Make<VAO(DRAW_MODE)>(DRAW_MODE::TRIANGLES, Make<IBO>(indices), positions));
		};

		while (GetLine(file)) {
			if (starts_with("f "))
			{
				sscanf_s(line + 2, "%d/%*d/%*d%d/%*d/%*d%d/%*d/%*d",
					&a, &b, &c);
				indices.emplace_back(glm::uvec3(a - 1, b - 1, c - 1));
			}
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

	// TODO fix
	inline static constexpr int BUFFER_SIZE = 1024;
	inline static char line[1024] {};
	bool m_bFetchNewLine = true;
};
_PREFAB_END
_GL_END