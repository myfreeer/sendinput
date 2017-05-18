#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void EmitError(const unsigned short errorCode) {
  // 0: no error
  // 1: keyCodeCombine == -1, VkKeyScan fails
  // 2: unknown high-order byte of VkKeyScan's return value
  LPSTR ErrorInfo[4];
  ErrorInfo[0] = "no error";
  ErrorInfo[1] = "keyCodeCombine == -1, VkKeyScan fails";
  ErrorInfo[2] = "unknown high-order byte of VkKeyScan's return value";
  ErrorInfo[3] = "cannot get keyCode2";

  MessageBox(NULL, ErrorInfo[errorCode], NULL, MB_OK | MB_ICONINFORMATION);
}

static UINT MouseClick(const unsigned int x, const unsigned int y, const unsigned char type) {
  SetCursorPos(x, y);
  INPUT input[2];
  input[0].type = input[1].type = INPUT_MOUSE;
  switch (type) {
  case 1:
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    break;
  case 2:
    input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
    input[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
  default:
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
  }
  return SendInput(2, input, sizeof(INPUT));
}

static void SetKeyState(const BOOL bState, const WORD keyCode) {
  BYTE keyState[256];
  INPUT input[2];

  GetKeyboardState((LPBYTE) &keyState);
  if ((bState && !(keyState[keyCode] & 1)) ||
    (!bState && (keyState[keyCode] & 1))) {
    ZeroMemory(input, sizeof(input));
    input[0].type = input[1].type = INPUT_KEYBOARD;
    input[0].ki.wVk = input[1].ki.wVk = keyCode;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    // Simulate a key input
    SendInput(2, input, sizeof(INPUT));
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

LPSTR ParseKeyString(const LPSTR keyString) {
  if (lstrlen(keyString) < 1) return 0;
  if (keyString[0] == '$' && keyString[1] == '{') {
    char commandBuffer[32];
    char param1Buffer[11];
    char param2Buffer[11];
    int param1, param2;
    BOOL commandMatched = FALSE;
    if (sscanf(keyString, "${%[A-Z]}", commandBuffer) == 1) {
      size_t offset = 2 + strnlen(commandBuffer, 32) + strnlen(param1Buffer, 11) + 1;
      if (keyString[offset - 1] == '}') {
        if (strcmp(commandBuffer, "DOLLAR") == 0) {
          ParseKeyString("$");
          commandMatched = TRUE;
        }
        
        if (commandMatched)
          return ParseKeyString(keyString + offset);
      }
    }
    if (sscanf(keyString, "${%[A-Z] %[0-9]}", commandBuffer, param1Buffer) == 2) {
      size_t offset = 3 + strnlen(commandBuffer, 32) + strnlen(param1Buffer, 11) + 1;
      param1 = atoi(param1Buffer);
      if (keyString[offset - 1] == '}') {
        if (strcmp(commandBuffer, "SLEEP") == 0) {
          WaitForSingleObject(GetCurrentThread(), param1);
          commandMatched = TRUE;
        } else if (strcmp(commandBuffer, "CAPSLOCK") == 0) {
          SetKeyState((BOOL) param1, VK_CAPITAL);
          commandMatched = TRUE;
        } else if (strcmp(commandBuffer, "NUMLOCK") == 0) {
          SetKeyState((BOOL) param1, VK_NUMLOCK);
          commandMatched = TRUE;
        } else if (strcmp(commandBuffer, "SCROLLLOCK") == 0) {
          SetKeyState((BOOL) param1, VK_SCROLL);
          commandMatched = TRUE;
        }
        if (commandMatched)
          return ParseKeyString(keyString + offset);
      }
    }
    if (sscanf(keyString, "${%[A-Z] %[0-9] %[0-9]}", commandBuffer, param1Buffer, param2Buffer) == 3) {
      size_t offset = 4 + strnlen(commandBuffer, 32) + strnlen(param1Buffer, 11) + strnlen(param2Buffer, 11) + 1;
      param1 = atoi(param1Buffer);
      param2 = atoi(param2Buffer);
      if (keyString[offset - 1] == '}') {
        if (strcmp(commandBuffer, "LEFTCLICK") == 0) {
          MouseClick(param1, param2, 0);
          commandMatched = TRUE;
        } else if (strcmp(commandBuffer, "RIGHTCLICK") == 0) {
          MouseClick(param1, param2, 1);
          commandMatched = TRUE;
        } else if (strcmp(commandBuffer, "MIDDLECLICK") == 0) {
          MouseClick(param1, param2, 2);
          commandMatched = TRUE;
        } else if (strcmp(commandBuffer, "MOUSEMOVE") == 0) {
          SetCursorPos(param1, param2);
          commandMatched = TRUE;
        }
        if (commandMatched)
          return ParseKeyString(keyString + offset);
      }
    }
  }
  const SHORT vKeyCode = VkKeyScan(keyString[0]);
  const WORD keyCode = vKeyCode & 0xFF;
  const WORD keyCodeCombine = vKeyCode >> 8;
  if (keyCodeCombine == -1 || keyCode == -1) {
    EmitError(1); //VkKeyScan fails
    return ParseKeyString(keyString + 1);
  }
  if (keyCodeCombine == 0) {
    SendSingleKey(keyCode);
    return ParseKeyString(keyString + 1);
  }
  WORD keyCode2;
  BOOL keyCode2Initialized = FALSE;
  switch (keyCodeCombine) {
  case 1:
    keyCode2 = VK_SHIFT; //shift
    keyCode2Initialized = TRUE;
    break;
  case 2:
    keyCode2 = VK_CONTROL; //control
    keyCode2Initialized = TRUE;
    break;
  case 4:
    keyCode2 = VK_MENU; //alt
    keyCode2Initialized = TRUE;
    break;
  default:
    EmitError(2); //unknown high-order byte of VkKeyScan's return value
    SendSingleKey(keyCode); //just send keycode
    return ParseKeyString(keyString + 1);
  }
  if (keyCode2Initialized)
    SendDoubleKey(keyCode2, keyCode);
  else {
    SendSingleKey(keyCode);
    EmitError(3); //cannot get keyCode2
  }
  return ParseKeyString(keyString + 1);
}

//main entry
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  const int cmdLineLength = lstrlen(lpCmdLine);
  if (cmdLineLength == 0) {
    return 1;
  }
  ParseKeyString(lpCmdLine);
  return 0;
}