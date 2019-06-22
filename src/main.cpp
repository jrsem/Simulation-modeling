#include "Team9.h"
int main()
{
	Team9 *team9 = new Team9();
	//	team9->showlist();
        double err = team9->halfWidthConfidenceInterval(0.80);
        cout<<"erroPAdrao: "<<err<<endl;
	team9->average();
	team9->max();
	team9->min();
	team9->mediane();
        team9->quartil(4);
        team9->quantile(2,4);
        team9->centil(25);
        team9->decil(2);
	 team9->mode();
	 team9->variance();
	// team9->splitList();
        team9->histogramClassLowerLimit(2);
        team9->histogramClassLowerLimit(3);
        team9->histogramClassLowerLimit(2);
        team9->stddeviation();
        team9->variationCoef();
        team9->newSampleSize(0.95, 5);
        team9->histogramNumClasses();
        team9->histogramClassLowerLimit(3);
        team9->histogramClassFrequency(3);
        team9->halfWidthConfidenceInterval(0.95);
	delete team9;

	return 0;
}
