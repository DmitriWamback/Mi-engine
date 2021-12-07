# Mi-engine 

<img width="2000" src="https://user-images.githubusercontent.com/56200546/144757621-8c34e502-ad62-4d3e-bb21-10eab52cb0c2.png">

<p>An interactive game & graphics engine built from OpenGL for Windows, MacOS and Linux. Currently working on the capability for MacOS and later to be portable for other operating systems.</p>
<p>The stb_image.h file should be added manually to the project</p>
<p>The <code>src/begin_temp.sh</code> shows the necessary libs used to compile and run the engine</p>

## REQUIREMENTS
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
    <span class="pl-s1">sh src/begin_temp.sh # MACOS</span>
    <span class="pl-s1">src\begin_temp.bat # WINDOWS</span>
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
</ul>

## CURRENT "IN DEVELOPMENT" UTILITIES
<ul>
    <li>Model loader (OBJ format)</li>
    <li>UI and 2D rendering engine (to be done at a later date)</li>
    <li>Audio</li>
    <li>(GLSL) including external files</li>
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

## CURRENT OVERLOOK
<img width="1804" alt="Screen Shot 2021-12-04 at 2 47 59 PM" src="https://user-images.githubusercontent.com/56200546/144722708-2edf065d-5a96-4224-9cb0-281d74b83b9c.png">
