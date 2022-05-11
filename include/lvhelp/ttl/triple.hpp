#ifndef LVHELP_TTL_TRIPLE_HPP
#define LVHELP_TTL_TRIPLE_HPP

#include <memory>
#include <vector>

#include "lvhelp/ttl/term.hpp"
#include "lvhelp/ttl/predicate.hpp"
#include "lvhelp/ttl/predicate_list.hpp"

namespace lvhelp{
namespace ttl{

class Triple{
private:
	std::unique_ptr<Term> _subject;
	// std::vector<std::unique_ptr<Predicate>> _predicate_list;
	PredicateList _predicate_list;
public:
	Triple(const Term& subject) : _subject(subject.clone()){}
	
	template<typename... Ts>
	Triple(const Term& subject, const Ts... params) : Triple(subject){
		append(params...);
	}

	template<typename... Ts>
	void append(const Ts... params){
		_predicate_list.append(params...);
	}


	std::string get_string(const unsigned tabs=0) const{

		std::string s = insert_tabs(tabs) + _subject->get_string() + "\n";
		s += _predicate_list.get_string(tabs+1) + ".";

		return s;
	}

	void add_prefixes_to_list(PrefixList& list) const{
		if(_subject){
			_subject->add_prefixes_to_list(list);
		}
		_predicate_list.add_prefixes_to_list(list);

	}

};


} // ttl
} // lvhelp

#endif