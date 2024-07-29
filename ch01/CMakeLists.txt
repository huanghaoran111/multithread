set(
  Programs
  01helloworld
  
)

foreach( Program ${Programs})
  add_executable(${Program} ${Program}.cpp)
  # target_include_directories(${Program} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endforeach( Program ${Programs})
