/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Team9.cpp
 * Author: LENOVO
 * 
 * Created on 21 de Junho de 2019, 16:21
 */

#include "Team9.h"

/*
https://www.geeksforgeeks.org/list-cpp-stl/
https://pt.cppreference.com/w/cpp/container/list
*/
//#include "Team-9.h"
#include <numeric>   //accumulate()
#include <algorithm> //max_element()
#include <math.h>    //fmod()
#include <map>       //map<>
using namespace std;

Team9::Team9()
{
  populateZCriticalValues();
  
  read_file();
  //Team9::sortList();
  numElements();
};

void Team9::read_file()
{
  list<double>::iterator it;
  string line;
  double convert_Number;
  ifstream myfile;
  //TODO TRY CaTCH
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

  //TODO NEW SAMPLE, RESET ALL
}



unsigned int Team9::numElements()
{
  _numElements = sample.size();
  cout << "data size:" << _numElements << endl;
  return _numElements;
};

double Team9::average()
{
    if(!_avgReady){
        double sum = accumulate(std::begin(sample), end(sample), 0.0);
        _average = sum / _numElements; //data.size;
        cout << "media:" << _average << endl;
        _avgReady = true;
    }
    return _average;
};

double Team9::max()
{
    if(!_maxReady){
        _max = *max_element(sample.begin(), sample.end());
        cout << "max:" << _max << endl;
        _maxReady = true;
    }
    return _max;
};

double Team9::min()
{
    if(!_minReady){
        _min = *min_element(sample.begin(), sample.end());
        cout << "min:" << _min << endl;
        _minReady = true;
    }
    return _min;
};

double Team9::mediane()
{
    if(!_medianeReady){
        
        if(!_sampleSorted)
            Team9::sortList();

        if (fmod(_numElements, 2) == 0)
        {
          list<double>::iterator right = next(sample.begin(), ((_numElements / 2)) - 1);
          list<double>::iterator left = next(sample.begin(), ((_numElements / 2)));
          cout << "right" << *right << endl;
          cout << "left" << *left << endl;
          _mediane = ((*right) + (*left)) / 2;
          cout << "mediane dois dois:" << _mediane << endl;

        }
        else
        {
          list<double>::iterator center = next(sample.begin(), ((_numElements) / 2));
          _mediane = *center;
          cout << "center mediane:" << _mediane << endl;

        }
        _medianeReady = true;
    }
    return _mediane;
};

double Team9::mode()
{
    if(!_modeReady){
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
        _modeReady = true;
    }
    return _mode;
};

double Team9::variance()
{
    if(!_varianceReady){
        _variance = 0;
        double avg = average();
        //duvida : é melhor utiliza mean ou everage?
        for (auto &&item : sample)
        {
          _variance += (item - avg) * (item - avg);
        }
        _variance /= _numElements;
        //sd = sqrt(var); //desvio padrão
        cout << "variancia:" << _variance << endl;
        //cout << "desvio padrão" << sd << endl;
        _varianceReady = true;
    }
  return _variance;
};

double Team9::stddeviation(){
    if(!_stddevReady){
        _stdDeviation = sqrt(Team9::variance());
        _stddevReady = true;
    }
    
    return _stdDeviation;
};

double Team9::variationCoef(){
    if(!cVReady){
        _variationCoef = Team9::stddeviation()/Team9::average();
        cVReady = true;
    }
    return _variationCoef;
};

//double Team9::centil(unsigned short num){};

//==================

// double Team9::decil(unsigned short num){};
// double Team9::halfWidthConfidenceInterval(double confidencelevel){};
// unsigned int Team9::histogramClassFrequency(unsigned short classNum){};
// double Team9::histogramClassLowerLimit(unsigned short classNum){};
// unsigned short Team9::histogramNumClasses(){};

// unsigned int Team9::newSampleSize(double confidencelevel, double halfWidth){};
// double Team9::quartil(unsigned short num){};
// void Team9::setHistogramNumClasses(unsigned short num){};

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


void Team9::sortList()
{
  sample.sort();
};

void Team9::splitList()
{
    //TODO Chamar funções e não as variaveis
  list<double>::iterator right = next(sample.begin(), ((_numElements / 2)) - 1);
  list<double>::iterator left = next(sample.begin(), ((_numElements / 2)));
  int i, j, limit, pos = 0;
  double Q2;
  list<double> auxList = {};
  list<double>::iterator ptr;
  //Q2
  Q2 = _mediane;

  //the list is par
  limit = (int)(_numElements / 2);
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
void Team9::populateZCriticalValues(){
    zScore.insert( pair<double, double>(0.05, 1.96) );
}
//===

