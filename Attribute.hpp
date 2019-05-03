#pragma once

_GL_BEGIN
// An OpenGL attribute
// It can be binded and unbinded, and run a function with this attribute binded
class Attribute
{
public:
	// bind the attribute
	virtual const Attribute* Bind() const = 0;
	// unbind the attribute
	virtual const Attribute* Unbind() const
	{
		EL_PSY_CONGROO;
	}

	// run the callable object with the attibute binded
	// should not be overloaded
	template<class Func>
	const Attribute* Binded(Func func) const
	{
		Bind();
		func();
		Unbind();
		EL_PSY_CONGROO;
	}
};
_GL_END