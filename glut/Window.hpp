#pragma once

#include <glm/gtx/transform.hpp>

_GL_BEGIN
// A OpenGL Window, the output
class Window : public IDObject, public Shared<Window>
{
public:
	template<class... T>
	Window(const std::string& name) : m_sName(name)
	{
	}

	~Window()
	{
		glutDestroyWindow(GetID());
	}
	
	Window* Data()
	{
		EL_PSY_CONGROO;
	}

	Window* SetMode(const std::initializer_list<DISPLAY_MODE>& modes)
	{
		m_nDisplayMode = 0;
		for (DISPLAY_MODE mode : modes)
			m_nDisplayMode |= static_cast<GLenum>(mode);
		EL_PSY_CONGROO;
	}
	
	template<class... T>
	Window* Data(const std::initializer_list<DISPLAY_MODE>& modes, T... t)
	{
		SetMode(modes);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	template<class... Modes, class = std::enable_if_t<std::conjunction_v<std::is_same<Modes, DISPLAY_MODE>...>>>
	Window* SetMode(Modes... modes)
	{
		m_nDisplayMode = (static_cast<GLenum>(modes) | ...);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Window* Data(DISPLAY_MODE mode, T... t)
	{
		m_nDisplayMode |= static_cast<GLenum>(mode);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* SetSize(int width, int height)
	{
		SetSize(glm::ivec2(width, height));
		EL_PSY_CONGROO;
	}

	template<class... T>
	Window* Data(int width, int height, T... t)
	{
		SetSize(glm::ivec2(width, height));
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* SetSize(const glm::ivec2& size)
	{
		m_n2Size = size;
		if (m_bCreated)
			glutReshapeWindow(m_n2Size[0], m_n2Size[1]);
		EL_PSY_CONGROO;
	}

	template<class... T>
	Window* Data(const glm::ivec2& size, T... t)
	{
		SetSize(size);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* SetProjMatrix(const std::shared_ptr<ProjMatrix>& projMatrix)
	{
		m_projMatrix = projMatrix;
		EL_PSY_CONGROO;
	}

	template<class... T>
	Window* Data(const std::shared_ptr<ProjMatrix>& proj, T... t)
	{
		SetProjMatrix(proj);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* SetViewMatrix(const std::shared_ptr<ViewMatrix>& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
		EL_PSY_CONGROO;
	}
	
	template<class... T>
	Window* Data(const std::shared_ptr<ViewMatrix>& view, T... t)
	{
		SetViewMatrix(view);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* SetWorld(const std::shared_ptr<Object>& world)
	{
		m_world = world;
		EL_PSY_CONGROO;
	}

	template<class... T>
	Window* Data(const std::shared_ptr<Object>& world, T... t)
	{
		SetWorld(world);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* SetBackgroundColor(const glm::vec4& color)
	{
		m_cBackground = color;
		EL_PSY_CONGROO;
	}

	template<class... T>
	Window* Data(const glm::vec4& color, T... t)
	{
		SetBackgroundColor(color);
		Data(std::forward<T>(t)...);
		EL_PSY_CONGROO;
	}

	Window* EnableTranslation(bool enable = true)
	{
		m_fTranslationSpeed = (enable ? 1.0f : -1.0f) * fabs(m_fTranslationSpeed);
		EL_PSY_CONGROO;
	}

	Window* SetTranslationSpeed(float speed)
	{
		m_fTranslationSpeed = speed;
		EL_PSY_CONGROO;
	}

	Window* EnableRotation(bool enable = true)
	{
		m_fRotationSpeed = (enable ? 1.0f : -1.0f) * fabs(m_fRotationSpeed);
		EL_PSY_CONGROO;
	}

	Window* SetRotationSpeed(float speed)
	{
		m_fRotationSpeed = speed;
		EL_PSY_CONGROO;
	}

	Window* SetRefresh(bool enable = true)
	{
		m_bRefresh = enable;
		EL_PSY_CONGROO;
	}

#if defined(GLUI_GLUI_H)
	template<class Fn, class = std::enable_if_t<std::is_invocable_v<Fn, GLUI*>>>
	Window* SetUI(Fn func)
	{
		m_fUI = func;
		EL_PSY_CONGROO;
	}
#endif

	template<GL::CALLBACK_FUNC type, class Fn>
	Window* Bind(Fn func)
	{

		if constexpr (type == GL::CALLBACK_FUNC::DISPLAY)
			m_fDisplay = func;
		else if constexpr (type == GL::CALLBACK_FUNC::KEYBOARD)
			m_fKeyboard = func;
		else if constexpr (type == GL::CALLBACK_FUNC::MOUSE)
			m_fMouse = func;
		else if constexpr (type == GL::CALLBACK_FUNC::IDLE)
			m_fIdle = func;
		else if constexpr (type == GL::CALLBACK_FUNC::RESHAPE)
			m_fReshape = func;
		else if constexpr (type == GL::CALLBACK_FUNC::MOTION)
			m_fMotion = func;
		else if constexpr (type == GL::CALLBACK_FUNC::PASSIVEMOTION)
			m_fPassiveMotion = func;
		else if constexpr (type == GL::CALLBACK_FUNC::INIT)
			m_fInit = func;
		else if constexpr (type == GL::CALLBACK_FUNC::UPDATE)
			m_fUpdate = func;
		else
			static_assert(false, "Unknown callback function type! Don't cast!");
		EL_PSY_CONGROO;
	}

	friend class App;

protected:
	void Create()
	{
		if (m_bCreated == false)
		{
			// provide default parameters if not set by user
			// default size
			if (m_n2Size.x == 0 || m_n2Size.y == 0)
				SetSize(800, 800);
			// default mode
			if (m_nDisplayMode == 0)
				SetMode(DISPLAY_MODE::RGBA, DISPLAY_MODE::DOUBLE, DISPLAY_MODE::DEPTH);
			
			// create OpenGL context
			glutInitDisplayMode(m_nDisplayMode);
			glutInitWindowSize(m_n2Size[0], m_n2Size[1]);
			ID() = glutCreateWindow(m_sName.c_str());
			m_context = wglGetCurrentContext();
			// share all the objects from previous contexts
			if (Initializer::GetShare())
				std::for_each(m_contexts.begin(), m_contexts.end(),
					std::bind(wglShareLists, std::placeholders::_1, m_context));

			m_contexts.emplace_back(m_context);
			m_windows[m_context] = this;
#if defined(__gl3w_h_)
			gl3wInit();
#elif defined(__glew_h__)
			glewInit();
#else
			#pragma warning("Unrecognized context, only support glew and gl3w")
#endif
			m_bCreated = true;

#if defined(GLUI_GLUI_H)
			if (m_fUI)
			{
				m_pGLUI = std::unique_ptr<GLUI, std::function<void(GLUI*)>>(
					GLUI_Master.create_glui("GLUI"), std::mem_fn(&GLUI::close));
				m_fUI(m_pGLUI.get());
				m_pGLUI->set_main_gfx_window(GetID());
			}
#endif

			// bind callback functions
			if (m_fInit)
				m_fInit();
			glutDisplayFunc(Window::DisplayFunc);
			glutKeyboardFunc(Window::KeyboardFunc);
			glutMouseFunc(Window::MouseFunc);
			if (m_fIdle)
				glutIdleFunc(Window::IdleFunc);
			if (m_fReshape)
				glutReshapeFunc(Window::ReshapeFunc);
			glutMotionFunc(Window::MotionFunc);
			if (m_fPassiveMotion)
				glutPassiveMotionFunc(Window::PassiveMotionFunc);
			
			// init
			Initializer::InitAll();
			if (detail::DepthMode(m_nDisplayMode))
				glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glutSetWindow(GetID());
		}
	}

	// attributes
	const std::string m_sName;
	GLenum m_nDisplayMode = 0;
	glm::ivec2 m_n2Size = glm::ivec2(0, 0);
	// TODO, for subwindow
	//std::weak_ptr<Window> m_wParent;
	HGLRC m_context;
	// default background color, white
	glm::vec4 m_cBackground = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	// helper variables
	bool m_bCreated = false;

	// navigation parameters, positive for valid parameter
	bool m_bShiftDown = false;
	bool m_bCtrlDown = false;
	bool m_bAltDown = false;
	float m_fTranslationSpeed = 0.05f;
	float m_fRotationSpeed = 0.001f;
	int m_nBaseX, m_nBaseY;
	glm::mat4 m_mBaseView;
	// matrices
	std::shared_ptr<ProjMatrix> m_projMatrix = defaultProjMatrix;
	std::shared_ptr<ViewMatrix> m_viewMatrix = defaultViewMatrix;
	// default matrices
	inline static const std::shared_ptr<ProjMatrix> defaultProjMatrix =
		std::make_shared<ProjMatrix>();
	inline static const std::shared_ptr<ViewMatrix> defaultViewMatrix =
		std::make_shared<ViewMatrix>();

	// world
	std::shared_ptr<Object> m_world;

#if defined(GLUI_GLUI_H)
	std::unique_ptr<GLUI, std::function<void(GLUI*)>> m_pGLUI;
	std::function<void(GLUI*)> m_fUI;
#endif
	
	// callback functions
	bool m_bRefresh = false;
	std::function<void()> m_fDisplay;
	std::function<void(unsigned char, int, int)> m_fKeyboard;
	std::function<void(int, int, int, int)> m_fMouse;
	std::function<void()> m_fIdle;
	std::function<void(int, int)> m_fReshape;
	std::function<void(int, int)> m_fMotion;
	std::function<void(int, int)> m_fPassiveMotion;
	// non standard
	std::function<void()> m_fInit;
	std::function<void()> m_fUpdate;

	static Window* GetCurrent()
	{
		if (std::map<HGLRC, Window*>::iterator it = m_windows.find(wglGetCurrentContext());
			it != m_windows.end())
			return it->second;
		else
			return nullptr;
	}

	// current there is a bug if not initialize this variable, so initialize to empty
	// https://developercommunity.visualstudio.com/content/problem/174388/internal-compiler-error-regarding-inline-static-va.html
	inline static std::vector<HGLRC> m_contexts {};
	inline static std::map<HGLRC, Window*> m_windows {};

private:
	// glut functions, note that only standard callback will appear here
	static void DisplayFunc()
	{
		Window* pWindow = GetCurrent();
		
		GLenum nMode = pWindow->m_nDisplayMode;

		glClearColor(pWindow->m_cBackground[0], pWindow->m_cBackground[1], pWindow->m_cBackground[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | (detail::DepthMode(nMode) ? GL_DEPTH_BUFFER_BIT : 0));

		pWindow->m_projMatrix->Bind();
		pWindow->m_viewMatrix->Bind();

		// update
		if (pWindow->m_fUpdate)
			pWindow->m_fUpdate();
		// Render world, if exists
		if (pWindow->m_world)
			pWindow->m_world->Render();
		// Additional rendering, if needed
		if (pWindow->m_fDisplay)
			pWindow->m_fDisplay();

		pWindow->m_projMatrix->Unbind();
		pWindow->m_viewMatrix->Unbind();

		if (nMode & int(GL::DISPLAY_MODE::SINGLE))
			glFlush();
		else
			glutSwapBuffers();
		if (pWindow->m_bRefresh)
			glutPostRedisplay();
	}

	static void KeyboardFunc(unsigned char key, int x, int y)
	{
		if (key == 27)
			exit(0);
		else if (key == 8)
			Initializer::Init(OBJECT_TYPE::GLSL);
		Window* pWindow = GetCurrent();
		if (pWindow->m_fKeyboard)
			pWindow->m_fKeyboard(key, x, y);
		if (float speed = pWindow->m_fTranslationSpeed; speed > 0.0f)
		{
			glm::mat4& view = *pWindow->m_viewMatrix;
			switch (key)
			{
			case 's':
				view = glm::translate(glm::vec3(0.0f, speed, 0.0f)) * view;
				break;
			case 'w':
				view = glm::translate(glm::vec3(0.0f, -speed, 0.0f)) * view;
				break;
			case 'a':
				view = glm::translate(glm::vec3(speed, 0.0f, 0.0f)) * view;
				break;
			case 'd':
				view = glm::translate(glm::vec3(-speed, 0.0f, 0.0f)) * view;
				break;
			}
		}
		if (std::shared_ptr<Group> group = std::dynamic_pointer_cast<Group>(pWindow->m_world))
		{
			if (key >= '0' && key <= '9')
			{
				size_t index = key == '0' ? 9 : (key - '1');
				if (index < group->GetObjects().size())
				{
					std::shared_ptr<GL::Object> o = group->GetObjects()[index];
					o->SetVisible(!o->GetVisible());
				}
			}
		}
		glutPostRedisplay();
	}

	static void MouseFunc(int button, int state, int x, int y)
	{
		Window* pWindow = GetCurrent();
		if (pWindow->m_fMouse)
			pWindow->m_fMouse(button, state, x, y);
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			pWindow->m_bShiftDown = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
			pWindow->m_bCtrlDown = glutGetModifiers() & GLUT_ACTIVE_CTRL;
			pWindow->m_bAltDown = glutGetModifiers() & GLUT_ACTIVE_ALT;
			pWindow->m_nBaseX = x;
			pWindow->m_nBaseY = y;
			pWindow->m_mBaseView = *pWindow->m_viewMatrix;
		}
		glutPostRedisplay();
	}

	static void IdleFunc()
	{
		if (Window* pWindow = GetCurrent(); pWindow != nullptr && pWindow->m_fIdle)
		{
			glutSetWindow(pWindow->GetID());
			pWindow->m_fIdle();
		}
	}

	static void ReshapeFunc(int width, int height)
	{
		GetCurrent()->m_fReshape(width, height);
		glutPostRedisplay();
	}

	static void MotionFunc(int x, int y)
	{
		Window* pWindow = GetCurrent();
		if (pWindow->m_fMotion)
			pWindow->m_fMotion(x, y);
		if (float speed = pWindow->m_fRotationSpeed; speed > 0.0f)
		{
			if (pWindow->m_bAltDown)
			{
				glm::vec4 center = pWindow->m_mBaseView * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
				glm::vec3 up = pWindow->m_mBaseView * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) - center;
				glm::vec3 right = pWindow->m_mBaseView * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) - center;
				glm::mat4 rx = glm::rotate(speed * (pWindow->m_nBaseX - x), up);
				glm::mat4 ry = glm::rotate(speed * (y - pWindow->m_nBaseY), right);
				*pWindow->m_viewMatrix = pWindow->m_mBaseView * rx * ry;
			}
			else if (pWindow->m_bShiftDown)
			{
				int cx = pWindow->m_n2Size.x / 2, cy = pWindow->m_n2Size.y / 2;
				float angle = atan2(pWindow->m_nBaseY - cy, pWindow->m_nBaseX - cx) - atan2(y - cy, x - cx);
				glm::mat4 r = glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
				*pWindow->m_viewMatrix = r * pWindow->m_mBaseView;
			}
			else
			{
				glm::mat4 rx = glm::rotate(speed * (x - pWindow->m_nBaseX), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 ry = glm::rotate(speed * (y - pWindow->m_nBaseY), glm::vec3(1.0f, 0.0f, 0.0f));
				*pWindow->m_viewMatrix = rx * ry * pWindow->m_mBaseView;
			}
		}
		if (float speed = pWindow->m_fTranslationSpeed; speed > 0.0f)
		{
			if (pWindow->m_bCtrlDown)
			{
				*pWindow->m_viewMatrix = glm::translate(glm::vec3(0.0f, 0.0f, speed * (y - pWindow->m_nBaseY))) * pWindow->m_mBaseView;
			}
		}
		glutPostRedisplay();
	}

	static void PassiveMotionFunc(int x, int y)
	{
		GetCurrent()->m_fPassiveMotion(x, y);
		glutPostRedisplay();
	}
};
_GL_END