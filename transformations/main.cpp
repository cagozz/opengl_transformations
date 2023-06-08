#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <cmath>
#include "vector.h"
#include "parser.h"
#include "matrix.h"
#include "scene.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall())



static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[Error] : " << error << std::endl;
        return false;
    }
    return true;
}

float x = 0, y = 0, z = 0;
float a = 0, b = 0, c = 0;
float c_a = 0, c_b = 0, c_c = 0;
float s = 1;
bool R = false;
bool up = false;

void input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {                                       
        x = 0.02;
    }
    else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {                                       
        x = -0.02;
    }
    else if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {                                      
        y = 0.02;
    }                                      
    else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        y = -0.02;
    }
    else if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        z = 0.02;
    }
    else if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        z = -0.02;
    }
    else if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        b = 0.02;
    }
    else if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        b = -0.02;
    }
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        a = 0.02;
    }
    else if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        a = -0.02;
    }
    else if (key == GLFW_KEY_Z && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c = 0.02;
    }
    else if (key == GLFW_KEY_X && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c = -0.02;
    }
    else if (key == GLFW_KEY_I && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c_b = 0.002;
    }
    else if (key == GLFW_KEY_K && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c_b = -0.02;
    }
    else if (key == GLFW_KEY_L && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c_a = 0.02;
    }
    else if (key == GLFW_KEY_J && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c_a = -0.002;
    }
    else if (key == GLFW_KEY_U && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c_c = 0.02;
    }
    else if (key == GLFW_KEY_O && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        c_c = -0.02;
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        R = true;
    }
    else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
        up = true;
    }
    else if (key == GLFW_KEY_C && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        s = 1.02;
    }
    else if (key == GLFW_KEY_V && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        s = 0.98;
    }
    else
    {
        x = 0; y = 0; z = 0;
        a = 0; b = 0; c = 0;
        c_a = 0, c_b = 0, c_c = 0;
        s = 1;
        R = false;
        up = false;
    }
}

int main()
{
    GLFWwindow* window;
    int width = 1000, height = 1000;

    if (!glfwInit())
        return -1;

    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Viewer", NULL, NULL);
    glfwSetKeyCallback(window, input);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        printf("Error\n");

    std::cout << glGetString(GL_VERSION);

    /*float near = 0.1;
    float far = 100;

    float aspectRatio = (float)width / height;
    float angle = 45;
    float scale = tan(angle * 0.5 * 3.141592 / 180) * near;
    float r = aspectRatio * scale, l = -r;
    float t = scale, bttm = -t;

    Shader demo = shaderParser("demo.vert", "demo.frag");

    Mesh obj;
    parser("input.off", obj);
    obj.setPerspective(near, far, r, l, t, bttm);
    obj.setShader(demo.vertex.c_str(), demo.fragment.c_str());
    obj.create();*/

    Scene scene(width, height, window);
    scene.setShader("demo.vert", "demo.frag");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    glClearColor(0.35, 0.35, 0.35, 1);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    

    float translation[] = { a, b, c };
    //bool c = true;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*glfwGetWindowSize(window, &width, &height);
        aspectRatio = (float)width / height;
        r = aspectRatio * scale, l = -r;
        obj.setPerspective(near, far, r, l, t, bttm);*/

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        //scene.getCamera().move(c_a, c_b, c_c);
        scene.draw();

        /*ImGui::Begin("Controller");

        if (ImGui::Button("Reset"))
        {
            obj.reset(true);
            translation[0] = 0, translation[1] = 0, translation[2] = 0;
        }

        ImGui::SliderFloat3("Translation", translation, -5, 5);

      
        ImGui::End();*/

        //glViewport(0, 0, width, height);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}