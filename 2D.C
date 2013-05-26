void Dopen()
{
	TCanvas *c = new TCanvas("c","omega",0,0,700,600);
	TGraph *dt = new TGraph("bestOmegaS.dat");
//	gStyle->SetPalette(1);
	dt->Draw("AC");
//	return c;
}

