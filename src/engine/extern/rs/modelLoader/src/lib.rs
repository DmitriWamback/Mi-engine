#[warn(unused_imports)]
#[warn(unused_variables)]

use std::ffi::CString;
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn load_model(file_path: *const c_char) -> *mut f32 {
    let mut test = vec![1.0, 1.0, 2.0, 4.0];
    let test_ptr = test.as_mut_ptr();

    std::mem::forget(test);
    return test_ptr;
}