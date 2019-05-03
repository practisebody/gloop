#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class Frustum : public VAO
{
public:
	Frustum() : VAO(DRAW_MODE::LINES)
	{
		AddAttribute(progUniformColor4);
		_GL_INIT_BEGIN;
		Data(0.1f, 1.0f, glm::radians(60.0f), glm::radians(40.0f));
		_GL_INIT_END;
	}

	Frustum* Data(float znear, float zfar, float hfov, float vfov)
	{
		float x = tan(hfov / 2);
		float y = tan(vfov / 2);
		glm::vec3 vs[4] =
		{
			{ -x, -y, -1.0f },
			{ +x, -y, -1.0f },
			{ +x, +y, -1.0f },
			{ -x, +y, -1.0f }
		};
		VAO::Data(
			Make<IBO>(std::vector<glm::uvec2>
			{
				{ 0, 1 },
				{ 1, 2 },
				{ 2, 3 },
				{ 3, 0 },
				{ 4, 5 },
				{ 5, 6 },
				{ 6, 7 },
				{ 7, 4 },
				{ 0, 4 },
				{ 1, 5 },
				{ 2, 6 },
				{ 3, 7 },
			}),
			std::vector<glm::vec3>
			{
				vs[0] * znear,
				vs[1] * znear,
				vs[2] * znear,
				vs[3] * znear,
				vs[0] * zfar,
				vs[1] * zfar,
				vs[2] * zfar,
				vs[3] * zfar,
			});
		EL_PSY_CONGROO;
	}

	Frustum* SetColor(const glm::vec4& color)
	{
		Uniform("fragColor", color);
		EL_PSY_CONGROO;
	}
};
_PREFAB_END
_GL_END