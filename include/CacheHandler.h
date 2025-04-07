#pragma once

#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>
#include <boost/property_tree/json_parser.hpp>

struct CacheEntry
{
    std::string domain;
    uint16_t port{};
    std::chrono::steady_clock::time_point expiration;
    std::string content;
};

class CacheHandler
{
public:
    CacheHandler() = default;
    ~CacheHandler() = default;

    CacheHandler(const CacheHandler &) = delete;
    CacheHandler& operator=(const CacheHandler &) = delete;
    CacheHandler(CacheHandler &&) = default;
    CacheHandler& operator=(CacheHandler &&) = default;

    void add(const std::string &domain, const uint16_t& port, const std::string &content);
    std::string get(const std::string &domain, const uint16_t& port) const;
    void remove(const std::string &domain, const uint16_t& port);
    void clear();

private:
    void readJsonFile();
    void writeJsonFile() const;

    // Cache storage
    std::vector<CacheEntry> _cache;

    // Constants
    const uint8_t MAX_CACHE_SIZE{100};
    const uint8_t EXPIRATION_TIME_H{24};
    const std::string CACHE_FILE{"cache.json"};
};