#ifndef TREE2_HPP
#define TREE2_HPP
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>
#include <utility>

template<typename T>
class tree;

template<typename T>
using treeSP = std::shared_ptr<tree<T>>;

template<typename T>
using treeSPVec = std::vector<treeSP<T>>;

template<typename T>
using node = std::pair<T, treeSP<T>>;


template<typename T>
std::ostream& operator<<(std::ostream& s, tree<T> &t);

template<typename T>
class tree: public std::pair<std::pair<T, treeSP<T>>, treeSPVec<T>>, 
			public std::enable_shared_from_this<tree<T>>
{
	public:
		tree(const T &d);
		void insert(const T &d);
		treeSP<T> getShared();
		treeSP<T> find(const T &d);
	private:
		tree(const T &d, const treeSP<T> &p);

};

template<typename T>
tree<T>::tree(const T &d)
	: std::pair< std::pair<T, treeSP<T>>, treeSPVec<T> >
		(std::make_pair(std::make_pair(d, treeSP<T>()), treeSPVec<T>()))
{
	return;
}

template<typename T>
tree<T>::tree(const T &d, const treeSP<T> &p)
	: std::pair< std::pair<T, treeSP<T>>, treeSPVec<T> >
		(std::make_pair(std::make_pair(d, p), treeSPVec<T>()))
{
	return;
}

template<typename T>
treeSP<T> tree<T>::getShared()
{
	return(this->shared_from_this());
}

template<typename T>
void tree<T>::insert(const T &d)
{
	treeSP<T>	newTree(new tree<T>(d, this->getShared()));
	
	this->second.push_back(newTree);
	return;
}

template<typename T>
treeSP<T> tree<T>::find(const T &d)
{
	treeSP<T>	r;
	if(this->first.first == d) { return this->getShared(); }
	for(auto &i : this->second) {
		if((r = i->find(d)) != NULL) return(r);
	}
	return(NULL);
}

template<typename T>
std::ostream& operator<<(std::ostream& s, tree<T> &t)
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
