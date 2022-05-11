#ifndef LVHELP_TTL_TERM_HPP
#define LVHELP_TTL_TERM_HPP

#include <string>
#include <memory>

#include "lvhelp/ttl/prefix.hpp"

namespace lvhelp{
namespace ttl{

inline std::string insert_tabs(const unsigned count){
	std::string s;
	for(unsigned i=0;i<count;i++){
		s += '\t';
	}
	return s;
}

class Term{
protected:
	std::string _term;
public:
	Term(){};
	Term(const char* term) : _term(term){}

	Term(const Term& other) : _term(other._term){}
	virtual ~Term() = default;

	virtual std::string get_string(const unsigned tabs=0) const = 0;
	virtual Term* clone() const = 0;
	virtual void add_prefixes_to_list(PrefixList&) const{}
};

class RawTerm : public Term{
public:
	RawTerm(const char* term) : Term(term){}
	RawTerm(const RawTerm& other) : Term(other){}

	template<typename T>
	RawTerm(const T term) : Term(std::to_string(term).c_str()){}

	~RawTerm() = default;
	std::string get_string(const unsigned=0) const override{
		return _term;
	}
	Term* clone() const override{ return new RawTerm(*this);}
};

class Iri : public Term{
	std::unique_ptr<Prefix> _prefix;
public:
	Iri(const char* term) : Term(term){}
	Iri(const char* term, const Prefix prefix) : Term(term), _prefix(new Prefix(prefix)){}

	Iri(const Iri& other) : Term(other){
		if(other._prefix){
			_prefix = std::make_unique<Prefix>(*other._prefix);
		}
	}

	virtual ~Iri() = default;
	virtual std::string get_string(const unsigned =0) const override{
		if(!_prefix){
			return "<" + _term + ">";
		}
		return _prefix->get_abbrv() + ":" + _term;
	}

	virtual Term* clone() const override{
		return new Iri(*this);
	}

	virtual void add_prefixes_to_list(PrefixList& list) const override{
		if(_prefix){
			list.try_add(*_prefix);
		}
	}
};

class Literal : public Term{
private:
	std::unique_ptr<Iri> _literal_type;
	std::unique_ptr<std::string> _language_tag;
public:
	Literal(const char* literal){
		// TODO: validate and escape characters
		// " = \"
		_term = literal;
	}

	Literal(const char* literal, const Iri& type) : Literal(literal){
		_literal_type = std::make_unique<Iri>(type);
	}
	Literal(const char* literal, const char* lang) : Literal(literal){
		_language_tag = std::make_unique<std::string>(lang);
	}

	Literal(const Literal& other) : Literal(other._term.c_str()){
		if(other._literal_type){
			_literal_type = std::make_unique<Iri>(*other._literal_type);
		}
		if(other._language_tag){
			_language_tag = std::make_unique<std::string>(*other._language_tag);
		}
	}

	virtual std::string get_string(const unsigned=0) const override{
		if(_literal_type){
			return "\"" + _term + "\"^^" + _literal_type->get_string();
		}
		if(_language_tag){
			return "\"" + _term + "\"@" + *_language_tag;
		}
		return "\"" + _term + "\"";
	}

	virtual Term* clone() const override{
		return new Literal(*this);
	}

	virtual void add_prefixes_to_list(PrefixList& list) const override{
		if(_literal_type){
			_literal_type->add_prefixes_to_list(list);
		}
	}
};



} // ttl
} // lvhelp

#endif