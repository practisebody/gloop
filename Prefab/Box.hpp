#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class Box : public VAO
{
public:
	Box() : VAO(DRAW_MODE::QUADS)
	{
		_GL_INIT_BEGIN;
		VAO::Data(
			GL::Make<GL::IBO>(std::vector<glm::uvec4>
			{
				{ 0, 1, 2, 3 },
				{ 0, 1, 5, 4 },
				{ 0, 3, 7, 4 },
				{ 1, 2, 6, 5 },
				{ 2, 3, 7, 6 },
				{ 4, 5, 6, 7 },
			}),
			std::vector<glm::vec3>
			{
				{ +0.5f, +0.5f, -0.5f },
				{ -0.5f, +0.5f, -0.5f },
				{ -0.5f, -0.5f, -0.5f },
				{ +0.5f, -0.5f, -0.5f },
				{ +0.5f, +0.5f, +0.5f },
				{ -0.5f, +0.5f, +0.5f },
				{ -0.5f, -0.5f, +0.5f },
				{ +0.5f, -0.5f, +0.5f },
			});
		_GL_INIT_END;
	}

	Box* SetColor(const glm::vec4& color)
	{
		AddAttribute(progUniformColor4);
		Uniform("fragColor", color);
		EL_PSY_CONGROO;
	}
};
_PREFAB_END
_GL_END