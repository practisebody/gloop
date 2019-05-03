#pragma once

_GL_BEGIN
// Singleton
// This class saves everything that to be initialized after OpenGL context is created
// deferring those calls when the context is actually created
class Initializer final : public Unique
{
public:
	// if OpenGL context is created, directly call the function
	// otherwise push to the queue to be called later
	template<class Fn>
	inline static void Push(Fn&& func, OBJECT_TYPE type)
	{
		if (wglGetCurrentContext())
			func();
		else
			switch (type)
			{
			case OBJECT_TYPE::GLSL:
				m_initGLSLFuncs.emplace_back(func);
				break;
			case OBJECT_TYPE::REGULAR:
				m_initRegularFuncs.emplace_back(func);
				break;
			case OBJECT_TYPE::CONTAINER:
				m_initContainerFuncs.emplace_back(func);
				break;
			case OBJECT_TYPE::OTHER:
				// it's not a OpenGL object, so initialize it directly
				func();
				m_initOtherFuncs.emplace_back(func);
				break;
			default:
				assert(false);
				break;
			}
	}

	// call all the functions in order, only to be called in GLWindow class,
	// where the context is created (glutCreateWindow)
	static void InitAll()
	{
		assert(wglGetCurrentContext());
		Init(OBJECT_TYPE::GLSL);
		if (m_init == false || m_share == false)
		{
			Init(OBJECT_TYPE::REGULAR);
			m_init = true;
		}
		Init(OBJECT_TYPE::CONTAINER);
	}

	static void Init(OBJECT_TYPE type)
	{
		switch (type)
		{
		case OBJECT_TYPE::GLSL:
			Init(m_initGLSLFuncs);
			break;
		case OBJECT_TYPE::REGULAR:
			Init(m_initRegularFuncs);
			break;
		case OBJECT_TYPE::CONTAINER:
			Init(m_initContainerFuncs);
			break;
		case OBJECT_TYPE::OTHER:
			Init(m_initOtherFuncs);
			break;
		default:
			assert(false);
			break;
		}
	}

	static void SetShare(bool share)
	{
		m_share = share;
	}

	static bool GetShare()
	{
		return m_share;
	}

protected:
	inline static std::unique_ptr<Initializer> instance = std::make_unique<Initializer>();

	static void Init(const std::vector<std::function<void()>>& funcs)
	{
		for (const std::function<void()>& f : funcs)
			f();
	}
	
	inline static bool m_init = false;
	// whether we share objects between contexts, or initialize every object for each context
	inline static bool m_share = true;

	inline static std::vector<std::function<void()>> m_initGLSLFuncs {};
	inline static std::vector<std::function<void()>> m_initRegularFuncs {};
	inline static std::vector<std::function<void()>> m_initContainerFuncs {};
	inline static std::vector<std::function<void()>> m_initOtherFuncs {};
};
_GL_END