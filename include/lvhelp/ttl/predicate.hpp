#ifndef LVHELP_TTL_PREDICATE_HPP
#define LVHELP_TTL_PREDICATE_HPP

#include <vector>
#include <memory>
#include <string>

#include "lvhelp/ttl/term.hpp"

namespace lvhelp{
namespace ttl{


class Predicate{
private:
	std::unique_ptr<Term> _term;
	std::vector<std::unique_ptr<Term>> _object_list;
public:
	Predicate(const Term& term) : _term(term.clone()){}

	template<typename... Ts>
	Predicate(const Term& term, const Ts... params) :
			Predicate(term){
		append(params...);
	}

	Predicate(const Predicate& other) : _term(other._term->clone()){
		for(const auto& element: other._object_list){
			append(*element);
		}
	}

	void append(const Term& term){
		_object_list.push_back(std::unique_ptr<Term>(term.clone()));
	}

	template<typename... Ts>
	void append(const Term& term, const Ts... params){
		append(term);
		append(params...);
	}

	std::string get_objects_string(const unsigned tabs=0) const{
		std::string s{};

		for(auto i=_object_list.begin();i<_object_list.end();i++){
			s = s + (*i)->get_string(tabs);
			if(i+1!=_object_list.end())
				s += ", ";
		}

		return s;
	}

	std::string get_string(const unsigned tabs=0) const{
		return insert_tabs(tabs) + _term->get_string(tabs+1) + " " + get_objects_string(tabs);
	}

	void add_prefixes_to_list(PrefixList& list){
		if(_term){
			_term->add_prefixes_to_list(list);
		}
		for(const auto& element: _object_list){
			element->add_prefixes_to_list(list);
		}
	}

	Predicate* clone() const{
		return new Predicate(*this);
	}
};



} // ttl
} // lvhelp


#endif