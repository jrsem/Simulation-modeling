#include "Team9.h"

using namespace std;
int main()
{
	Team9 *team9 = new Team9("./data/datahuge.txt");
  cout<<"Main Test"<<endl;
	cout << "media: " << fixed << team9->average() << endl;
	cout << "max: " << team9->max() << endl;
	cout << "min: " << team9->min() << endl; 
	cout << "mediane: " << team9->mediane() << endl; 
  cout << "quartil 3: "<< team9->quartil(3) <<endl;
  cout << "centil 25: "<< team9->centil(25) <<endl;
  cout << "decil 2: "<< team9->decil(2) <<endl;
	cout << "more freqent: " << team9->mode() << endl;
	cout << "variancia: " << team9->variance() << endl;
  team9->histogramClassLowerLimit(2);
  team9->histogramClassLowerLimit(3);
  team9->histogramClassLowerLimit(2);
  cout<<"stddeviation: "<< team9->stddeviation() <<endl;
  cout << "variationCoef: "<< team9->variationCoef() <<endl;
  cout << "newSampleSize: "<< team9->newSampleSize(0.95, 5) <<endl;
  cout<<"numClasses: "<< team9->histogramNumClasses() <<endl;
  cout << "frequency class 3: "<< team9->histogramClassFrequency(3) <<endl;
  cout<<"erroPAdrao(.95): "<< team9->halfWidthConfidenceInterval(0.95) <<endl;  
	delete team9;

	return 0;
}
