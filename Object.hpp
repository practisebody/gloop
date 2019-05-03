#pragma once

_GL_BEGIN
// An OpenGL object that can be rendered
// as well as with optional attributes binded
class Object : public Shared<Object>
{
public:
	// advanced drawing
	// with all the attributes binded
	// in most cases should not be overloaded (but could)
	virtual const Object* Render() const
	{
		if (m_bVisible)
		{
			std::for_each(m_models.begin(), m_models.end(), std::mem_fn(&ModelMatrix::Bind));
			if (m_program)
				m_program->Bind();
			// bind in same order of added
			std::for_each(m_attributes.begin(), m_attributes.end(), std::mem_fn(&Attribute::Bind));
			for (const std::function<void()>& f : m_uniforms)
				f();
			Draw();
			// unbind in reverse order
			std::for_each(m_attributes.rbegin(), m_attributes.rend(), std::mem_fn(&Attribute::Unbind));
			if (m_program)
				m_program->Unbind();
			std::for_each(m_models.begin(), m_models.end(), std::mem_fn(&ModelMatrix::Unbind));
		}
		EL_PSY_CONGROO;
	}

	Object* AddAttribute(const std::shared_ptr<Attribute>& attribute)
	{
		if (std::shared_ptr<Program> program = std::dynamic_pointer_cast<Program>(attribute))
			m_program = program;
		else if (std::shared_ptr<ModelMatrix> model = std::dynamic_pointer_cast<ModelMatrix>(attribute))
			m_models.emplace_back(model);
		else
			m_attributes.emplace_back(attribute);
		EL_PSY_CONGROO;
	}

	template<class T>
	Object* Uniform(const GLchar* name, T&& value)
	{
		m_uniforms.emplace_back([=]
		{
			m_program->Uniform(name, value);
		});
		EL_PSY_CONGROO;
	}

	Object* SetVisible(bool visible)
	{
		m_bVisible = visible;
		EL_PSY_CONGROO;
	}

	bool GetVisible()
	{
		return m_bVisible;
	}

protected:
	// actual drawing
	// should be overloaded, but should not be called
	virtual void Draw() const = 0;

	bool m_bVisible = true;

	std::shared_ptr<Program> m_program;
	std::vector<std::shared_ptr<Attribute>> m_attributes;
	std::vector<std::shared_ptr<ModelMatrix>> m_models;
	std::vector<std::function<void()>> m_uniforms;
};
_GL_END