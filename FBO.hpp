#pragma once

_GL_BEGIN
class FBO : public GLContainer, public Object, public Shared<FBO>
{
public:
	using Shared<FBO>::QED;

	FBO() : m_tex(GL::Make<GL::Texture2D>())
	{
		_GL_INIT_BEGIN;
		glGenFramebuffers(1, &ID());
		glGenRenderbuffers(1, &m_uDepthId);
		_GL_INIT_END;
	}

	~FBO()
	{
		glDeleteFramebuffers(1, &GetID());
		glDeleteRenderbuffers(1, &m_uDepthId);
	}

	virtual const FBO* Bind() const override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, GetID());
		EL_PSY_CONGROO;
	}

	virtual const FBO* Unbind() const override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		m_tex->Unbind();
		EL_PSY_CONGROO;
	}

	FBO* Data(const int width, const int height)
	{
		m_nWidth = width;
		m_nHeight = height;
		m_tex->Data(m_nWidth, m_nHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, GetID());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex->GetID(), 0);
		glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_nWidth, m_nHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uDepthId);
		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		m_tex->Unbind();
		EL_PSY_CONGROO;
	}

	FBO* SetWorld(const std::shared_ptr<Object>& world)
	{
		m_world = world;
		EL_PSY_CONGROO;
	}

	FBO* Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		EL_PSY_CONGROO;
	}

	inline const std::shared_ptr<Texture2D>& Texture() const
	{
		return m_tex;
	}

	inline const FBO* ReadPixel(void* data) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, GetID());
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(0, 0, m_nWidth, m_nHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		EL_PSY_CONGROO;
	}

protected:
	virtual void Draw() const override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, GetID());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_world->Render();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		m_tex->Unbind();
	}

	int m_nWidth, m_nHeight;
	const std::shared_ptr<Texture2D> m_tex;
	GLuint m_uDepthId;
	std::shared_ptr<Object> m_world;
};
_GL_END