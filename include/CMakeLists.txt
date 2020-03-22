add_library(jit INTERFACE)

target_include_directories(jit INTERFACE .)
target_sources(jit INTERFACE jit.h)

target_compile_features(jit
	INTERFACE
	cxx_std_17
)
