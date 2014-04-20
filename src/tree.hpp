#include <memory>
#include <utility>
#include <unordered_map>

template<typename T, typename H>
class tree;

template<typename T, typename H>
class tree : public std::unordered_map<T, std::shared_ptr<tree<T, H>>, H> { };
