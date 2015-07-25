#ifndef MANAGEDARRAY_H
#define MANAGEDARRAY_H

#include <memory>

template <typename Element>
namespace Utility
{
    class ManagedArray
    {
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
