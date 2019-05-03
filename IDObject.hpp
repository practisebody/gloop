#pragma once

_GL_BEGIN
// Unique object with an ID
class IDObject : public Unique
{
public:
	inline const GLuint& GetID() const
	{
		return m_id;
	}

	inline GLuint& ID()
	{
		return m_id;
	}

private:
	GLuint m_id = 0;
};
_GL_END