#import <Foundation/Foundation.h>
#import "imgui.h"
#import "backends/imgui_impl_opengl3.h"
#import <opengl/engine.h>

void OpenGLCallback() {
    
}

int main(int argc, const char * argv[]) {
    
    Mi::Core::CreateContext(1000, 1000);
    Mi::Core::RunContext(OpenGLCallback);
    return 0;
}