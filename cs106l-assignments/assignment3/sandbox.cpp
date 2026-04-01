/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include "class.h"
#include<iostream>

void sandbox() {
  Class math("math","lqx",114514);
  std::cout<<math.getNumber()<<"\n";
  math.setNumber(123456);
  std::cout<<math.getNumber();
}