#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

static void MouseClick(const unsigned int x, const unsigned int y,
                       const unsigned char type) {
  SetCursorPos(x, y);
  INPUT input;
  ZeroMemory(&input, sizeof(input));
  input.type = INPUT_MOUSE;
  switch (type) {
  case 1:
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(input));
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    break;
  case 2:
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
    SendInput(1, &input, sizeof(input));
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
    break;
  default:
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(input));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  }
  SendInput(1, &input, sizeof(input));
}