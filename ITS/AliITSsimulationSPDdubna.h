#ifndef ALIITSSIMULATIONSPDDUBNA_H
#define ALIITSSIMULATIONSPDDUBNA_H

#include "AliITSsimulation.h"

class AliITSMapA2;
class AliITSsegmentation;
class AliITSresponse;
class AliITSmodule;

//-------------------------------------------------------------------

class AliITSsimulationSPDdubna : public AliITSsimulation {

public:
        
  AliITSsimulationSPDdubna();
  AliITSsimulationSPDdubna(AliITSsegmentation *seg, AliITSresponse *res);
  virtual ~AliITSsimulationSPDdubna();
  AliITSsimulationSPDdubna(const AliITSsimulationSPDdubna &source); // copy constructor
  AliITSsimulationSPDdubna& operator=(const AliITSsimulationSPDdubna &source); // ass. operator

  void InitSimulationModule(Int_t module, Int_t event);
  void SDigitiseModule(AliITSmodule *mod, Int_t mask, Int_t event);
  void WriteSDigits(AliITSpList *pList);
  void FinishSDigitiseModule();
  void SDigitsToDigits(Int_t module, AliITSpList *pList);
  void DigitiseModule(AliITSmodule *mod,Int_t module,Int_t dummy);
  void UpdateMapSignal(Int_t i, Int_t j, Int_t trk, Int_t ht,
		       Int_t module, Double_t signal, AliITSpList *pList);
  void UpdateMapNoise(Int_t i, Int_t j, Int_t ix, Int_t iz, Int_t module,
		      Double_t sig, Float_t noise, AliITSpList *pList);
  void HitToDigit(AliITSmodule *mod,Int_t module,Int_t dummy);
  void HitToSDigit(AliITSmodule *mod, Int_t module, Int_t dummy,
		   AliITSpList *pList);
  void ChargeToSignal(AliITSpList *pList);
  
  void CreateHistograms();
  void ResetHistograms();
  TObjArray*  GetHistArray() {
    // get hist array
    return fHis;
  }

private:

  AliITSMapA2  *fMapA2;        //! MapA2
  Float_t      fNoise;         //! Noise
  Float_t      fBaseline;      //! Baseline
  Int_t        fNPixelsX;      //! NPixelsX
  Int_t        fNPixelsZ;      //! NPixelsZ

  TObjArray *fHis;             //! just in case for histogramming
    
  ClassDef(AliITSsimulationSPDdubna,1)  // Simulation of SPD clusters

};

#endif 
