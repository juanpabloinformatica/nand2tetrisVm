#! /usr/bin/bash
# set -x
root_folder=$(git rev-parse --show-toplevel)
function test_chapter_7() {
    mapfile -t chapter7vmfiles < <(find /home/jppm/Documents/courses/nand2tetris/projects/7/ -type f -name "*.vm")
    echo "${chapter7vmfiles[@]}"
    for f in "${chapter7vmfiles[@]}"; do
        echo -e "File:\t${f}\n"
        ./build/vm $f
    done
}
function run_tests() {
    mapfile -t tests < <(find "${root_folder}"/build/test -type f -name "*.cpp.out")
    for test in "${tests[@]}"; do
        (
            echo -e "TEST:\t${test}\n"
            ${test}
        )
    done
}
function run_test() {
    "$(find "${root_folder}"/build/test -type f -name "*.cpp.out" | fzf)"
}

function main() {
    for arg in "$@"; do
        case $arg in
        --c7)
            test_chapter_7
            shift # Remove --log or -l from processing
            ;;
        --rt)
            run_tests
            shift
            ;;
        --t)
            run_test
            shift
            ;;
        *)
            # Unknown option
            ;;
        esac
    done
}
main $@
