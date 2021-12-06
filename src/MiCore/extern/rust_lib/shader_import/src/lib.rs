use std::os::raw::{c_char, c_int};
use std::ffi::{CString, CStr};

#[no_mangle]
pub unsafe extern "C" fn load_shader_imports(length: *mut c_int, shader_source: *const c_char) -> *mut *mut c_char {

    let src: String = unsafe { CStr::from_ptr(shader_source) }.to_str().unwrap().to_owned();

    let lines = src.split("\n").collect::<Vec<&str>>();

    let mut iter: i32 = 0;
    let mut include_paths = vec![];
    loop {
        if iter >= lines.len() as i32 {
            break;
        }
        if lines[iter as usize].contains("#pragma(include(\"") {
            let include_line = lines[iter as usize];
            let file = include_line.split("#pragma(include(\"").collect::<Vec<&str>>()[1].split("\"").collect::<Vec<&str>>()[0];
            let file_c_str = CString::new(file).unwrap();
            include_paths.push(file_c_str);
        }
        iter = iter + 1;
    }

    let mut out = include_paths.into_iter().map(|s| s.into_raw()).collect::<Vec<_>>();
    out.shrink_to_fit();

    let len = out.len();
    let ptr = out.as_mut_ptr();
    assert!(out.len() == out.capacity());

    std::mem::forget(out);
    std::ptr::write(length, len as c_int);
    ptr
}