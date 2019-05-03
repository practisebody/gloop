#pragma once

_GL_BEGIN
// Projection matrix
// default glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f)
class ProjMatrix : public Matrix
{
public:
	ProjMatrix() : Matrix(name)
	{
	}

	using Matrix::operator=;

	static const std::string& GetName()
	{
		return name;
	}

	static const ProjMatrix* GetCurrent()
	{
		return static_cast<const ProjMatrix*>(ProgramAttribute::GetCurrent(name));
	}

protected:
	inline static const std::string name = "projection";
};
_GL_END