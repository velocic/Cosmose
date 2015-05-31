#ifndef ASSETCACHE_H
#define ASSETCACHE_H

#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <utilities/ioutils.h>

namespace Utility
{
    template<typename CacheItem>
    class AssetCache
    {
        private:
            std::unordered_map<std::string, std::weak_ptr<CacheItem>> cachedItems;
        public:
            AssetCache() {};

            std::shared_ptr<CacheItem> get(std::string key) {
                auto iterator = cachedItems.find(key);

                if (iterator != cachedItems.end()) {
                    
                    //Found the key. Need to check if value is still a valid pointer
                    if (iterator->second.expired()) {
                        //Create new CacheItem, create a shared_ptr to it to return, and save a weak_ptr to it in iterator->second
                        std::vector<char> fileContents;
                        IOUtils::getFileContents(fileContents, key);
                        CacheItem *item = new CacheItem(&fileContents);
                        std::shared_ptr<CacheItem> sharedItemPointer(item);
                        std::weak_ptr<CacheItem> cacheOwnedItemPointer(sharedItemPointer);
                        iterator->second = cacheOwnedItemPointer;

                        return sharedItemPointer;
                    }

                    //Found the key, and the item is still cached. Return a shared_ptr created from cache's weak_ptr
                    return iterator->second.lock();
                }

                //Key not found. Create a new CacheItem, store it in the cache with the given Key.
                std::vector<char> fileContents;
                IOUtils::getFileContents(fileContents, key);

                CacheItem *item = new CacheItem(&fileContents);
                std::shared_ptr<CacheItem> sharedItemPointer(item);
                std::weak_ptr<CacheItem> cacheOwnedItemPointer(sharedItemPointer);
                cachedItems.insert(
                    std::pair<std::string, std::weak_ptr<CacheItem>>(
                        key,
                        cacheOwnedItemPointer
                    )
                );

                return sharedItemPointer;
            }
    };
}

#endif
