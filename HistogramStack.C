#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLine.h>
#include <THStack.h>
#include <TStyle.h>
#include <TRandom3.h>

void HistogramStack(){

    TRandom3 random;

    TH1F *hist1 = new TH1F("hist1", "Histogram 1", 100, 0, 100);
    TH1F *hist2 = new TH1F("hist2", "Histogram 2", 100, 0, 100);
    TH1F *hist3 = new TH1F("hist3", "Histogram 3", 100, 0, 100);
    TH1F *hist4 = new TH1F("hist4", "Histogram 4", 100, 0, 100);
}