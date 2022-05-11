#ifndef LVHELP_TTL_TYPE_IRI_HPP
#define LVHELP_TTL_TYPE_IRI_HPP

#include "lvhelp/port.hpp"
#include "iri.hpp"
#include "predicate.hpp"
#include "term.hpp"

#include "lvhelp/util/template_literals.hpp"

namespace lvhelp{
namespace type_iri{

template<typename T>
struct of{
	inline static auto get(){return ttl::Iri("MissingIri");}
};

// Ignore ref and const
template<typename T>
struct of<T&>{
	inline static auto get(){return of<T>::get();}
};
template<typename T>
struct of<const T>{
	inline static auto get(){return of<T>::get();}
};


template<>
struct of<port_type::Audio>{
	inline static auto get(){return ttl::iri::lv2::core::port::Audio::get();}
};

template<>
struct of<port_type::CV>{
	inline static auto get(){return ttl::iri::lv2::core::port::CV::get();}
};

template<>
struct of<port_type::Control>{
	inline static auto get(){return ttl::iri::lv2::core::port::Control::get();}
};


template<typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
struct of<Port<TYPE, idx, symbol, name, Ts...>>{
	inline static auto get(){
		return ttl::Predicate{ttl::iri::rdf::is_type::get(),
				ttl::iri::lv2::core::port::Port::get(),
				of<TYPE>::get()
			};
	}
};

template<typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
struct of<InputPort<TYPE, idx, symbol, name, Ts...>>{
	inline static auto get(){
		return ttl::Predicate{ttl::iri::rdf::is_type::get(),
				ttl::iri::lv2::core::port::Input::get(),
				of<TYPE>::get()
			};
	}
};

template<typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
struct of<OutputPort<TYPE, idx, symbol, name, Ts...>>{
	inline static auto get(){
		return ttl::Predicate{ttl::iri::rdf::is_type::get(),
				ttl::iri::lv2::core::port::Output::get(),
				of<TYPE>::get()
			};
	}
};

template<typename T>
struct property_predicate{
	inline static auto get(){
		return ttl::Predicate{ttl::Iri("PropertyNotRecognized"), ttl::Iri("PropertyNotRecognized")};
	}
};

template<TemplateDouble value>
struct property_predicate<port::property::maximum<value>>{
	inline static auto get(){
		return ttl::Predicate{
				ttl::iri::lv2::core::maximum::get(), 
				ttl::RawTerm(value.value)
		};
	}
};
template<TemplateDouble value>
struct property_predicate<port::property::minimum<value>>{
	inline static auto get(){
		return ttl::Predicate{
				ttl::iri::lv2::core::minimum::get(), 
				ttl::RawTerm(value.value)
		};
	}
};
template<TemplateDouble value>
struct property_predicate<port::property::default_value<value>>{
	inline static auto get(){
		return ttl::Predicate{
				ttl::iri::lv2::core::default_value::get(), 
				ttl::RawTerm(value.value)
		};
	}
};


template<typename T>
struct properties_of{};
template<typename T>
struct properties_of<const T>{
	inline static auto get(){return properties_of<T>::get();}
};
template<typename T>
struct properties_of<T&>{
	inline static auto get(){return properties_of<T>::get();}
};

template<template<typename, uint32_t idx, TEMPLATE_STR, TEMPLATE_STR, typename...> typename PORT, typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... PROPERTIEs>
struct properties_of<PORT<TYPE, idx, symbol, name, PROPERTIEs...>>{
	inline static auto get(){
		ttl::PredicateList predicate_list;
		((predicate_list.append(property_predicate<PROPERTIEs>::get())),...);
		return predicate_list;
	}
};

} // type_iri
} // lvhelp

#endif