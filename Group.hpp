#pragma once

_GL_BEGIN
// A group of objects
class Group : public Object, public Shared<Group>
{
public:
	using Shared<Group>::QED;

	Group* AddObject(const std::shared_ptr<Object>& o)
	{
		m_objects.emplace_back(o);
		EL_PSY_CONGROO;
	}

	std::vector<std::shared_ptr<Object>>& GetObjects()
	{
		return m_objects;
	}

protected:
	virtual void Draw() const override
	{
		std::for_each(m_objects.begin(), m_objects.end(), std::mem_fn(&Object::Render));
	}

	std::vector<std::shared_ptr<Object>> m_objects;
};
_GL_END