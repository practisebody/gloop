#pragma once

_GL_BEGIN
enum class CALLBACK_FUNC : GLenum
{
	// standard
	DISPLAY,
	KEYBOARD,
	MOUSE,
	IDLE,
	RESHAPE,
	MOTION,
	PASSIVEMOTION,
	// non-standard
	INIT,
	UPDATE,
};

enum class DISPLAY_MODE : GLenum
{
	RGB = GLUT_RGB,
	RGBA = GLUT_RGBA,
	SINGLE = GLUT_SINGLE,
	DOUBLE = GLUT_DOUBLE,
	DEPTH = GLUT_DEPTH,
};

namespace detail {
[[nodiscard]] const bool DepthMode(GLenum mode)
{
	return mode & static_cast<GLenum>(GL::DISPLAY_MODE::DEPTH);
}
}
_GL_END