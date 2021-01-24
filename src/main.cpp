/**
 * main.cpp Entry point into application
 * @author Nathan McCulloch
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <Shader.hpp>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"
#include "Controls.hpp"
#include "Scene.hpp"
#include "Cube.hpp"
#include "ObjLoader.hpp"
#include "Group.hpp"
#include "CubeMap.hpp"
#include "Line.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadCubeMap(std::vector<std::string> faces);

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
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
    Shader* cubeMapShader = new Shader("src/shaders/cubeMapVertex.shader", "src/shaders/cubeMapFragment.shader");
    Shader* lineShader = new Shader("src/shaders/lineVertex.shader", "src/shaders/lineFragment.shader");

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    ObjLoader* objLoader = new ObjLoader();
    Group* monkey = new Group();
    bool res = objLoader->loadOBJMTL("src/models/monkey.obj", monkey);
    monkey->init();
    std::cout << "Loaded Model" << std::endl;

    Scene* scene = new Scene();
    monkey->setScaleMatrix(0.001f);
    scene->addObject(monkey);
    std::cout << "Created Scene" << std::endl;
    
    
    Camera* camera = new Camera();
    camera->setCameraPosition(glm::vec3(0, 0, -10));
    camera->setCameraTarget(glm::vec3(0, 0, 0));
    Controls* controls = new Controls(camera);
    controls->setCameraMovementSpeed(30);
    std::cout << "Created Camera" << std::endl;

    std::vector<std::string> faces {
        "src/textures/cubeMap/right.jpg",
        "src/textures/cubeMap/left.jpg",
        "src/textures/cubeMap/top.jpg",
        "src/textures/cubeMap/bottom.jpg",
        "src/textures/cubeMap/front.jpg",
        "src/textures/cubeMap/back.jpg",
    };


    CubeMap* cubemap = new CubeMap(faces, cubeMapShader, WINDOW_HEIGHT, WINDOW_WIDTH);
    Line* x = new Line(glm::vec3(-1000.0, 0.0, 0.0), glm::vec3(1000.0, 0.0, 0.0), lineShader);
    x->setColour(glm::vec3(1.0, 0.0, 0.0));
    Line* y = new Line(glm::vec3(0.0, -1000.0, 0.0), glm::vec3(0.0, 1000.0, 0.0), lineShader);
    y->setColour(glm::vec3(0.0, 1.0, 0.0));
    Line* z = new Line(glm::vec3(0.0, 0.0, -1000.0), glm::vec3(0.0, 0.0, 1000.0), lineShader);
    z->setColour(glm::vec3(0.0, 0.0, 1.0));

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

        ImGui::Text("Frame Draw time(avg): \n %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();


        controls->checkUserInputs(window);
        scene->render(camera);
        cubemap->render(camera);
        x->render(camera);
        y->render(camera);
        z->render(camera);


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


unsigned int loadCubeMap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char * data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "ERROR::FAILED_TO_LOAD_CUBEMAP_TEXTURE" << faces[i] << "\n" << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}