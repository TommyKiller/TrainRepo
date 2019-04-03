#include "Render.h"

Graphics::Render::Render()
{}

Graphics::Render::~Render()
{}

Graphics::Render& Graphics::Render::GetInstance()
{
	static Graphics::Render instance;

	return instance;
}

void Graphics::Render::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	Graphics::Render::GetInstance().ReshapeViewport(xpos, ypos, width, height);
}

void Graphics::Render::Unbind()
{
	glBindTexture(GL_TEXTURE_1D, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_3D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Graphics::Render::ReshapeViewport(int xpos, int ypos, int width, int height)
{
	glViewport(xpos, ypos, width, height);
}

void Graphics::Render::ClearColor(glm::vec4 clear_color)
{
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
}

void Graphics::Render::Enable(GLenum cap)
{
	glEnable(cap);
}

void Graphics::Render::operator()(ShaderProgram* shader_program, Game::Actor* actor, glm::mat4 projection)
{
	shader_program->Use();
	shader_program->SetUniform("projection", 1, GL_FALSE, projection);
	shader_program->SetUniform("view", 1, GL_FALSE, Graphics::Camera::GetInstance().CalcViewMat());
	shader_program->SetUniform("texture1", 0);
	actor->GetModel()->UseTexture();
	actor->GetModel()->UseMesh();
	shader_program->SetUniform("model", 1, GL_FALSE, actor->GetModel()->CalcModelMat());
	glDrawElements(GL_TRIANGLES, actor->GetModel()->GetElementsCount(), GL_UNSIGNED_INT, 0);
	Unbind();
}

void Graphics::Render::operator()(ShaderProgram* shader_program, std::weak_ptr<Game::Scene> scene)
{
	shader_program->Use();
	shader_program->SetUniform("projection", 1, GL_FALSE, scene.lock()->GetProjection());
	shader_program->SetUniform("view", 1, GL_FALSE, Graphics::Camera::GetInstance().CalcViewMat());
	shader_program->SetUniform("texture1", 0);
	std::for_each(scene.lock()->GetActors().begin(), scene.lock()->GetActors().end(), [&shader_program](std::pair<int, std::weak_ptr<Game::Actor>> actor)
		{
			actor.second.lock()->GetModel()->UseTexture();
			actor.second.lock()->GetModel()->UseMesh();
			shader_program->SetUniform("model", 1, GL_FALSE, actor.second.lock()->GetModel()->CalcModelMat());
			glDrawElements(GL_TRIANGLES, actor.second.lock()->GetModel()->GetElementsCount(), GL_UNSIGNED_INT, 0);
		});
	Unbind();
}
