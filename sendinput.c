#include "sendinput.h"

#ifndef __GNUC__
#define UNUSED
#else // __GNUC__
#define UNUSED __attribute__((unused))
#endif // __GNUC__

void EmitError(const unsigned short errorCode) {
    MessageBox(NULL, ErrorInfo[errorCode], NULL,
               MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
}

// main entry
int WINAPI WinMain(HINSTANCE UNUSED hInstance, HINSTANCE UNUSED hPrevInstance,
                   LPSTR lpCmdLine, int UNUSED nShowCmd) {
    unsigned int cmdLineLength = (unsigned int) lstrlen(lpCmdLine);
    if (cmdLineLength == 0) {
        return 1;
    }
    ParseSendKeys(lpCmdLine, cmdLineLength);
    return 0;
}