#pragma once

#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>
#include <boost/property_tree/json_parser.hpp>

/**
 * @struct CacheEntry
 * @brief Represents a single entry in the cache.
 */
struct CacheEntry
{
    std::string domain; ///< The domain name associated with the cache entry.
    uint16_t port{}; ///< The port number associated with the cache entry.
    std::chrono::steady_clock::time_point expiration; ///< The expiration time of the cache entry.
    std::string content; ///< The cached content.
};

/**
 * @class CacheHandler
 * @brief Manages a cache of HTTP responses.
 */
class CacheHandler
{
public:
    /**
     * @brief Constructor.
     */
    CacheHandler();

    /**
     * @brief Destructor.
     */
    ~CacheHandler();

    /**
     * @brief Deleted copy constructor.
     */
    CacheHandler(const CacheHandler &) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    CacheHandler& operator=(const CacheHandler &) = delete;

    /**
     * @brief Default move constructor.
     */
    CacheHandler(CacheHandler &&) = default;

    /**
     * @brief Default move assignment operator.
     */
    CacheHandler& operator=(CacheHandler &&) = default;

    /**
     * @brief Adds a new entry to the cache.
     * @param domain The domain name associated with the entry.
     * @param port The port number associated with the entry.
     * @param content The content to be cached.
     */
    void add(const std::string &domain, const uint16_t& port, const std::string &content);

    /**
     * @brief Retrieves a cached entry.
     * @param domain The domain name associated with the entry.
     * @param port The port number associated with the entry.
     * @return The cached content if found, otherwise an empty string.
     */
    std::string get(const std::string &domain, const uint16_t& port) const;

    /**
     * @brief Removes a specific entry from the cache.
     * @param domain The domain name associated with the entry.
     * @param port The port number associated with the entry.
     */
    void remove(const std::string &domain, const uint16_t& port);

    /**
     * @brief Clears all entries from the cache.
     */
    void clear();

private:
    /**
     * @brief Reads the cache data from a JSON file.
     */
    void readJsonFile();

    /**
     * @brief Writes the cache data to a JSON file.
     */
    void writeJsonFile() const;

    std::vector<CacheEntry> _cache; ///< The internal storage for cache entries.

    const uint8_t MAX_CACHE_SIZE{100}; ///< The maximum number of entries allowed in the cache.
    const uint8_t EXPIRATION_TIME_H{24}; ///< The expiration time for cache entries in hours.
    const std::string CACHE_FILE{"cache.json"}; ///< The file name for storing cache data.
};