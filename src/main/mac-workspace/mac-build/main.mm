//
//  main.m
//  mac-build
//
//  Created by NewTest on 2022-06-18.
//

#import <Foundation/Foundation.h>
#import "imgui.h"
#import "imgui_impl_glfw.h"
#import "imgui_impl_opengl3.h"

#import "style.mm"
#define MI_ENGINE_OPENGL_BUILD

#if defined(MI_ENGINE_OPENGL_BUILD)
    // needs to link to Mi-Registry
    #import <mi-core/engine.h>
#endif

#define LOGOUT(s) NSLog(s)

void callback() {
    
    ImGui::NewFrame();
    
    UpdateStyle();
    
    ImGui::Begin("Hello");
    ImGui::Text("This is an ImGui test in Objective-C++");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(int argc, const char * argv[]) {
    
    Mi::Engine::MiCoreBegin(1200, 1000, "Test");
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    ImGui_ImplGlfw_InitForOpenGL(main_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    Mi::Inheritable::Scene* scene = new Mi::Inheritable::Scene("hello");
    
    Mi::Engine::AddScene(scene);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    
    Mi::Engine::StartMainLoop(scene->scene_name, callback);
}
