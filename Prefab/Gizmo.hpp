#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class Gizmo : public VAO
{
public:
	Gizmo() : VAO(DRAW_MODE::LINES)
	{
		_GL_INIT_BEGIN;
		Data(
			std::vector<glm::vec3>
			{
				{ 0.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f },
			}, 
			std::vector<glm::vec3>
			{
				{ 1.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f },
				{ 0.0f, 0.0f, 1.0f },
			});
		_GL_INIT_END;
		AddAttribute(progColor3);
	}
};
_PREFAB_END
_GL_END