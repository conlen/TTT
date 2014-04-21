#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>

template<typename T, typename H>
class tree;

template<typename T, typename H>
class tree : public std::unordered_map<T, std::shared_ptr<tree<T, H>>, H> 
{ 
	using std::unordered_map<T, std::shared_ptr<tree<T, H>>, H>::insert;
	public:
		void insert(const T &d);
};

template<typename T, typename H>
void tree<T, H>::insert(const T &d)
{
		this->insert(std::pair<T, std::shared_ptr<tree<T, H>>>(d, std::make_shared<tree<T, H>>())); 
		return;
}

template<typename T, typename H>
std::ostream& operator<<(std::ostream& s, const tree<T, H> &t);

template<typename T, typename H>
std::ostream& operator<<(std::ostream& s, const tree<T, H> &t)
{
	for(auto i : t) {
		s << i.first << std::endl;
		s << *i.second << std::endl;
	}
	return s;
}