#include "../ShapeCollectionBase.h"

/**
 * A simple collection storing shapes as unique_ptr pointing to base class
 */
class SimpleShapeCollectionBase : public ShapeCollectionBase
{
    public:
        using ShapeVector = std::vector<shape_base_ptr>;

        /**
         * Reserve space for n items
         */
        void reserve(std::size_t n) override;
        /**
         * Add a new shape to the collection
         */
        void insert(std::unique_ptr<shape_base>& shape) override;
    protected:
        ShapeVector m_shapes;
};
