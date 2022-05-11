#ifndef LVHELP_TTL_NESTED_BLANK_NODE
#define LVHELP_TTL_NESTED_BLANK_NODE

#include "lvhelp/ttl/predicate_list.hpp"

namespace lvhelp{
namespace ttl{

class NestedBlankNode : public Term{
private:
	PredicateList _list;
public:
	NestedBlankNode() = default;
	NestedBlankNode(const NestedBlankNode& other) : Term(other), _list(other._list){}

	template<typename... Ts>
	NestedBlankNode(const Ts... params){
		append(params...);
	}

	template<typename... Ts>
	void append(const Ts... params){
		_list.append(params...);
	}

	std::string get_string(const unsigned tabs=0) const override{
		return "[\n" + _list.get_string(tabs+1) + "\n" + insert_tabs(tabs) + "]";
	}

	virtual Term* clone() const override{
		return new NestedBlankNode(*this);
	}

	virtual void add_prefixes_to_list(PrefixList& list) const override{
		_list.add_prefixes_to_list(list);
	}
};

} // ttl
} // lvhelp

#endif