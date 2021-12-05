# Mi-engine 
<p>A custom made game engine built from OpenGL</p>
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
    <span class="pl-s1">python3 src/MiCore/extern/py/load_lib.py</span>
    <span class="pl-s1">sh src/begin_temp.sh # MACOS</span>
    <span class="pl-s1">src\begin_temp.bat # WINDOWS</span>
</pre>

### IMPORTANT!

<p>After running the 'src/MiCore/extern/py/load_lib.py' script, move the libmi_[...].lib or dylib (found in [...]/target/release) into src/MiLibs</p>

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
</ul>

## CURRENT OVERLOOK
<img width="1804" alt="Screen Shot 2021-12-04 at 2 47 59 PM" src="https://user-images.githubusercontent.com/56200546/144722708-2edf065d-5a96-4224-9cb0-281d74b83b9c.png">
