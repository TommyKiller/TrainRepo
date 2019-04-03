#include <cmath>
#include <vector>
#include "framework.h"


const float MOVING_SPEED = 0.02f;


System::Window* window;
std::shared_ptr<Game::World> world;
Graphics::ShaderProgram* shader;

std::unordered_map<GLenum, const char*> shaderFiles =
{
	{ GL_VERTEX_SHADER, "Shaders/vertexShader.shr" },
	{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.shr" }
};

int main()
{
	// Setting system up //
	System::InitialiseGLFW(3, 3);
	window = new System::Window(0, 0, 1360, 768, "Test", false);
	window->MakeCurrent();
	window->SetCallbacks(Graphics::Render::GetInstance().FramebufferSizeCallback, Input::InputController::KeyCallback, Input::InputController::MouseCallback);
	window->DisableCursor();
	System::InitialiseGLEW(window);
	Graphics::Render::GetInstance().ClearColor(glm::vec4(0.4f, 0.3f, 0.5f, 1.0f));
	Graphics::Render::GetInstance().Enable(GL_DEPTH_TEST);

	// Create objects //
	int framebuffer_width, framebuffer_height;
	window->GetFramebufferSize(&framebuffer_width, &framebuffer_height);
	world = std::make_shared<Game::World>();
	world->AddScene(new Game::Scene(0, glm::perspective(45.0f, (GLfloat)framebuffer_width / (GLfloat)framebuffer_height, 0.1f, 100.0f)));
	world->SetActiveScene(0);
	shader = new Graphics::ShaderProgram(shaderFiles);
	Graphics::Camera::GetInstance().Initialise(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 3.0f, 0.1f);
	Engine::Editor::GetInstance().EditWorld(world);

	while (!window->ShouldClose())
	{
		System::CalcDeltaTime();

		glfwPollEvents();
		Input::InputController::GetInstance().PollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering //
		Graphics::Render::GetInstance()(shader, world->GetActiveScene());

		window->SwapBuffers();
	}

	glfwTerminate();

	return 0;
}
