#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.h"
#include "mouse.h"
#include "sendkey.h"

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

LPSTR ParseKeyString(const LPSTR keyString);
static BOOL ParseCommand(char* commandBuffer);

static BOOL ParseCommand(char * commandBuffer) {
  const unsigned long length = strnlen(commandBuffer, COMMAND_MAX_LENGTH);
  const unsigned long hash = crc32(commandBuffer, length);
  switch (hash) {
  case 1005452284L: //DOLLAR
    ParseKeyString("$");
    return TRUE;
  case 4213349504L: //BACKSPACE
  case 1911832374L: //BS
  case 2523624168L: //BKSP
    SendSingleKey(VK_BACK);
    return TRUE;
  case 3846439302L: //TAB
    SendSingleKey(VK_TAB);
    return TRUE;
  case 317010870L: //CLEAR
    SendSingleKey(VK_CLEAR);
    return TRUE;
  case 1310982878L: //ENTER
    SendSingleKey(VK_RETURN);
    return TRUE;
  case 1382021621L: //SHIFT
    SendSingleKey(VK_SHIFT);
    return TRUE;
  case 884448462L: //CTRL
    SendSingleKey(VK_CONTROL);
    return TRUE;
  case 3201542913L: //ALT
    SendSingleKey(VK_MENU);
    return TRUE;
  case 550391901L: //PAUSE
    SendSingleKey(VK_PAUSE);
    return TRUE;
  case 2439287330L: //CAPS
  case 3274666208L: //CAPSLOCK
    SendSingleKey(VK_CAPITAL);
    return TRUE;
  case 4149446788L: //ESC
    SendSingleKey(VK_ESCAPE);
    return TRUE;
  case 82448359L: //PAGEUP
  case 859550494L: //PGUP
    SendSingleKey(VK_PRIOR);
    return TRUE;
  case 1528306972L: //PAGEDOWN
  case 2599267693L: //PGDN
    SendSingleKey(VK_NEXT);
    return TRUE;
  case 2522575163L: //END
    SendSingleKey(VK_END);
    return TRUE;
  case 1195630948L: //HOME
    SendSingleKey(VK_HOME);
    return TRUE;
  case 3864525061L: //LEFTARROW
  case 1290930908L: //LEFT
    SendSingleKey(VK_LEFT);
    return TRUE;
  case 156158474L: //UPARROW
  case 3984517658L: //UP
    SendSingleKey(VK_UP);
    return TRUE;
  case 112782023L: //RIGHTARROW
  case 1134475172L: //RIGHT
    SendSingleKey(VK_RIGHT);
    return TRUE;
  case 2947281234L: //DOWNARROW
  case 711622031L: //DOWN
    SendSingleKey(VK_DOWN);
    return TRUE;
  case 3138006342L: //SELECT
    SendSingleKey(VK_SELECT);
    return TRUE;
  case 3800219350L: //PRINT
    SendSingleKey(VK_PRINT);
    return TRUE;
  case 3223776964L: //EXECUTE
    SendSingleKey(VK_EXECUTE);
    return TRUE;
  case 2836567439L: //PRINTSCREEN
  case 2328061742L: //PRTSC
    SendSingleKey(VK_SNAPSHOT);
    return TRUE;
  case 479333784L: //INS
  case 892623219L: //INSERT
    SendSingleKey(VK_INSERT);
    return TRUE;
  case 2058767093L: //DEL
  case 3404380929L: //DELETE
    SendSingleKey(VK_DELETE);
    return TRUE;
  case 1041412376L: //HELP
    SendSingleKey(VK_HELP);
    return TRUE;
  case 1256517092L: //NUM
  case 3844504896L: //NUMLOCK
    SendSingleKey(VK_NUMLOCK);
    return TRUE;
  case 2251377965L: //SCROLLLOCK
    SendSingleKey(VK_SCROLL);
    return TRUE;
  case 4067218798L: //LEFTWINDOWS
  case 699046007L: //LWIN
    SendSingleKey(VK_LWIN);
    return TRUE;
  case 2401157523L: //RIGHTWINDOWS
  case 2574039259L: //RWIN
    SendSingleKey(VK_RWIN);
    return TRUE;
  case 1660628960L: //APPLICATIONS
    SendSingleKey(VK_APPS);
    return TRUE;
  case 1771420896L: //COMPUTERSLEEP
    SendSingleKey(VK_SLEEP);
    return TRUE;
  case 3615866119L: //MULTIPLY
    SendSingleKey(VK_MULTIPLY);
    return TRUE;
  case 1807561069L: //ADD
    SendSingleKey(VK_ADD);
    return TRUE;
  case 3543192423L: //SEPARATOR
    SendSingleKey(VK_SEPARATOR);
    return TRUE;
  case 3882583749L: //SUBTRACT
    SendSingleKey(VK_SUBTRACT);
    return TRUE;
  case 1706577289L: //DECIMAL
    SendSingleKey(VK_DECIMAL);
    return TRUE;
  case 1936067278L: //DIVIDE
    SendSingleKey(VK_DIVIDE);
    return TRUE;
  case 1408638381L: //NUM0
  case 2111931934L: //NUMPAD0
    SendSingleKey(VK_NUMPAD0);
    return TRUE;
  case 619785531L: //NUM1
  case 182892168L: //NUMPAD1
    SendSingleKey(VK_NUMPAD1);
    return TRUE;
  case 3187178625L: //NUM2
  case 2481973042L: //NUMPAD2
    SendSingleKey(VK_NUMPAD2);
    return TRUE;
  case 3405728791L: //NUM3
  case 3840464804L: //NUMPAD3
    SendSingleKey(VK_NUMPAD3);
    return TRUE;
  case 1419499956L: //NUM4
  case 2056012295L: //NUMPAD4
    SendSingleKey(VK_NUMPAD4);
    return TRUE;
  case 597485858L: //NUM5
  case 227242641L: //NUMPAD5
    SendSingleKey(VK_NUMPAD5);
    return TRUE;
  case 3130374296L: //NUM6
  case 2491556651L: //NUMPAD6
    SendSingleKey(VK_NUMPAD6);
    return TRUE;
  case 3448932366L: //NUM7
  case 3817149373L: //NUMPAD7
    SendSingleKey(VK_NUMPAD7);
    return TRUE;
  case 1563268511L: //NUM8
  case 1933184556L: //NUMPAD8
    SendSingleKey(VK_NUMPAD8);
    return TRUE;
  case 707437833L: //NUM9
  case 71122618L: //NUMPAD9
    SendSingleKey(VK_NUMPAD9);
    return TRUE;
  case 3055876678L: //F1
    SendSingleKey(VK_F1);
    return TRUE;
  case 791522300L: //F2
    SendSingleKey(VK_F2);
    return TRUE;
  case 1479187306L: //F3
    SendSingleKey(VK_F3);
    return TRUE;
  case 3327004361L: //F4
    SendSingleKey(VK_F4);
    return TRUE;
  case 2974367327L: //F5
    SendSingleKey(VK_F5);
    return TRUE;
  case 675311589L: //F6
    SendSingleKey(VK_F6);
    return TRUE;
  case 1598513011L: //F7
    SendSingleKey(VK_F7);
    return TRUE;
  case 3489153762L: //F8
    SendSingleKey(VK_F8);
    return TRUE;
  case 3103748724L: //F9
    SendSingleKey(VK_F9);
    return TRUE;
  case 1808932734L: //F10
    SendSingleKey(VK_F10);
    return TRUE;
  case 483733480L: //F11
    SendSingleKey(VK_F11);
    return TRUE;
  case 2245819986L: //F12
    SendSingleKey(VK_F12);
    return TRUE;
  case 4074458820L: //F13
    SendSingleKey(VK_F13);
    return TRUE;
  case 1824512871L: //F14
    SendSingleKey(VK_F14);
    return TRUE;
  case 465103857L: //F15
    SendSingleKey(VK_F15);
    return TRUE;
  case 2192685643L: //F16
    SendSingleKey(VK_F16);
    return TRUE;
  case 4122381021L: //F17
    SendSingleKey(VK_F17);
    return TRUE;
  case 1695127372L: //F18
    SendSingleKey(VK_F18);
    return TRUE;
  case 302950362L: //F19
    SendSingleKey(VK_F19);
    return TRUE;
  case 1090473149L: //F20
    SendSingleKey(VK_F20);
    return TRUE;
  case 939031595L: //F21
    SendSingleKey(VK_F21);
    return TRUE;
  case 2935041425L: //F22
    SendSingleKey(VK_F22);
    return TRUE;
  case 3656785159L: //F23
    SendSingleKey(VK_F23);
    return TRUE;
  case 1200785572L: //F24
    SendSingleKey(VK_F24);
    return TRUE;
  case 2607492222L: //LEFTSHIFT
  case 1562731868L: //LSHIFT
    SendSingleKey(VK_LSHIFT);
    return TRUE;
  case 2072264636L: //RIGHTSHIFT
  case 1694041783L: //RSHIFT
    SendSingleKey(VK_RSHIFT);
    return TRUE;
  case 4233133246L: //LEFTCONTROL
  case 1322385799L: //LCTRL
    SendSingleKey(VK_LCONTROL);
    return TRUE;
  case 2166515779L: //RIGHTCONTROL
  case 2432837732L: //RCTRL
    SendSingleKey(VK_RCONTROL);
    return TRUE;
  case 1936054868L: //LEFTMENU
  case 838158958L: //LMENU
  case 2970897034L: //LALT
    SendSingleKey(VK_LMENU);
    return TRUE;
  case 1235158622L: //RIGHTMENU
  case 3995427725L: //RMENU
  case 30566950L: //RALT
    SendSingleKey(VK_RMENU);
    return TRUE;
  case 3954267447L: //IMEPROCESS
    SendSingleKey(VK_PROCESSKEY);
    return TRUE;
  }
  return FALSE;
}

