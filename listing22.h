/* ========================================================================
   LISTING 22
   ======================================================================== */

#pragma once

#include "shape_type.h"

#include <cstdint>

using u32 = uint32_t;
constexpr param_type Pi32 = 3.14;

class shape_base
{
public:
    virtual ~shape_base() = default;
    virtual param_type Area() = 0;
};

class square : public shape_base
{
public:
    square(param_type SideInit) : Side(SideInit) {}
    virtual param_type Area() {return Side*Side;}
    
private:
    param_type Side;
};

class rectangle : public shape_base
{
public:
    rectangle(param_type WidthInit, param_type HeightInit) : Width(WidthInit), Height(HeightInit) {}
    virtual param_type Area() {return Width*Height;}
    
private:
    param_type Width, Height;
};

class triangle : public shape_base
{
public:
    triangle(param_type BaseInit, param_type HeightInit) : Base(BaseInit), Height(HeightInit) {}
    virtual param_type Area() {return 0.5f*Base*Height;}
    
private:
    param_type Base, Height;
};

class circle : public shape_base
{
public:
    circle(param_type RadiusInit) : Radius(RadiusInit) {}
    virtual param_type Area() {return Pi32*Radius*Radius;}
    
private:
    param_type Radius;
};

