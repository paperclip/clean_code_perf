
#pragma once

#include "../shape_type.h"

#include <sstream>
#include <string>

namespace Sorted
{
    class shape_base
    {
    public:

        virtual ~shape_base() = default;
        virtual param_type Area() const = 0;
        virtual bool operator<(const shape_base& other) const = 0;
        virtual shape_type getShapeType() const = 0;
        virtual std::string str() const = 0;
    };

    template<shape_type shape_t>
    class sortable_shape_base : public shape_base
    {
        static constexpr const shape_type shapeType = shape_t;
        bool operator<(const shape_base& other) const
        {
            return shapeType < other.getShapeType();
        }
        virtual shape_type getShapeType() const override
        {
            return shapeType;
        }
    };

    class square : public sortable_shape_base<SQUARE>
    {
    public:
        square(param_type SideInit) : Side(SideInit) {}
        
        param_type Area() const override
        {return Side*Side;}

        std::string str() const override
        {
            std::ostringstream ost;
            ost << "square( " << Side << ")";
            return ost.str();
        }
        
    private:
        param_type Side;
    };

    class rectangle : public sortable_shape_base<RECTANGLE>
    {
    public:
        rectangle(param_type WidthInit, param_type HeightInit) : Width(WidthInit), Height(HeightInit) {}
        virtual param_type Area() const {return Width*Height;}
        
        std::string str() const override
        {
            std::ostringstream ost;
            ost << "rectange( " << Width << ", " << Height << ")";
            return ost.str();
        }

    private:
        param_type Width, Height;
    };

    class triangle : public sortable_shape_base<TRIANGLE>
    {
    public:
        triangle(param_type BaseInit, param_type HeightInit) : Base(BaseInit), Height(HeightInit) {}
        virtual param_type Area() const {return 0.5f*Base*Height;}
        
        std::string str() const override
        {
            std::ostringstream ost;
            ost << "triangle( " << Base << ", " << Height << ")";
            return ost.str();
        }
        
    private:
        param_type Base, Height;
    };

    class circle : public sortable_shape_base<CIRCLE>
    {
    public:
        circle(param_type RadiusInit) : Radius(RadiusInit) {}
        virtual param_type Area() const {return Pi32*Radius*Radius;}
        
        std::string str() const override
        {
            std::ostringstream ost;
            ost << "circle( " << Radius << ")";
            return ost.str();
        }
    private:
        param_type Radius;
    };
}