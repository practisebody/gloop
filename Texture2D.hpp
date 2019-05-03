#pragma once

_GL_BEGIN
class Texture2D : public Texture
{
public:
	Texture2D() : Texture(TEXTURE_TYPE::T2D)
	{
		
	}

	virtual Texture2D* Data(const void* image = nullptr) override
	{
		glBindTexture(m_type, GetID());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, m_dataFormat, m_dataType, image);
		EL_PSY_CONGROO;
	}

	Texture2D* SetType(const GL::DATA_TYPE type)
	{
		m_dataType = static_cast<GLenum>(type);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Texture2D* Data(const GL::DATA_TYPE type, T... t)
	{
		SetType(type);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Texture2D* SetFormat(const GL::TEXTURE_FORMAT format)
	{
		m_dataFormat = static_cast<GLenum>(format);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Texture2D* Data(const GL::TEXTURE_FORMAT format, T... t)
	{
		SetFormat(format);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Texture2D* Data(const int width, const int height, T... t)
	{
		m_nWidth = width;
		m_nHeight = height;
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}
protected:
	size_t m_nWidth = 0, m_nHeight = 0;
};
_GL_END