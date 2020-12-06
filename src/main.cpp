/**
 * main.cpp Entry point into application
 * @author Nathan McCulloch
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Shader.hpp>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"
#include "Controls.hpp"
#include "Scene.hpp"
#include "Cube.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

int main() {
    // Initialize and configure GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Render Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD failed to initialize" << std::endl;
    }

    // Enable OpenGL depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
    //glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    Shader* myShader = new Shader("src/shaders/vertex.shader", "src/shaders/fragment.shader");

    Scene* scene = new Scene();
    Cube* cube1 = new Cube("src/textures/wooden_container.jpg");
    Cube* cube2 = new Cube("src/textures/wooden_container.jpg");
    cube1->setTranslationMatrix(glm::vec3(0.0, 3.0, 0.0));
    cube2->setTranslationMatrix(glm::vec3(3.0, 0.0, 0.0));
    cube1->setObjectShader(myShader);
    cube2->setObjectShader(myShader);
    scene->addObject(cube1);
    scene->addObject(cube2);
    
    
    Camera* camera = new Camera();
    camera->setCameraPosition(glm::vec3(0, 0, 5));
    camera->setCameraTarget(glm::vec3(0, 0, 0));
    Controls* controls = new Controls(camera);
    controls->setCameraMovementSpeed(3);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        controls->checkUserInputs(window);
        scene->render(camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}