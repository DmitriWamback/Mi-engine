use std::os::raw::c_char;
use std::fs::File;
use std::ffi::{CStr};

/* LOADING VERTICES */
// VERTICES
#[no_mangle]
pub extern "C" fn load_model_vertices(file_path: *const c_char) -> *mut f32 {

    let mut vertices = vec![0.0];

    let c_str: &CStr = unsafe { CStr::from_ptr(file_path) };
    let slice: &str = c_str.to_str().unwrap();
    let filename: String = slice.to_owned();

    let mut vertex_file = File::open(filename)
        .expect("Couldn't open file");

    println!("")

    let mut test = vec![1.0, 1.0, 2.0, 4.0];
    let test_ptr = test.as_mut_ptr();

    std::mem::forget(test);
    return test_ptr;
}

/*
// NORMALS
#[no_mangle]
pub extern "C" fn load_model_normals(file_path: *const c_char) -> *mut f32 {
    
}

// UVs
#[no_mangle]
pub extern "C" fn load_model_uvs(file_path: *const c_char) -> *mut f32 {
    
}

/* LOADING INDICES */
// VERTEX INDICES
#[no_mangle]
pub extern "C" fn load_model_vertex_indices(file_path: *const c_char) -> *mut i64 {

}

// NORMAL INDICES
#[no_mangle]
pub extern "C" fn load_model_normal_indices(file_path: *const c_char) -> *mut i64 {

}

// UV INDICES
#[no_mangle]
pub extern "C" fn load_model_uv_indices(file_path: *const c_char) -> *mut i64 {

}
*/