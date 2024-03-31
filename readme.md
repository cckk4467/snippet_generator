# Introduction
Read all cpp files in the archive, and generate corresponding VsCode snippet "cpp.json".

# Structure
script_src: include script source files.
archive: include cpp files that will be snippetized.

# Usage
## Step 1
Create a new cpp file within the target directory (archive is default). And you can create any subdirectory in the archive directory and put your files there.
## Step 2
Run the script
```
./script --root_path ./archive --output_file_name cpp.json --target_extension .cpp
```
--root_path: indicate the target cpp directory(default ./archive)
--output_file_name: as its name(default cpp.json)
--target_extension: target file extension(default .cpp)
## Step 3
Copy the cpp.json file to vscode user snippets directory.
1. You can just open vscode and copy to *Manange -> User snippets -> cpp.json*
2. Normally, location: `C:\Users\%USERNAME%\AppData\Roaming\Code\User\snippets`

And done!

# How to compile
Modify the snippets files,
and simplely:
```bash
cd $(this_directory)
make 
# or 
make run # with default arguments
```