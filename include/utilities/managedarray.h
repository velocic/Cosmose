#ifndef MANAGEDARRAY_H
#define MANAGEDARRAY_H

#include <memory>

template <typename Element>
namespace Utility
{
    class ManagedArray
    {
        /*
         * A customzied generic collection object meant for efficient deletion,
         * and to allow objects to hold non-invalidating references to its'
         * contained elements while this object is live. This collection assumes
         * that its Elements 
         */
        private:
            std::unique_ptr<Element[]> collection;
            unsigned int currentSize;
            unsigned int maxSize;
        public:
            ManagedArray();
            ~ManagedArray();
            const std::unique_ptr<Element[]> getCollection() const;
            unsigned int getSize();
            unsigned int getSizeInBytes();
            void insert(Element element);
            void remove(unsigned int index);
    };
}

#endif
