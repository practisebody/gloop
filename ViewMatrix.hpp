#pragma once

_GL_BEGIN
// View matrix
// default glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))
class ViewMatrix : public Matrix
{
public:
	ViewMatrix() : Matrix(name)
	{
	}

	using Matrix::operator=;

	static const std::string& GetName()
	{
		return name;
	}

	static const ViewMatrix* GetCurrent()
	{
		return static_cast<const ViewMatrix*>(ProgramAttribute::GetCurrent(name));
	}

protected:
	inline static const std::string name = "view";
};
_GL_END