#pragma once

_GL_BEGIN
// the class that delete copy constructor and copy assignment
// default constructor and move constructor/assignment is still available
class Unique
{
public:
	// default constructor
	Unique() = default;
	// copy constructor
	Unique(const Unique&) = delete;
	// move constructor
	Unique(Unique&&) = default;
	// copy assignment
	Unique& operator=(const Unique&) = delete;
	// move assignment
	Unique& operator=(Unique&&) = default;
};
_GL_END