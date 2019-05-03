#pragma once

_GL_BEGIN
// OpenGL program attribute objects
template<class T>
class ProgramAttribute : public GLExtraObject, public T
{
public:
	using element_type = T;

	ProgramAttribute(const std::string& name) : m_sName(name)
	{
		if (stacks.count(m_sName) == 0)
			stacks.emplace(m_sName, std::vector<const ProgramAttribute*>{});
	}

	template<class... T>
	ProgramAttribute(const std::string& name, T&&... t) : ProgramAttribute(name)
	{
		element_type::operator=(element_type(std::forward<T>(t)...));
	}

	template<class T>
	ProgramAttribute& operator=(T&& t)
	{
		element_type::operator=(std::forward<T>(t));
		return *this;
	}

	const element_type& operator*() const
	{
		return *this;
	}

	virtual const ProgramAttribute* Bind() const override
	{
		stacks[m_sName].emplace_back(this);
		Uniform();
		EL_PSY_CONGROO;
	}

	virtual const ProgramAttribute* Unbind() const override
	{
		stacks[m_sName].pop_back();
		if (stacks[m_sName].size())
			Uniform();
		EL_PSY_CONGROO;
	}

	template<class T>
	ProgramAttribute* Data(T&& t)
	{
		element_type::operator=(std::forward<T>(t));
		EL_PSY_CONGROO;
	}

	const std::string& GetName()
	{
		return m_sName;
	}

	static const ProgramAttribute* GetCurrent(const std::string name)
	{
		return stacks[name].back();
	}

protected:
	void Uniform() const
	{
		Program::GetCurrent()->Uniform(m_sName.c_str(), GetCurrent(m_sName));
	}

	const std::string m_sName;
	inline static std::map<std::string, std::vector<const ProgramAttribute*>> stacks {};
};
_GL_END