#ifndef ASSETCACHE_H
#define ASSETCACHE_H

#include <fstream>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <vector>
#include <opengl/texture.h>

namespace Utility
{
    template<typename CacheItem>
    class AssetCache
    {
        private:
            std::unordered_map<std::string, std::weak_ptr<CacheItem>> cachedItems;
            //Note: break this into its own part of the Utility namespace.
            //No good reason to restrict it to the AssetCache
            bool getFileContents(std::vector<unsigned char> &fileBuffer, std::string filePath) {
                std::ifstream inFileStream(filePath, std::ios::binary);

                if (!inFileStream) {
                    return false;
                }

                inFileStream.seekg(0, std::ios::end);
                std::streampos fileLength = inFileStream.tellg();
                inFileStream.seekg(0, std::ios::beg);

                fileBuffer.resize(length);
                inFileStream.read(&fileBuffer[0], fileLength);

                return true;
            }
        public:
            AssetCache() {};

            std::shared_ptr<CacheItem> get(std::string key) {
                auto iterator = cachedItems.find(key);

                if (iterator != cachedItems.end()) {
                    
                    //Found the key. Need to check if value is still a valid pointer
                    if (iterator->second.expired()) {
                        //Create new CacheItem, create a shared_ptr to it to return, and save a weak_ptr to it in iterator->second
                        CacheItem *item = new CacheItem(); //need to pass file data here to CacheItem's constructor
                        std::shared_ptr<CacheItem> sharedItemPointer(item);
                        std::weak_ptr<CacheItem> cacheOwnedItemPointer(sharedItemPointer);
                        iterator->second = cacheOwnedItemPointer;

                        return sharedItemPointer;
                    }

                    //Found the key, and the item is still cached. Return a shared_ptr created from cache's weak_ptr
                    return iterator->second.lock();
                }

                //Key not found. Create a new CacheItem, store it in the cache with the given Key.
                CacheItem *item = new CacheItem(); //need to pass file data here to CacheItem's constructor
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
