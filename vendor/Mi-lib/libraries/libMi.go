package main

import (
	"C"
	"fmt"
	"unsafe"
	"./utilities"
	"strings"
	"io/ioutil"
)

/*
____________________________________________
MITI LIBRARY

MITI (Mi transfer interface)
MITI is used to transfer data from one project to another to
visualize it in a seperate branch of Mi (MITI). The data can 
either be 2 dimensional data (graphs) or 3 dimensional data 
(3D visualization). MITI is built seperately from the core of
Mi, it uses OpenGL and can be found in the src/mit/ directory 
in: https://github.com/DmitriWamback/Mi-engine
*/

//export MitiFindDType
func MitiFindDType(data *C.char) {
	str := C.GoString(data)
	dtype := utilities.ExtractDType(str)
	fmt.Println(dtype)
}

//export MitiParse
func MitiParse(data *C.char, size *C.int) *C.float {

 	arrLen := 100
	a := make([]C.float, arrLen)

	vertices := C.malloc(C.size_t(len(a)) * C.size_t(unsafe.Sizeof(uintptr(0))))
	item := (*[1000000]C.float)(vertices) // 1000000 max inputs 

	for i := 0; i < arrLen; i++ {
		item[i] = C.float(i*i)
	}

	presize := C.int(190)
	size = &presize

	return (*C.float)(vertices)
}

/*
____________________________________________
GLSL SI

GLSL SI (GLSL Shader Importer)
GSI is a custom-built importer for glsl shaders to
facilitate and customize shaders. GSI makes it
easier to organize shader code by splitting the code
into several unique folders and files. These files 
must explicitly be in the src/res/shaders/lib folder.

An example would be:
#version VERSION
#INCLUDE "file.glsl"
*/

func ReadShader(shaderImport *C.char) string {
	str := C.GoString(shaderImport)

	content, err := ioutil.ReadFile(str)
	if err == nil {
		return string(content)
	}

	fmt.Println(err)
	return ""
}

func ReplaceLine(reference string, toreplace string, replacement string) string {

	return strings.Replace(reference, toreplace, replacement, 1)
}

//export GLSLImport
func GLSLImport(shaderSource *C.char, shaderPath *C.char) *C.char {

	path := strings.Split(C.GoString(shaderPath), "/")
	cpath := ""

	for i := 0; i < len(path)-1; i++ {
		cpath += path[i]+"/"
	}
	
	fullSource := C.GoString(shaderSource)
	for i := 0; i < 10; i++ {
		str := strings.Split(fullSource, "\n")

		for i := 0; i < len(str); i++ {
			if strings.HasPrefix(str[i], "#INCLUDE \"") {
				file := strings.Split(strings.Split(str[i], "#INCLUDE \"")[1], "\"")[0]
				source := ReadShader(C.CString(cpath+file))

				fullSource = ReplaceLine(fullSource, str[i], source)
			}
		}
	}

	return C.CString(fullSource)
}


/*
____________________________________________
.OBJ LOADER
*/

// TEST
//export Pointer
func Pointer(a *C.int) {
	b := (C.int)(40)
	a = &b
}

func main() {}