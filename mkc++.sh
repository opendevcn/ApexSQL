#!/bin/bash
# shellcheck disable=SC1091
# shellcheck disable=SC2206
# shellcheck disable=SC2086


source share.sh

SRC="src" # Source code directory
INCLUDE="src/.include" # Header file directory
LOG="log" # Log directory
BIN="bin" # Executable file directory

BASE_DIR_ARRAY_LIST=(${SRC} ${INCLUDE} ${LOG} ${BIN}) # Base directory array

encoding_environment_inspect

if ! platform_inspect; then
    if ! permission_inspect; then
        exit 1
    fi
fi

# Check if base directories exist
for DIR in "${BASE_DIR_ARRAY_LIST[@]}"; do
    if [[ ! -d $DIR ]]; then
        error "Directory does not exist: ${DIR}"
        exit 1
    fi
    infor "Directory exists: ${DIR}"
done

##################################################################################################

HPP_FILES_ARRAY_LIST=() # C++ header file array
CPP_FILES_ARRAY_LIST=() # C++ source file array
INCLUDE_DIRS_ARRAY_LIST=() # Header file search path array
FILE_BINARY="bin/apexsql"
FILE_LOG="log/apexsql-compile-errlog.txt"

# Collect all header file search paths
if command -v find >/dev/null 2>&1; then
    while IFS= read -r -d '' dir; do
        INCLUDE_DIRS_ARRAY_LIST+=(${dir})
    done < <(find "${INCLUDE}" -type d -print0)
else
    # Compatible with environments without find command
    INCLUDE_DIRS_ARRAY_LIST+=(${INCLUDE})
    for dir in "${INCLUDE}"/*; do
        if [[ -d "${dir}" ]]; then
            INCLUDE_DIRS_ARRAY_LIST+=(${dir})
        fi
    done
fi

# Recursively get all header files from src/.include directory
if command -v find >/dev/null 2>&1; then
    while IFS= read -r -d '' hppf; do
        HPP_FILES_ARRAY_LIST+=(${hppf}) # Add to header file array
    done < <(find "${INCLUDE}" -name "*.hpp" -type f -print0)
else
    # Compatible with environments without find command
    for hppf in "${INCLUDE}"/*.hpp "${INCLUDE}"/*/*.hpp; do
        if [[ -f "${hppf}" ]]; then
            HPP_FILES_ARRAY_LIST+=(${hppf}) # Add to header file array
        fi
    done
fi

# Recursively get all source files from src directory
if command -v find >/dev/null 2>&1; then
    while IFS= read -r -d '' cppf; do
        CPP_FILES_ARRAY_LIST+=(${cppf}) # Add to source file array
    done < <(find "${SRC}" -name "*.cpp" -type f -print0)
else
    # Compatible with environments without find command
    for cppf in "${SRC}"/*.cpp "${SRC}"/*/*.cpp; do
        if [[ -f "${cppf}" ]]; then
            CPP_FILES_ARRAY_LIST+=(${cppf}) # Add to source file array
        fi
    done
fi

##################################################################################################

welcome_message() {
    infor "Welcome to mkc++ script, compiling project 'ApexSQL'"
    infor "Executable file directory: ${BIN}/apexsql"
    infor "Log details directory: ${LOG}/apexsql-compile-errlog.txt"
}

# Print all header files
print_all_hpp_files() {
    if [[ ${#HPP_FILES_ARRAY_LIST[@]} -eq 0 ]]; then
        error "Header file array is empty, no header files found!"
        exit 1
    fi
    
    for hf in "${HPP_FILES_ARRAY_LIST[@]}"; do
        infor "Found header file: ${hf}"
    done
}

# Print all source files
print_all_cpp_files() {
    if [[ ${#CPP_FILES_ARRAY_LIST[@]} -eq 0 ]]; then
        error "Source file array is empty, no source files found!"
        exit 1
    fi
    
    for cf in "${CPP_FILES_ARRAY_LIST[@]}"; do
        infor "Found source file: ${cf}"
    done
}

compile_project_for_platform_windows() {
    local include_params=""
    
    infor "Starting to compile icon resource files, please wait ..."
    if ! windres tmp/apexsql.rc -o tmp/apexsql_resource.o 2>${FILE_LOG}; then
        error "Icon file compilation failed, log details: ${FILE_LOG}"
        exit 1
    fi
    allow "Icon resource file compilation successful!"
    
    for dir in "${INCLUDE_DIRS_ARRAY_LIST[@]}"; do
        include_params+="-I${dir} "
    done
    
    if ! g++ -std=c++20 -static ${include_params} "${CPP_FILES_ARRAY_LIST[@]}" tmp/apexsql_resource.o -o "${FILE_BINARY}" 2> "${FILE_LOG}"; then
        error "Compilation failed, log details: ${FILE_LOG}"
        exit 1
    fi
    allow "Compilation successful, executable file: ${FILE_BINARY}"
    
    if ! rm -f tmp/apexsql_resource.o 2>${FILE_LOG}; then
        error "Failed to clean up compiled icons ..."
    else
        allow "Successfully cleaned up compiled icons ..."
    fi
}

compile_project_for_platform_unix() {
    local include_params=""
    for dir in "${INCLUDE_DIRS_ARRAY_LIST[@]}"; do
        include_params+="-I${dir} "
    done
    
    if ! g++ -std=c++20 -static ${include_params} "${CPP_FILES_ARRAY_LIST[@]}" -o "${FILE_BINARY}" 2> "${FILE_LOG}"; then
        error "Compilation failed, log details: ${FILE_LOG}"
        exit 1
    fi
    allow "Compilation successful, executable file: ${FILE_BINARY}"
}

# Main function
main() {
    welcome_message
    print_all_hpp_files
    print_all_cpp_files
    if [[ $OSTYPE == "msys" || $OS == "Windows_NT" ]]; then
        compile_project_for_platform_windows
    else
        compile_project_for_platform_unix
    fi
}
main