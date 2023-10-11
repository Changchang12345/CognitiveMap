#ifndef __BUILDING_H__
#define __BUILDING_H__

class building
{
private:
    /* data */
    int location;
    double range;
    int id;
    int order;
    bool choose;
    double start;
    double end;
    int polidx;
    
public:
    building(int,int,double,double,double ,int ,bool);
    ~building();
    building();
    double getStart();
    double getEnd();
    int getLocation();
    double getRange(); 
    bool getChoose();
    int getId();
    int getOrd();
    double getLength();
    int getPolidx();
    
    void setEnd(double end);
    void setStart(double start);
    void setLength(double len);
    void setChoose(bool choose);
    void setOrder(int);
    void setId(int);
    void setPolidx(int);
};


#endif // __BUILDING_H__