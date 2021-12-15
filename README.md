# Mi-engine 

<img width="1000" src="https://user-images.githubusercontent.com/56200546/145132401-5d2f7365-68eb-4b51-a9ad-3624cf18ffb6.png">

Mi is an interactive game & graphics engine built from OpenGL for Windows, MacOS and Linux. Currently working on the capability for MacOS and later to be portable for other operating systems.

<p>The stb_image.h file should be added manually to the project</p>
<p>The <code>src/begin_temp.sh</code> shows the necessary libs used to compile and run the engine</p>
<p>Created on the 15th of November 2021, the Mi Engine is still in early development and many things are subject to change</p>

## DEPENDENCIES
<ul>
    <li>g++ (C++ compiler)</li>
    <li>python3 (Python compiler)</li>
    <li>rustc (Rust compiler)</li>
    <li>GLFW 3.0+ (libraries and includes)</li>
    <li>GLEW 3.0+ (libraries and includes)</li>
</ul>

## BUILDING AND COMPILING

<pre>
    <span class="pl-s1">python3 src/MiCore/extern/python_lib/load_lib.py</span>
    <span class="pl-s1">(MAC) sh src/osx_begin.sh</span>
    <span class="pl-s1">(WINDOWS) src\wind_begin.bat</span>
</pre>

### IMPORTANT!

<p>After running the 'src/MiCore/extern/python_lib/load_lib.py' script, move the libmi_[...].lib or dylib (found in [...]/target/release) into src/MiLibs</p>

## AVAILABLE UTILITIES:
<ul>
    <li>Framebuffers</li>
    <li>Textures</li>
    <li>3D Movement, world and rendering</li>
    <li>Physically based rendering (PBR)</li>
    <li>Inheritable Scene class</li>
    <li>Cubemaps</li>
    <li>(GLSL) including external files</li>
    <li>Model loader (OBJ format)</li>
</ul>

## CURRENT "IN DEVELOPMENT" UTILITIES
<ul>
    <li>UI and 2D rendering engine (to be done at a later date)</li>
    <li>Audio</li>
    <li>Instanced rendering</li>
</ul>

## IMPORTING EXTERNAL GLSL FILES
<span>B.glsl, or any other equivalent, must be inside of src/res/shaders/lib</span>
```glsl
    A.glsl

    #version VERSION

    out vec4 fragc;

    // including files
    #pragma(include("B.glsl"))
    vec3 red(); // defining functions to use
    
    void main() {
        fragc = vec4(red(), 1.0);
    }
```

```glsl
    B.glsl
    
    vec3 red() {
        return vec3(1.0, 0.0, 0.0);
    }
```

### COMPLEX IMPORTS
<span>Imports that have several functions</span>

```glsl
    A.glsl

    #version VERSION

    out vec4 fragc;

    // including files
    #pragma(include("B.glsl"))
    vec3 yellow(); // defining functions to use
    
    void main() {
        fragc = vec4(yellow(), 1.0);
    }
```

```glsl
    B.glsl

    vec3 green() {
        return vec3(0.0, 1.0, 0.0);
    }
    
    vec3 red() {
        return vec3(1.0, 0.0, 0.0);
    }

    // The main function where all the calculations are done is always placed at the bottom of the file
    vec3 yellow() {
        return red() + green();
    }
```