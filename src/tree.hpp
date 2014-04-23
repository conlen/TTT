#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>

template<typename T, typename H>
class tree;

template<typename T, typename H>
using treeSP = std::shared_ptr<tree<T, H>>; 

template<typename T, typename H>
using treeSPPair = std::pair<treeSP<T, H>, treeSP<T, H>>;

template<typename T, typename H>
std::ostream& operator<<(std::ostream& s, const tree<T, H> &t);

template<typename T, typename H>
class tree : public std::unordered_map<T, treeSPPair<T, H>, H>, public std::enable_shared_from_this<tree<T, H>>
{ 
	using std::unordered_map<T, treeSPPair<T, H>, H>::insert;
	public:
		void insert(const T &d);
		void insert(const T &d, treeSP<T, H> p);
		treeSP<T, H> getShared();
		treeSP<T, H> find(const T &d);
	friend std::ostream& operator<< <T, H>(std::ostream& s, const tree<T, H> &t);
};

// This does not point to the parent, it points to itself.
template<typename T, typename H>
void tree<T, H>::insert(const T &d)
{
		auto newTree = std::make_shared<tree<T, H>>();
		insert(std::pair<T, treeSPPair<T, H>>(d, std::make_pair(newTree, this->shared_from_this()))); 
		return;
}

template<typename T, typename H>
void tree<T, H>::insert(const T &d, treeSP<T, H> p)
{
		insert(std::pair<T, treeSPPair<T, H>>(d, std::make_pair(std::make_shared<tree<T, H>>(), p))); 
		return;
}

template<typename T, typename H>
treeSP<T, H> tree<T, H>::getShared() 
{
	
	return(this->shared_from_this());
}

template<typename T, typename H>
treeSP<T, H> tree<T, H>::find(const T &d)
{
	treeSP<T, H>	r;

	for(auto &i : *this) {
		if(d == i.first) {
			return(this->shared_from_this());
		} else {
			if(i.second.first != NULL) { if((r = i.second.first->find(d)) != NULL) { return(r); } }
		}
	}
	return(std::shared_ptr<tree<T, H>>(NULL));
}

template<typename T, typename H>
std::ostream& operator<<(std::ostream& s, const tree<T, H> &t);

template<typename T, typename H>
std::ostream& operator<<(std::ostream& s, tree<T, H> &t)
{
	
	s << "Node degree = " << t.size() << std::endl;
	for(auto i : t) {
		s << t.getShared() << ", " << i.first << ", " << i.second.first << ", " << i.second.second << std::endl;
		s << *i.second.first << std::endl;
	}
	return s;
}
#endif
