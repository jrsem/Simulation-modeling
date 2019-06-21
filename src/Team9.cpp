/*
https://www.geeksforgeeks.org/list-cpp-stl/
https://pt.cppreference.com/w/cpp/container/list
*/
#include "Team-9.h"
#include <numeric>   //accumulate()
#include <algorithm> //max_element()
#include <math.h>    //fmod()
#include <map>       //map<>
using namespace std;

double Team9::getSample_size()
{
  sample_size = sample.size();
  cout << "data size:" << sample_size << endl;
  return sample_size;
};

double Team9::average()
{
  double sum = accumulate(std::begin(sample), end(sample), 0.0);
  _everage = sum / sample_size; //data.size;
  cout << "media:" << _everage << endl;
  return _everage;
};

Team9::Team9()
{
  read_file();
  Team9::ordoredList();
  getSample_size();
};

double Team9::max()
{
  _max = *max_element(sample.begin(), sample.end());
  cout << "max:" << _max << endl;
  return _max;
};

double Team9::min()
{
  _min = *min_element(sample.begin(), sample.end());
  cout << "min:" << _min << endl;
  return _min;
};

double Team9::mediane()
{
  // Team9::ordoredList();
  if (fmod(sample_size, 2) == 0)
  {
    list<double>::iterator right = next(sample.begin(), ((sample_size / 2)) - 1);
    list<double>::iterator left = next(sample.begin(), ((sample_size / 2)));
    cout << "right" << *right << endl;
    cout << "left" << *left << endl;
    _mediane = ((*right) + (*left)) / 2;
    cout << "mediane dois dois:" << _mediane << endl;
    return _mediane;
  }
  else
  {
    list<double>::iterator center = next(sample.begin(), ((sample_size) / 2));
    _mediane = *center;
    cout << "center mediane:" << _mediane << endl;
    return _mediane;
  }
};

double Team9::mode()
{

  std::map<double, double> mydict = {};
  double cnt = 0;
  double itm = 0; // in Python you made this a string '', which seems like a bug

  for (auto &&item : sample)
  {
    mydict[item] = mydict.emplace(item, 0).first->second + 1;
    if (mydict[item] >= cnt)
    {
      tie(cnt, itm) = tie(mydict[item], item);
    }
  }
  //TODO pode ter mais de um mode ou seja 2 ou mais numero com mesma frequencia
  cout << "more freqent:" << itm << endl;
  _mode = itm;
  return itm;
};

double Team9::variance()
{
  double var = 0;
  double sd = 0;
  //duvida : é melhor utiliza mean ou everage?
  for (auto &&item : sample)
  {
    var += (item - _everage) * (item - _everage);
  }
  var /= sample_size;
  sd = sqrt(var); //desvio padrão
  cout << "variancia:" << var << endl;
  cout << "desvio padrão" << sd << endl;
  return var;
};
double Team9::centil(unsigned short num){};

//==================

// double Team9::decil(unsigned short num){};
// double Team9::halfWidthConfidenceInterval(double confidencelevel){};
// unsigned int Team9::histogramClassFrequency(unsigned short classNum){};
// double Team9::histogramClassLowerLimit(unsigned short classNum){};
// unsigned short Team9::histogramNumClasses(){};

// unsigned int Team9::newSampleSize(double confidencelevel, double halfWidth){};
// double Team9::quartil(unsigned short num){};
// void Team9::setHistogramNumClasses(unsigned short num){};
// double Team9::stddeviation(){};

// double Team9::variationCoef(){};

//===
/*
data.push_back(i * 2); 
data.push_front(i * 3); 

data.front();  
data.back(); 

showlist(data); 
*/

//print the STL list
void Team9::showlist()
{
  for (auto &&item : sample)
    cout << '\t' << item;
  cout << '\n';
};

void Team9::read_file()
{
  list<double>::iterator it;
  string line;
  double convert_Number;
  ifstream myfile;
  myfile.open("./data/data.txt");
  if (myfile.is_open())
  {
    while (myfile.eof() == false)
    {
      myfile >> convert_Number;
      this->sample.push_back(convert_Number);
    }
    myfile.close();
  }
  else
    cout << "Error opening file\n";
  //================================
  // ifstream myfile("./data/data.txt");
  // if (myfile.is_open())
  // {
  //   while (myfile.good())
  //   {
  //     getline(myfile, line);
  //     cout << line << endl;
  //     convert_Number == stoi(line);
  //     this->data.push_front(convert_Number);
  //   }
  //   myfile.close();
  // }

  // else
  //   cout << "Unable to open file";
  //======================
  // fstream fs("./data/data.txt", std::fstream::in); //input file
  // double k;
  // while (fs >> k)
  // {
  //   cout << "value" << k;
  //   this->data.push_front(k);
  // }
  // fs.close();
}
// double Team9::mean()
// {
//   double result = 0;
//   for (auto &&item : data)
//   {
//     result += item;
//   }
//   calculed_mean = result;
//   cout<<"a media:"<<calculed_mean<<endl;
//   return result;
// }

void Team9::ordoredList()
{
  sample.sort();
};

void Team9::splitList()
{
  list<double>::iterator right = next(sample.begin(), ((sample_size / 2)) - 1);
  list<double>::iterator left = next(sample.begin(), ((sample_size / 2)));
  int i, j, limit, pos = 0;
  double Q2;
  list<double> auxList = {};
  list<double>::iterator ptr;
  //Q2
  Q2 = _mediane;

  //the list is par
  limit = (int)(sample_size / 2);
  for (i = 0; i < limit; i++)
  {
    ptr = next(sample.begin(), i);
    auxList.push_front(*ptr);
  }
  classes.push_front(auxList);

  //point ptr to limit posistion in the data

  for (auto &&item : auxList)
    cout << '\t' << item;
  cout << '\n';
};
//===