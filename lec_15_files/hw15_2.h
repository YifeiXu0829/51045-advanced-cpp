#ifndef TRAIN_H
#  define TRAIN_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;


namespace cspp51045 {
struct model_locomotive{
  void blow_horn() { 
    cout << "model_locomotive, honk" << endl; 
  }
};

struct model_freight_car {
  void load_coal(){
    cout << "model_freight_car Filling with coal dust. Pretending it's coal" << endl;
  }
};

struct model_caboose {
  void wave(){
    cout << "model_caboose Model conductor has hand in waving position" << endl;
  }
};

struct real_locomotive{
  void blow_horn(){
    cout << "real_locomotive HOOOOONNNNNNKKKKK" 
         << endl;
  }
};

struct real_freight_car{
  void load_coal(){
    cout << "real_freight_car Powering our nation (and heating our planet)" << endl;
  }
};

struct real_caboose{
  void wave(){
    cout << "real_caboose Bye, kids" << endl;
  }
};


}

#endif
