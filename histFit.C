#include "TH1F.h"
#include "TF1.h"
#include "nResponse.hpp"


void histFit(TH1F *hIn, Bool_t kFit){

    double xMax = hIn->GetBinCenter(hIn->GetMaximumBin());
    double yMax = hIn->GetBinContent(hIn->GetMaximumBin());
    double upperX = hIn->GetBinCenter(hIn->GetNbinsX());
    TF1 *fTOF = new TF1("f1",nResponse,0,1000,11);
    fTOF->SetNpx(1000);
    fTOF->SetParNames("t0","a0","sig0","sig1","k1","d1","k2","d2","k3","d3","AA");
    //fTOF->SetParameter(0,xMax);
    //fTOF->SetParameter(10,yMax);
    cout << "Fitting Response around " << xMax << endl;
    
    hIn->Draw();
    fTOF->SetParameters(xMax,0.000137084,1.70043,0.631166,0.156033,2.51831,0.012205,11.976,0.00737744,234.81,yMax);
    //fTOF->SetParameters(32.2901, 0.000137084, 1.70043, 0.631166, 0.156033, 2.51831, 0.012205, 11.976, 0.00737744, 234.81, 34292.2);

    if(kFit) hIn->Fit(fTOF,"","",xMax-20,upperX);
    else fTOF->Draw("same");

    return;
}