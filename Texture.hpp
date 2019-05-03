#pragma once

_GL_BEGIN
class Texture : public GLRegular
{
public:
	Texture(const TEXTURE_TYPE type) : m_type(static_cast<GLenum>(type))
	{
		_GL_INIT_BEGIN;
		glEnable(m_type);
		glGenTextures(1, &ID());
		glBindTexture(m_type, GetID());
		// they are set to GL_REPEAT by default
		//glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(m_type, 0);
		_GL_INIT_END;
	}

	~Texture()
	{
		glDeleteTextures(1, &GetID());
	}

	virtual const Texture* Bind() const override
	{
		glEnable(m_type);
		glBindTexture(m_type, GetID());
		EL_PSY_CONGROO;
	}

	virtual const Texture* Unbind() const override
	{
		glBindTexture(m_type, 0);
		glDisable(m_type);
		EL_PSY_CONGROO;
	}
	
	Texture* Data()
	{
		Data(NULL);
	}

	virtual Texture* Data(const void* data) = 0;

	Texture* SetType(DATA_TYPE type)
	{
		m_dataType = static_cast<GLenum>(type);
		EL_PSY_CONGROO;
	}

	Texture* SetFormat(TEXTURE_FORMAT format)
	{
		m_dataFormat = static_cast<GLenum>(format);
		EL_PSY_CONGROO;
	}

protected:
	// 1d or 2d or 3d
	const GLenum m_type;
	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
	// type: float, int
	GLenum m_dataType = GL_UNSIGNED_BYTE;
	// format: RGB, RGBA, BGR
	GLenum m_dataFormat = GL_RGBA;
};
_GL_END