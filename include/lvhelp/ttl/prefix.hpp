#ifndef LVHELP_TTL_PREFIX_HPP
#define LVHELP_TTL_PREFIX_HPP

#include <string>
#include <exception>
#include <stdexcept>
#include <unordered_map>

namespace lvhelp{
namespace ttl{

class Prefix{
private:
	const char* _abbrv;
	const char* _iri;
public:
	constexpr Prefix(const char* abbrv, const char* iri) : _abbrv(abbrv), _iri(iri){}

	std::string get_abbrv() const{
		return _abbrv;
	}
	std::string get_iri() const{
		return _iri;
	}
};

class prefix_conflict : public std::runtime_error {
public:
	prefix_conflict(const char* what) : runtime_error(what){}
};

class PrefixList : std::unordered_map<std::string, std::string>{
public:

	std::string get_string() const{
		std::string s;
		for(const auto& pair : (*this)){
			s += "@prefix " + pair.first + ": <" + pair.second + ">.\n";
		}
		return s;
	}

	void try_add(const std::string abbrv, const std::string iri){
		auto search = find(abbrv);
		if(search == end()){
			(*this)[abbrv] = iri;
		}else{
			if(search->second != iri){
				throw prefix_conflict{"Prefix name conflict"};
			}
		}
	}

	
	void try_add(const Prefix& pre){
		try_add(pre.get_abbrv(), pre.get_iri());
	}

	template<typename T>
	void add_from(const T& element){
		element.add_prefixes_to_list((*this));
	}

	template<typename T, typename... U>
	void add_from(const T& element, const U&... params){
		add_from(element);
		add_from(params...);
	}
};

} // ttl
} // lvhelp

#endif