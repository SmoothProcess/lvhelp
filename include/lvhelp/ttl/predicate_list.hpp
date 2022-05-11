#ifndef LVHELP_TTL_PREDICATE_LIST
#define LVHELP_TTL_PREDICATE_LIST

#include <vector>
#include <memory>
#include <string>

#include "lvhelp/ttl/predicate.hpp"

namespace lvhelp{
namespace ttl{

class PredicateList{
private:
	std::vector<std::unique_ptr<Predicate>> _vec;
public:
	PredicateList() = default;
	PredicateList(const PredicateList& other){
		append(other);
	}

	void append(const Predicate& predicate){
		_vec.push_back(std::unique_ptr<Predicate>(predicate.clone()));
	}

	void append(const PredicateList& other){
		for(const auto& p: other._vec){
			append(*p);
		}
	}

	template<typename T, typename... Ts>
	void append(const T& obj, const Ts... params){
		append(obj);
		append(params...);
	}

	std::string get_string(const unsigned tabs=0) const{
		std::string s;
		for(auto i=_vec.begin();i<_vec.end();i++){
			s = s + (*i)->get_string(tabs);
			if(i+1!=_vec.end())
				s += ";\n";
		}
		return s;
	}

	void add_prefixes_to_list(PrefixList& list) const{
		for(const auto& element: _vec){
			element->add_prefixes_to_list(list);
		}
	}
};

} // ttl
} // lvhelp

#endif