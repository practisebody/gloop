#pragma once

_GL_BEGIN
class VAO : public GLContainer, public Object, public Shared<VAO>
{
public:
	using Shared<VAO>::QED;

	VAO(const DRAW_MODE mode) : m_nMode(static_cast<GLenum>(mode))
	{
		_GL_INIT_BEGIN;
		glGenVertexArrays(1, &ID());
		_GL_INIT_END;
	}

	~VAO()
	{
		glDeleteVertexArrays(1, &GetID());
	}

	virtual const VAO* Bind() const override
	{
		glBindVertexArray(GetID());
		EL_PSY_CONGROO;
	}

	virtual const VAO* Unbind() const override
	{
		glBindVertexArray(0);
		EL_PSY_CONGROO;
	}

	template<class... T>
	VAO* Data(T&&... t)
	{
		glBindVertexArray(GetID());
		m_vbos.clear();
		(AddVBO(std::forward<T>(t)), ...);
		size_t height = m_vbos.front()->Height();
#ifdef _DEBUG
		for (const std::shared_ptr<VBO>& vbo : m_vbos)
			assert(vbo->Height() == height);
#endif
		EL_PSY_CONGROO;
	}

	template<class T, class... Ts,
		class = std::enable_if_t<std::is_invocable_v<decltype(&VAO::SetIBO), VAO*, T>>>
	VAO* Data(T&& index, Ts&&... ts)
	{
		SetIBO(std::forward<T>(index));
		Data(std::forward<Ts>(ts)...);
		EL_PSY_CONGROO;
	}

	VAO* SetIBO(const std::shared_ptr<IBO>& index)
	{
		m_index = index;
		EL_PSY_CONGROO;
	}

	template<class... T>
	VAO* AddVBO(T&&... t)
	{
		std::shared_ptr<VBO> vbo = Make<VBO(GLuint)>(m_vbos.size(), std::forward<T>(t)...);
		AddVBO(vbo);
		EL_PSY_CONGROO;
	}

	template<>
	VAO* AddVBO<std::shared_ptr<VBO>&>(std::shared_ptr<VBO>& vbo)
	{
		//Bind();
		m_vbos.emplace_back(vbo);
		vbo->Bind();
		EL_PSY_CONGROO;
	}

	std::shared_ptr<VBO> GetVBO(size_t index)
	{
		return m_vbos[index];
	}

protected:
	virtual void Draw() const override
	{
		Draw(static_cast<DRAW_MODE>(m_nMode));
	}

	const void Draw(const DRAW_MODE mode) const
	{
		Bind();
		if (m_index)
			m_index->Binded(std::bind(glDrawElements, static_cast<GLenum>(mode),
				m_index->Count(), static_cast<GLenum>(m_index->Type()), nullptr));
		else if (m_vbos.size())
			glDrawArrays(static_cast<GLenum>(mode), 0, m_vbos.front()->Count());
		Unbind();
	}

	const GLenum m_nMode;
	std::vector<std::shared_ptr<VBO>> m_vbos;
	std::shared_ptr<IBO> m_index;
};
_GL_END