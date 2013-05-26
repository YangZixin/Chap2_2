void Dopen()
{
	TCanvas *c = new TCanvas("c","Slice's landing length",0,0,700,600);
	TGraph2D *dt = new TGraph2D("slice_x_-5to0.dat");
//	gStyle->SetPalette(1);
	dt->Draw("AC");
//	return c;
}

