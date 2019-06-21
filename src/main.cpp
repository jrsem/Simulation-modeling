#include "Team-9.h"
int main()
{
	Team9 *team9 = new Team9();
	//	team9->showlist();
	team9->average();
	team9->max();
	team9->min();
	//team9->mediane();
	// team9->mode();
	// team9->variance();
	// team9->splitList();
	delete team9;

	return 0;
}
