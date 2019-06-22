#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Team9
{
  list<double> sample = {};
  list<list<double>> classes = {};

private:
  double _numElements;
  double _average;
  double _max;
  double _min;
  double _mediane;
  double _mode;
  double _variance;
  double _stdDeviation;
  double _variationCoef;
  double _halfWidthConfidenceInterval;
  double _newSampleSize;
  double _quantile;
  double _quartil;
  double _decil;
  double _centil;
  unsigned short _histogramNumClasses;
  //double
  bool _minReady = false;
  bool _maxReady = false;
  bool _avgReady = false;
  bool _medianeReady = false;
  bool _modeReady = false;
  bool _sampleSorted = false;
  bool _stddevReady = false;
  bool _varianceReady = false;
  bool cVReady = false;
  bool _histoNumClassesReady = false;

public:
  Team9();
  double average();
  double centil(unsigned short num);
  double decil(unsigned short num);
  double halfWidthConfidenceInterval(double confidencelevel);
  unsigned int histogramClassFrequency(unsigned short classNum);
  double histogramClassLowerLimit(unsigned short classNum);
  unsigned short histogramNumClasses();
  double max();
  double mediane();
  double mediane_bkp();
  double min();
  double mode();
  unsigned int newSampleSize(double confidencelevel, double halfWidth);
  double quartil(unsigned short num);
  void setHistogramNumClasses(unsigned short num);
  double stddeviation();
  double variance();
  double variationCoef();
  map<double,double> zScore;
  void populateZCriticalValues();
  double quantile(unsigned short num, unsigned short subsets);
  //===
  // int read_file();
  void showlist(list<double> data);
  void splitList();
  void sortList();
  unsigned int numElements();
  void showlist();
  void read_file();
  //===
};
