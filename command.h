#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdint.h>
#include "mouse.h"
#include "sendkey.h"

#define COMMAND_MAX_LENGTH 16
static WORD ParseCommand(const uint32_t hash) {
  switch (hash) {
    case 4213349504U: // BACKSPACE
    case 1911832374U: // BS
    case 2523624168U: // BKSP
      return VK_BACK;
    case 3727033226U: // SPACE
      return VK_SPACE;
    case 3846439302U: // TAB
      return VK_TAB;
    case 317010870U: // CLEAR
      return VK_CLEAR;
    case 1310982878U: // ENTER
      return VK_RETURN;
    case 1382021621U: // SHIFT
      return VK_SHIFT;
    case 884448462U: // CTRL
      return VK_CONTROL;
    case 3201542913U: // ALT
      return VK_MENU;
    case 550391901U: // PAUSE
      return VK_PAUSE;
    case 2439287330U: // CAPS
    case 3274666208U: // CAPSLOCK
      return VK_CAPITAL;
    case 4149446788U: // ESC
      return VK_ESCAPE;
    case 82448359U: // PAGEUP
    case 859550494U: // PGUP
      return VK_PRIOR;
    case 1528306972U: // PAGEDOWN
    case 2599267693U: // PGDN
      return VK_NEXT;
    case 2522575163U: // END
      return VK_END;
    case 1195630948U: // HOME
      return VK_HOME;
    case 3864525061U: // LEFTARROW
    case 1290930908U: // LEFT
      return VK_LEFT;
    case 156158474U: // UPARROW
    case 3984517658U: // UP
      return VK_UP;
    case 112782023U: // RIGHTARROW
    case 1134475172U: // RIGHT
      return VK_RIGHT;
    case 2947281234U: // DOWNARROW
    case 711622031U: // DOWN
      return VK_DOWN;
    case 3138006342U: // SELECT
      return VK_SELECT;
    case 3800219350U: // PRINT
      return VK_PRINT;
    case 3223776964U: // EXECUTE
      return VK_EXECUTE;
    case 2836567439U: // PRINTSCREEN
    case 2328061742U: // PRTSC
      return VK_SNAPSHOT;
    case 479333784U: // INS
    case 892623219U: // INSERT
      return VK_INSERT;
    case 2058767093U: // DEL
    case 3404380929U: // DELETE
      return VK_DELETE;
    case 1041412376U: // HELP
      return VK_HELP;
    case 1256517092U: // NUM
    case 3844504896U: // NUMLOCK
      return VK_NUMLOCK;
    case 2251377965U: // SCROLLLOCK
      return VK_SCROLL;
    case 4067218798U: // LEFTWINDOWS
    case 699046007U: // LWIN
      return VK_LWIN;
    case 2401157523U: // RIGHTWINDOWS
    case 2574039259U: // RWIN
      return VK_RWIN;
    case 1660628960U: // APPLICATIONS
      return VK_APPS;
    case 1771420896U: // COMPUTERSLEEP
      return VK_SLEEP;
    case 3615866119U: // MULTIPLY
      return VK_MULTIPLY;
    case 1807561069U: // ADD
      return VK_ADD;
    case 3543192423U: // SEPARATOR
      return VK_SEPARATOR;
    case 3882583749U: // SUBTRACT
      return VK_SUBTRACT;
    case 1706577289U: // DECIMAL
      return VK_DECIMAL;
    case 1936067278U: // DIVIDE
      return VK_DIVIDE;
    case 1408638381U: // NUM0
    case 2111931934U: // NUMPAD0
      return VK_NUMPAD0;
    case 619785531U: // NUM1
    case 182892168U: // NUMPAD1
      return VK_NUMPAD1;
    case 3187178625U: // NUM2
    case 2481973042U: // NUMPAD2
      return VK_NUMPAD2;
    case 3405728791U: // NUM3
    case 3840464804U: // NUMPAD3
      return VK_NUMPAD3;
    case 1419499956U: // NUM4
    case 2056012295U: // NUMPAD4
      return VK_NUMPAD4;
    case 597485858U: // NUM5
    case 227242641U: // NUMPAD5
      return VK_NUMPAD5;
    case 3130374296U: // NUM6
    case 2491556651U: // NUMPAD6
      return VK_NUMPAD6;
    case 3448932366U: // NUM7
    case 3817149373U: // NUMPAD7
      return VK_NUMPAD7;
    case 1563268511U: // NUM8
    case 1933184556U: // NUMPAD8
      return VK_NUMPAD8;
    case 707437833U: // NUM9
    case 71122618U: // NUMPAD9
      return VK_NUMPAD9;
    case 3055876678U: // F1
      return VK_F1;
    case 791522300U: // F2
      return VK_F2;
    case 1479187306U: // F3
      return VK_F3;
    case 3327004361U: // F4
      return VK_F4;
    case 2974367327U: // F5
      return VK_F5;
    case 675311589U: // F6
      return VK_F6;
    case 1598513011U: // F7
      return VK_F7;
    case 3489153762U: // F8
      return VK_F8;
    case 3103748724U: // F9
      return VK_F9;
    case 1808932734U: // F10
      return VK_F10;
    case 483733480U: // F11
      return VK_F11;
    case 2245819986U: // F12
      return VK_F12;
    case 4074458820U: // F13
      return VK_F13;
    case 1824512871U: // F14
      return VK_F14;
    case 465103857U: // F15
      return VK_F15;
    case 2192685643U: // F16
      return VK_F16;
    case 4122381021U: // F17
      return VK_F17;
    case 1695127372U: // F18
      return VK_F18;
    case 302950362U: // F19
      return VK_F19;
    case 1090473149U: // F20
      return VK_F20;
    case 939031595U: // F21
      return VK_F21;
    case 2935041425U: // F22
      return VK_F22;
    case 3656785159U: // F23
      return VK_F23;
    case 1200785572U: // F24
      return VK_F24;
    case 2607492222U: // LEFTSHIFT
    case 1562731868U: // LSHIFT
      return VK_LSHIFT;
    case 2072264636U: // RIGHTSHIFT
    case 1694041783U: // RSHIFT
      return VK_RSHIFT;
    case 4233133246U: // LEFTCONTROL
    case 1322385799U: // LCTRL
      return VK_LCONTROL;
    case 2166515779U: // RIGHTCONTROL
    case 2432837732U: // RCTRL
      return VK_RCONTROL;
    case 1936054868U: // LEFTMENU
    case 838158958U: // LMENU
    case 2970897034U: // LALT
      return VK_LMENU;
    case 1235158622U: // RIGHTMENU
    case 3995427725U: // RMENU
    case 30566950U: // RALT
      return VK_RMENU;
    case 3954267447U: // IMEPROCESS
      return VK_PROCESSKEY;
    case 1710951019U: // LBUTTON
      return VK_LBUTTON;
    case 1377496568U: // RBUTTON
      return VK_RBUTTON;
    case 2800616180U: // CANCEL
      return VK_CANCEL;
    case 3280732639U: // MBUTTON
      return VK_MBUTTON;
    case 2703791036U: // XBUTTON1
      return VK_XBUTTON1;
    case 941736454U: // XBUTTON2
      return VK_XBUTTON2;
    case 1945007743U: // BROWSERBACK
      return VK_BROWSER_BACK;
    case 2673191389U: // BROWSERFORWARD
      return VK_BROWSER_FORWARD;
    case 407185056U: // BROWSERREFRESH
      return VK_BROWSER_REFRESH;
    case 2809569790U: // BROWSERSTOP
      return VK_BROWSER_STOP;
    case 2009014991U: // BROWSERSEARCH
      return VK_BROWSER_SEARCH;
    case 387432145U: // BROWSERFAVORITES
      return VK_BROWSER_FAVORITES;
    case 1878440856U: // BROWSERHOME
      return VK_BROWSER_HOME;
    case 2714356834U: // VOLUMEMUTE
    case 4197228264U: // MUTE
      return VK_VOLUME_MUTE;
    case 1905209093U: // VOLUMEDOWN
    case 2053074917U: // VDOWN
      return VK_VOLUME_DOWN;
    case 2143919418U: // VOLUMEUP
    case 1003975669U: // VUP
      return VK_VOLUME_UP;
    case 2145333128U: // MEDIANEXTTRACK
      return VK_MEDIA_NEXT_TRACK;
    case 644010588U: // MEDIAPREVTRACK
      return VK_MEDIA_PREV_TRACK;
    case 4222509918U: // MEDIASTOP
    case 3368439803U: // MSTOP
      return VK_MEDIA_STOP;
    case 1261637064U: // MEDIAPLAYPAUSE
    case 790202359U: // MPLAY
      return VK_MEDIA_PLAY_PAUSE;
    case 11509296U: // LAUNCHMAIL
      return VK_LAUNCH_MAIL;
    case 3101998649U: // LAUNCHMEDIASELECT
      return VK_LAUNCH_MEDIA_SELECT;
    default:break;
  }
  return FALSE;
}

