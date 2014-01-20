/*
   libcharguess   -   Guess the encoding/charset of a string
    Copyright (C) 2003  Stephane Corbe <noubi@users.sourceforge.net>
   Based on Mozilla sources

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef nsCodingStateMachine_h__
#define nsCodingStateMachine_h__

#include "pkgInt.h"

typedef enum {
   eStart = 0,
   eError = 1,
   eItsMe = 2 
} nsSMState;

#define GETCLASS(ca) GETFROMPCK(((uchar)(ca)), mModel->classTable)

//state machine model
typedef struct 
{
  nsPkgInt classTable;
  uint32_t classFactor;
  nsPkgInt stateTable;
  const uint32_t* charLenTable;
  const char* name;
} SMModel;

class nsCodingStateMachine {
public:
  nsCodingStateMachine(SMModel* sm){
          mCurrentState = eStart;
          mModel = sm;
        };
  nsSMState NextState(char ca){
    //for each byte we get its class , if it is first byte, we also get byte length
    uint32_t byteCls = GETCLASS(ca);
    if (mCurrentState == eStart)
    { 
      mCurrentBytePos = 0; 
      mCurrentCharLen = mModel->charLenTable[byteCls];
    }
    //from byte's class and stateTable, we get its next state
    mCurrentState=(nsSMState)GETFROMPCK(mCurrentState*(mModel->classFactor)+byteCls,
                                       mModel->stateTable);
    mCurrentBytePos++;
    return mCurrentState;
  };
  uint32_t  GetCurrentCharLen() {return mCurrentCharLen;};
  void      Reset() {mCurrentState = eStart;};
  const char * GetCodingStateMachine() {return mModel->name;};

protected:
  nsSMState mCurrentState;
  uint32_t mCurrentCharLen;
  uint32_t mCurrentBytePos;

  SMModel *mModel;
};

extern SMModel UTF8SMModel;
extern SMModel Big5SMModel;
extern SMModel EUCJPSMModel;
extern SMModel EUCKRSMModel;
extern SMModel EUCTWSMModel;
extern SMModel GB18030SMModel;
extern SMModel SJISSMModel;
extern SMModel UCS2BESMModel;


extern SMModel HZSMModel;
extern SMModel ISO2022CNSMModel;
extern SMModel ISO2022JPSMModel;
extern SMModel ISO2022KRSMModel;

#endif /* nsCodingStateMachine_h__ */

