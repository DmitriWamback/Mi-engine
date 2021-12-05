import platform
import sys
import os
import subprocess

OSs = {
    'Darwin': 'macOS',
    'Windows': 'wind',
    'Linux': 'linux'
}
CargoExtensions = {
    'macOS': 'cdylib',
    'wind': 'clib',
    'linux': 'clib'
}
Extensions = {
    'macOS': 'dylib',
    'wind': 'lib',
    'linux': 'lib'
}

current_os = OSs[platform.system()]

default_cargo = """
[package]
name = CARGO_NAME
version = "0.1.0"
author = "Dmitri Wamback"

[lib]
crate-type = CARGO_LIB
path = "src/lib.rs"
"""

def search_dir(_dir: str):

    directories = subprocess.check_output(['ls', _dir]).decode('utf-8').split('\n')
    nb_dir = len(directories) - 1

    dirs = []
    toml_files = []

    for i in range(nb_dir):
        p = f'{_dir}/{directories[i]}'
        if os.path.isdir(p):
            dirs.append(p)
        
        if 'Cargo.toml' in p:
            toml_files.append(p)

    return dirs, toml_files

# Overwriting Rust cargos to include a name and a library 
def overwrite_cargos(_dirs):
    global default_cargo

    tomls = []
    for i in _dirs:
        dirs, toml_paths = search_dir(i)
        for j in toml_paths:
            tomls.append(j)

    for t in tomls:
        with open(t, 'w+') as f:

            name = f"mi_{t.split('/Cargo.toml')[0].split('/')[-1]}"
            cargo = default_cargo.replace('CARGO_NAME', f'"{name}"').replace('CARGO_LIB', f'["{CargoExtensions[current_os]}"]')
            f.write(cargo)

        subprocess.call(['cargo', 'run', '--manifest-path', t, '--release'])

rust_libs = '../rust_lib'
current_path = sys.argv[0]
current_name = os.path.basename(current_path)

current_path = current_path.split(current_name)[0]
rs_path = f'{current_path}{rust_libs}'

dirs, toml_paths = search_dir(rs_path)
overwrite_cargos(dirs)
        
