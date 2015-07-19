aux_source_directory(. BIN_SRC)

add_executable(3d-fractals ${BIN_SRC})
target_link_libraries(3d-fractals ${ALL_LIBS} srclib)
