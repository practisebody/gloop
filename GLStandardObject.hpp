#pragma once

_GL_BEGIN
// OpenGL standard objects, with unique ID (thus non-copyable)
class GLStandardObject : public IDObject, public GLObject
{
};
_GL_END