 
#include "pch.h"
#include "core.h"
#include "window.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

// kekw / como estas?
const bool LOG_ERROR_ONLY = true;

void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{

    if (LOG_ERROR_ONLY)
    {
        if (type == GL_DEBUG_TYPE_ERROR)
            std::cout << "[GL ERROR]: " << "source: " << source << " severity: " << severity << " message: " << message << std::endl;

        else
            return;
    }

    const char *typetext = type == GL_DEBUG_TYPE_ERROR ? "[GL ERROR] " : "[GL Debug Message]";
    std::cout << typetext << "source: " << source << " severity: " << severity << " message: " << message << std::endl;
    //ConsoleLogLocation(__func__, __FILE__, __LINE__);
}

void OnEvent(Event &event)
{

}

int main()
{

    std::cout << "hello" << std::endl;
    /* WINDOW */
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    const std::string title = "-kNUG";
    Window window(title, WINDOW_WIDTH, WINDOW_HEIGHT);
    window.SetEventCallback(OnEvent);

    /* ImGUi Setup */
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));


    /* GLEW */
    //glew init must be after glfw context is set
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::cout << "glew is NOT OK!" << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugCallback, (const void *)ConsoleLogLocation);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!window.shouldClose())
    {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* put your shit here inbetween */

        ImGui::Begin("Test ImGui Window");
        ImGui::Text("First line");
        ImGui::Separator();
        ImGui::Text("Second line");
        ImGui::End();
        
        /* END */

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.OnUpdate();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}