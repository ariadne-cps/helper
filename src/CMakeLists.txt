set(LIBRARY_NAME HELPER_SRC)

add_library(${LIBRARY_NAME} OBJECT
        stack_trace.cpp
        )

foreach(WARN ${LIBRARY_EXCLUSIVE_WARN})
    target_compile_options(${LIBRARY_NAME} PUBLIC -W${WARN})
endforeach()
