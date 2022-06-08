include_directories(${RH_DIFF_INCLUDE})
link_directories(${RH_DIFF_LIB})

add_executable(chunk_test chunk.cpp)
target_link_libraries(chunk_test PRIVATE librhDiff.so)

add_executable(signature_test signature.cpp)
target_link_libraries(signature_test PRIVATE librhDiff.so)

add_executable(delta_test delta.cpp)
target_link_libraries(delta_test PRIVATE librhDiff.so)

add_test(
  NAME chunk_test
  COMMAND $<TARGET_FILE:chunk_test>
  )

add_test(
  NAME signature_test
  COMMAND $<TARGET_FILE:signature_test>
  )

add_test(
  NAME delta_test
  COMMAND $<TARGET_FILE:signature_test>
  )
