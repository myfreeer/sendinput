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
  ,"cannot get high-order byte from VkKeyScan"
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

static const unsigned char vkeyCodeCombine[3] = {
	VK_SHIFT, //shift
	VK_CONTROL, //ctrl
	VK_MENU //alt
};

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
    if (sscanf(keyString, "${%15[A-Z] %9[0-9]}", param[0], param[1]) == 2) {
      const size_t offset = 4 + strnlen(param[0], COMMAND_MAX_LENGTH) + strnlen(param[1], COMMAND_MAX_LENGTH);
      if (keyString[offset - 1] == '}') {
        const int paramInt = atoi(param[1]);
        if (ParseCommandWithParams(crc32(param[0], strnlen(param[0], COMMAND_MAX_LENGTH)), &paramInt, 1))
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
    if (sscanf(keyString, "${%15[A-Z] %9[0-9] %9[0-9]}", param[0], param[1], param[2]) == 3) {
      const size_t offset = 5 + strnlen(param[0], COMMAND_MAX_LENGTH) + strnlen(param[1], COMMAND_MAX_LENGTH) + strnlen(param[2], COMMAND_MAX_LENGTH);
      if (keyString[offset - 1] == '}') {
        int paramInt[2];
        paramInt[0] = atoi(param[1]);
        paramInt[1] = atoi(param[2]);
        if (ParseCommandWithParams(crc32(param[0], strnlen(param[0], COMMAND_MAX_LENGTH)), paramInt, 2))
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
  WORD keyCode[3];
  keyCode[0] = vKeyCode & 0xFF;
  const WORD keyCodeCombine = vKeyCode >> 8;
  if (vKeyCode == -1) {
    EmitError(1); //VkKeyScan fails
    return ParseKeyString(keyString + 1);
  }
  if (keyCodeCombine == 0) {
    SendSingleKey(keyCode[0]);
    return ParseKeyString(keyString + 1);
  }
  unsigned char keyCount = 0;
  for (unsigned char i = 0; i < 3; i++) {
    if (((keyCodeCombine >> i) & 0x1) == 1) {
      keyCount++;
      keyCode[i + 1] = keyCode[i];
      keyCode[i] = vkeyCodeCombine[i];
    }
  }
  if (keyCount > 0)
    SendMultipleKey(keyCode, keyCount + 1);
  else {
    if (keyCodeCombine > 4) EmitError(2); //unknown high-order byte of VkKeyScan's return value
    else EmitError(3); //cannot get high-order byte from VkKeyScan
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