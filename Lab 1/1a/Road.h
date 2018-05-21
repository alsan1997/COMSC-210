// Lab 1a, Class Programming And Testing
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

class Road
{
  private:
    float width;
    float length;
  public:
    void setWidth(float w){width = w;}
    void setLength(float l){length = l;}
    float getWidth() const{return width;}
    float getLength() const{return length;}
    float asphalt(float thickness) const;
};

#endif // ROAD_H_INCLUDED
