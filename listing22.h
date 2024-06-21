/* ========================================================================
   LISTING 22
   ======================================================================== */

#pragma once

#include "shape_type.h"

class shape_base
{
public:
    virtual ~shape_base() = default;
    virtual param_type Area() const = 0;
};

class square : public shape_base
{
public:
    square(param_type SideInit) : Side(SideInit) {}
    
    param_type Area() const override
     {return Side*Side;}
    
private:
    param_type Side;
};

class rectangle : public shape_base
{
public:
    rectangle(param_type WidthInit, param_type HeightInit) : Width(WidthInit), Height(HeightInit) {}
    virtual param_type Area() const {return Width*Height;}
    
private:
    param_type Width, Height;
};

class triangle : public shape_base
{
public:
    triangle(param_type BaseInit, param_type HeightInit) : Base(BaseInit), Height(HeightInit) {}
    virtual param_type Area() const {return 0.5f*Base*Height;}
    
private:
    param_type Base, Height;
};

class circle : public shape_base
{
public:
    circle(param_type RadiusInit) : Radius(RadiusInit) {}
    virtual param_type Area() const {return Pi32*Radius*Radius;}
    
private:
    param_type Radius;
};

