#!/bin/bash
# shellcheck disable=SC2034


# This is a shared resource script, all "*.sh" files depend on this script, otherwise fatal issues will occur.
readonly E="\033[0m"    # Highlight: Reset

readonly R="\033[0;31m" # Highlight: Red, Font: Normal
readonly G="\033[0;32m" # Highlight: Green, Font: Normal
readonly Y="\033[0;33m" # Highlight: Yellow, Font: Normal
readonly B="\033[0;34m" # Highlight: Blue, Font: Normal
readonly P="\033[0;35m" # Highlight: Purple, Font: Normal
readonly C="\033[0;36m" # Highlight: Cyan, Font: Normal
readonly W="\033[0;37m" # Highlight: White, Font: Normal

readonly R1="\033[1;31m" # Highlight: Red, Font: Bold
readonly G1="\033[1;32m" # Highlight: Green, Font: Bold
readonly Y1="\033[1;33m" # Highlight: Yellow, Font: Bold
readonly B1="\033[1;34m" # Highlight: Blue, Font: Bold
readonly P1="\033[1;35m" # Highlight: Purple, Font: Bold
readonly C1="\033[1;36m" # Highlight: Cyan, Font: Bold
readonly W1="\033[1;37m" # Highlight: White, Font: Bold

# Get current time
ntime() {
    echo -e "${R1}[${Y}$(date '+%Y-%m-%d %H:%M:%S.%3N')${R1}]${E}"
}

# Level: INFOR, Information
# Parameter: ${1}, Information content
infor() {
    echo -e "$(ntime) ${B}INFOR${W}: ${C}${1}${E}"
}

# Level: ERROR, Error
# Parameter: ${1}, Error message content
error() {
    echo -e "$(ntime) ${R}ERROR${W}: ${P}${1}${E}"
}

# Level: ALLOW, Allow
# Parameter: ${1}, Allow message content
allow() {
    echo -e "$(ntime) ${G}ALLOW${W}: ${C}${1}${E}"
}

# Check if current platform is Windows
# Return: 0, if it's Windows platform
# Return: 1, if it's not Unix platform
platform_inspect() {
    if [[ $OSTYPE == "msys" || $OS == "Windows_NT" ]]; then
        echo -e "$(ntime) ${G}ALLOW${W}: ${C}Current platform: ${P}Windows${E}"
        return 0 # Return 0 indicates Windows platform
    fi
    echo -e "$(ntime) ${G}ALLOW${W}: ${C}Current platform: ${P}Unix${E}"
    return 1 # Return 1 indicates Unix platform
}

# Check if current user is root
# Return: 0, if it's root user
# Return: 1, if it's not root user
permission_inspect() {
    if [[ "$(id -u)" -ne 0 ]]; then
        echo -e "$(ntime) ${R}ERROR${W}: ${P}You are not root user, please run this script as root.${P}${W}.${E}"
        return 1 # Return 1 indicates not root user
    fi
    echo -e "$(ntime) ${G}ALLOW${W}: ${C}Current user: ${P}$(whoami)${E}"
    return 0 # Return 0 indicates root user
}

# Check if current character set environment is Chinese 'zh_CN.UTF-8'
# Return: 0, if it's Chinese environment
# Return: 1, if it's not Chinese environment
encoding_environment_inspect() {
    if [[ $LANG != "zh_CN.UTF-8" ]]; then
        echo -e "$(ntime) ${Y}WARNING${W}: ${P}You are not in Chinese environment. Please set your environment to Chinese.${W}.${E}"
        echo -e "$(ntime) ${W}Environment is not 'zh_CN.UTF-8', may cause garbled Chinese characters${E}"
        return 1 # Return 1 indicates not Chinese environment
    fi
    echo -e "$(ntime) ${G}ALLOW${W}: ${C}Current character set environment: ${P}${LANG}${E}"
    return 0 # Return 0 indicates Chinese environment
}