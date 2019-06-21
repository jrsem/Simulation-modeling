#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;

class Team9
{
  list<double> sample = {};
  list<list<double>> classes = {};

private:
  double sample_size;
  double _everage;
  double _max;
  double _min;
  double _mediane;
  double _mode;
  //double

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
  double min();
  double mode();
  unsigned int newSampleSize(double confidencelevel, double halfWidth);
  double quartil(unsigned short num);
  void setHistogramNumClasses(unsigned short num);
  double stddeviation();
  double variance();
  double variationCoef();
  //===
  // int read_file();
  void showlist(list<double> data);
  void splitList();
  void ordoredList();
  double getSample_size();
  void showlist();
  void read_file();
  //===
};