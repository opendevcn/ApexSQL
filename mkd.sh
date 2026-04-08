#!/bin/bash
# shellcheck disable=SC1091
source share.sh

DIR_NAME="${1}"

SRC="src" # Source code directory
INCLUDE="src/.include" # Header file directory

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

##################################################################################################

# Check if directory name is empty
if [[ -z $DIR_NAME ]]; then
    error "Directory name cannot be empty: ${DIR_NAME}"
    exit 1
fi

# Check if directory exists in both src and include directories
if [[ -d "${SRC}/${DIR_NAME}" && -d "${INCLUDE}/${DIR_NAME}" ]]; then
    infor "Directory already exists: ${SRC}/${DIR_NAME}"
    infor "Directory already exists: ${INCLUDE}/${DIR_NAME}"
    exit 1
fi

# Check if directory exists in src directory
if [[ -d "${SRC}/${DIR_NAME}" ]]; then
    error "Directory already exists: ${SRC}/${DIR_NAME}"
    exit 1
fi

# Check if directory exists in include directory
if [[ -d "${INCLUDE}/${DIR_NAME}" ]]; then
    error "Directory already exists: ${INCLUDE}/${DIR_NAME}"
    exit 1
fi

# Create directories
if [[ ! -d "${SRC}/${DIR_NAME}" && ! -d "${INCLUDE}/${DIR_NAME}" ]]; then
    
    # Create directory in src directory
    if ! mkdir "${SRC}/${DIR_NAME}"; then
        error "Failed to create directory: ${SRC}/${DIR_NAME}"
        exit 1
    fi
    infor "Successfully created directory: ${SRC}/${DIR_NAME}"
    
    # Create directory in include directory
    if ! mkdir "${INCLUDE}/${DIR_NAME}"; then
        error "Failed to create directory: ${INCLUDE}/${DIR_NAME}"
        exit 1
    fi
    infor "Successfully created directory: ${INCLUDE}/${DIR_NAME}"
fi
