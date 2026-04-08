#!/bin/bash
source share.sh

LOG="log/apex-sync-errlog.txt"

GITHUB_LOCAL_REPO="/e/github/ApexSQL"
CURRENT_PROJECT="/e/programdev/ApexSQL"

init() {
    if [[ ! -d "${GITHUB_LOCAL_REPO}" ]]; then
        error "github repo local path: ${GITHUB_LOCAL_REPO} not exists!"
        return 1
    fi
    infor "github repo local path: ${GITHUB_LOCAL_REPO} exists!"
    return 0
}

removeOldRepo() {
    if ! /bin/rm -rf "${GITHUB_LOCAL_REPO}" 2>"${LOG}"; then
        error "remove github old repo local path: ${GITHUB_LOCAL_REPO} failed!"
        return 1
    fi
    infor "remove github old repo local path: ${GITHUB_LOCAL_REPO} success!"
    return 0
}

createNewRepo() {
    if ! /bin/mkdir -p "${GITHUB_LOCAL_REPO}" 2>"${LOG}"; then
        error "create github repo repo local path: ${GITHUB_LOCAL_REPO} failed!"
        return 1
    fi
    infor "create github repo local path: ${GITHUB_LOCAL_REPO} success!"
    return 0
}

copyToRepo() {
    if [[ ! -d "${CURRENT_PROJECT}" ]]; then
        error "current project path: ${CURRENT_PROJECT} not exists!"
        return 1
    fi
    infor "current project path: ${CURRENT_PROJECT} exists!"
    
    if ! /bin/cp -rpf "${CURRENT_PROJECT}"/. "${GITHUB_LOCAL_REPO}" 2>"${LOG}"; then
        error "copy current project to github repo local path: ${GITHUB_LOCAL_REPO} failed!"
        return 1
    fi
    
    infor "copy current project to github repo local path: ${GITHUB_LOCAL_REPO} success!"
    return 0
}

main() {
    init
    removeOldRepo
    createNewRepo
    copyToRepo
}
main