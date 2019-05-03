#pragma once

#include <iostream>
#include <glm/gtx/string_cast.hpp>

_GL_BEGIN
class Program : public GLSL, public Shared<Program>
{
public:
	Program()
	{
		_GL_INIT_BEGIN;
		ID() = glCreateProgram();
		_GL_INIT_END;
	}

	~Program()
	{
		if (m_vertex)
			glDetachShader(GetID(), m_vertex->GetID());
		if (m_fragment)
			glDetachShader(GetID(), m_fragment->GetID());
		glDeleteProgram(GetID());
	}

	virtual const Program* Bind() const override
	{
		m_bInUse = true;
		glUseProgram(GetID());
		current = this;
		if (m_lProjection != -1)
			glUniformMatrix4fv(m_lProjection, 1, false, *ProjMatrix::GetCurrent());
		if (m_lView != -1)
			glUniformMatrix4fv(m_lView, 1, false, *ViewMatrix::GetCurrent());
		if (m_lModel != -1)
			glUniformMatrix4fv(m_lModel, 1, false, *ModelMatrix::GetCurrent());
		std::for_each(m_uniforms.begin(), m_uniforms.end(), std::mem_fn(&std::function<void()>::operator()));
		EL_PSY_CONGROO;
	}

	virtual const Program* Unbind() const override
	{
		m_uTextureIndex = 0;
		glUseProgram(0);
		m_bInUse = false;
		current = nullptr;
		EL_PSY_CONGROO;
	}

	Program* Data(const std::string& vertex, const std::string& fragment)
	{
		Data(Make<VertexShader>(vertex), Make<FragShader>(fragment));
		EL_PSY_CONGROO;
	}

	Program* Data(const std::string& vertex, const std::string& geometry, const std::string& fragment)
	{
		Data(Make<VertexShader>(vertex), Make<GeometryShader>(geometry), Make<FragShader>(fragment));
		EL_PSY_CONGROO;
	}

