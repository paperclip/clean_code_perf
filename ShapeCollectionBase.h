
#include "listing22.h"

#include <memory>
#include <vector>

class ShapeCollectionBase
{
    public:
        using shape_base_ptr = std::unique_ptr<shape_base>;
        /**
         * Reserve space for n items
         */
        virtual void reserve(std::size_t n) = 0;
        /**
         * Add a new shape to the collection
         */
        virtual void insert(std::unique_ptr<shape_base>& shape) = 0;

        void setup(int seed, u32 shapeCount);

        /**
         * Post setup fix up point.
         */
        virtual void postSetup() {};

        
        // Test method
        virtual param_type TotalArea() = 0;

        /**
         * Get a short-description of the test
         */
        virtual std::string description() = 0;
};
