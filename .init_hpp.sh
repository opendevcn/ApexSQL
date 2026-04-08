#!/bin/bash
# # shellcheck disable=SC1091
# source share.sh

HPP_FILE_PATH="${1}"
HPP_FILE_NAME="${2}.hpp"
UPPER_HPP_FILE_NAME="${2^^}_HPP"

HPP_FILE_NAME_PATH="${HPP_FILE_PATH}/${HPP_FILE_NAME}"

if [[ -z $HPP_FILE_NAME ]]; then
    error "Failed to get header file name: ${HPP_FILE_NAME}"
    exit 1
fi
infor "Successfully got header file name: ${HPP_FILE_NAME}"

if [[ -z "${HPP_FILE_PATH}" ]]; then
    error "Failed to get header file path: ${HPP_FILE_PATH}"
    exit 1
fi
infor "Successfully got header file path: ${HPP_FILE_PATH}"

# If file exists, directly overwrite content
if ! true > "${HPP_FILE_NAME_PATH}" 2>"log/init_hpp-errlog.txt"; then
    error "Failed to format header file: ${HPP_FILE_NAME_PATH}"
    echo -e "${Y1}Error log: log/init_hpp-errlog.txt${E}"
    exit 1
fi
infor "Successfully formatted header file: ${HPP_FILE_NAME_PATH}"

HPP_INIT_CONTENT=(
    "#pragma once"
    ""
    "#ifndef ${UPPER_HPP_FILE_NAME}"
    "#define ${UPPER_HPP_FILE_NAME}"
    ""
    "namespace XXX {}; /* namespace XXX */"
    ""
    "#endif // ${UPPER_HPP_FILE_NAME}"
)

for line in "${HPP_INIT_CONTENT[@]}"; do
    if [[ -z "${line}" ]]; then
        infor "Adding empty line: ... ..."
    else
        infor "Adding header file content: ${line}"
    fi
    echo -e "${line}" >> "${HPP_FILE_NAME_PATH}"
done
infor "Completed adding header file content: ${HPP_FILE_NAME_PATH}"
