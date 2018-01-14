#include <windows.h>
#include <stdint.h>
#include "mouse.h"
#include "sendkey.h"

static WORD ParseCommand(const uint32_t hash) {
  switch (hash) {
  case 4213349504: // BACKSPACE
  case 1911832374: // BS
  case 2523624168: // BKSP
    return VK_BACK;
  case 3727033226: // SPACE
    return VK_SPACE;
  case 3846439302: // TAB
    return VK_TAB;
  case 317010870: // CLEAR
    return VK_CLEAR;
  case 1310982878: // ENTER
    return VK_RETURN;
  case 1382021621: // SHIFT
    return VK_SHIFT;
  case 884448462: // CTRL
    return VK_CONTROL;
  case 3201542913: // ALT
    return VK_MENU;
  case 550391901: // PAUSE
    return VK_PAUSE;
  case 2439287330: // CAPS
  case 3274666208: // CAPSLOCK
    return VK_CAPITAL;
  case 4149446788: // ESC
    return VK_ESCAPE;
  case 82448359:  // PAGEUP
  case 859550494: // PGUP
    return VK_PRIOR;
  case 1528306972: // PAGEDOWN
  case 2599267693: // PGDN
    return VK_NEXT;
  case 2522575163: // END
    return VK_END;
  case 1195630948: // HOME
    return VK_HOME;
  case 3864525061: // LEFTARROW
  case 1290930908: // LEFT
    return VK_LEFT;
  case 156158474:  // UPARROW
  case 3984517658: // UP
    return VK_UP;
  case 112782023:  // RIGHTARROW
  case 1134475172: // RIGHT
    return VK_RIGHT;
  case 2947281234: // DOWNARROW
  case 711622031:  // DOWN
    return VK_DOWN;
  case 3138006342: // SELECT
    return VK_SELECT;
  case 3800219350: // PRINT
    return VK_PRINT;
  case 3223776964: // EXECUTE
    return VK_EXECUTE;
  case 2836567439: // PRINTSCREEN
  case 2328061742: // PRTSC
    return VK_SNAPSHOT;
  case 479333784: // INS
  case 892623219: // INSERT
    return VK_INSERT;
  case 2058767093: // DEL
  case 3404380929: // DELETE
    return VK_DELETE;
  case 1041412376: // HELP
    return VK_HELP;
  case 1256517092: // NUM
  case 3844504896: // NUMLOCK
    return VK_NUMLOCK;
  case 2251377965: // SCROLLLOCK
    return VK_SCROLL;
  case 4067218798: // LEFTWINDOWS
  case 699046007:  // LWIN
    return VK_LWIN;
  case 2401157523: // RIGHTWINDOWS
  case 2574039259: // RWIN
    return VK_RWIN;
  case 1660628960: // APPLICATIONS
    return VK_APPS;
  case 1771420896: // COMPUTERSLEEP
    return VK_SLEEP;
  case 3615866119: // MULTIPLY
    return VK_MULTIPLY;
  case 1807561069: // ADD
    return VK_ADD;
  case 3543192423: // SEPARATOR
    return VK_SEPARATOR;
  case 3882583749: // SUBTRACT
    return VK_SUBTRACT;
  case 1706577289: // DECIMAL
    return VK_DECIMAL;
  case 1936067278: // DIVIDE
    return VK_DIVIDE;
  case 1408638381: // NUM0
  case 2111931934: // NUMPAD0
    return VK_NUMPAD0;
  case 619785531: // NUM1
  case 182892168: // NUMPAD1
    return VK_NUMPAD1;
  case 3187178625: // NUM2
  case 2481973042: // NUMPAD2
    return VK_NUMPAD2;
  case 3405728791: // NUM3
  case 3840464804: // NUMPAD3
    return VK_NUMPAD3;
  case 1419499956: // NUM4
  case 2056012295: // NUMPAD4
    return VK_NUMPAD4;
  case 597485858: // NUM5
  case 227242641: // NUMPAD5
    return VK_NUMPAD5;
  case 3130374296: // NUM6
  case 2491556651: // NUMPAD6
    return VK_NUMPAD6;
  case 3448932366: // NUM7
  case 3817149373: // NUMPAD7
    return VK_NUMPAD7;
  case 1563268511: // NUM8
  case 1933184556: // NUMPAD8
    return VK_NUMPAD8;
  case 707437833: // NUM9
  case 71122618:  // NUMPAD9
    return VK_NUMPAD9;
  case 3055876678: // F1
    return VK_F1;
  case 791522300: // F2
    return VK_F2;
  case 1479187306: // F3
    return VK_F3;
  case 3327004361: // F4
    return VK_F4;
  case 2974367327: // F5
    return VK_F5;
  case 675311589: // F6
    return VK_F6;
  case 1598513011: // F7
    return VK_F7;
  case 3489153762: // F8
    return VK_F8;
  case 3103748724: // F9
    return VK_F9;
  case 1808932734: // F10
    return VK_F10;
  case 483733480: // F11
    return VK_F11;
  case 2245819986: // F12
    return VK_F12;
  case 4074458820: // F13
    return VK_F13;
  case 1824512871: // F14
    return VK_F14;
  case 465103857: // F15
    return VK_F15;
  case 2192685643: // F16
    return VK_F16;
  case 4122381021: // F17
    return VK_F17;
  case 1695127372: // F18
    return VK_F18;
  case 302950362: // F19
    return VK_F19;
  case 1090473149: // F20
    return VK_F20;
  case 939031595: // F21
    return VK_F21;
  case 2935041425: // F22
    return VK_F22;
  case 3656785159: // F23
    return VK_F23;
  case 1200785572: // F24
    return VK_F24;
  case 2607492222: // LEFTSHIFT
  case 1562731868: // LSHIFT
    return VK_LSHIFT;
  case 2072264636: // RIGHTSHIFT
  case 1694041783: // RSHIFT
    return VK_RSHIFT;
  case 4233133246: // LEFTCONTROL
  case 1322385799: // LCTRL
    return VK_LCONTROL;
  case 2166515779: // RIGHTCONTROL
  case 2432837732: // RCTRL
    return VK_RCONTROL;
  case 1936054868: // LEFTMENU
  case 838158958:  // LMENU
  case 2970897034: // LALT
    return VK_LMENU;
  case 1235158622: // RIGHTMENU
  case 3995427725: // RMENU
  case 30566950:   // RALT
    return VK_RMENU;
  case 3954267447: // IMEPROCESS
    return VK_PROCESSKEY;
  case 1710951019: // LBUTTON
    return VK_LBUTTON;
  case 1377496568: // RBUTTON
    return VK_RBUTTON;
  case 2800616180: // CANCEL
    return VK_CANCEL;
  case 3280732639: // MBUTTON
    return VK_MBUTTON;
  case 2703791036: // XBUTTON1
    return VK_XBUTTON1;
  case 941736454: // XBUTTON2
    return VK_XBUTTON2;
  case 1945007743: // BROWSERBACK
    return VK_BROWSER_BACK;
  case 2673191389: // BROWSERFORWARD
    return VK_BROWSER_FORWARD;
  case 407185056: // BROWSERREFRESH
    return VK_BROWSER_REFRESH;
  case 2809569790: // BROWSERSTOP
    return VK_BROWSER_STOP;
  case 2009014991: // BROWSERSEARCH
    return VK_BROWSER_SEARCH;
  case 387432145: // BROWSERFAVORITES
    return VK_BROWSER_FAVORITES;
  case 1878440856: // BROWSERHOME
    return VK_BROWSER_HOME;
  case 2714356834: // VOLUMEMUTE
  case 4197228264: // MUTE
    return VK_VOLUME_MUTE;
  case 1905209093: // VOLUMEDOWN
  case 2053074917: // VDOWN
    return VK_VOLUME_DOWN;
  case 2143919418: // VOLUMEUP
  case 1003975669: // VUP
    return VK_VOLUME_UP;
  case 2145333128: // MEDIANEXTTRACK
    return VK_MEDIA_NEXT_TRACK;
  case 644010588: // MEDIAPREVTRACK
    return VK_MEDIA_PREV_TRACK;
  case 4222509918: // MEDIASTOP
  case 3368439803: // MSTOP
    return VK_MEDIA_STOP;
  case 1261637064: // MEDIAPLAYPAUSE
  case 790202359:  // MPLAY
    return VK_MEDIA_PLAY_PAUSE;
  case 11509296: // LAUNCHMAIL
    return VK_LAUNCH_MAIL;
  case 3101998649: // LAUNCHMEDIASELECT
    return VK_LAUNCH_MEDIA_SELECT;
  }
  return FALSE;
}

