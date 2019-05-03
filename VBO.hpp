#pragma once

_GL_BEGIN
// a vertex attribute buffer object
// think as matrix format
// # of rows = # of vertices, # of cols = # of dimensions
class VBO : public Buffer2D<BUFFER_TYPE::ARRAY_BUFFER>
{
public:
	VBO(GLuint index) : m_uIndex(index)
	{
	}

	virtual const VBO* Bind() const override
	{
		glEnableVertexAttribArray(m_uIndex);
		glBindBuffer(m_bufferType, GetID());
		glVertexAttribPointer(m_uIndex, m_uWidth, m_dataType, m_bNormalized, m_uStride, NULL);
		EL_PSY_CONGROO;
	}

	virtual const VBO* Unbind() const override
	{
		glDisableVertexAttribArray(m_uIndex);
		glBindBuffer(m_bufferType, 0);
		EL_PSY_CONGROO;
	}

	template<class T>
	const VBO* Data(T&& data, bool normalized = false, size_t stride = 0)
	{
		m_bNormalized = normalized;
		m_uStride = stride;
		Buffer2D::Data(data);
		m_data = data;
		EL_PSY_CONGROO;
	}

	const std::any& GetData()
	{
		return m_data;
	}

protected:
	const GLuint m_uIndex;
	GLboolean m_bNormalized;
	GLuint m_uStride;
	std::any m_data;
};
_GL_END