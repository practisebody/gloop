#pragma once

_GL_BEGIN
// ª√ ¿°∏•∂°§•Ô©`•Î•…°π
// basically is a group of objects, cannot be inherited
class World final : public Group, public Shared<World>
{
public:
	using Shared<World>::QED;

	//template<class... T>
	//World* Data(T&&... t)
	//{
	//	Group::Data(std::forward<T>(t)...);
	//	EL_PSY_CONGROO;
	//}

	World* AddObject(const std::shared_ptr<Object>& t)
	{
		Group::AddObject(t);
		EL_PSY_CONGROO;
	}
};
_GL_END