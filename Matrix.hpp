#pragma once

#include <glm/gtc/matrix_access.hpp>

_GL_BEGIN
// base class for OpenGL matrices
class Matrix : public ProgramAttribute<glm::mat4>
{
public:
	using ProgramAttribute::ProgramAttribute;
	using ProgramAttribute::operator=;

	operator const GLfloat*() const
	{
		return glm::value_ptr(static_cast<const glm::mat4&>(*this));
	}

	virtual const Matrix* Bind() const override
	{
		stacks[m_sName].emplace_back(this);
		EL_PSY_CONGROO;
	}

	virtual const Matrix* Unbind() const override
	{
		stacks[m_sName].pop_back();
		EL_PSY_CONGROO;
	}
};
_GL_END