/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Team9.cpp
 * Author: LENOVO
 * 
 * Created on 13 de Junho de 2019, 16:21
 */

#include "Team9.h"

//#include "Team-9.h"
#include <numeric>   //accumulate()
#include <algorithm> //max_element()
#include <math.h>    //fmod()
#include <map>       //map<>
using namespace std;

/**
 * @brief Construct a new Team 9:: Team 9 object
 * 
 */
Team9::Team9(string path)
{
    //Initialize Table with z values.
  populateZCriticalValues();
  
  read_file(path);

  numElements();
};

/*
    Iteration is made through file .txt provided, which values are inserted in sample list
 */

/**
 * @brief 
 * 
 */
void Team9::read_file(string path)
{
  double convert_Number;
  ifstream myfile;
  try{
    myfile.open(path);
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
  
/*
    Attributed are cleared so new calculate is possible for new file
 */

/**
 * @brief 
 * 
 */
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

/**
 * @brief Return number of elements in "sample"
 * 
 * @return unsigned int 
 */
unsigned int Team9::numElements()
{
  _numElements = sample.size();
  // cout << "data size:" << _numElements << endl;
  return _numElements;
};

/**
 * @brief The average is made through the increment of each value divided by the number of elements in list,
 * making the average to be increment little by little, making the risk of overflow shorter
 * 
 * @return double 
 */
double Team9::average()
{
    if(!_avgReady){
        double N = Team9::numElements();
        for(auto &&item:sample){
            _average += item/N;
        }
    
        _avgReady = true;
    }
    return _average;
};

/*
We left this here because we found a possible better way to calculate the average, but we can't really understand the equation being used.
https://www.quora.com/How-can-I-compute-the-average-of-a-large-array-of-integers-without-running-into-overflow
double Team9::average()
{
    if(!_avgReady){
        int size = sample.size();
        int x = 0;
        int y = 0;
        for(int i : sample) {
            x += i / size;
            int b = i % size;
            if (y >= size - b) {
                x++;
                y -= size - b;
            } else {
                y += b;
            }
        }

        cout << "media:" << x << endl;
        _avgReady = true;
    }
    return _average;
};
 */


/**
 * @brief Utilização de uma library c++ que itera em cima da lista em busca do maior valor
            Foi considerao fazermos uma ordenação de lista antes, mas isso iria requerer uma complexidade O(n log n),
            enquanto a iteração feita tem complexidade O(n)
 * 
 * @return double 
 */
double Team9::max()
{
    if(!_maxReady){
        _max = *max_element(sample.begin(), sample.end());
        _maxReady = true;
    }
    return _max;
};

/**
 * @brief Utilização de uma library c++ que itera em cima da lista em busca do menor valor
            Foi considerao fazermos uma ordenação de lista antes, mas isso iria requerer uma complexidade O(n log n),
            enquanto a iteração feita tem complexidade O(n)
 * 
 * @return double 
 */
double Team9::min()
{
    if(!_minReady){
        _min = *min_element(sample.begin(), sample.end());
        _minReady = true;
    }
    return _min;
};

/**
 * @brief Como sugerido pelo professor, para o cálculo da mediana utilizamos o método genérico "quantile"
 * 
 * @return double 
 */
double Team9::mediane()
{
    if(!_medianeReady){
        _mediane = Team9::quantile(1,2);
        _medianeReady = true;
    }
    return _mediane;
};


/**
 * @brief Moda: é feita uma iteração por todos os valores de sample, que são inseridos como chave em um dicionário, 
            e então determinado qual valor apareceu com maior frequencia 
 * 
 * @return double 
 */
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
        _mode = itm;
        _modeReady = true;
    }
    return _mode;
};

/**
 * @brief Para o cálculo da variância, optamos por fazer a divisão a cada iteração ao invés do final,
            de forma a diminuir o crescimento do somatório
 * 
 * @return double 
 */
double Team9::variance()
{
    if(!_varianceReady){
        _variance = 0;
        double avg = average();
        for (auto &&item : sample)
        {
          _variance += ((item - avg) * (item - avg)) / (_numElements-1);
        }
        //sd = sqrt(var); //desvio padrão
        
        //cout << "desvio padrão" << sd << endl;
        _varianceReady = true;
    }
  return _variance;
};


/**
 * @brief Cálculo padrão de desvio padrão
 * 
 * @return double 
 */
