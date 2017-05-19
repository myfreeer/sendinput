#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.h"
#include "mouse.h"
#include "sendkey.h"
#include "command.h"

#define COMMAND_MAX_LENGTH 32
#define PARAM_MAX_LENGTH 12

static const LPSTR ErrorInfo[] = {
  "no error"
  ,"keyCodeCombine == -1, VkKeyScan fails"
  ,"unknown high-order byte of VkKeyScan's return value"
  ,"cannot get keyCode2"
};

static void EmitError(const unsigned short errorCode) {
  MessageBox(NULL, ErrorInfo[errorCode], NULL, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
}

LPSTR ParseKeyString(const LPSTR keyString) {
  if (lstrlen(keyString) < 1) return 0;
  if (keyString[0] == '$' && keyString[1] == '{') {
    char commandBuffer[COMMAND_MAX_LENGTH];
    char param1Buffer[PARAM_MAX_LENGTH];
    char param2Buffer[PARAM_MAX_LENGTH];
    int param1, param2;
    if (sscanf(keyString, "${%[A-Z0-9]}", commandBuffer) == 1) {
      size_t offset = 3 + strnlen(commandBuffer, COMMAND_MAX_LENGTH);
      if (keyString[offset - 1] == '}') {
        const unsigned long hash = crc32(commandBuffer, offset - 3);
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
    if (sscanf(keyString, "${%[A-Z] %[0-9]}", commandBuffer, param1Buffer) == 2) {
      size_t offset = 4 + strnlen(commandBuffer, COMMAND_MAX_LENGTH) + strnlen(param1Buffer, PARAM_MAX_LENGTH);
      param1 = atoi(param1Buffer);
      if (keyString[offset - 1] == '}') {
        BOOL commandMatched = FALSE;
        switch (crc32(commandBuffer, strnlen(commandBuffer, COMMAND_MAX_LENGTH))) {
        case 4167499804L: //SLEEP
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
    if (sscanf(keyString, "${%[A-Z]+%[0-9A-Za-z]}", commandBuffer, param1Buffer) == 2) {
      size_t offset = 4 + strnlen(commandBuffer, COMMAND_MAX_LENGTH) + strnlen(param1Buffer, PARAM_MAX_LENGTH);
      if (keyString[offset - 1] == '}') {
        const WORD commandLength = strnlen(commandBuffer, COMMAND_MAX_LENGTH);
        const WORD param1Length = strnlen(param1Buffer, PARAM_MAX_LENGTH);
        const unsigned long hash1 = crc32(commandBuffer, commandLength);
        const unsigned long hash2 = crc32(param1Buffer, param1Length);
        WORD keyCode1 = ParseCommand(hash1);
        WORD keyCode2 = ParseCommand(hash2);
        if (keyCode1 && keyCode2) {
          SendDoubleKey(keyCode1, keyCode2);
          return ParseKeyString(keyString + offset);
        } else {
          if (keyCode1 && param1Length == 1) {
            const SHORT vKeyCode = VkKeyScan(param1Buffer[0]);
            keyCode2 = vKeyCode & 0xFF;
            if (vKeyCode>>8 == 0 || vKeyCode>>8 == 1) {
              SendDoubleKey(keyCode1, keyCode2);
              return ParseKeyString(keyString + offset);
            }
          } else if (keyCode2 && commandLength == 1) {
            const SHORT vKeyCode = VkKeyScan(commandBuffer[0]);
            keyCode1 = vKeyCode & 0xFF;
            if (vKeyCode>>8 == 0 || vKeyCode>>8 == 1) {
              SendDoubleKey(keyCode1, keyCode2);
              return ParseKeyString(keyString + offset);
            }
          }
        }
      }
    }
    if (sscanf(keyString, "${%[A-Z] %[0-9] %[0-9]}", commandBuffer, param1Buffer, param2Buffer) == 3) {
      size_t offset = 5 + strnlen(commandBuffer, COMMAND_MAX_LENGTH) + strnlen(param1Buffer, PARAM_MAX_LENGTH) + strnlen(param2Buffer, PARAM_MAX_LENGTH);
      param1 = atoi(param1Buffer);
      param2 = atoi(param2Buffer);
      if (keyString[offset - 1] == '}') {
        BOOL commandMatched = FALSE;
        switch (crc32(commandBuffer, strnlen(commandBuffer, COMMAND_MAX_LENGTH))) {
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
    if (sscanf(keyString, "${%[A-Z]+%[A-Z]+%[0-9A-Za-z]}", commandBuffer, param1Buffer, param2Buffer) == 3) {
     const WORD paramLength[3] = {
       strnlen(commandBuffer, COMMAND_MAX_LENGTH),
       strnlen(param1Buffer, PARAM_MAX_LENGTH),
       strnlen(param2Buffer, PARAM_MAX_LENGTH)
     };
     size_t offset = 5 + paramLength[0] + paramLength[1] + paramLength[2];
     if (keyString[offset - 1] == '}') {
       const unsigned long hash[3] = {
         crc32(commandBuffer, paramLength[0]),
         crc32(param1Buffer, paramLength[1]),
         crc32(param2Buffer, paramLength[2])
       };

       WORD keyCode[3];
       for (unsigned char i = 0; i < 3; i++) {
         keyCode[i] = ParseCommand(hash[i]);
         if (!keyCode[i] && paramLength[i] == 1) {
           SHORT vKeyCode = -1;
           switch (i) {
           case 0:
             vKeyCode = VkKeyScan(commandBuffer[0]);
             break;
           case 1:
             vKeyCode = VkKeyScan(param1Buffer[0]);
             break;
           case 2:
             vKeyCode = VkKeyScan(param2Buffer[0]);
             break;
           }
           if (vKeyCode != -1)
             if (vKeyCode >> 8 == 0 || vKeyCode >> 8 == 1)
               keyCode[i] = vKeyCode & 0xFF;
         }
         if (keyCode[0] && keyCode[1] && keyCode[2]) {
           SendTripleKey(keyCode[0], keyCode[1], keyCode[2]);
           return ParseKeyString(keyString + offset);
         }
       }
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
    keyCode2 = VK_CONTROL; //ctrl
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
    EmitError(3); //cannot get keyCode2
    SendSingleKey(keyCode);
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