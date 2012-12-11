#include "CLError.hpp"
#include <iostream>

CLError::CLError(int errorCode){
  this->error = errorCode;
}

void CLError::printError(){
  std::cout << this->error << std::endl;
}
