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

//#include "Team-9.h"
#include <numeric>   //accumulate()
#include <algorithm> //max_element()
#include <math.h>    //fmod()
#include <map>       //map<>
using namespace std;

Team9::Team9()
{
    //Inicializa Tabela com valores de Z.
  populateZCriticalValues();
  
  read_file();
  //Team9::sortList();
  numElements();
};

void Team9::read_file()
{
  double convert_Number;
  ifstream myfile;
  try{
    myfile.open("./data/dataTest.txt");
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
  }
  catch(int e){
        cout << "Error nro "<<e<<endl;
        throw;
  }
  
  // NEW SAMPLE, RESET ALL
  _minReady = false;
  _maxReady = false;
  _avgReady = false;
  _medianeReady = false;
  _modeReady = false;
  _sampleSorted = false;
  _stddevReady = false;
  _varianceReady = false;
  cVReady = false;
  _histoNumClassesReady = false;
  histoCLLReady = false;
  
  mapClassLowerLimit.clear();
  mapQuartilCalculated.clear();
  mapDecilCalculated.clear();
  mapCentilCalculated.clear();
  mapConfidenceHalfWidthCalculated.clear();
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
        double N = Team9::numElements();
        for(auto &&item:sample){
            _average += item/N;
        }
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

double Team9::mediane_bkp()
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

double Team9::mediane()
{
    if(!_medianeReady){
        _mediane = Team9::quantile(1,2);
        _medianeReady = true;
    }
    return _mediane;
};
double Team9::mode()
{
    if(!_modeReady){
        std::map<double, double> mydict = {};
        double cnt = 0;
        double itm = 0; // 

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
        _variance /= _numElements-1;
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
double Team9::halfWidthConfidenceInterval(double confidencelevel){
    if(mapConfidenceHalfWidthCalculated[confidencelevel]==0){     
        double z = zScore[confidencelevel];
        if(z==0)
            throw("Confidence Interval not available.");
 
        _halfWidthConfidenceInterval = z * Team9::stddeviation() / sqrt(Team9::numElements());
        mapConfidenceHalfWidthCalculated.insert(pair<double,double> (confidencelevel,_halfWidthConfidenceInterval));
    }
    else
        _halfWidthConfidenceInterval = mapConfidenceHalfWidthCalculated[confidencelevel];
    //cout<<"Z= "<<zScore[confidencelevel]<<endl;
    return _halfWidthConfidenceInterval;
};
unsigned int Team9::newSampleSize(double confidencelevel, double halfWidth){
    double z2 = pow(zScore[confidencelevel],2);
    double hW2 = pow(halfWidth,2);
 
    _newSampleSize = z2 * Team9::variance() / hW2;

    return _newSampleSize;
};

double Team9::quartil(unsigned short num){
    if(num<1 || num>3)
     throw invalid_argument("Quartil value must be between 1 and 3.");
    //verifica se ja foi calculado, se não, insere no map.
    if(mapQuartilCalculated[num]==0){
        _quartil = Team9::quantile(num, 4);
        mapQuartilCalculated.insert(pair<unsigned short, double>(num, _quartil));
    }
    else
       _quartil = mapQuartilCalculated[num]; 
    return _quartil;
};
double Team9::decil(unsigned short num){
     if(num<1 || num>10)
        throw invalid_argument("Decil value must be between 1 and 10.");
     //verifica se ja foi calculado, se não, insere no map.
    if(mapDecilCalculated[num]==0){
        _decil = Team9::quantile(num, 10);
        mapDecilCalculated.insert(pair<unsigned short, double>(num, _decil));
    }
    else
       _decil = mapDecilCalculated[num]; 
    
    return _decil;
};
double Team9::centil(unsigned short num){
     if(num<1 || num>100)
        throw invalid_argument("Centil value must be between 1 and 100.");
     //verifica se ja foi calculado, se não, insere no map.
    if(mapCentilCalculated[num]==0){
        _centil = Team9::quantile(num, 100);
        mapCentilCalculated.insert(pair<unsigned short, double>(num, _centil));
    }
    else
       _centil = mapCentilCalculated[num]; 
    
    return _centil;
};

double Team9::quantile(unsigned short num, unsigned short subsets){
     if(!_sampleSorted)
            Team9::sortList();
     
    double n = Team9::numElements();
    double position =  num * (n+1)/ subsets;
    double integ;
    double fraction;
    fraction = modf(position, &integ);
    list<double>::iterator pos = next(sample.begin(), integ-1);
    if(fraction > 0){
        //fracionario, fazer interpolacao
         
         list<double>::iterator posAfter = next(sample.begin(), integ);
         _quantile = (*pos + *posAfter)/2;
    }
    else{
        _quantile = *pos;
    }
    //cout<<"quantile:"<<_quantile<<endl;
    return _quantile;
}

void Team9::setHistogramNumClasses(unsigned short num){
    _histogramNumClasses = num;
    //Novo numero de classes setado, valores calculador anteriormente não servem mais.
    mapClassLowerLimit.clear();
    _amplitudeReady = false;
};
unsigned short Team9::histogramNumClasses(){
     if(!_histoNumClassesReady){
         double n = Team9::numElements();
         if(n<=25)
             _histogramNumClasses = 5;
         else
            //regra de Sturges para o nro de classes
            _histogramNumClasses = round(1 + 3.32*log10(n));
        _histoNumClassesReady = true;
    }
    return _histogramNumClasses;
};
// 

double Team9::getClassAmplitude(){
    if(!_amplitudeReady){
        if(_histogramNumClasses==0)
                 //Se o numero de classes nao foi definido manualmente, faz o calculo
                 _histogramNumClasses = Team9::histogramNumClasses();

        double minValue = Team9::min();
        double maxValue = Team9::max();
        _amplitude = ceil((maxValue-minValue)/_histogramNumClasses);
        _amplitudeReady = true;
    }
    
    return _amplitude;
}
//Classes do histograma iniciam em 0.
 double Team9::histogramClassLowerLimit(unsigned short classNum){
     if(mapClassLowerLimit.count(classNum)==0){//verifica se já foi calculado antes
         
         
         _histogramClassLowerLimit = Team9::min() + (classNum)* Team9::getClassAmplitude();
         mapClassLowerLimit.insert( pair<unsigned short,double>(classNum, _histogramClassLowerLimit) );
          cout << "calculou Lower Limit: " <<_histogramClassLowerLimit <<" da clase " <<classNum<< endl;
  
     }
     else{
         _histogramClassLowerLimit = mapClassLowerLimit[classNum];
         cout << "recuperou Lower Limit: " <<_histogramClassLowerLimit <<" da clase " <<classNum<< endl;
     }
       return _histogramClassLowerLimit;
 };
unsigned int Team9::histogramClassFrequency(unsigned short classNum){
     if(mapClassFrequency.count(classNum)==0){//verifica se já foi calculado antes
         double lowerLimit = Team9::histogramClassLowerLimit(classNum);
         double upperLimit = lowerLimit + Team9::getClassAmplitude();
         unsigned int frequency = 0;
         for (auto &&value : sample){
             if(value >= lowerLimit && value < upperLimit )
                 frequency++;
         }
        
         _histogramClassFrequency = frequency;
         mapClassFrequency.insert( pair<unsigned short,unsigned int>(classNum, _histogramClassFrequency) );
       
     }
     else{
         _histogramClassFrequency = mapClassFrequency[classNum];
        
     }
     return _histogramClassFrequency;
};
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

void Team9::populateZCriticalValues(){
    zScore.insert( pair<double, double>(0.70, 1.04) );
    zScore.insert( pair<double, double>(0.75, 1.15) );
    zScore.insert( pair<double, double>(0.80, 1.28) );
    zScore.insert( pair<double, double>(0.85, 1.44) );
    zScore.insert( pair<double, double>(0.90, 1.645) );
    zScore.insert( pair<double, double>(0.92, 1.75) );
    zScore.insert( pair<double, double>(0.95, 1.96) );
    zScore.insert( pair<double, double>(0.96, 2.05) );
    zScore.insert( pair<double, double>(0.98, 2.33) );
    zScore.insert( pair<double, double>(0.99, 2.58) );
}
//===

