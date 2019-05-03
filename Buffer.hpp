#pragma once

_GL_BEGIN
// standard OpenGL buffer object
template<BUFFER_TYPE type>
class Buffer : public GLRegular
{
public:
	Buffer(const GLenum usage = GL_STATIC_DRAW) : m_usage(usage)
	{
		_GL_INIT_BEGIN;
		glGenBuffers(1, &ID());
		_GL_INIT_END;
	}

	~Buffer()
	{
		glDeleteBuffers(1, &GetID());
	}

	virtual const Buffer* Bind() const override
	{
		glBindBuffer(m_bufferType, GetID());
		EL_PSY_CONGROO;
	}

	virtual const Buffer* Unbind() const override
	{
		glBindBuffer(m_bufferType, 0);
		EL_PSY_CONGROO;
	}

	Buffer* Data(const size_t size, const void* data)
	{
		m_uSize = size;
		m_uCount = 0;
		glBindBuffer(m_bufferType, GetID());
		glBufferData(m_bufferType, m_uSize, data, m_usage);
		EL_PSY_CONGROO;
	}

	template<class T>
	Buffer* Data(const size_t size, const T* data)
	{
		using _T = std::decay_t<T>;
		if constexpr (std::is_same_v<_T, GLubyte>)
			m_dataType = GL_UNSIGNED_BYTE;
		else if constexpr (std::is_same_v<_T, GLuint>)
			m_dataType = GL_UNSIGNED_INT;
		else if constexpr (std::is_same_v<_T, GLfloat>)
			m_dataType = GL_FLOAT;
		else
			static_assert(false, "Unknown value type. GLubyte, GLuint GLfloat only~");
		m_uSize = size * sizeof(T);
		m_uCount = size;
		glBindBuffer(m_bufferType, GetID());
		glBufferData(m_bufferType, m_uSize, data, m_usage);
		EL_PSY_CONGROO;
	}

	template<class T>
	Buffer* Data(const T* begin, const T* end)
	{
		m_uCount = end - begin;
		Data(m_uCount, begin);
		EL_PSY_CONGROO;
	}

	template<class T>
	Buffer* Data(const T begin, const T end)
	{
		using value_type = typename T::value_type;
		m_uCount = end - begin;
		Data(m_uCount, std::addressof(*begin));
		EL_PSY_CONGROO;
	}

	const size_t& Size() const
	{
		return m_uSize;
	}

	const GLenum& Usage() const
	{
		return m_usage;
	}

	const size_t& Count() const
	{
		return m_uCount;
	}

	const DATA_TYPE Type() const
	{
		return static_cast<DATA_TYPE>(m_dataType);
	}

protected:
	inline static const GLenum m_bufferType = static_cast<GLenum>(type);

	const GLenum m_usage;
	size_t m_uSize;
	size_t m_uCount;
	GLenum m_dataType;
};
_GL_END