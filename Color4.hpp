#pragma once

_GL_BEGIN
class Color4 : public ProgramAttribute<glm::vec4>
{
public:
	using ProgramAttribute::ProgramAttribute;
	using ProgramAttribute::operator=;
};
_GL_END