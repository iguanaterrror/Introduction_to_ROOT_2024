#include <TH1F.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <THStack.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TGraph.h>

void HistogramStack() {
    THStack *stack = new THStack("stack", "Stacked Histograms");

    // Tworzenie histogramów
    TH1F *hist1 = new TH1F("hist1", "Gaussian Distribution", 100, -5, 5);
    TH1F *hist2 = new TH1F("hist2", "Exponential Distribution", 100, -5, 5);
    TH1F *hist3 = new TH1F("hist3", "Landau Distribution", 100, -5, 5);
    TH1F *hist4 = new TH1F("hist4", "Linear Distribution (pol1)", 100, -5, 5);

    // Wypełnianie histogramów losowymi danymi
    hist1->FillRandom("gaus", 1000);
    hist2->FillRandom("expo", 1000);
    hist3->FillRandom("landau", 500);
    hist4->FillRandom("pol1", 500);

    // Zmiana wyglądu histogramów
    hist1->SetFillColor(kRed);           
    hist1->SetLineColor(kBlack);         
    hist1->SetLineWidth(2);              

    hist2->SetFillColor(kBlue);          
    hist2->SetLineColor(kBlack);         
    hist2->SetLineWidth(2);              
    hist3->SetFillColor(kGreen);         
    hist3->SetLineColor(kBlack);         
    hist3->SetLineWidth(2);              
    hist4->SetFillColor(kOrange);        
    hist4->SetLineColor(kBlack);         
    hist4->SetLineWidth(2);              
    
    // Dodanie histogramów do stacka
    stack->Add(hist1);
    stack->Add(hist2);
    stack->Add(hist3);
    stack->Add(hist4);
    
    TCanvas *c1 = new TCanvas("c1", "Histogram Stack", 800, 600);
 
    // Rysoawnie stacka
    c1->cd();
    stack->Draw("nostack");

    c1->SetGrid();                

    // Dodawanie legendy
    TLegend *leg = new TLegend(0.15, 0.65, 0.3, 0.85);
    leg->AddEntry(hist1, "Gaussian", "f");
    leg->AddEntry(hist2, "Exponential", "f");
    leg->AddEntry(hist3, "Landau", "f");
    leg->AddEntry(hist4, "Linear (pol1)", "f");
    leg->SetFillColor(0);                
    leg->Draw();

    //
    c1->Update();
    c1->Draw();
    c1->WaitPrimitive();

    delete c1;
    delete stack;
    delete hist1;
    delete hist2;
    delete hist3;
    delete hist4;
    delete leg;
}