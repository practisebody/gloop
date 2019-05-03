#pragma once

_GL_BEGIN
class Color3 : public ProgramAttribute<glm::vec3>
{
public:
	using ProgramAttribute::ProgramAttribute;
	using ProgramAttribute::operator=;
};
_GL_END