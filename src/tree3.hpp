#ifndef TREE3_HPP
#define TREE3_HPP
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>
#include <utility>

template<typename T, typename C>
class tree;

template<typename T, typename C>
using treeSP = std::shared_ptr<tree<T, C>>;

template<typename T, typename C>
using treeSPVec = std::vector<treeSP<T, C>>;

template<typename T, typename C>
using node = std::pair<T, treeSP<T, C>>;

template<typename T, typename C>
std::ostream& operator<<(std::ostream& s, tree<T, C> &t);

template<typename T, typename C>
class tree: public std::pair<std::pair<T, treeSP<T, C>>, treeSPVec<T, C>>, 
			public std::enable_shared_from_this<tree<T, C>>
{
	public:
		tree(const T &d);
		void insert(const T &d);
		treeSP<T, C> getShared();
		treeSP<T, C> find(const T &d);
	private:
		tree(const T &d, const treeSP<T, C> &p);

};

template<typename T, typename C>
tree<T, C>::tree(const T &d)
	: std::pair< std::pair<T, treeSP<T, C>>, treeSPVec<T, C> >
		(std::make_pair(std::make_pair(d, treeSP<T, C>()), treeSPVec<T, C>()))
{
	return;
}

template<typename T, typename C>
tree<T, C>::tree(const T &d, const treeSP<T, C> &p)
	: std::pair< std::pair<T, treeSP<T, C>>, treeSPVec<T, C> >
		(std::make_pair(std::make_pair(d, p), treeSPVec<T, C>()))
{
	return;
}

template<typename T, typename C>
treeSP<T, C> tree<T, C>::getShared()
{
	return(this->shared_from_this());
}

template<typename T, typename C>
void tree<T, C>::insert(const T &d)
{
	treeSP<T, C>	newTree(new tree<T, C>(d, this->getShared()));
	
	this->second.push_back(newTree);
	return;
}

template<typename T, typename C>
treeSP<T, C> tree<T, C>::find(const T &d)
{
	treeSP<T, C>	r;
	if(this->first.first == d) { return this->getShared(); }
	for(auto &i : this->second) {
		if((r = i->find(d)) != NULL) return(r);
	}
	return(NULL);
}

template<typename T, typename C>
std::ostream& operator<<(std::ostream& s, tree<T, C> &t)
{
	s << t.getShared() << ", " << t.first.first << ", " << t.first.second <<  std::endl;
	if(t.second.size() != 0) { 
		for(auto &i : t.second) {
			s << *i << std::endl;
		}
	}
	return s;
}

#endif
