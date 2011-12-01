/**************************************************************************
 * Copyright(c) 1998-2007, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

//-------------------------------------------------------------------------
//     Container class for AOD VZERO data
//     Author: Cvetan Cheshkov
//     cvetan.cheshkov@cern.ch 2/02/2011
//-------------------------------------------------------------------------

#include "AliAODTZERO.h"
#include "AliLog.h"

ClassImp(AliAODTZERO)

//__________________________________________________________________________
AliAODTZERO::AliAODTZERO()
  :TObject(),
   fPileup(0),
   fSattelite(0),
   fBackground(0)
{   
  // Default constructor 
  for(Int_t j=0; j<3; j++){ 
    fT0TOF[j]     = 999;
    fT0TOFbest[j] = 999;
  }
}

//__________________________________________________________________________
AliAODTZERO::AliAODTZERO(const AliAODTZERO &source)
  :TObject(source),
   fPileup(source.fPileup),
   fSattelite(source.fSattelite),
   fBackground(source.fBackground)
{   
  // Default constructor 
  for(Int_t j=0; j<3; j++) {
    fT0TOF[j]     = source.fT0TOF[j];
    fT0TOFbest[j] = source.fT0TOFbest[j];
  }
}

//__________________________________________________________________________
AliAODTZERO& AliAODTZERO::operator=(const AliAODTZERO& source)
{
  // Assignment operator
  //
  if(this==&source) return *this;
  // Assignment operator
  fPileup     = source.fPileup;
  fSattelite  = source.fSattelite;
  fBackground = source.fBackground;

  for(Int_t j=0; j<3; j++){
    fT0TOF[j]     = source.fT0TOF[j];
    fT0TOFbest[j] = source.fT0TOFbest[j];
  }
  return *this;
}

