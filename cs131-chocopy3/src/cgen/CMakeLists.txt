add_executable(cgen chocopy_cgen.cpp)
# llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(cgen PUBLIC ir-optimizer-lib parser-lib semantic-lib cjson fmt::fmt)
# target_link_libraries(cgen PUBLIC ${llvm_libs})
target_compile_definitions(cgen PUBLIC _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
target_compile_definitions(cgen PUBLIC PA4=1)
add_dependencies(cgen chocopy_stdlib)

add_executable(chocopy chocopy_cgen.cpp)
target_link_libraries(chocopy PUBLIC ir-optimizer-lib parser-lib semantic-lib cjson fmt::fmt ${llvm_libs})
#target_link_libraries(chocopy PUBLIC ${llvm_libs})
target_compile_definitions(chocopy PUBLIC _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
target_compile_definitions(chocopy PUBLIC ALL=1)
add_dependencies(chocopy chocopy_stdlib)

include_directories(${CMAKE_SOURCE_DIR}/include/cgen)
include_directories(${CMAKE_SOURCE_DIR}/include/ir-optimizer)
include_directories(${CMAKE_SOURCE_DIR}/include/semantic)
include_directories(${CMAKE_SOURCE_DIR}/include/parser)