// +++ ATTENTION! +++
// This is just a snippet to show how to get the path for a certain DLL on the Windows-platform.
// First absed on the "current working directory", then the environment variable "PATH", then via WinAPI-call.
// Of course, this does not work for any other OS. Nor is this epxected to survive any Windows-makeover (or patch set :X)
// +++ ATTENTION! +++


#if defined(Q_OS_WIN) || defined(Q_OS_CYGWIN)
// for the plugin-path
#include <windows.h>
#include <libloaderapi.h>
#endif

bool
properSdkPath(QString const path)
{
#if defined(Q_OS_WIN) || defined(Q_OS_CYGWIN)
    // Check for the existance of a very, very, very important DLL.
    return QFileInfo(path + "/SDK.dll").exists();
#endif
#ifdef Q_OS_MAC
    // macOS has SDK-support, so using the current application-path is sufficient
    return true;
#endif
}

// Return the path to the hardware-plugins.
// First check is based on the current working directory.
// If this fails, check the contents of the environment-variable 'PATH' (set at install time).
// If this fails, then check via Win-API.
QString
getPluginPath()
{
    QString pathToSDK;

    // Try first the current working directory
    pathToSDK = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN) || defined(Q_OS_CYGWIN)
    // If this failed (has no SDK.dll), indagnate the PATH environment variable.
    // Which is set during installation.
    if(!properSdkPath(pathToSDK))
    {
        // Get the directory from the PATH (is set during APPLICATION SDK installation).
        auto const path = QString::fromLocal8Bit(qgetenv("PATH"));
        auto const splitPath = path.split(";", QString::SkipEmptyParts);

        for(auto const& item : splitPath)
        {
            if(item.contains("APPLICATION SDK"))
            {
                pathToSDK = QFileInfo(item).absoluteFilePath();
                break;
            }
        }

        // If even this failed, then fall back to GetModuleFileName (happens with VS-testrunner).
        if(!properSdkPath(pathToSDK))
        {
            // get the handle of the DLL
            HMODULE handleModule = GetModuleHandleA("SDK.dll");
            LPWSTR modulePath = nullptr;
            DWORD bufLen = 4096;

            // reserve enough memory
            if(!(modulePath = (TCHAR*)malloc(sizeof(TCHAR) * (size_t)bufLen)))
            {
                TRACE_INFO("Could not allocate 4 KB memory. Please consider an hardware upgrade.")
            }

            // retrieve the path
            DWORD pathSize = 4096;
            pathSize = GetModuleFileName(handleModule, modulePath, pathSize);

            if(pathSize)
            {
                QString outputPath = QString::fromWCharArray(modulePath, static_cast<int>(pathSize));
                pathToSDK = outputPath.replace("SDK.dll", "");
            }
            else
            {
                TRACE_INFO("GetModuleFileName failed:" << GetLastError());
            }
        }
    }
#endif

    if(!properSdkPath(pathToSDK))
    {
        TRACE_INFO("Could not determine proper plugin-path.");
        pathToSDK.clear(); // reset
    }

    // convert to proper separators and append the suffix for the plugin-location
    QString const hardwarePluginPath = QFileInfo(pathToSDK).filePath() + "/Plugins";

    return hardwarePluginPath;
}
