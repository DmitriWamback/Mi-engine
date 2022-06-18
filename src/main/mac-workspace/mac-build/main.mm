//
//  main.m
//  mac-build
//
//  Created by NewTest on 2022-06-18.
//

#import <Foundation/Foundation.h>
#import "imgui.h"

#define MI_ENGINE_OPENGL_BUILD

#if defined(MI_ENGINE_OPENGL_BUILD)
    // needs to link to Mi-Registry
    //#import <mi-core/engine.h>
#endif

#define LOGOUT(s) NSLog(s)

int main(int argc, const char * argv[]) {
    
    IMGUI_CHECKVERSION();
}
