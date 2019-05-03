#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class Quad : public VAO
{
public:
	Quad() : VAO(DRAW_MODE::QUADS)
	{
		_GL_INIT_BEGIN;
		VAO::Data(
			std::vector<glm::vec3>
			{
				{ -0.5f, -0.5f, 0.0f },
				{ +0.5f, -0.5f, 0.0f },
				{ +0.5f, +0.5f, 0.0f },
				{ -0.5f, +0.5f, 0.0f },
			},
			std::vector<glm::vec2>
			{
				{ 0.0f, 1.0f },
				{ 1.0f, 1.0f },
				{ 1.0f, 0.0f },
				{ 0.0f, 0.0f },
			});
		_GL_INIT_END;
	}

	Quad* SetTexture(const std::shared_ptr<Texture2D>& texture)
	{
		AddAttribute(progTexture);
		Uniform("tex", texture);
		EL_PSY_CONGROO;
	}

	Quad* SetColor(const glm::vec4& color)
	{
		AddAttribute(progUniformColor4);
		Uniform("fragColor", color);
		EL_PSY_CONGROO;
	}
};
_PREFAB_END
_GL_END