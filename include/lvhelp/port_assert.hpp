#ifndef LVHELP_PORT_ASSERT_HPP
#define LVHELP_PORT_ASSERT_HPP

#include <array>

#include <boost/pfr.hpp>
#include <lvhelp/port_traits.hpp>

namespace lvhelp{

template<typename PORTs, typename T, T... ints>
[[nodiscard]] constexpr auto get_ids_as_array(std::integer_sequence<T, ints...> int_seq){
	PORTs ports;
	constexpr std::array<uint32_t, int_seq.size()> arr = {
		lvhelp::port_traits::index<decltype(boost::pfr::get<ints>(ports))>...
	};
	return arr;
}

template<typename PORTs>
constexpr bool are_ids_unique(){

	constexpr auto n = boost::pfr::tuple_size<PORTs>::value;

	constexpr auto ids = get_ids_as_array<PORTs>(std::make_index_sequence<n>());

	for(uint32_t i=1;i<n;i++){
		for(uint32_t j=0;j<i;j++){
			if(ids[i]==ids[j]){
				return false;
			}
		}
	}

	return true;
}


} // lvhelp

#endif