class mySignal
{
public:
    int channel;
    double energy;
    double t0;
    double tot;

    mySignal(): channel(0), energy(0), t0(0), tot(0) {}
    mySignal(int ch, double en, double t, double to): channel(ch), energy(en), t0(t), tot(to) {}
    ~mySignal() {}
};


void saveSignal(const std::string& filename = "data.txt")
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "File not found" << std::endl;
        return;
    }
    else
    {
        std::cout << "File opened" << std::endl;
    }

    std::string header;
    std::getline(file, header);

    TFile *fout = new TFile("signals.root", "RECREATE");
    TTree *tree = new TTree("T", "Signals");

    mySignal s;
    tree->Branch("channel", &s.channel, "channel/I");
    tree->Branch("energy", &s.energy, "energy/D");
    tree->Branch("t0", &s.t0, "t0/D");
    tree->Branch("tot", &s.tot, "tot/D");

    while (file >> s.channel >> s.t0 >> s.energy >> s.tot) {
        tree->Fill(); // Fill tree with current signal object
    }

    // Close the input file
    file.close();

    // Write the tree and close the ROOT file
    tree->Write();
    fout->Close();

    std::cout << "Data saved to signals.root" << std::endl;
}



