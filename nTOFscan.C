#include "histMaker.h"
#include "nResponse.hpp"
#include "TH1D.h"
#include "TKey.h"
#include "TCanvas.h"
#include <iostream>

void nTOFscan(void){
    histMaker("fileList.txt",9);
    TFile *fIn = new TFile("simHists.root","READ");
    TIter next(fIn->GetListOfKeys());
    TKey *iK;
    TCanvas *c1 = new TCanvas();
    TH1D *hIn;
    TF1 *fTOF = new TF1("f1",nResponse,0,1000,11);
    fTOF->SetNpx(1000);
    string dummy;
    while ((iK=(TKey*)next())){
        TClass *cl = gROOT->GetClass(iK->GetClassName());
        if( !cl->InheritsFrom("TH1")) continue;
        hIn = (TH1D*)iK->ReadObj();
        double xMax = hIn->GetBinCenter(hIn->GetMaximumBin());
        double yMax = hIn->GetBinContent(hIn->GetMaximumBin());
        double upperX = hIn->GetBinCenter(hIn->GetNbinsX());
        cout << "Fitting Response around " << xMax << endl;
        fTOF->SetParameters(xMax,0.02,1.5,2.0,0.09,2.5,0.13,8.2,0.021,17.5,yMax);
        hIn->Draw();
        hIn->Fit(fTOF,"N","",xMax-40,xMax+600);
        fTOF->Draw("same");
        c1->Update();
        c1->WaitPrimitive();


        
        //getline(cin,dummy);
    }
    c1->Close();
    fIn->Close();
}