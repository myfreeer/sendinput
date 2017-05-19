static WORD ParseCommand(const unsigned long hash) {
  switch (hash) {
  case 4213349504L: //BACKSPACE
  case 1911832374L: //BS
  case 2523624168L: //BKSP
    return VK_BACK;
  case 3727033226: //SPACE
    return VK_SPACE;
  case 3846439302L: //TAB
    return VK_TAB;
  case 317010870L: //CLEAR
    return VK_CLEAR;
  case 1310982878L: //ENTER
    return VK_RETURN;
  case 1382021621L: //SHIFT
    return VK_SHIFT;
  case 884448462L: //CTRL
    return VK_CONTROL;
  case 3201542913L: //ALT
    return VK_MENU;
  case 550391901L: //PAUSE
    return VK_PAUSE;
  case 2439287330L: //CAPS
  case 3274666208L: //CAPSLOCK
    return VK_CAPITAL;
  case 4149446788L: //ESC
    return VK_ESCAPE;
  case 82448359L: //PAGEUP
  case 859550494L: //PGUP
    return VK_PRIOR;
  case 1528306972L: //PAGEDOWN
  case 2599267693L: //PGDN
    return VK_NEXT;
  case 2522575163L: //END
    return VK_END;
  case 1195630948L: //HOME
    return VK_HOME;
  case 3864525061L: //LEFTARROW
  case 1290930908L: //LEFT
    return VK_LEFT;
  case 156158474L: //UPARROW
  case 3984517658L: //UP
    return VK_UP;
  case 112782023L: //RIGHTARROW
  case 1134475172L: //RIGHT
    return VK_RIGHT;
  case 2947281234L: //DOWNARROW
  case 711622031L: //DOWN
    return VK_DOWN;
  case 3138006342L: //SELECT
    return VK_SELECT;
  case 3800219350L: //PRINT
    return VK_PRINT;
  case 3223776964L: //EXECUTE
    return VK_EXECUTE;
  case 2836567439L: //PRINTSCREEN
  case 2328061742L: //PRTSC
    return VK_SNAPSHOT;
  case 479333784L: //INS
  case 892623219L: //INSERT
    return VK_INSERT;
  case 2058767093L: //DEL
  case 3404380929L: //DELETE
    return VK_DELETE;
  case 1041412376L: //HELP
    return VK_HELP;
  case 1256517092L: //NUM
  case 3844504896L: //NUMLOCK
    return VK_NUMLOCK;
  case 2251377965L: //SCROLLLOCK
    return VK_SCROLL;
  case 4067218798L: //LEFTWINDOWS
  case 699046007L: //LWIN
    return VK_LWIN;
  case 2401157523L: //RIGHTWINDOWS
  case 2574039259L: //RWIN
    return VK_RWIN;
  case 1660628960L: //APPLICATIONS
    return VK_APPS;
  case 1771420896L: //COMPUTERSLEEP
    return VK_SLEEP;
  case 3615866119L: //MULTIPLY
    return VK_MULTIPLY;
  case 1807561069L: //ADD
    return VK_ADD;
  case 3543192423L: //SEPARATOR
    return VK_SEPARATOR;
  case 3882583749L: //SUBTRACT
    return VK_SUBTRACT;
  case 1706577289L: //DECIMAL
    return VK_DECIMAL;
  case 1936067278L: //DIVIDE
    return VK_DIVIDE;
  case 1408638381L: //NUM0
  case 2111931934L: //NUMPAD0
    return VK_NUMPAD0;
  case 619785531L: //NUM1
  case 182892168L: //NUMPAD1
    return VK_NUMPAD1;
  case 3187178625L: //NUM2
  case 2481973042L: //NUMPAD2
    return VK_NUMPAD2;
  case 3405728791L: //NUM3
  case 3840464804L: //NUMPAD3
    return VK_NUMPAD3;
  case 1419499956L: //NUM4
  case 2056012295L: //NUMPAD4
    return VK_NUMPAD4;
  case 597485858L: //NUM5
  case 227242641L: //NUMPAD5
    return VK_NUMPAD5;
  case 3130374296L: //NUM6
  case 2491556651L: //NUMPAD6
    return VK_NUMPAD6;
  case 3448932366L: //NUM7
  case 3817149373L: //NUMPAD7
    return VK_NUMPAD7;
  case 1563268511L: //NUM8
  case 1933184556L: //NUMPAD8
    return VK_NUMPAD8;
  case 707437833L: //NUM9
  case 71122618L: //NUMPAD9
    return VK_NUMPAD9;
  case 3055876678L: //F1
    return VK_F1;
  case 791522300L: //F2
    return VK_F2;
  case 1479187306L: //F3
    return VK_F3;
  case 3327004361L: //F4
    return VK_F4;
  case 2974367327L: //F5
    return VK_F5;
  case 675311589L: //F6
    return VK_F6;
  case 1598513011L: //F7
    return VK_F7;
  case 3489153762L: //F8
    return VK_F8;
  case 3103748724L: //F9
    return VK_F9;
  case 1808932734L: //F10
    return VK_F10;
  case 483733480L: //F11
    return VK_F11;
  case 2245819986L: //F12
    return VK_F12;
  case 4074458820L: //F13
    return VK_F13;
  case 1824512871L: //F14
    return VK_F14;
  case 465103857L: //F15
    return VK_F15;
  case 2192685643L: //F16
    return VK_F16;
  case 4122381021L: //F17
    return VK_F17;
  case 1695127372L: //F18
    return VK_F18;
  case 302950362L: //F19
    return VK_F19;
  case 1090473149L: //F20
    return VK_F20;
  case 939031595L: //F21
    return VK_F21;
  case 2935041425L: //F22
    return VK_F22;
  case 3656785159L: //F23
    return VK_F23;
  case 1200785572L: //F24
    return VK_F24;
  case 2607492222L: //LEFTSHIFT
  case 1562731868L: //LSHIFT
    return VK_LSHIFT;
  case 2072264636L: //RIGHTSHIFT
  case 1694041783L: //RSHIFT
    return VK_RSHIFT;
  case 4233133246L: //LEFTCONTROL
  case 1322385799L: //LCTRL
    return VK_LCONTROL;
  case 2166515779L: //RIGHTCONTROL
  case 2432837732L: //RCTRL
    return VK_RCONTROL;
  case 1936054868L: //LEFTMENU
  case 838158958L: //LMENU
  case 2970897034L: //LALT
    return VK_LMENU;
  case 1235158622L: //RIGHTMENU
  case 3995427725L: //RMENU
  case 30566950L: //RALT
    return VK_RMENU;
  case 3954267447L: //IMEPROCESS
    return VK_PROCESSKEY;
  case 1710951019L: //LBUTTON
     return VK_LBUTTON;
  case 1377496568L: //RBUTTON
     return VK_RBUTTON;
  case 2800616180L: //CANCEL
     return VK_CANCEL;
  case 3280732639L: //MBUTTON
     return VK_MBUTTON;
  case 2703791036L: //XBUTTON1
     return VK_XBUTTON1;
  case 941736454L: //XBUTTON2
     return VK_XBUTTON2;
  case 1945007743L: //BROWSERBACK
     return VK_BROWSER_BACK;
  case 2673191389L: //BROWSERFORWARD
     return VK_BROWSER_FORWARD;
  case 407185056L: //BROWSERREFRESH
     return VK_BROWSER_REFRESH;
  case 2809569790L: //BROWSERSTOP
     return VK_BROWSER_STOP;
  case 2009014991L: //BROWSERSEARCH
     return VK_BROWSER_SEARCH;
  case 387432145L: //BROWSERFAVORITES
     return VK_BROWSER_FAVORITES;
  case 1878440856L: //BROWSERHOME
     return VK_BROWSER_HOME;
  case 2714356834L: //VOLUMEMUTE
  case 4197228264L: //MUTE
     return VK_VOLUME_MUTE;
  case 1905209093L: //VOLUMEDOWN
  case 2053074917L: //VDOWN
     return VK_VOLUME_DOWN;
  case 2143919418L: //VOLUMEUP
  case 1003975669L: //VUP
     return VK_VOLUME_UP;
  case 2145333128L: //MEDIANEXTTRACK
     return VK_MEDIA_NEXT_TRACK;
  case 644010588L: //MEDIAPREVTRACK
     return VK_MEDIA_PREV_TRACK;
  case 4222509918L: //MEDIASTOP
  case 3368439803L: //MSTOP
     return VK_MEDIA_STOP;
  case 1261637064L: //MEDIAPLAYPAUSE
  case 790202359L: //MPLAY
     return VK_MEDIA_PLAY_PAUSE;
  case 11509296L: //LAUNCHMAIL
     return VK_LAUNCH_MAIL;
  case 3101998649L: //LAUNCHMEDIASELECT
     return VK_LAUNCH_MEDIA_SELECT;
  }
  return FALSE;
}