#ifndef TELNETIAC_H
#define TELNETIAC_H

#define IAC_SE      0xF0
#define IAC_NOP     0xF1
#define IAC_DM      0xF2
#define IAC_BRK     0xF3
#define IAC_IP      0xF4
#define IAC_AO      0xF5
#define IAC_AYT     0xF6
#define IAC_EC      0xF7
#define IAC_EL      0xF8
#define IAC_GA      0xF9
#define IAC_SB      0xFA
#define IAC_WILL    0xFB
#define IAC_WONT    0xFC
#define IAC_DO      0xFD
#define IAC_DONT    0xFE
#define IAC_IAC     0xFF

#define IAC_ECHO    0x01
#define IAC_STOP    0x03
#define IAC_TERM    0x18
#define IAC_WINS    0x1F


#endif // TELNETIAC_H
