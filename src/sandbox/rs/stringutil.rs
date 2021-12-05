use std::os::raw::c_char;
use std::ffi::{CString};

pub extern "C" fn load_shader_imports() -> *mut *const c_char {
    let test_src = 
    "#version 330 core

    out vec4 fragColor;
    #pragma(include(\"test_lib\"))
    
    void main() {
        fragColor = vec4(1.0);
    }";
    let lines = test_src.split("\n").collect::<Vec<&str>>();

    let mut iter: i32 = 0;
    let include_paths: Vec<&str> = Vec::new();
    loop {
        if iter >= lines.len() as i32 {
            break;
        }
        if lines[iter as usize].contains("#pragma(include(\"") {
            let include_line = lines[iter as usize];
            let file = include_line.split("#pragma(include(\"").collect::<Vec<&str>>()[1].split("\"").collect::<Vec<&str>>()[0];
            include_paths.push(file);
        }
        iter = iter + 1;
    }

    let c = CString::new(include_paths.as_mut_ptr()).unwrap();
    let _c = c.as_ptr() as *mut *const c_char;
    return _c;
}

fn main() {
    println!("{}", load_shader_imports());
}