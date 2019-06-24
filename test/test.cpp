#include "Team9.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

using namespace std;
int main()
{
	cout << "Executing tests. " << endl;
	Team9 *team9 = new Team9("./data/datahuge.txt");
	assert(team9->average() >= 5000325.942097 && team9->average() <= 5000325.942098);
	assert(team9->max() == 7145890);
	assert(team9->min() == 2859480);
	assert(team9->median() == 5000300);
	assert(team9->quartil(3) == 5337270);
	assert(team9->centil(25) == 4662920);
	assert(team9->decil(2) == 4579680);
	assert(team9->mode() == 4993250);
	assert(team9->variance() >= 249472695237.867218 && team9->variance() <= 249472695237.867219);
	assert(team9->stddeviation() <= 499472.416894 && team9->stddeviation() >= 499472.416893);
	assert(team9->variationCoef() <= 0.099888 && team9->variationCoef() >= 0.099887);
	assert(team9->newSampleSize(0.95, 5) == 3975233873);
	assert(team9->histogramNumClasses() == 22);
	assert(team9->histogramClassFrequency(3) == 4593);
	assert(team9->halfWidthConfidenceInterval(0.95) <= 692.233280 && team9->halfWidthConfidenceInterval(0.95) >= 692.233279);

	cout << "Congratulations! Everything worked!" << endl;
	
	delete team9;

	return 0;
}

