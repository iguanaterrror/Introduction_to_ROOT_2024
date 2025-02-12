void readTree(const std::string& filename = "signals.root", const std::string& output_filename = "output_signals.root") {
    TFile *f = TFile::Open(filename.c_str());
    if (!f || f->IsZombie()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    TTree *tree = (TTree*)f->Get("T");
    if (!tree) {
        std::cerr << "Could not find tree in file: " << filename << std::endl;
        return;
    }

    std::set<int> channels;
    int channel;
    double energy, tot, t0;
    tree->SetBranchAddress("energy", &energy);
    tree->SetBranchAddress("tot", &tot);
    tree->SetBranchAddress("t0", &t0);
    tree->SetBranchAddress("channel", &channel);

    Long64_t nentries = tree->GetEntries();

    // Loop over all entries and store the channels
    for (Long64_t i = 0; i < nentries; ++i) {
        tree->GetEntry(i);
        std::cout << "Channel: " << channel << std::endl;
        channels.insert(channel);
    }
    
    // Find max values for dynamic binning
    double max_energy = 0, max_tot = 0, max_t0 = 0, min_energy = 1e9, min_tot = 1e9, min_t0 = 1e9;
    for (Long64_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        max_energy = std::max(max_energy, energy);
        max_tot = std::max(max_tot, tot);
        max_t0 = std::max(max_t0, t0);

        min_energy = std::min(min_energy, energy);
        min_tot = std::min(min_tot, tot);
        min_t0 = std::min(min_t0, t0);
    }
    std::cout << "Max energy: " << max_energy << ", Max TOT: " << max_tot << ", Max T0: " << max_t0 << std::endl;

    // Create a new ROOT file to save the histograms
    TFile *outputFile = new TFile(output_filename.c_str(), "RECREATE");

    


    std::cout << "Found " << channels.size() << " unique channels" << std::endl;
    // Create histograms and fill them
    for (int ch : channels) {
        std::cout << "Creating histograms for channel: " << ch << std::endl;
        std::string energy_histname = "energy_channel_" + std::to_string(ch);
        std::string tot_histname = "tot_channel_" + std::to_string(ch);
        std::string t0_histname = "t0_channel_" + std::to_string(ch);

        // Create histograms with dynamic range based on the data
        TH1F *energy_hist = new TH1F(energy_histname.c_str(), energy_histname.c_str(), 100, min_energy*0.9, max_energy * 1.2);
        TH1F *tot_hist = new TH1F(tot_histname.c_str(), tot_histname.c_str(), 100, min_tot*0.9, max_tot * 1.2);
        TH1F *t0_hist = new TH1F(t0_histname.c_str(), t0_histname.c_str(), 100, min_t0*0.9, max_t0 * 1.2);

        // Loop to fill histograms
        for (Long64_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            if (channel == ch) {
                energy_hist->Fill(energy);
                tot_hist->Fill(tot);
                t0_hist->Fill(t0);
            }
        }

        // Save histograms to the output file
        energy_hist->Write();
        tot_hist->Write();
        t0_hist->Write();
    }

    // Close the output file
    outputFile->Close();

    f->Close();
}
