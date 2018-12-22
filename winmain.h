// Small alternative startfile for WinMain()
// Build with gcc perms:
// -nostartfiles -mwindows -lshlwapi
#pragma once
#ifndef STARTFILE_WINMAIN_H
#define STARTFILE_WINMAIN_H
#include <windows.h>
#include <shlwapi.h>

#ifdef UNICODE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine, int nCmdShow);
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
#endif
int __cdecl WinMainCRTStartup() {
  STARTUPINFO startupInfo;
  ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
  GetStartupInfo(&startupInfo);
  DWORD __nShowCmd = SW_SHOWDEFAULT;
  __nShowCmd = startupInfo.dwFlags & STARTF_USESHOWWINDOW
                 ? startupInfo.wShowWindow
                 : SW_SHOWDEFAULT;
  const int exitCode =
#ifdef UNICODE
      wWinMain(GetModuleHandleW(NULL), NULL, PathGetArgsW(GetCommandLineW()), __nShowCmd);
#else
      WinMain(GetModuleHandleA(NULL), NULL, PathGetArgsA(GetCommandLineA()), __nShowCmd);
#endif
  ExitProcess(exitCode);
  return exitCode;
}
#endif
