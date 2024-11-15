#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TStyle.h>

void WidmoCsBin(std::string filename = "Cs-137.bin"){
    // Otwieranie pliku
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if(!file.is_open()){
        std::cerr << "File not found" << std::endl;
        return;
    }
    else{
        std::cout << "File opened" << std::endl;
    }

    std::vector<double> y;
    double value;

    // Odczytanie danych z pliku binarnego
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        y.push_back(value);
        std::cout << value << std::endl;  
    }

    file.close();

    // Tworzenie histogramu
    TH1F *hist = new TH1F("hist", "Widmo Cs-137", 1024, 0, 2000);
    for(int i = 0; i < y.size(); i++){
        hist->SetBinContent(i + 1, y[i]);
    }

    for(int i = 1; i <= hist->GetNbinsX(); i++){
        hist->SetBinError(i, sqrt(hist->GetBinContent(i)));
    }

    TCanvas *c1 = new TCanvas("c1", "Widmo Cs-137", 800, 600);

    gStyle->SetOptStat(0);

    hist->Draw();
    
    hist->GetXaxis()->SetTitle("Kanal");
    hist->GetYaxis()->SetTitle("Zliczenia");

    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();

    hist->GetXaxis()->SetRangeUser(0, 1024);
    hist->GetYaxis()->SetRangeUser(0, 1700);

    c1->cd();  

    // Dodanie linii i etykiet
    TLine *l1 = new TLine(511, 0, 511, 1250);
    l1->SetLineColor(kRed);
    l1->SetLineWidth(2);
    l1->SetLineStyle(2);
    l1->Draw("same");

    TLine *l2 = new TLine(355, 0, 355, 450);
    l2->SetLineColor(kRed);
    l2->SetLineWidth(2);
    l2->SetLineStyle(2);
    l2->Draw("same");

    TText *label1 = new TText(240+80, 1220, "662 keV - photopeak");
    label1->SetTextColor(kRed);
    label1->SetTextSize(0.02);
    label1->Draw();

    TText *label2 = new TText(40+100, 420, "482 keV - Compton edge");
    label2->SetTextColor(kRed);
    label2->SetTextSize(0.02);
    label2->Draw();

    // Zapisywanie histogramu i canvasu
    c1->SetGrid();
    c1->Update();
    c1->Draw();
    c1->SaveAs("Canvas_WidmoCsBin.root");
    hist->SaveAs("Hist_WidmoCsBin.root");
    std::cout << "File saved" << std::endl;
    
    delete c1;
    delete hist;
}