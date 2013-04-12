// 7zHeader.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"
#include "7zHeader.h"


namespace n7z
{

byte kSignature[kSignatureSize] = {'7', 'z', 0xBC, 0xAF, 0x27, 0x1C};
#ifdef _7Z_VOL
byte kFinishSignature[kSignatureSize] = {'7', 'z', 0xBC, 0xAF, 0x27, 0x1C + 1};
#endif

}