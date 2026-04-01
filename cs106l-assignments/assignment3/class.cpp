#include "class.h"
#include<string>

void Class::toNewSemester(){
    studentsNumber=0;
}

int Class::getNumber()const{
    return studentsNumber;
}

void Class::setNumber(int number){
    studentsNumber=number;
}