// Will Gilstrap - Game Engine
// 1/27/2014

#include <Input.h>

void Input::Rotate(GLFWwindow* window, Sprite &s, mat4 &trans)
{
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_R))
		{
			trans = glm::rotate(trans, 180.0f, vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
}

void Input::Move(GLFWwindow* window, Sprite &s, mat4 &trans)
{
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W))	// up
		{
			trans = glm::translate(trans, vec3(0.0f, 0.006f, 0.0f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_S))	// down
		{
			trans = glm::translate(trans, vec3(0.0f, -0.006f, 0.0f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A))	// left
		{
			trans = glm::translate(trans, vec3(-0.006f, 0.0f, 0.0f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_D))	// right
		{
			trans = glm::translate(trans, vec3(0.006f, 0.0f, 0.0f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
}

void Input::Scale(GLFWwindow* window, Sprite &s, mat4 &trans)
{
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_O))	// smaller
		{
			trans = glm::scale(trans, vec3(0.99f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_P))	// bigger
		{
			trans = glm::scale(trans, vec3(1.009f, 1.009f, 0.0f));
			glUniformMatrix4fv(s.uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
}