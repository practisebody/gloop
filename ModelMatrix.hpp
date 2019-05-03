#pragma once

_GL_BEGIN
// Model matrix, by default identity matrix
class ModelMatrix : public Matrix
{
public:
	ModelMatrix() : Matrix(name)
	{
	}

	ModelMatrix(const glm::mat4& m) : Matrix(name, m)
	{
	}

	using Matrix::operator=;

	virtual const ModelMatrix* Bind() const override
	{
		ModelMatrix top = stack.back();
		stack.emplace_back(top * *this);
		EL_PSY_CONGROO;
	}

	virtual const ModelMatrix* Unbind() const override
	{
		stack.pop_back();
		EL_PSY_CONGROO;
	}

	static const std::string& GetName()
	{
		return name;
	}

	static const ModelMatrix* GetCurrent()
	{
		return &stack.back();
	}

protected:
	inline static const std::string name = "model";
	inline static std::vector<ModelMatrix> stack = std::vector<ModelMatrix>(1);
};
_GL_END