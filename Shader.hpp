#pragma once

_GL_BEGIN
template<SHADER_TYPE type>
class Shader : private GLSL
{
public:
	~Shader()
	{
		glDeleteShader(GetID());
	}

	Shader* Data(const std::string& name)
	{
		m_name = name;
		const char* source = nullptr;
		std::string text;
		std::ifstream ifs(name, std::ios::in);
		if (ifs.is_open())
		{
			std::string line;
			while (ifs.good())
			{
				std::getline(ifs, line);
				text += line + "\n";
			}
			source = text.c_str();
		}
		else
			source = name.c_str();
		ID() = glCreateShader(m_type);
		glShaderSource(GetID(), 1, &source, NULL);
		glCompileShader(GetID());
#ifdef _DEBUG
		GLint maxLength = 0;
		glGetShaderiv(GetID(), GL_INFO_LOG_LENGTH, &maxLength);
		if (maxLength != 0)
		{
			GLchar* info = new GLchar[maxLength];
			glGetShaderInfoLog(GetID(), maxLength, &maxLength, info);
			fprintf(stderr, "Compile Info: %s\n %s\n", name.c_str(), info);
			delete[] info;
		}
#endif
		EL_PSY_CONGROO;
	}

	const std::string& Name()
	{
		return m_name;
	}

	friend class Program;
protected:
	std::string m_name;

	inline static const GLenum m_type = static_cast<GLenum>(type);

private:
	virtual const Shader* Bind() const override
	{
		EL_PSY_CONGROO;
	}
};

typedef Shader<SHADER_TYPE::VERTEX> VertexShader;
typedef Shader<SHADER_TYPE::GEOMETRY> GeometryShader;
typedef Shader<SHADER_TYPE::FRAGMENT> FragShader;
_GL_END