#include "FileUtils.h"

#include <algorithm>

#if __cplusplus <= 201402L
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

//#include "LogUtils.h"

bool FileUtils::getFilePath(std::string& meshFilePath, std::string& fileName)
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
        fileName = std::experimental::filesystem::path(str).stem().generic_string();
        meshFilePath = str;
        return true;
    }

    return false;
}
