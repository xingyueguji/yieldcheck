#include "src/readReport.cpp"
//#include "dataYield.cpp"

void testLoop(){

  for (Int_t i=2480;i<3102;i++)
    {
      Double_t target=readReport(i,"target");
      //      if(readReport(i,"target")==target && readReport(i,"mom")==mom && readReport(i,"Spec Angle")==angle)
      if(target==12.01)
	{
	cout <<i<<"\t"<<readReport(i,"mom")<<"\t"<<readReport(i,"Spec Angle")<<"\t"<<target<<"\t"<<readReport(i,"Ps2 fact")<<endl;
	}
    }
  return;
}
