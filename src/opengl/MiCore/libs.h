/* Including required libraries */
/* C++ built-in libraries */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <thread>

/* 3rd Party libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Custom libraries */
#include "extern.h"

#define DEBUG_LIBRARIES

#ifdef DEBUG_LIBRARIES
    #ifdef __APPLE__
        #include "libutil/osx_dylib.h"
    #else
        #include "libutil/csharp_dll.h"
    #endif
#endif