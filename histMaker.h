#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include <iostream>


void histMaker(const char *fileListname, const int nF){
    gROOT->Reset();
    ifstream inFile;
    inFile.open(fileListname);
    string fName;
    char hName[50];
    TFile *rootIn;
    TTree *inTree;
    TFile *fOut = new TFile("simHists.root","RECREATE");

    Int_t ih=0;
    TH1D *hh;

    TCanvas *c1 = new TCanvas();
//    string dummy;

    while (getline(inFile,fName)){
        rootIn = new TFile(fName.c_str(),"READ");
        rootIn->GetObject("vandleTree",inTree);
        rootIn->cd();        
        sprintf(hName,"corTof>>hTOF%d(1000,0,1000)",ih);
        inTree->Draw(hName,"vandleQDC>5","goff");
        sprintf(hName,"hTOF%d",ih);
        hh = (TH1D*)gDirectory->Get(hName);
        fName.erase(fName.end()-12,fName.end());
        fName.erase(fName.begin(),fName.begin()+9);
        hh->SetName(fName.c_str());
        hh->SetDirectory(fOut->GetDirectory(""));
        fOut->cd();
        hh->Write();
        ++ih;
        fName.erase();
        rootIn->Close();
    }
    inFile.close();
    fOut->Close();
    return;
}