#pragma once

#include "heco_n_map_stable.h"

#include "../ShapeCollectionBase.h"

#include <cassert>

class HecoContainer : public ShapeCollectionBase
{
    public:
        HecoContainer();

        /**
         * Reserve space for n items
         */
        void reserve(std::size_t n) override
        {
            assert(m_total == 0);
        }

        /**
         * Add a new shape to the collection
         */
        void insert(std::unique_ptr<shape_base>& shape) override;

        /**
         * Post setup fix up point.
         */
        void postSetup() override {};

        
        // Test method
        param_type TotalArea() override;

        /**
         * Get a short-description of the test
         */
        std::string description() override
        {
            return "HeCo";
        }
    protected:
        heco::HeterogeneousContainer_n m_shapes;
        int m_total;
};

class HecoContainerTBB : public HecoContainer
{
    public:
    
        // Test method
        param_type TotalArea() override;

        /**
         * Get a short-description of the test
         */
        std::string description() override
        {
            return "HeCoTBB";
        }

        bool enabled() override;
};