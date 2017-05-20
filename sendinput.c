#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.h"
#include "mouse.h"
#include "sendkey.h"
#include "command.h"

#define COMMAND_MAX_LENGTH 16

static const LPSTR ErrorInfo[] = {
  "no error"
  ,"keyCodeCombine == -1, VkKeyScan fails"
  ,"unknown high-order byte of VkKeyScan's return value"
  ,"cannot get keyCode2"
};

static void EmitError(const unsigned short errorCode) {
  MessageBox(NULL, ErrorInfo[errorCode], NULL, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
}

BOOL ParseKeyCombination(const char param[][COMMAND_MAX_LENGTH], const WORD paramLength[], const unsigned char paramCount) {
  WORD keyCode[paramCount];
  unsigned long hash[paramCount];
  for (unsigned char i = 0; i < paramCount; i++) {
    hash[i] = crc32(param[i], paramLength[i]);
    keyCode[i] = ParseCommand(hash[i]);
    if (!keyCode[i] && paramLength[i] == 1) {
      SHORT vKeyCode = VkKeyScan(param[i][0]);
      if (vKeyCode >> 8 == 0 || vKeyCode >> 8 == 1)
        keyCode[i] = vKeyCode & 0xFF;
    }
    if (!keyCode[i])
      return FALSE;
  }
  SendMultipleKey(keyCode, paramCount);
  return TRUE;
}

LPSTR ParseKeyString(const LPSTR keyString) {
  if (lstrlen(keyString) < 1) return 0;
  if (keyString[0] == '$' && keyString[1] == '{') {
    char param[3][COMMAND_MAX_LENGTH];
    if (sscanf(keyString, "${%15[A-Z0-9]}", param[0]) == 1) {
      const size_t offset = 3 + strnlen(param[0], COMMAND_MAX_LENGTH);
      if (keyString[offset - 1] == '}') {
        const unsigned long hash = crc32(param[0], offset - 3);
        if (hash == 1005452284L) { //DOLLAR
          ParseKeyString("$");
          return ParseKeyString(keyString + offset);
        } else {
          const WORD keyCode = ParseCommand(hash);
          if (keyCode) {
            SendSingleKey(keyCode);
            return ParseKeyString(keyString + offset);
          }
        }
      }
    }
    if (sscanf(keyString, "${%15[A-Z] %10[0-9]}", param[0], param[1]) == 2) {
      const size_t offset = 4 + strnlen(param[0], COMMAND_MAX_LENGTH) + strnlen(param[1], COMMAND_MAX_LENGTH);
      const int param1 = atoi(param[1]);
      if (keyString[offset - 1] == '}') {
        BOOL commandMatched = FALSE;
        switch (crc32(param[0], strnlen(param[0], COMMAND_MAX_LENGTH))) {
        case 4167499804L: //SLEEP
        case 1266380369L: //WAIT
          Sleep(param1);
          commandMatched = TRUE;
          break;
        case 2439287330L: //CAPS
        case 3274666208L: //CAPSLOCK
          SetKeyState((BOOL) param1, VK_CAPITAL);
          commandMatched = TRUE;
          break;
        case 1256517092L: //NUM
        case 3844504896L: //NUMLOCK
          SetKeyState((BOOL) param1, VK_NUMLOCK);
          commandMatched = TRUE;
          break;
        case 2251377965L: //SCROLLLOCK
          SetKeyState((BOOL) param1, VK_SCROLL);
          commandMatched = TRUE;
          break;
        }
        if (commandMatched)
          return ParseKeyString(keyString + offset);
      }
    }
    if (sscanf(keyString, "${%15[A-Z]+%15[0-9A-Za-z]}", param[0], param[1]) == 2) {
      WORD paramLength[2];
      for (unsigned char i = 0; i < 2; i++)
        paramLength[i] = strnlen(param[i], COMMAND_MAX_LENGTH);
      const size_t offset = 4 + paramLength[0] + paramLength[1];
      if (keyString[offset - 1] == '}') {
        if (ParseKeyCombination(param, paramLength, 2))
          return ParseKeyString(keyString + offset);
      }
    }
    if (sscanf(keyString, "${%15[A-Z] %10[0-9] %10[0-9]}", param[0], param[1], param[2]) == 3) {
      const size_t offset = 5 + strnlen(param[0], COMMAND_MAX_LENGTH) + strnlen(param[1], COMMAND_MAX_LENGTH) + strnlen(param[2], COMMAND_MAX_LENGTH);
      const int param1 = atoi(param[1]);
      const int param2 = atoi(param[2]);
      if (keyString[offset - 1] == '}') {
        BOOL commandMatched = FALSE;
        switch (crc32(param[0], strnlen(param[0], COMMAND_MAX_LENGTH))) {
        case 1302462608L: //CLICK
        case 1121492025L: //LCLICK
        case 2224477467L: //LEFTCLICK
          MouseClick(param1, param2, 0);
          commandMatched = TRUE;
          break;
        case 2063925202L: //RCLICK
        case 1685702361L: //RIGHTCLICK
          MouseClick(param1, param2, 1);
          commandMatched = TRUE;
          break;
        case 2307149724L: //MCLICK
        case 1843602477L: //MIDDLECLICK
          MouseClick(param1, param2, 2);
          commandMatched = TRUE;
          break;
        case 2858569247L: //MOUSEMOVE
          SetCursorPos(param1, param2);
          commandMatched = TRUE;
          break;
        }
        if (commandMatched)
          return ParseKeyString(keyString + offset);
      }
    }
    if (sscanf(keyString, "${%15[A-Z]+%15[0-9A-Za-z]+%15[0-9A-Za-z]}", param[0], param[1], param[2]) == 3) {
      WORD paramLength[3];
      for (unsigned char i = 0; i < 3; i++) {
        paramLength[i] = strnlen(param[i], COMMAND_MAX_LENGTH);
      };
      const size_t offset = 5 + paramLength[0] + paramLength[1] + paramLength[2];
      if (keyString[offset - 1] == '}') {
        if (ParseKeyCombination(param, paramLength, 3))
          return ParseKeyString(keyString + offset);
      }
    }
  }

  const SHORT vKeyCode = VkKeyScan(keyString[0]);
  WORD keyCode[2];
  keyCode[1] = vKeyCode & 0xFF;
  const WORD keyCodeCombine = vKeyCode >> 8;
  if (keyCodeCombine == -1 || keyCode[1] == -1) {
    EmitError(1); //VkKeyScan fails
    return ParseKeyString(keyString + 1);
  }
  if (keyCodeCombine == 0) {
    SendSingleKey(keyCode[1]);
    return ParseKeyString(keyString + 1);
  }
  BOOL keyCode2Initialized = FALSE;
  switch (keyCodeCombine) {
  case 1:
    keyCode[0] = VK_SHIFT; //shift
    keyCode2Initialized = TRUE;
    break;
  case 2:
    keyCode[0] = VK_CONTROL; //ctrl
    keyCode2Initialized = TRUE;
    break;
  case 4:
    keyCode[0] = VK_MENU; //alt
    keyCode2Initialized = TRUE;
    break;
  default:
    EmitError(2); //unknown high-order byte of VkKeyScan's return value
    SendSingleKey(keyCode[1]); //just send keycode
    return ParseKeyString(keyString + 1);
  }
  if (keyCode2Initialized)
    SendMultipleKey(keyCode, 2);
  else {
    EmitError(3); //cannot get keyCode[0]
    SendSingleKey(keyCode[1]);
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