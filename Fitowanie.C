#include <iostream>


// definicja funkcji
Double_t custom_fun(Double_t *x, Double_t *par)
{
    Double_t gauss_1 = par[0]*exp(-0.5*(pow(((x[0]-par[1])/par[2]),2)));
    Double_t gauss_2 = par[3]*exp(-0.5*(pow(((x[0]-par[4])/par[5]),2)));
    Double_t gauss_3 = par[8]*exp(-0.5*(pow(((x[0]-par[9])/par[10]),2)));
    Double_t bg = exp(par[6]+par[7]*x[0]);
    
    return gauss_1+gauss_2+bg;
}

// odczytanie histogramu z pliku ROOT i fitowannie
Bool_t Fitowanie(TString fname = "Hist_WidmoCs.root", TString hname = "hist")
{
    
    TFile *fin = new TFile(fname, "READ");
    
    if(!fin->IsOpen())
    {
        std::cerr << "Could not open file: " << fname << std::endl;
        return kFALSE;
    }
    
    TH1F *hist = (TH1F*)fin->FindObjectAny(hname);
    hist->Print();
    
    TF1 *fun = new TF1("custom_fun", custom_fun, 0, 1000, 8);
    TF1 *fun2 = new TF1("custom_fun", custom_fun, 400, 600, 8);
    fun->SetParameter(0, 1400);  // Amplitude of first Gaussian
    fun->SetParameter(1, 75);  // Mean of first Gaussian (center of the peak)
    fun->SetParameter(2, 25);   // Sigma (width) of first Gaussian
    fun->SetParameter(3, 1200); // Amplitude of second Gaussian
    fun->SetParameter(4, 500);  // Mean of second Gaussian
    fun->SetParameter(5, 30);   // Sigma (width) of second Gaussian
    fun->SetParameter(6, 7);    // Background parameter (scale)
    fun->SetParameter(7, -0.005); // Background parameter (slope)
    
    
    hist->Fit(fun, "R", "", 0, 600);
    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    hist->Draw();
    Double_t peak1 = fun->GetParameter(1);
    std::cout << "Peak 1: " << peak1 << std::endl;
    Double_t peak2 = fun->GetParameter(4);
    Double_t peak1_err = fun->GetParError(1);
    Double_t peak2_err = fun->GetParError(4);
    Double_t channels[2] = {peak1, peak2};
    Double_t channels_err[2] = {peak1_err, peak2_err};
    Double_t energies[2] = {32, 662};
    Double_t energies_err[2] = {0, 0};
    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
    TGraphErrors *gr = new TGraphErrors(2, channels, energies, channels_err, energies_err);
    TF1 *lin = new TF1("lin", "[0]*x+[1]", 0, 1024);
    lin->SetParameter(0, 1);
    lin->SetParameter(1, 0);
    gr->Fit(lin, "R");
    gr->SetTitle("Kalibracja");
    gr->GetXaxis()->SetTitle("Kanał");
    gr->GetYaxis()->SetTitle("Energia [keV]");
    gr->SetMarkerStyle(20);

    gr->Draw("AP");


    Double_t a = lin->GetParameter(0);
    Double_t b = lin->GetParameter(1);
    Int_t n = hist->GetNbinsX();
    std::cout << "a: " << a << " b: " << b << std::endl;
    std::cout <<"n"<<n<<std::endl;
    TH1F *hist2 = new TH1F("hist2", "hist2", n, 0, n);
    
    for(Int_t i = 1; i <= n; i++)
    {
        Double_t x = hist->GetBinCenter(i);
        Double_t y = hist->GetBinContent(i);
        Double_t y_err = hist->GetBinError(i);
        Double_t bin = a*x + b;
        hist2->SetBinContent(bin, y);
        hist2->SetBinError(bin, y_err);
        
    }
    
    TCanvas *c4 = new TCanvas("c4", "c4", 800, 600);
    hist2->SetLineColor(kGreen);
    hist2->SetMarkerColor(kGreen);
    hist2->SetMarkerStyle(20);
    hist2->SetMarkerSize(0.5);
    hist2->SetTitle("Kalibracja");
    hist2->GetXaxis()->SetTitle("Energia [keV]");
    hist2->GetYaxis()->SetTitle("Ilość zliczeń");
    hist2->GetXaxis()->CenterTitle();
    hist2->GetYaxis()->CenterTitle();
    hist2->Draw();

    c4->cd();

    // Rysowanie linii
    TLine *l1 = new TLine(662, 0, 662, 1500);
    l1->SetLineColor(kRed);
    l1->SetLineWidth(2);
    l1->SetLineStyle(2);
    l1->Draw("same");

    TLine *l2 = new TLine(482, 0, 482, 1500);
    l2->SetLineColor(kRed);
    l2->SetLineWidth(2);
    l2->SetLineStyle(2);
    l2->Draw("same");

    TLine *l3 = new TLine(32, 0, 32, 1500);
    l3->SetLineColor(kRed);
    l3->SetLineWidth(2);
    l3->SetLineStyle(2);
    l3->Draw("same");

    TLine *l4 = new TLine(180, 0, 180, 1500);
    l4->SetLineColor(kRed);
    l4->SetLineWidth(2);
    l4->SetLineStyle(2);
    l4->Draw("same");

    


   
    return kTRUE;
}