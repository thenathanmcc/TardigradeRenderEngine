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
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//using namespace ImGUI;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int WINDOW_WIDTH = 2560;
const unsigned int WINDOW_HEIGHT = 1440;
const char* glsl_version = "#version 130";
const char* gpu_info;

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

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    gpu_info = reinterpret_cast<const char *>(renderer);


    // Enable OpenGL depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
    //glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


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
    camera->setCameraPosition(glm::vec3(0, 0, -5));
    camera->setCameraTarget(glm::vec3(0, 3, 0));
    Controls* controls = new Controls(camera);
    controls->setCameraMovementSpeed(3);


    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Tardigrade Render Engine");
        ImGui::SetWindowSize(ImVec2(250.0f, 400.0f));
        //ImGui::BeginMenuBar();
        ImGui::Text("GPU: ");
        ImGui::Text(gpu_info);
        //ImGui::EndMenuBar();

        ImGui::Text("Avg Frame Draw time: \n %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();


        controls->checkUserInputs(window);
        scene->render(camera);


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}