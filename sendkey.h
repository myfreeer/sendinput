#include <windows.h>

static void SetKeyState(const BOOL bState, const WORD keyCode) {
  BYTE keyState[256];
  INPUT input;

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
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = keyCode;
  input.ki.dwFlags = 0;
  SendInput(1, &input, sizeof(input));

  input.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof(input));
}

//function SendDoubleKey: press keyCode1, press keyCode2, release keyCode1, release keyCode2
static void SendDoubleKey(const WORD keyCode1, const WORD keyCode2) {
  INPUT input;
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = keyCode1;
  input.ki.dwFlags = 0;
  SendInput(1, &input, sizeof(input));

  input.ki.wVk = keyCode2;
  SendInput(1, &input, sizeof(input));

  input.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof(input));

  input.ki.wVk = keyCode1;
  SendInput(1, &input, sizeof(input));
}