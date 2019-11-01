#include "TH1F.h"
#include "TF1.h"
#include "nResponse.hpp"


void histFit(TH1F *hIn, Bool_t kFit){

    double xMax = hIn->GetBinCenter(hIn->GetMaximumBin());
    double yMax = hIn->GetBinContent(hIn->GetMaximumBin());
    double upperX = hIn->GetBinCenter(hIn->GetNbinsX());
    TF1 *fTOF = new TF1("f1",nResponse,0,1000,11);
    fTOF->SetNpx(1000);
    //fTOF->SetParameter(0,xMax);
    //fTOF->SetParameter(10,yMax);
    cout << "Fitting Response around " << xMax << endl;
    
    hIn->Draw();
    fTOF->SetParameters(xMax,0.02,1.5,2.0,0.09,2.5,0.13,8.2,0.021,17.5,yMax);
    if(kFit) hIn->Fit(fTOF,"","",xMax-40,upperX);
        else fTOF->Draw("same");

    return;
}