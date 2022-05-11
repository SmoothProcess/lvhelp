#ifndef LVHELP_PORT_HPP
#define LVHELP_PORT_HPP

#include <algorithm>
#include <lvhelp/util/template_literals.hpp>


namespace lvhelp{

namespace port_type{

struct Audio{
	using value_type = float;
};

struct Control{
	using value_type = float;
};

struct CV{
	using value_type = float;
};


} // port_type

namespace port{
namespace property{

template<TemplateDouble value>
struct default_value{};

template<TemplateDouble value>
struct maximum{};

template<TemplateDouble value>
struct minimum{};

} // property
} // port

template<typename DERIVED>
class PortBase{
public:
	bool try_connect(const uint32_t port_id, void* ptr){
		auto& underlying = static_cast<DERIVED&>(*this);
		if(port_id == DERIVED::get_index()){
			underlying.port = reinterpret_cast<typename DERIVED::PortType>(ptr);
			return true;
		}
		return false;
	}

private:
	// Enforce CRTP
	constexpr PortBase(){}
	friend DERIVED;
};

template<typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
class Port : public PortBase<Port<TYPE, idx, symbol, name, Ts...>>{
public:
	using PortType = typename TYPE::value_type*;
	PortType port = nullptr;

	static constexpr uint32_t get_index(){return idx;}
};

template<typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
class InputPort : public PortBase<InputPort<TYPE, idx, symbol, name, Ts...>>{
public:
	using PortType = const typename TYPE::value_type*;
	PortType port = nullptr;

	static constexpr uint32_t get_index(){return idx;}
};

template<typename TYPE, uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
class OutputPort : public PortBase<OutputPort<TYPE, idx, symbol, name, Ts...>>{
public:
	using PortType = typename TYPE::value_type*;
	PortType port = nullptr;

	static constexpr uint32_t get_index(){return idx;}
};

template<uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
using InputAudioPort = InputPort<port_type::Audio, idx, symbol, name, Ts...>;

template<uint32_t idx, TEMPLATE_STR symbol, TEMPLATE_STR name, typename... Ts>
using OutputAudioPort = OutputPort<port_type::Audio, idx, symbol, name, Ts...>;


} // lvhelp

#endif