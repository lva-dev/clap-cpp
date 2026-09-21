function(clap_add_single_file_example TARGET SOURCE)
    add_executable("${TARGET}" "${SOURCE}")
    target_link_libraries("${TARGET}" PRIVATE clap)
endfunction()

clap_add_single_file_example(abcd Abcd.cpp)