double Team9::stddeviation(){
    if(!_stddevReady){
        _stdDeviation = sqrt(Team9::variance());
        _stddevReady = true;
    }
    
    return _stdDeviation;
};


/**
 * @brief Cáculo padrão de Coeficiente de Variancia
 * 
 * @return double 
 */
double Team9::variationCoef(){
    if(!cVReady){
        _variationCoef = Team9::stddeviation()/Team9::average();
        cVReady = true;
    }
    return _variationCoef;
};


/**
 * @brief Para o calculo da margem de erro, é necessário utilizar um nível de confiança disponível para o calculo do z score.
            O cálculo foi feito utilizando: z * desvio padrao / raiz de n
 * 
 * @param confidencelevel 
 * @return double 
 */
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


/**
 * @brief Para o calculo do tamanho da amostra, é necessário utilizar um nível de confiança disponível para o calculo do z score.
            O cálculo foi feito utilizando: z² * variancia / (margem de erro)²
 * 
 * @param confidencelevel 
 * @param halfWidth 
 * @return unsigned int 
 */
unsigned int Team9::newSampleSize(double confidencelevel, double halfWidth){
    double z2 = pow(zScore[confidencelevel],2);
    double hW2 = pow(halfWidth,2);
 
    _newSampleSize = z2 * Team9::variance() / hW2;

    return _newSampleSize;
};


/**
 * @brief Quartil utiliza a função generica quantile.
 * 
 * @param num 
 * @return double 
 */
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

/**
 * @brief Decil utiliza a função generica quantile.
 * 
 * @param num 
 * @return double 
 */
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

/**
 * @brief Centil utiliza a função generica quantile.
 * 
 * @param num 
 * @return double 
 */
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

/**
 * @brief A primeira etapa do método é fazer a ordenação da lista, 
            pois todos os métodos que utilizam o mesmo precisam se uma lista ordenada para serem calculados.
 * 
 * @param num 
 * @param subsets 
 * @return double 
 */
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
        // caso a quantidade de elementos seja par
         list<double>::iterator posAfter = next(sample.begin(), integ);
         _quantile = (*pos + *posAfter)/2;
    }
    else{
        _quantile = *pos;
    }
    //cout<<"quantile:"<<_quantile<<endl;
    return _quantile;
}

/**
 * @brief Setter
 * 
 * @param num 
 */
void Team9::setHistogramNumClasses(unsigned short num){
    _histogramNumClasses = num;
    //Novo numero de classes setado, valores calculador anteriormente não servem mais.
    mapClassLowerLimit.clear();
    _amplitudeReady = false;
};

/**
 * @brief Getter, mas levasse em consideração o numero de elementos
 * 
 * @return unsigned short 
 */
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

/**
 * @brief Para o cálculo da amplitude foi usada a equação: (Valor maximo - Valor minimo) / numero de classes
 * 
 * @return double 
 */
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


/**
 * @brief O limite inferior é determinado com um deslocamento baseado no valor minimo + a amplitude da classe, vezes o numero da classe desejada.
 *          Classes do histograma iniciam em 0.
 * 
 * @param classNum 
 * @return double 
 */
 double Team9::histogramClassLowerLimit(unsigned short classNum){
     if(mapClassLowerLimit.count(classNum)==0){//verifica se já foi calculado antes         
         _histogramClassLowerLimit = Team9::min() + (classNum)* Team9::getClassAmplitude();
         mapClassLowerLimit.insert( pair<unsigned short,double>(classNum, _histogramClassLowerLimit) );
          cout << "calculou Lower Limit: " <<_histogramClassLowerLimit <<" da classe " << classNum<< endl;
  
     }
     else{
         _histogramClassLowerLimit = mapClassLowerLimit[classNum];
         cout << "recuperou Lower Limit: " <<_histogramClassLowerLimit <<" da classe " << classNum<< endl;
     }
       return _histogramClassLowerLimit;
 };

/**
 * @brief 
 * 
 * @param classNum 
 * @return unsigned int 
 */
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


/**
 * @brief Método para verificação dos itens da lista
 * 
 */
void Team9::showlist()
{
  for (auto &&item : sample)
    cout << '\t' << item;
  cout << '\n';
};


/**
 * @brief Método de ordenação
 * 
 */
void Team9::sortList()
{
  sample.sort();
};


/**
 * @brief Mapeamento de zScore
 * 
 */
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

