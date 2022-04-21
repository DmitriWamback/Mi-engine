use std::os::raw::{c_char, c_int};
use std::fs;
use std::ffi::{CStr};

#[no_mangle]
pub unsafe extern "C" fn parse_vertex_data(data: *const c_char, vertex_count: *mut c_int) -> *mut f32 {
    
}