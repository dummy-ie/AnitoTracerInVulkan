# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-src"
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-build"
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix"
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix/tmp"
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix/src/capstone-populate-stamp"
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix/src"
  "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix/src/capstone-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix/src/capstone-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/profiler/build/_deps/capstone-subbuild/capstone-populate-prefix/src/capstone-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
