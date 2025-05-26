void Draw_errors(bool graphN, const int n, double *x, double *yPE, double *yME);
void inputData(bool graphN, double *x, double *y, double *yPE, double *yME);

void errBandPlot() {

  const int n = 10;
  double x1[n], y1[n], yPE1[n], yME1[n];
  double x2[n], y2[n], yPE2[n], yME2[n];


  inputData(0, x1, y1, yPE1, yME1);
  inputData(1, x2, y2, yPE2, yME2);

  TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
  c1->SetGrid();

  TGraph *gLine1 = new TGraph(n,x1,y1);
  gLine1->SetMarkerColor(4);
  gLine1->SetMarkerStyle(21);
  gLine1->GetXaxis()->SetLimits(-0.4, 1.5);
  gLine1->SetMaximum(15.4);
  gLine1->Draw("ALP");   // draw central values
  Draw_errors(0, n, x1, yPE1, yME1);  // draw error area with fillcolor

  TGraph *gLine2 = new TGraph(n,x2,y2);
  gLine2->SetMarkerColor(2);
  gLine2->SetMarkerStyle(8);
  gLine2->Draw("SAME LP");   // draw central values
  Draw_errors(1, n, x2, yPE2, yME2);  // draw error area with fillcolor

  gLine2->Draw("SAME LP");  // re-draw (overwrite) central values
  gLine1->Draw("SAME LP");  // re-draw (overwrite) central values

  //c1->Print("error_band_func.png");
}

void Draw_errors(bool graphN, int n, double *x, double *yPE, double *yME){
  //    x[i], yPE[i], x[n+i], yME[i] 
  const int n2 = 2*n;
  double xx[2*n], yE[2*n];

  for (int dataP=0; dataP < 10; dataP++) {
    xx[dataP]      = x[dataP];
    yE[dataP]     = yPE[dataP];
    xx[2*n-dataP-1]  = x[dataP];
    yE[2*n-dataP-1]  = yME[dataP] ;
  }

  int fillStyle[2] = {3014, 3019};
  int fillColor[2] = {kGreen+1, kOrange+8};

  TGraph *gEBand = new TGraph(2*n, xx,yE);
  gEBand->SetFillColor(fillColor[graphN]);
  gEBand->SetFillStyle(fillStyle[graphN]);
  gEBand->Draw("SAME F");

  return;
} 


void inputData(bool graphN, double *x, double *y, double *yPE, double *yME){

  const int n = 10;
  double inX[n] = {-.22,.05,.25,.35,.5,.61,.7,.85,.99,1.2};
  double inY[n] = {1.0, 2.9, 5.6, 7.4, 9.5, 9.6, 8.7, 6.3, 4.5, 2.5};
  double inYPErr[n] = {1.2, 3.2, 5.9, 7.9,10.2,10.1, 9.5, 6.7, 5.0, 2.9};
  double inYMErr[n] = {0.8, 2.5, 5.0, 6.9, 8.5, 9.0, 8.0, 5.7, 4.0, 2.0};

  for (int dataP=0; dataP < n; dataP++) {
    x[dataP]       =    inX[dataP]  + 0.1*graphN;
    y[dataP]      = (1-graphN) * inY[dataP] + graphN * (11. - inY[dataP]);
    yPE[dataP] =  (1 - graphN) *inYPErr[dataP]  + graphN*(y[dataP] + 10.*inX[dataP]*inX[dataP]);
    yME[dataP] =  (1 - graphN) *inYMErr[dataP] + graphN*(y[dataP] -   3.* abs(inX[dataP]));
  }

}