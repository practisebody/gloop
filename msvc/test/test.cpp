#include <memory>

#include <gl3w.h>
#include <gloop/gloop.hpp>
#include <gloop/glut.hpp>
#include <gloop/Prefab.hpp>

const glm::vec2 g_WindowSize(800, 600);

const std::vector<glm::vec3> vert =
{
	{ -1.0f, -1.0f, 0.0f },
	{ 1.0f, -1.0f, 0.0f, },
	{ 0.0f,  1.0f, 0.0f, },
};

glm::vec4 color(1.0f, 1.0f, 0.0f, 0.0f);
glm::vec2 testtt(1, 1);

glm::vec3 eye(0.0f, 0.0f, -1.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f);
std::shared_ptr<GL::ViewMatrix> view = GL::Make<GL::ViewMatrix>(glm::lookAt(eye, center, up));

std::shared_ptr<GL::Texture2D> lenna = GL::Make<GL::Prefab::BMPTexture>("Lenna.bmp");

std::shared_ptr<GL::Program> renderer = GL::Make<GL::Program>("default.vs", "test.fs")
	->Uniform("cin", color)
	->Uniform("a", testtt)
	//->Uniform("a", glm::vec2(1, 1))
	->Uniform("tttt", lenna)
	->QED();

std::shared_ptr<GL::Object> world = std::make_shared<GL::World>()
	->AddObject(GL::Make<GL::VAO(GL::Any<1>)>(GL::DRAW_MODE::TRIANGLES,
		GL::Make<GL::IBO>(
			std::vector<glm::uvec3>
			{
				{ 0, 1, 2 },
			}
		),
		std::vector<glm::vec3>
		{
			{ -1.0f, -1.0f, 0.0f },
			{ 1.0f, -1.0f, 0.0f },
			{ 0.0f,  1.0f, 0.0f },
		},
		std::vector<glm::vec2>
		{
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 0.0f }
		},
		std::vector<glm::vec3>
		{
			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f },
		})
		//->AddAttribute(renderer)
		//->AddAttribute(GL::Prefab::progPmxMaterial)
		//->Uniform("m.diffuse", color)
		->QED())
	//->AddObject(GL::Make<GL::Prefab::Quad>()
	//	->SetTexture(GL::Make<GL::Prefab::BMPTexture>("Lenna.bmp"))
	//	->QED())
	->QED();

std::shared_ptr<GL::ModelMatrix> a = GL::Make<GL::ModelMatrix>(glm::scale(glm::vec3(0.03f, 0.03f, 0.03f)));

std::shared_ptr<GL::Object> world2 = std::make_shared<GL::World>()
	//->AddObject(GL::Make<GL::Prefab::PmxObjObject>("Model/MikuLuan.obj"))
	->AddObject(GL::Make<GL::Prefab::PmxObjObject>("test.obj"))
	/*->AddObject(GL::Make<GL::Prefab::Box>()
		->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
		->QED())*/
	//->AddObject(GL::Make<GL::Prefab::Frustum>())
	->QED();

int main(int argc, char* argv[])
{
	GL::App::Init(argc, argv)
		->AddWindow(std::make_shared<GL::Window>("Main")
			->SetMode(GL::DISPLAY_MODE::RGBA, GL::DISPLAY_MODE::DOUBLE, GL::DISPLAY_MODE::DEPTH)
			->SetSize(g_WindowSize)
			->SetWorld(world2)
			->SetViewMatrix(view)
			BIND_KEYBOARD(key, x, y)
				switch (key)
				{
				case 27:
					exit(0);
				case 'w':
					eye.x -= 1.0f;
					center.x -= 1.0f;
					*view = glm::lookAt(eye, center, up);
					break;
				case 'g':
					testtt.x = 1.0f - testtt.x;
					color.y -= 0.1f;
					break;
				}
			END_BIND
			->QED())
		/*->AddWindow(std::make_shared<GL::Window>("Second")
			->SetMode(GL::DISPLAY_MODE::RGBA, GL::DISPLAY_MODE::DOUBLE, GL::DISPLAY_MODE::DEPTH)
			->SetSize(g_WindowSize)
			->SetWorld(world)
			->SetViewMatrix(view)
			BIND_KEYBOARD(key, x, y)
			switch (key)
			{
			case 27:
				exit(0);
			case 'w':
				eye.x -= 1.0f;
				center.x -= 1.0f;
				*view = glm::lookAt(eye, center, up);
				break;
			case 'g':
				color.y -= 0.1f;
				break;
			}
			END_BIND
			->QED())*/
		->Run();
	return 0;
}