/*
-Grupo-
Lucas Lima Aires RA: 22202072
Pedro Paulo Gadioli
Rafael Lavoyer
*/

#include<GLFW/glfw3.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<vector>
#include "modL.h"

// Declarações das funções
void init(GLFWwindow* window);
void kBoard(GLFWwindow * window, int key, int scancode, int action, int mods);
void view(int w, int h);
float speed = 0;
static float angle = 0;
static unsigned IdModel;

// Posições e rotação do carrossel
void draw(float data) {
	glLoadIdentity();
	vt1 position(0.f, 37.f, 0.f);
	vt1 direction(0.f, 0.f, -3.f);
	vt1 up(0.f, 1.f, 0.f);
	vt1 look = position + direction;// direction;
	gluLookAt(
	position.x, position.y, position.z,
	look.x, look.y, look.z,
	up.x, up.y, up.z);
	angle += speed;
	glPushMatrix();
	glTranslatef(0.f, 0.f, -155.f);
	glRotatef(-angle, 0.f, 1.0f, 0.f);
	glCallList(IdModel);
	glPopMatrix();
	if (angle >= 360.0)
		angle = 0.0;
}

// Função principal
int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Tutorial Light - Blender", NULL, NULL);
	init(window);
	float lastTime = 0.0;
	bool running = true;
	while (running)
	{
		float currentTime = (float)glfwGetTime();
		float data = currentTime - lastTime;
		lastTime = currentTime;
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor (1.0, 1.0, 1.0, 1.0);
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		view(width, height);
		draw(data);
		glfwSwapBuffers(window);
		running = !glfwWindowShouldClose(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// Inicia a janela GLFW
void init(GLFWwindow* window) {
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, kBoard);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	modL::loadModel(IdModel, "carrossel.obj");
}

// Função para acertar a visualização
void view(int w, int h){
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

// Função do teclado para aumentar ou diminuir a velocidade do carrossel
void kBoard(GLFWwindow * window, int key, int scancode, int action, int mods){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) && (speed > 0))
		speed--;
	if ((glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) && (speed < 5))
		speed++;
}