	Program* Data()
	{
		glLinkProgram(GetID());
#ifdef _DEBUG
		GLint nLength = 0;
		glGetProgramiv(GetID(), GL_INFO_LOG_LENGTH, &nLength);
		if (nLength != 0)
		{
			std::unique_ptr<GLchar[]> info = std::make_unique<GLchar[]>(nLength);
			glGetProgramInfoLog(GetID(), nLength, &nLength, info.get());
			std::cerr << "Link Info:";
			if (m_vertex)
				std::cerr << " vertex " << m_vertex->Name();
			if (m_geometry)
				std::cerr << " geometry " << m_geometry->Name();
			if (m_fragment)
				std::cerr << " fragment " << m_fragment->Name();
			std::cerr << std::endl;
			fprintf(stderr, "%s\n", info.get());
		}
#endif
		m_lProjection = GetLocation(ProjMatrix::GetName().c_str());
		m_lView = GetLocation("view");
		m_lModel = GetLocation("model");
		glUseProgram(0);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Program* Data(const std::shared_ptr<VertexShader>& vertex, T... t)
	{
		if (vertex)
		{
			m_vertex = vertex;
			glAttachShader(GetID(), m_vertex->GetID());
		}
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Program* Data(const std::shared_ptr<GeometryShader>& geometry, T... t)
	{
		if (geometry)
		{
			m_geometry = geometry;
			glAttachShader(GetID(), m_geometry->GetID());
		}
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Program* Data(const std::shared_ptr<FragShader>& fragment, T... t)
	{
		if (fragment)
		{
			m_fragment = fragment;
			glAttachShader(GetID(), m_fragment->GetID());
		}
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	template<class T>
	Program* Uniform(const GLchar* name, T&& value)
	{
		//static_assert(std::is_lvalue_reference_v<T>);
		using _T = std::decay_t<T>;
		// if value type
		if constexpr (std::is_fundamental_v<_T> || detail::is_glm_vec_v<_T>
			|| detail::is_glm_mat_v<_T>)
		{
			using value_type = detail::remove_glm_t<_T>;
			const value_type* ptr;
			if constexpr (std::is_fundamental_v<_T>)
				ptr = std::addressof(value);
			else
				ptr = glm::value_ptr(value);
			// if value or glm::vec
			if constexpr (std::is_fundamental_v<_T> || detail::is_glm_vec_v<_T>)
			{
				size_t length;
				if constexpr (std::is_fundamental_v<_T>)
					length = 1;
				else
					length = _T::length();
				assert(length >= 1 && length <= 4);
				if constexpr (std::is_same_v<value_type, GLfloat>)
				{
					_GL_INIT_BEGIN;
					if (length == 1)
						Uniform(std::bind(glUniform1fv, GetLocation(name), 1u, ptr));
					else if (length == 2)
						Uniform(std::bind(glUniform2fv, GetLocation(name), 1u, ptr));
					else if (length == 3)
						Uniform(std::bind(glUniform3fv, GetLocation(name), 1u, ptr));
					else // if (length == 4)
						Uniform(std::bind(glUniform4fv, GetLocation(name), 1u, ptr));
					_GL_INIT_END;
				}
				else if constexpr (std::is_same_v<value_type, GLint>)
				{
					_GL_INIT_BEGIN;
					if (length == 1)
						Uniform(std::bind(glUniform1iv, GetLocation(name), 1u, ptr));
					else if (length == 2)
						Uniform(std::bind(glUniform2iv, GetLocation(name), 1u, ptr));
					else if (length == 3)
						Uniform(std::bind(glUniform3iv, GetLocation(name), 1u, ptr));
					else // if (length == 4)
						Uniform(std::bind(glUniform4iv, GetLocation(name), 1u, ptr));
					_GL_INIT_END;
				}
				else if constexpr (std::is_same_v<value_type, GLuint>)
				{
					_GL_INIT_BEGIN;
					if (length == 1)
						Uniform(std::bind(glUniform1uiv, GetLocation(name), 1u, ptr));
					else if (length == 2)
						Uniform(std::bind(glUniform2uiv, GetLocation(name), 1u, ptr));
					else if (length == 3)
						Uniform(std::bind(glUniform3uiv, GetLocation(name), 1u, ptr));
					else // if (length == 4)
						Uniform(std::bind(glUniform4uiv, GetLocation(name), 1u, ptr));
					_GL_INIT_END;
				}
				else
				{
					static_assert(false, "Unknown value type. GLfloat, GLint, GLuint only~");
				}
			}
			else if constexpr (detail::is_glm_mat_v<_T>)
			{
				const size_t first = _T::row_type::length();
				const size_t second = _T::col_type::length();
				assert(first >= 1 && first <= 4);
				assert(second >= 1 && second <= 4);
				_GL_INIT_BEGIN;
				if (first == 2)
				{
					if (second == 2)
						Uniform(std::bind(glUniformMatrix2fv, GetLocation(name), 1u, false, ptr));
					else if (second == 3)
						Uniform(std::bind(glUniformMatrix2x3fv, GetLocation(name), 1u, false, ptr));
					else // if (second == 4)
						Uniform(std::bind(glUniformMatrix2x4fv, GetLocation(name), 1u, false, ptr));
				}
				else if (first == 3)
				{
					if (second == 2)
						Uniform(std::bind(glUniformMatrix3x2fv, GetLocation(name), 1u, false, ptr));
					else if (second == 3)
						Uniform(std::bind(glUniformMatrix3fv, GetLocation(name), 1u, false, ptr));
					else // if (second == 4)
						Uniform(std::bind(glUniformMatrix3x4fv, GetLocation(name), 1u, false, ptr));
				}
				else // if (first == 4)
				{
					if (second == 2)
						Uniform(std::bind(glUniformMatrix4x2fv, GetLocation(name), 1u, false, ptr));
					else if (second == 3)
						Uniform(std::bind(glUniformMatrix4x3fv, GetLocation(name), 1u, false, ptr));
					else // if (second == 4)
						Uniform(std::bind(glUniformMatrix4fv, GetLocation(name), 1u, false, ptr));
				}
				_GL_INIT_END;
			}
			else
			{
				static_assert(false, "Unknown data format. Fundamental, glm::tvec and glm::tmat only~");
			}
		}
		else if constexpr (std::is_base_of_v<Texture, detail::remove_shared_ptr_t<_T>>)
		{
			GLuint index = m_uTextureIndex++;
			if constexpr (detail::is_shared_ptr_v<_T>)
			{
				Uniform([=]()
				{
					glUniform1i(GetLocation(name), index);
					glActiveTexture(GL_TEXTURE0 + index);
					value->Bind();
				});
			}
			else
			{
				Uniform([&]()
				{
					glUniform1i(GetLocation(name), index);
					glActiveTexture(GL_TEXTURE0 + index);
					value.Bind();
				});
			}
		}
		else
		{
			Uniform(name, *value);
			//static_assert(false, "Unknown value type. raw, glm and GL::Texture only~");
		}
		EL_PSY_CONGROO;
	}

	static Program* GetCurrent()
	{
		return const_cast<Program*>(current);
	}

protected:
	const GLint GetLocation(const GLchar* name)
	{
		glUseProgram(GetID());
		GLint location = glGetUniformLocation(GetID(), name);
#ifdef _DEBUG
		if (m_bWarning && location == -1)
			fprintf(stderr, "Warning: Location of '%s' not found!\n", name);
#endif
		return location;
	}

	void Uniform(std::function<void()>&& uniform)
	{
		// call it or save for later
		if (m_bInUse)
			uniform();
		else
			m_uniforms.emplace_back(std::move(uniform));
	}

	bool m_bWarning = true;

	std::shared_ptr<VertexShader> m_vertex;
	std::shared_ptr<GeometryShader> m_geometry;
	std::shared_ptr<FragShader> m_fragment;

	GLint m_lProjection;
	GLint m_lView;
	GLint m_lModel;

	std::vector<std::function<void()>> m_uniforms;
	mutable bool m_bInUse = false;
	mutable size_t m_uTextureIndex = 0;

	inline static const Program* current;
};
_GL_END