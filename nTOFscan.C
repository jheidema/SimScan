#include "histMaker.h"
#include "nResponse.hpp"
#include "TH1D.h"
#include "TKey.h"
#include "TCanvas.h"
#include <iostream>

void nTOFscan(Bool_t kMake = true){
    if(kMake) histMaker("fileList.txt",9);
    TFile *fIn = new TFile("simHists.root","READ");
    TIter next(fIn->GetListOfKeys());
    TKey *iK;
    TCanvas *c1 = new TCanvas();
    c1->SetLogy();
    TH1D *hIn;
    TF1 *fTOF = new TF1("f1",nResponse,0,1000,11);
    fTOF->SetNpx(1000);
    fTOF->SetParNames("t0","a0","sig0","sig1","k1","d1","k2","d2","k3","d3","AA");
    fTOF->SetParLimits(1,1E-4,1);
//    fTOF->SetParameters(0,0.02,1.5,2.0,0.09,2.5,0.13,8.2,0.021,17.5,0);
    fTOF->SetParameters(173.198, 0.0803184, 6.50088, 4.00965, 0.0976356, 2.36471, 0.0633735, 20.8976, 0.0203776, 59.0845, 16310.5);
    string dummy;
    Int_t energies[9] = {200,300,500,700,1000,2000,3000,5000,7000};
    Double_t parVals[9][11];
    Int_t ih=0;
    while ((iK=(TKey*)next())){
        TClass *cl = gROOT->GetClass(iK->GetClassName());
        if( !cl->InheritsFrom("TH1")) continue;
        hIn = (TH1D*)iK->ReadObj();
        double xMax = hIn->GetBinCenter(hIn->GetMaximumBin());
        double yMax = hIn->GetBinContent(hIn->GetMaximumBin());
        double upperX = hIn->GetBinCenter(hIn->GetNbinsX());
        //cout << "Fitting Response around " << xMax << endl;
        fTOF->SetParameter(0,xMax);
        fTOF->SetParameter(10,yMax);
        c1->cd();
        hIn->Draw();
        double leftSig = fTOF->GetParameter(2);
        hIn->Fit(fTOF,"NQ","",xMax-xMax*20,xMax+600);
        fTOF->Draw("same");
        c1->Update();
        c1->WaitPrimitive();

        cout << energies[ih] << ", " ;
        for (int ip=0; ip<11; ++ip){
            cout << fTOF->GetParameter(ip) << ", ";
            parVals[ih][ip] = fTOF->GetParameter(ip);
        }   
        cout << endl;
        //getline(cin,dummy);
        ih++;
    }
    c1->Close();
    fIn->Close();


    TFile *fOut = new TFile("parVals.root","RECREATE");
    TGraph *gp[11];
    for (int ig = 0; ig<11; ig++){
        gp[ig]=new TGraph();
        gp[ig]->SetName(fTOF->GetParName(ig));
        for (int iE=0; iE<9;iE++){
            gp[ig]->SetPoint(iE,energies[iE],parVals[iE][ig]);
        }
        gp[ig]->Write();
    }


return;
}