include("D:/C++ Projects/AnitoTracerInVulkan/src/tracy-0.11.1/cmake/CPM.cmake")
CPMAddPackage("NAME;freetype;GITHUB_REPOSITORY;freetype/freetype;GIT_TAG;VER-2-13-2;OPTIONS;FT_DISABLE_HARFBUZZ ON;FT_WITH_HARFBUZZ OFF")
set(freetype_FOUND TRUE)