#pragma once

_GL_BEGIN
namespace detail {
inline size_t SizeOf(GLenum type)
{
	switch (type)
	{
	case GL_UNSIGNED_BYTE:
		return sizeof(GLubyte);
	case GL_UNSIGNED_INT:
		return sizeof(GLuint);
	case GL_FLOAT:
		return sizeof(GLfloat);
	default:
		assert(false);
		return 0;
	}
}

inline size_t ChannelOf(GLenum type)
{
	switch (type)
	{
	case GL_RGB:
		return 3;
	case GL_RGBA:
		return 4;
	default:
		assert(false);
		return 0;
	}
}
}
_GL_END