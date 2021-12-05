use std::os::raw::c_char;
use std::ffi::{CStr};

#[no_mangle]
pub extern "C" fn import_new_shader(shader_source: *const c_char) -> *const c_char {

    let c_str: &CStr = unsafe { CStr::from_ptr(shader_source) };
    let slice: &str = c_str.to_str().unwrap();
    let shader_src: String = slice.to_owned();

    
}