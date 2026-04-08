#!/bin/bash
# shellcheck disable=SC1091
source share.sh

FILE_PATH="${1}"
FILE_NAME="${2}"

HPP_FILE_PATH="src/.include" # Default header file path
if [[ ! -z $FILE_PATH ]]; then
    HPP_FILE_PATH="src/.include/${FILE_PATH}" # Target file path
fi

SRC="src" # Source code directory
INCLUDE="src/.include" # Header file directory
SRC_FILE_PATH="${SRC}" # Default source file path
if [[ ! -z $FILE_PATH ]]; then
    SRC_FILE_PATH="${SRC}/${FILE_PATH}" # Target source file path
fi

encoding_environment_inspect

if ! platform_inspect; then
    if ! permission_inspect; then
        exit 1
    fi
fi

if [[ ! -d $SRC ]]; then
    error "Source code directory does not exist: ${SRC}"
    exit 1
fi
infor "Source code directory exists: ${SRC}"

if [[ ! -d $INCLUDE ]]; then
    error "Header file directory does not exist: ${INCLUDE}"
    exit 1
fi
infor "Header file directory exists: ${INCLUDE}"

if [[ ! -d $HPP_FILE_PATH ]]; then
    error "Target header file path does not exist: ${HPP_FILE_PATH}"
    exit 1
fi
infor "Target header file path exists: ${HPP_FILE_PATH}"

# Check and create source file directory
if [[ ! -d $SRC_FILE_PATH ]]; then
    error "Target source file path does not exist: ${SRC_FILE_PATH}"
    exit 1
fi
infor "Target source file path exists: ${SRC_FILE_PATH}"

##################################################################################################

# Check if file name is empty
if [[ -z $FILE_NAME ]]; then
    error "File name cannot be empty: ${FILE_NAME}"
    exit 1
fi

# Check if both source and header files exist
if [[ -f "${SRC_FILE_PATH}/${FILE_NAME}.cpp" && -f "${HPP_FILE_PATH}/${FILE_NAME}.hpp" ]]; then
    infor "Source file already exists: ${SRC_FILE_PATH}/${FILE_NAME}.cpp"
    infor "Header file already exists: ${HPP_FILE_PATH}/${FILE_NAME}.hpp"
    exit 1
fi

# Check if source file exists
if [[ -f "${SRC_FILE_PATH}/${FILE_NAME}.cpp" ]]; then
    error "Source file already exists: ${SRC_FILE_PATH}/${FILE_NAME}.cpp"
    exit 1
fi

# Check if header file exists
if [[ -f "${HPP_FILE_PATH}/${FILE_NAME}.hpp" ]]; then
    error "Header file already exists: ${HPP_FILE_PATH}/${FILE_NAME}.hpp"
    exit 1
fi

# Create files
if [[ ! -f "${SRC_FILE_PATH}/${FILE_NAME}.cpp" && ! -f "${HPP_FILE_PATH}/${FILE_NAME}.hpp" ]]; then
    
    # Create cpp file in specified path
    if ! touch "${SRC_FILE_PATH}/${FILE_NAME}.cpp"; then
        error "Failed to create source file: ${SRC_FILE_PATH}/${FILE_NAME}.cpp"
        exit 1
    fi
    infor "Successfully created source file: ${SRC_FILE_PATH}/${FILE_NAME}.cpp"
    
    # Create header file in specified path
    if ! touch "${HPP_FILE_PATH}/${FILE_NAME}.hpp"; then
        error "Failed to create header file: ${HPP_FILE_PATH}/${FILE_NAME}.hpp"
        exit 1
    fi
    infor "Successfully created header file: ${HPP_FILE_PATH}/${FILE_NAME}.hpp"
fi

source .init_hpp.sh "${HPP_FILE_PATH}" "${FILE_NAME}"

