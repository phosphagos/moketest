target_sources(
    moketest

    PRIVATE
    comparator.cpp
    host_profiler.cpp
)

if (MOKE_PLATFORM STREQUAL "cuda")
    target_sources(moketest PRIVATE device_profiler.cu)
endif()
