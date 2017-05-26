#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Sphere.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

cg::Sphere* sun = nullptr;

cg::Sphere* planet1 = nullptr;
cg::Sphere* planet2 = nullptr;

cg::Sphere* moon1_1 = nullptr;
cg::Sphere* moon1_2 = nullptr;
cg::Sphere* moon1_3 = nullptr;

cg::Sphere* moon2_1 = nullptr;
cg::Sphere* moon2_2 = nullptr;
cg::Sphere* moon2_3 = nullptr;
cg::Sphere* moon2_4 = nullptr;


glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

const float sun_size = 1.4f;
const float planet_size = 0.6f;
const float moon_size = 0.3f;


GLint alpha = 0;
GLint beta = 45;

/*
Release resources on termination.
*/
void release()
{
	delete sun;
	delete planet1;
	delete planet2;

	delete moon1_1;
	delete moon1_2;
	delete moon1_3;

	delete moon2_1;
	delete moon2_2;
	delete moon2_3;
	delete moon2_4;
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{

	// OpenGL stuff. Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Width of the lines.
	glLineWidth(1.0f);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 8.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create pyramid object.
	try
	{
		sun = new cg::Sphere(glm::vec3(1.0f, 1.0f, 0.0f), true);

		planet1 = new cg::Sphere(glm::vec3(0.0f, 1.0f, 0.0f), true);
		planet2 = new cg::Sphere(glm::vec3(1.0f, 1.0f, 1.0f), true);

		moon1_1 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
		moon1_2 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
		moon1_3 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));

		moon2_1 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
		moon2_2 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
		moon2_3 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
		moon2_4 = new cg::Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	catch (const std::exception& e)
	{
		release();
		std::cerr << e.what() << std::endl;
		return false;
	}

	// Translate, Rotate, Scale and Draw

	sun->model = glm::scale(sun->model, glm::vec3(sun_size));
	

	planet1->model = glm::translate(planet1->model, glm::vec3(4.0f, 0.0f, 0.0f));
	planet1->model = glm::scale(planet1->model, glm::vec3(planet_size));
	
	moon1_1->model = glm::translate(planet1->model, glm::vec3(2.0f, 0.0f, 0.0f));
	moon1_1->model = glm::scale(moon1_1->model, glm::vec3(moon_size));

	moon1_2->model = glm::translate(planet1->model, glm::vec3(0.0f, 0.0f, 2.0f));
	moon1_2->model = glm::scale(moon1_2->model, glm::vec3(moon_size));

	moon1_3->model = glm::translate(planet1->model, glm::vec3(0.0f, 0.0f, -2.0f));
	moon1_3->model = glm::scale(moon1_3->model, glm::vec3(moon_size));
	
	planet2->model = glm::translate(sun->model, glm::vec3(-2.5f, 0.0f, 0.0f));
	planet2->model = glm::rotate(planet2->model, ((glm::pi<float>() * 2) / (360/(alpha+beta))), glm::vec3(0.0f, 0.0f, 1.0f));
	planet2->model = glm::scale(planet2->model, glm::vec3(planet_size));

	moon2_1->model = glm::translate(planet2->model, glm::vec3(-2.0f, 0.0f, 0.0f));
	moon2_1->model = glm::scale(moon2_1->model, glm::vec3(moon_size));

	moon2_2->model = glm::translate(planet2->model, glm::vec3(0.0f, 0.0f, 2.0f));
	moon2_2->model = glm::scale(moon2_2->model, glm::vec3(moon_size));

	moon2_3->model = glm::translate(planet2->model, glm::vec3(0.0f, 0.0f, -2.0f));
	moon2_3->model = glm::scale(moon2_3->model, glm::vec3(moon_size));

	moon2_4->model = glm::translate(planet2->model, glm::vec3(2.0f, 0.0f, 0.0f));
	moon2_4->model = glm::scale(moon2_4->model, glm::vec3(moon_size));

	std::cout << "Use x, y, z to rotate the sphere" << std::endl;
	std::cout << "Use + and - to scale the sphere" << std::endl;

	return true;
}

/*
 Rendering.
 */
