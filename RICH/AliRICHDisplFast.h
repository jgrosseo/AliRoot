#ifndef AliRICHDisplFast_h
#define AliRICHDisplFast_h

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include <TTask.h>
#include "AliRICH.h"
#include <AliRun.h>

class AliRICH;

class AliRICHDisplFast : public TTask {
   public :
 
   AliRICHDisplFast();
   ~AliRICHDisplFast(){;}
   void Display();

ClassDef(AliRICHDisplFast,0)

};
    
#endif // #ifdef AliRICHDisplFast_cxx

