#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static const unsigned long crc32tab[] = {
 0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL,
 0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
 0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L,
 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
 0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
 0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L,
 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
 0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L,
 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
 0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L,
 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
 0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL,
 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L,
 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
 0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
 0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
 0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL,
 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
 0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L,
 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
 0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L,
 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
 0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L,
 0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
 0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL,
 0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
 0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
 0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL,
 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL,
 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
 0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L,
 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
 0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L,
 0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
 0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
 0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L,
 0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
 0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L,
 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
 0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL,
 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
 0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L,
 0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L,
 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
 0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L,
 0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
 0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL 
};

unsigned long crc32(const char * buf, unsigned long size) {
  unsigned long i, crc;
  crc = 0xFFFFFFFF;
  for (i = 0; i < size; i++)
    crc = crc32tab[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
  return crc ^ 0xFFFFFFFF;
}

static void MouseClick(const unsigned int x, const unsigned int y, const unsigned char type) {
  SetCursorPos(x, y);
  INPUT input;
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
  default:
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(input));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  }
  SendInput(1, &input, sizeof(input));
}

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
    SendSingleKey(VK_LMENU);
    return TRUE;
  case 1235158622L: //RIGHTMENU
  case 3995427725L: //RMENU
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