void render()
{
	// Translate, Rotate, Scale and Draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	sun->render(view, projection);

	planet1->render(view, projection);
	planet2->render(view, projection);

	moon1_1->render(view, projection);
	moon1_2->render(view, projection);
	moon1_3->render(view, projection);

	moon2_1->render(view, projection);
	moon2_2->render(view, projection);
	moon2_3->render(view, projection);
	moon2_4->render(view, projection);

	
	sun->model = glm::rotate(sun->model, 0.00025f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));

	
	static GLfloat speed = 0.0000f; //Hier
	
	planet1->model = glm::translate(sun->model, glm::vec3(4.0f, 0.0f, 0.0f));
	planet1->model = glm::rotate(planet1->model, speed, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))); //Hier
	planet1->model = glm::scale(planet1->model, glm::vec3(planet_size));

	moon1_1->model = glm::translate(planet1->model, glm::vec3(2.0f, 0.0f, 0.0f));
	moon1_1->model = glm::scale(moon1_1->model, glm::vec3(moon_size));

	moon1_2->model = glm::translate(planet1->model, glm::vec3(0.0f, 0.0f, 2.0f));
	moon1_2->model = glm::scale(moon1_2->model, glm::vec3(moon_size));

	moon1_3->model = glm::translate(planet1->model, glm::vec3(0.0f, 0.0f, -2.0f));
	moon1_3->model = glm::scale(moon1_3->model, glm::vec3(moon_size));

	planet2->model = glm::translate(sun->model, glm::vec3(-3.0f, 0.0f, 0.0f));
	planet2->model = glm::rotate(planet2->model, ((glm::pi<float>() * 2) / (360 / beta)), glm::vec3(0.0f, 0.0f, 1.0f));
	planet2->model = glm::rotate(planet2->model, speed, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))); //Hier
	planet2->model = glm::scale(planet2->model, glm::vec3(planet_size));
	

	moon2_1->model = glm::translate(planet2->model, glm::vec3(-2.0f, 0.0f, 0.0f));
	moon2_1->model = glm::scale(moon2_1->model, glm::vec3(moon_size));
	
	moon2_2->model = glm::translate(planet2->model, glm::vec3(0.0f, 0.0f, 2.0f));
	moon2_2->model = glm::scale(moon2_2->model, glm::vec3(moon_size));

	moon2_3->model = glm::translate(planet2->model, glm::vec3(0.0f, 0.0f, -2.0f));
	moon2_3->model = glm::scale(moon2_3->model, glm::vec3(moon_size));

	moon2_4->model = glm::translate(planet2->model, glm::vec3(2.0f, 0.0f, 0.0f));
	moon2_4->model = glm::scale(moon2_4->model, glm::vec3(moon_size));

	speed += 0.0005f; //Hier
}

/*
 Resize callback.
 */
void resize(GLFWwindow* window, int width, int height)
{
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void keyboard(GLFWwindow* window, unsigned int codepoint)
{
	switch (codepoint)
	{
	case '+':
		sun->model = glm::scale(sun->model, glm::vec3(1.2f));
		break;
	case '-':
		sun->model = glm::scale(sun->model, glm::vec3(0.8f));
		break;
	case 's':
		if (alpha < 36) {
			alpha += 1;
			sun->model = glm::rotate(sun->model, ((glm::pi<float>()*2)/36) , glm::vec3(0.0f, 0.0f, 1.0f));
		}
		break;
	case 'S':
		if (alpha > 0) {
			alpha -= 1;
			sun->model = glm::rotate(sun->model, -((glm::pi<float>() * 2) / 36), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		break;
	case 'x':
		sun->model = glm::rotate(sun->model, 0.1f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		break;
	case 'X':
		sun->model = glm::rotate(sun->model, -0.1f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		break;
	case 'y':
		sun->model = glm::rotate(sun->model, 0.1f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case 'Y':
		sun->model = glm::rotate(sun->model, -0.1f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case 'z':
		sun->model = glm::rotate(sun->model, 0.1f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
		break;
	case 'Z':
		sun->model = glm::rotate(sun->model, -0.1f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
		break;
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window;

	// Initialize glfw library (window toolkit).
	if (!glfwInit())
		return -1;

	// Create a window and opengl context (version 3.3 core profile).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Turn this on for smoother lines.
	// glfwWindowHint(GLFW_SAMPLES, 8);
	
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sphere example", nullptr, nullptr);
	
	if (!window)
	{
		glfwTerminate();
		return -2;
	}

	// Make the window's opengl context current.
	glfwMakeContextCurrent(window);

	// Load opengl extensions
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	if (result != GLEW_OK)
	{
		glfwTerminate();
		return -3;
	}

	// Set callbacks for resize and keyboard events.
	glfwSetWindowSizeCallback(window, resize);
	glfwSetCharCallback(window, keyboard);

	if (!init())
	{
		release();
		glfwTerminate();

		return -4;
	}

	// We have to call resize once for a proper setup.
	resize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up everything on termination.
	release();
	glfwTerminate();

	return 0;
}