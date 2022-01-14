use std::os::raw::{c_char, c_int};
use std::fs;
use std::ffi::{CStr};

/* LOADING VERTICES */
// VERTICES

#[no_mangle]
pub unsafe extern "C" fn load_model_vertices(file_path: *const c_char, vertex_count: *mut c_int, vertex_type: i32) -> *mut f32 {

    let mut vertices = vec![];
    let faces = vec!["v ", "vn ", "vt "];

    let c_str: &CStr = CStr::from_ptr(file_path);
    let slice: &str = c_str.to_str().unwrap();
    let filename: String = slice.to_owned();

    let vertex_file = fs::read_to_string(filename)
        .expect("Couldn't open file");

    let comp = vertex_file.split("\n");

    for s in comp {
        if s.starts_with(faces[vertex_type as usize]) {
            
            let verts = s.split(" ").collect::<Vec<&str>>();
            let x: f32 = verts[1].to_owned().parse::<f32>().unwrap();
            let y: f32 = verts[2].to_owned().parse::<f32>().unwrap();
            if vertex_type != 2 {
                let z: f32 = verts[3].to_owned().parse::<f32>().unwrap();

                vertices.push(x);
                vertices.push(y);
                vertices.push(z);
            }
            else {
                vertices.push(x);
                vertices.push(y);
            }
        }
    }
    let len = vertices.len();
    std::ptr::write(vertex_count, len as c_int);
    let test_ptr = vertices.as_mut_ptr();

    std::mem::forget(vertices);
    return test_ptr;
}

/* LOADING INDICES */


#[no_mangle]
pub unsafe extern "C" fn load_model_indices(file_path: *const c_char, index_count: *mut c_int, index_type: i32) -> *mut u32 {
    let mut indices = vec![];

    let c_str: &CStr = CStr::from_ptr(file_path);
    let slice: &str = c_str.to_str().unwrap();
    let filename: String = slice.to_owned();

    let vertex_file = fs::read_to_string(filename)
        .expect("Couldn't open file");

    let comp = vertex_file.split("\n");

    for s in comp {
        if s.starts_with("f ") {
            
            let verts = s.split("f ").collect::<Vec<&str>>()[1].split(" ").collect::<Vec<&str>>();
            let x: u32 = verts[0].split("/").collect::<Vec<&str>>()[index_type as usize].to_owned().parse::<u32>().unwrap() - 1;
            let y: u32 = verts[1].split("/").collect::<Vec<&str>>()[index_type as usize].to_owned().parse::<u32>().unwrap() - 1;
            let z: u32 = verts[2].split("/").collect::<Vec<&str>>()[index_type as usize].to_owned().parse::<u32>().unwrap() - 1;

            indices.push(x);
            indices.push(y);
            indices.push(z);
        }
    }
    let test_ptr = indices.as_mut_ptr();
    let len = indices.len();

    std::mem::forget(indices);
    std::ptr::write(index_count, len as c_int);
    return test_ptr;
}

