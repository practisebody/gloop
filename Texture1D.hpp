#pragma once

_GL_BEGIN
class Texture1D : public Texture
{
public:
	template<class ...T>
	Texture1D(T... t) : Texture(TEXTURE_TYPE::T1D)
	{
	}

	virtual Texture* Data(const void* data) override
	{
		glBindTexture(m_type, GetID());
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, m_nWidth, 0, m_dataFormat, m_dataType, data);
	}

	Texture1D* Data(const int width, const DATA_TYPE type, const TEXTURE_FORMAT format, const void* data)
	{
		m_nWidth = width;
		m_dataType = static_cast<GLenum>(type);
		glBindTexture(m_type, GetID());
		Data(data);
		EL_PSY_CONGROO;
	}
protected:
	size_t m_nWidth;
};
_GL_END