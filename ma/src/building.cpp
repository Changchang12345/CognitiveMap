#include <iostream>
#include <string>
#include "C:\ma\include\building.h"

using namespace std;

int building::getLocation(){
    return this->location;
}

double building::getStart(){
    return this->start;
}

double building::getEnd(){
    return this->end;
}

double building::getRange(){
    return this->range;
}

bool building::getChoose(){
    return this->choose;
}
int building::getId(){
    return this->id;
}

int building::getOrd(){
    return this->order;
}

double building::getLength(){
    return this->range;
}

int building::getPolidx(){
    return this->polidx;
}


building::building(int id,int location,double range,double start,double end, int order,bool choose)
{
    this->choose = choose;
    this->id = id;
    this->location = location;
    this->start = start;
    this->end = end;
    this->order = order;
    this->range = range;
}
building::building(){

}

void building::setEnd(double end){
    this->end = end;
}

void building::setLength(double len){
    this->range = len;
}

void building::setStart(double start){
    this->start = start;
}

void building::setChoose(bool choose){
    this->choose = choose;
}

void building::setOrder(int order){
    this->order = order;
}

void building::setId(int id){
    this->id = id;
}

void building::setPolidx(int polidx){
    this->polidx = polidx;
}


building::~building()
{
    
}