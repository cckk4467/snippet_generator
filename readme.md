# Introduction
Read all cpp files in the archive, and generate corresponding VsCode snippet "cpp.json" for the CodeForces contest.

# Structure
script_src: include script source files
archive: include cpp files that will be snippetized

# Usage
./script --root_path ./archive --output_file_name cpp.json --target_extension .cpp

## parameters
--root_path: indicate the target cpp directory(default ./archive)
--output_file_name: as its name(default cpp.json)
--target_extension: target file extension(default .cpp)

# How to compile
simplely 
```bash
cd $(this_directory)
make 
# or 
make run # if need run the script immediately with default arguments
```