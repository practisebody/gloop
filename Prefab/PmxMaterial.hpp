 #pragma once

_GL_BEGIN
_PREFAB_BEGIN
class PmxMaterial : public ProgramAttribute<std::tuple<>>
{
public:
	PmxMaterial(const std::string& name) : ProgramAttribute(name),
		m_cAmbient(name + ".ambient"), m_cDiffuse(name + ".diffuse"), m_cSpecular(name + ".specular")
	{
	}
	
	virtual const PmxMaterial* Bind() const override
	{
		Program* program = Program::GetCurrent();
		program->Uniform((m_sName + ".bTexture").c_str(), m_bTexture);
		if (m_texDiffuse)
			program->Uniform((m_sName + ".tDiffuse").c_str(), m_texDiffuse);
		m_cAmbient.Bind();
		m_cDiffuse.Bind();
		m_cSpecular.Bind();
		program
			->Uniform((m_sName + ".exponent").c_str(), m_fExponent)
			->Uniform((m_sName + ".dissolve").c_str(), m_fDissolve);
		EL_PSY_CONGROO;
	}
	
	PmxMaterial* SetTexDiffuse(const std::shared_ptr<Texture2D>& texDiffuse)
	{
		m_texDiffuse = texDiffuse;
		m_bTexture = static_cast<bool>(m_texDiffuse);
		EL_PSY_CONGROO;
	}

	PmxMaterial* SetAmbient(const glm::vec4& ambient)
	{
		m_cAmbient = ambient;
		EL_PSY_CONGROO;
	}

	PmxMaterial* SetDiffuse(const glm::vec4& diffuse)
	{
		m_cDiffuse = diffuse;
		EL_PSY_CONGROO;
	}

	PmxMaterial* SetSpecular(const glm::vec4& specular)
	{
		m_cSpecular = specular;
		EL_PSY_CONGROO;
	}

	PmxMaterial* SetSpecularExponent(const float exponent)
	{
		m_fExponent = exponent;
		EL_PSY_CONGROO;
	}

	PmxMaterial* SetDissolve(const float dissolve)
	{
		m_fDissolve = dissolve;
		EL_PSY_CONGROO;
	}

	bool HasTexture()
	{
		return static_cast<bool>(m_texDiffuse);
	}

protected:
	int m_bTexture = 0;
	std::shared_ptr<Texture2D> m_texDiffuse;
	Color3 m_cAmbient;
	Color3 m_cDiffuse;
	Color3 m_cSpecular;
	float m_fExponent;
	float m_fDissolve;
};
_PREFAB_END
_GL_END