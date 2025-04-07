#include <algorithm>
#include "CacheHandler.h"

CacheHandler::CacheHandler()
{
    readJsonFile();
}

CacheHandler::~CacheHandler()
{
    writeJsonFile();
}

void CacheHandler::add(const std::string &domain, const uint16_t &port, const std::string &content)
{
    if (_cache.size() == MAX_CACHE_SIZE)
    {
        return;
    }

    // Add a new entry to the cache
    auto expiration = std::chrono::steady_clock::now() + std::chrono::hours(EXPIRATION_TIME_H);

    CacheEntry entry{};
    entry.domain = domain;
    entry.port = port;
    entry.expiration = expiration;
    entry.content = content;

    _cache.push_back(entry);
}

void CacheHandler::remove(const std::string &domain, const uint16_t &port)
{
    auto it = std::remove_if(_cache.begin(), _cache.end(), [&](const CacheEntry &entry)
                             { return entry.domain == domain && entry.port == port; });

    if (it != _cache.end())
    {
        _cache.erase(it, _cache.end());
    }
}

std::string CacheHandler::get(const std::string &domain, const uint16_t &port) const
{
    auto it = std::find_if(_cache.begin(), _cache.end(), [&](const CacheEntry &entry)
                           { return entry.domain == domain && entry.port == port; });
    if (it != _cache.end())
    {
        return it->content;
    }
    return "";
}

void CacheHandler::clear()
{
    _cache.clear();
    writeJsonFile();
}

void CacheHandler::readJsonFile()
{
    boost::property_tree::ptree pt;
    std::ifstream file(CACHE_FILE);
    if (!file)
    {
        return;
    }

    boost::property_tree::read_json(CACHE_FILE, pt);
    if (pt.empty())
    {
        return;
    }

    for (const auto &entry : pt.get_child("cache"))
    {
        CacheEntry cacheEntry;
        cacheEntry.domain = entry.second.get<std::string>("domain");
        cacheEntry.port = entry.second.get<uint16_t>("port");
        cacheEntry.content = entry.second.get<std::string>("content");
        auto expiration_seconds = entry.second.get<long>("expiration");
        cacheEntry.expiration = std::chrono::steady_clock::time_point(
            std::chrono::seconds(expiration_seconds));

        _cache.push_back(cacheEntry);
    }
}

void CacheHandler::writeJsonFile() const
{
    boost::property_tree::ptree pt;
    for (const auto &entry : _cache)
    {
        boost::property_tree::ptree child;
        child.put("domain", entry.domain);
        child.put("port", entry.port);
        child.put("content", entry.content);
        child.put("expiration", std::chrono::duration_cast<std::chrono::seconds>(
            entry.expiration.time_since_epoch()).count()); // Store expiration time in seconds

        pt.add_child("cache.entry", child);
    }
    boost::property_tree::write_json("cache.json", pt);
}