#ifndef LVHELP_PLUGIN_HPP
#define LVHELP_PLUGIN_HPP

#include <lvtk/plugin.hpp>
#include <boost/pfr.hpp>

#include <lvhelp/port_assert.hpp>

namespace lvhelp{

// Example:
// class MyPlugin : public lvhelp::Plugin<
//		lvtk::Plugin<MyPlugin, lvtk::URID>, MyPorts, MyURIs>{
// public:
// 	void run(uint32_t n_samples){
// 		// ... code ...
// 	}
// }

template<typename LVTKPlugin, typename PORTS, typename URIS>
class Plugin : public LVTKPlugin{

	static_assert(lvhelp::are_ids_unique<PORTS>(), "Ports Error: ids are not unique");

protected:
	PORTS _ports;
	URIS _uris;
public:
	Plugin(const lvtk::Args& args) : LVTKPlugin(args){
		// TODO: map URIS here
	}

	void connect_port(uint32_t port_id, void* ptr){
		boost::pfr::for_each_field(_ports,
			[port_id, ptr](auto& port){
				port.try_connect(port_id, ptr);
			}
		);
	}
};



} // lvhelp

#endif