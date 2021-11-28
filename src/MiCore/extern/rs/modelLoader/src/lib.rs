use std::os::raw::c_char;
use std::fs;
use std::ffi::{CStr};

/* LOADING VERTICES */
// VERTICES
#[no_mangle]
pub extern "C" fn load_model_vertices(file_path: *const c_char) -> *mut f32 {

    let mut vertices = vec![0.0];

    let c_str: &CStr = unsafe { CStr::from_ptr(file_path) };
    let slice: &str = c_str.to_str().unwrap();
    let filename: String = slice.to_owned();

    let vertex_file = fs::read_to_string(filename)
        .expect("Couldn't open file");

    let comp = vertex_file.split("\n");

    for s in comp {
        if s.starts_with("v ") {
            let verts = s.split(" ").collect::<Vec<&str>>();
            let x: f32 = verts[1].to_owned().parse::<f32>().unwrap();
            let y: f32 = verts[2].to_owned().parse::<f32>().unwrap();
            let z: f32 = verts[3].to_owned().parse::<f32>().unwrap();

            vertices.push(x);
            vertices.push(y);
            vertices.push(z);
        }
    }
    let test_ptr = vertices.as_mut_ptr();

    std::mem::forget(vertices);
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