#pragma once

_GL_BEGIN
// OpenGL app, contains windows
class App final : public Unique
{
public:
	static App* Init(int argc, char** argv)
	{
		return Init(&argc, argv);
	}

	static App* Init(int* argcp, char** argv)
	{
		glutInit(argcp, argv);
		return instance.get();
	}

	static App* AddWindow(const std::shared_ptr<Window>& window)
	{
		m_windows.emplace_back(std::move(window));
		return instance.get();
	}

	static void Run()
	{
		for_each(m_windows.begin(), m_windows.end(), std::mem_fn(&Window::Create));
		glutMainLoop();
	}

protected:
	inline static std::unique_ptr<App> instance = std::make_unique<App>();

	// all the windows are saved here, won't be actually used
	// just to make sure they will be destructed correctly
	inline static std::vector<std::shared_ptr<Window>> m_windows {};
};
_GL_END