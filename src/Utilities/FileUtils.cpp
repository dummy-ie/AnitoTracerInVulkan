#include "FileUtils.h"

#include <algorithm>
#include <commdlg.h>

// #if __cplusplus <= 201402L
// #define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
// #include <experimental/filesystem>
// #endif

//#include "LogUtils.h"

std::filesystem::path FileUtils::getAssetsFolderPath()
{
    std::filesystem::path p = getExecutablePath().parent_path().parent_path().append("assets");
    //std::cout << "Assets folder: " << p << '\n';
    return p;
}

std::filesystem::path FileUtils::getExecutablePath()
{
    //return std::filesystem::current_path();
        {
    #ifdef _WIN32
            wchar_t path[MAX_PATH] = { 0 };
            GetModuleFileName(nullptr, path, MAX_PATH);
            return path;
    #else
            char result[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
            return std::string(result, (count > 0) ? count : 0);
    #endif
        }
}

// Prompts the user to open an obj file. Supply a reference to a filePath and fileName string for the result.
bool FileUtils::getFilePath(std::string& filePath, std::string& fileName)
{
    //gdeng03::LogUtils::log("OpenFile");
    wchar_t path[MAX_PATH] = L"";

    OPENFILENAME openFile = OPENFILENAME();
    openFile.lStructSize = sizeof(OPENFILENAME);
    openFile.hwndOwner = nullptr;
    openFile.nMaxFile = MAX_PATH;
    openFile.lpstrFile = path;
    openFile.lpstrFilter = L"OBJ Files\0*.obj\0All Files\0*.*\0";
    openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&openFile)) {
        std::wstring ws(path);
        std::string str(ws.begin(), ws.end());
        std::ranges::replace(str, '\\', '/');
        fileName = std::filesystem::path(str).stem().generic_string();
        filePath = str;
        return true;
    }

    return false;
}