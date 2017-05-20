#include <windows.h>

static void SetKeyState(const BOOL bState, const WORD keyCode) {
  BYTE keyState[256];
  INPUT input;
  ZeroMemory(&input, sizeof(input));

  GetKeyboardState((LPBYTE) &keyState);
  if ((bState && !(keyState[keyCode] & 1)) ||
    (!bState && (keyState[keyCode] & 1))) {
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = keyCode;
    SendInput(1, &input, sizeof(input));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));
  }
}

static void SendSingleKey(const WORD keyCode) {
  INPUT input;
  ZeroMemory(&input, sizeof(input));
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = keyCode;
  input.ki.dwFlags = 0;
  SendInput(1, &input, sizeof(input));

  input.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof(input));
}

static void SendMultipleKey(const WORD keyCode[], const unsigned short count) {
  INPUT input;
  ZeroMemory(&input, sizeof(input));
  input.type = INPUT_KEYBOARD;
  input.ki.dwFlags = 0;
  for (unsigned short i = 0; i<count; i++) {
  	  input.ki.wVk = keyCode[i];
  	  SendInput(1, &input, sizeof(input));
  }
  input.ki.dwFlags = KEYEVENTF_KEYUP;
  for (unsigned short i = count; i-->0;) {
  	  input.ki.wVk = keyCode[i];
  	  SendInput(1, &input, sizeof(input));
  }
}