static BOOL ParseCommandWithParams(const uint32_t hash, const int params[],
                                   const unsigned char paramCount) {
  if (paramCount == 1) {
    switch (hash) {
    case 4167499804: // SLEEP
    case 1266380369: // WAIT
      Sleep(params[0]);
      return TRUE;
    case 2439287330: // CAPS
    case 3274666208: // CAPSLOCK
      SetKeyState((BOOL)params[0], VK_CAPITAL);
      return TRUE;
    case 1256517092: // NUM
    case 3844504896: // NUMLOCK
      SetKeyState((BOOL)params[0], VK_NUMLOCK);
      return TRUE;
    case 2251377965: // SCROLLLOCK
      SetKeyState((BOOL)params[0], VK_SCROLL);
      return TRUE;
    }
  } else if (paramCount == 2) {
    switch (hash) {
    case 1302462608: // CLICK
    case 1121492025: // LCLICK
    case 2224477467: // LEFTCLICK
      MouseClick(params[0], params[1], 0);
      return TRUE;
    case 2063925202: // RCLICK
    case 1685702361: // RIGHTCLICK
      MouseClick(params[0], params[1], 1);
      return TRUE;
    case 2307149724: // MCLICK
    case 1843602477: // MIDDLECLICK
      MouseClick(params[0], params[1], 2);
      return TRUE;
    case 2858569247: // MOUSEMOVE
      SetCursorPos(params[0], params[1]);
      return TRUE;
    }
  }
  return FALSE;
}