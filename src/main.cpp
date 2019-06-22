#include "Team9.h"

using namespace std;
int main()
{
	Team9 *team9 = new Team9();
	//	team9->showlist();
        cout<<"Main Test"<<endl;
	team9->average();
	team9->max();
	team9->min();
	team9->mediane();
        double q = team9->quartil(3);
         cout<<"quartil 3: "<<q<<endl;
       // team9->quantile(2,4);
        q = team9->centil(25);
          cout<<"centil 25: "<<q<<endl;
        q = team9->decil(2);
          cout<<"decil 2: "<<q<<endl;
	 team9->mode();
	 team9->variance();
	// team9->splitList();
        team9->histogramClassLowerLimit(2);
        team9->histogramClassLowerLimit(3);
        team9->histogramClassLowerLimit(2);
        q = team9->stddeviation();
         cout<<"stddeviation: "<<q<<endl;
        q=team9->variationCoef();
         cout<<"variationCoef: "<<q<<endl;
        q=team9->newSampleSize(0.95, 5);
         cout<<"newSampleSize: "<<q<<endl;
        q=team9->histogramNumClasses();
         cout<<"numClasses: "<<q<<endl;
        q=team9->histogramClassFrequency(3);
         cout<<"frequency class 3: "<<q<<endl;
        q=team9->halfWidthConfidenceInterval(0.95);
         cout<<"erroPAdrao(.95): "<<q<<endl;
	delete team9;

	return 0;
}