static BOOL ParseCommandWithParams(const uint32_t hash, const int params[],
                                   const unsigned char paramCount) {
  if (paramCount == 1) {
    switch (hash) {
      case 4167499804U: // SLEEP
      case 1266380369U: // WAIT
        Sleep((DWORD) params[0]);
        return TRUE;
      case 2439287330U: // CAPS
      case 3274666208U: // CAPSLOCK
        SetKeyState((BOOL) params[0], VK_CAPITAL);
        return TRUE;
      case 1256517092U: // NUM
      case 3844504896U: // NUMLOCK
        SetKeyState((BOOL) params[0], VK_NUMLOCK);
        return TRUE;
      case 2251377965U: // SCROLLLOCK
        SetKeyState((BOOL) params[0], VK_SCROLL);
        return TRUE;
      default:break;
    }
  } else if (paramCount == 2) {
    switch (hash) {
      case 1302462608U: // CLICK
      case 1121492025U: // LCLICK
      case 2224477467U: // LEFTCLICK
        MouseClick((const unsigned int) params[0], (const unsigned int) params[1], 0);
        return TRUE;
      case 2063925202U: // RCLICK
      case 1685702361U: // RIGHTCLICK
        MouseClick((const unsigned int) params[0], (const unsigned int) params[1], 1);
        return TRUE;
      case 2307149724U: // MCLICK
      case 1843602477U: // MIDDLECLICK
        MouseClick((const unsigned int) params[0], (const unsigned int) params[1], 2);
        return TRUE;
      case 2858569247U: // MOUSEMOVE
        SetCursorPos(params[0], params[1]);
        return TRUE;
      default:break;
    }
  }
  return FALSE;
}


BOOL ParseKeyCombination(const char param[][COMMAND_MAX_LENGTH],
                         const WORD paramLength[],
                         const unsigned char paramCount) {
  WORD keyCode[paramCount];
  uint32_t hash[paramCount];
  for (unsigned char i = 0; i < paramCount; i++) {
    hash[i] = crc32(param[i], paramLength[i]);
    keyCode[i] = ParseCommand(hash[i]);
    if (!keyCode[i] && paramLength[i] == 1) {
      SHORT vKeyCode = VkKeyScan(param[i][0]);
      if (vKeyCode >> 8 == 0 || vKeyCode >> 8 == 1)
        keyCode[i] = (WORD) (vKeyCode & 0xFF);
    }
    if (!keyCode[i])
      return FALSE;
  }
  SendMultipleKey(keyCode, paramCount);
  return TRUE;
}