LPSTR ParseKeyString(const LPSTR keyString) {
  if (lstrlen(keyString) < 1) return 0;
  if (keyString[0] == '$' && keyString[1] == '{') {
    char commandBuffer[COMMAND_MAX_LENGTH];
    char param1Buffer[PARAM_MAX_LENGTH];
    char param2Buffer[PARAM_MAX_LENGTH];
    int param1, param2;
    if (sscanf(keyString, "${%[A-Z0-9]}", commandBuffer) == 1) {
      size_t offset = 2 + strnlen(commandBuffer, COMMAND_MAX_LENGTH) + 1;
      if (keyString[offset - 1] == '}') {
        if (ParseCommand(commandBuffer))
          return ParseKeyString(keyString + offset);
      }
    }
    if (sscanf(keyString, "${%[A-Z] %[0-9]}", commandBuffer, param1Buffer) == 2) {
      size_t offset = 3 + strnlen(commandBuffer, COMMAND_MAX_LENGTH) + strnlen(param1Buffer, PARAM_MAX_LENGTH) + 1;
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
    if (sscanf(keyString, "${%[A-Z] %[0-9] %[0-9]}", commandBuffer, param1Buffer, param2Buffer) == 3) {
      size_t offset = 4 + strnlen(commandBuffer, COMMAND_MAX_LENGTH) + strnlen(param1Buffer, PARAM_MAX_LENGTH) + strnlen(param2Buffer, PARAM_MAX_LENGTH) + 1;
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