#ifndef LVHELP_PORT_TRAITS_HPP
#define LVHELP_PORT_TRAITS_HPP

#include <type_traits>
#include "port.hpp"

namespace lvhelp{
namespace port_traits{


template<typename T>
constexpr uint32_t index = 404; // TODO: throw error, or return RawTerm and warning instead

template<typename T>
constexpr uint32_t index<const T> = index<T>;

template<typename T>
constexpr uint32_t index<T&> = index<T>;


template<template<typename, uint32_t, TEMPLATE_STR, TEMPLATE_STR, typename...> typename PORT, typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
constexpr uint32_t index<PORT<TYPE, idx, symbol, name, Ts...>> = idx;




template<typename T>
constexpr const char* symbol = "missing_symbol_error";

template<typename T>
constexpr const char* symbol<const T> = symbol<T>;

template<typename T>
constexpr const char* symbol<T&> = symbol<T>;



template<template<typename, uint32_t, TEMPLATE_STR, TEMPLATE_STR, typename...> typename PORT, typename TYPE, uint32_t idx, TEMPLATE_STR SYMBOL, TEMPLATE_STR name, typename... Ts>
constexpr const char* symbol<PORT<TYPE, idx, SYMBOL, name, Ts...>> = SYMBOL.value;



template<typename T>
constexpr const char* name = "missing_name_error";

template<typename T>
constexpr const char* name<const T> = name<T>;

template<typename T>
constexpr const char* name<T&> = name<T>;


template<template<typename, uint32_t, TEMPLATE_STR, TEMPLATE_STR, typename...> typename PORT, typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR NAME, typename... Ts>
constexpr const char* name<PORT<TYPE, idx, symbol, NAME, Ts...>> = NAME.value;


} // port_traits
} // lvhelp

#endif