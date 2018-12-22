#ifndef SENDINPUT_H
#define SENDINPUT_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "crc32.h"
#include "command.h"

extern void EmitError(unsigned short);
const LPSTR ErrorInfo[] = {
    "no error",
    "keyCodeCombine == -1, VkKeyScan fails",
    "unknown high-order byte of VkKeyScan's return value",
    "cannot get high-order byte from VkKeyScan"
};
static const unsigned char vkeyCodeCombine[3] = {
    VK_SHIFT,   // shift
    VK_CONTROL, // ctrl
    VK_MENU     // alt
};

void ParseSendKeys(const char *keyString, size_t length) {
  if (length < 1)
    return;
  for (size_t index = 0; index < length;) {
    if (index & 0x200)
      Sleep(1); // workaround: preventing mistype by waiting for a while
    if (keyString[index] == '\r' && keyString[index + 1] == '\n') {
      // skip cr-lf line endings
      ++index;
    }
    if (length > 4 && keyString[index] == '$' && keyString[index + 1] == '{') {
      char param[3][COMMAND_MAX_LENGTH];
      if (sscanf(keyString + index, "${%15[A-Z0-9]}", param[index]) == 1) {
        const size_t offset = 3 + strnlen(param[index], COMMAND_MAX_LENGTH);
        if (keyString[index + offset - 1] == '}') {
          const uint32_t hash = crc32(param[index], offset - 3);
          if (hash == 1005452284) { // DOLLAR
            ParseSendKeys("$", 1);
            index += offset;
            continue;
          } else {
            const WORD keyCode = ParseCommand(hash);
            if (keyCode) {
              SendSingleKey(keyCode);
              index += offset;
              continue;
            }
          }
        }
      }
      if (sscanf(keyString + index, "${%15[A-Z] %9[0-9]}", param[0], param[1]) == 2) {
        const size_t offset = 4 + strnlen(param[0], COMMAND_MAX_LENGTH) +
                              strnlen(param[1], COMMAND_MAX_LENGTH);
        if (keyString[index + offset - 1] == '}') {
          const int paramInt = atoi(param[1]);
          if (ParseCommandWithParams(
              crc32(param[0], strnlen(param[0], COMMAND_MAX_LENGTH)),
              &paramInt, 1)) {

            index += offset;
            continue;
          }
        }
      }
      if (sscanf(keyString + index, "${%15[A-Z]+%15[0-9A-Za-z]}", param[0], param[1]) == 2) {
        WORD paramLength[2];
        for (unsigned char i = 0; i < 2; i++)
          paramLength[i] = (WORD) strnlen(param[i], COMMAND_MAX_LENGTH);
        const size_t offset = 4 + paramLength[0] + paramLength[1];
        if (keyString[index + offset - 1] == '}') {
          if (ParseKeyCombination(param, paramLength, 2)) {

            index += offset;
            continue;
          }
        }
      }
      if (sscanf(keyString + index, "${%15[A-Z] %9[0-9] %9[0-9]}", param[0], param[1],
                 param[2]) == 3) {
        const size_t offset = 5 + strnlen(param[0], COMMAND_MAX_LENGTH) +
                              strnlen(param[1], COMMAND_MAX_LENGTH) +
                              strnlen(param[2], COMMAND_MAX_LENGTH);
        if (keyString[offset + index - 1] == '}') {
          int paramInt[2];
          paramInt[0] = atoi(param[1]);
          paramInt[1] = atoi(param[2]);
          if (ParseCommandWithParams(
              crc32(param[0], strnlen(param[0], COMMAND_MAX_LENGTH)),
              paramInt, 2)) {

            index += offset;
            continue;
          }
        }
      }
      if (sscanf(keyString + index, "${%15[A-Z]+%15[0-9A-Za-z]+%15[0-9A-Za-z]}",
                 param[0], param[1], param[2]) == 3) {
        WORD paramLength[3];
        for (unsigned char i = 0; i < 3; i++) {
          paramLength[i] = (WORD) strnlen(param[i], COMMAND_MAX_LENGTH);
        };
        const size_t offset =
            5 + paramLength[0] + paramLength[1] + paramLength[2];
        if (keyString[offset + index - 1] == '}') {
          if (ParseKeyCombination(param, paramLength, 3)) {

            index += offset;
            continue;
          }
        }
      }
    }

    // const SHORT vKeyCode = VkKeyScanEx(keyString[0],GetKeyboardLayout(0));
    const SHORT vKeyCode = VkKeyScan(keyString[index]);

    WORD keyCode[3] = {0};
    keyCode[0] = (WORD) (vKeyCode & 0xFF);
    const WORD keyCodeCombine = (const WORD) (vKeyCode >> 8);
    if (vKeyCode == -1) {
      EmitError(1); // VkKeyScan fails
      ++index;
      continue;
    }
    if (keyCodeCombine == 0) {
      SendSingleKey(keyCode[0]);
      ++index;
      continue;
    }
    unsigned char keyCount = 0;
    for (unsigned char i = 0; i < 3; i++) {
      if (((keyCodeCombine >> i) & 0x1) == 1) {
        keyCode[keyCount + 1] = keyCode[keyCount];
        keyCode[keyCount] = vkeyCodeCombine[i];
        keyCount++;
      }
    }
    if (keyCount > 0)
      SendMultipleKey(keyCode, (const unsigned short) (keyCount + 1));
    else {
      if (keyCodeCombine > 4)
        EmitError(2); // unknown high-order byte of VkKeyScan's return value
      else
        EmitError(3); // cannot get high-order byte from VkKeyScan
      SendSingleKey(keyCode[0]);
    }
    ++index;
  }
}

#endif //SENDINPUT_H
