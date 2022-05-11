# lvhelp

Helps simplify the making of [LV2 plugins](https://lv2plug.in/) with c++20 by minimizing duplication.

This is in very early stages so be aware it is very incomplete, bugs may be many and the API may change. If you can help improve lvhelp it is very appreciated.

Tested on linux using clang-12.

Depends on [lvtk](https://lvtk.org) and [magic_get (boost/pfr)](https://github.com/apolukhin/magic_get).

## What does it do?

Developing LV2 plugins typically involves a lot of boilerplate code. Lvtk eases this somewhat but still leaves some things that could be further simplified.

One example are ports (and currently the only one implemented).

Ports must be declared as pointers of the appropriate type and must be connected inside the `connect_port` function if they match a specific index. And then they must also be listed on the turtle file so that the host knows they exist.

So this means when you decide to create or modify a port you must edit on three different locations. So you have to cross-reference each of these to change what is conceptually one element. This makes it more work and error prone that it could be.

Using lvhelp you declare a `struct` that contains (*only*) the plugin's ports specifying all the relevant data in one place.

For example:

```cpp
#include <lvhelp/port.hpp>

struct Ports{
	lvhelp::InputAudioPort<0, "input", "Input"> input;
	lvhelp::OutputAudioPort<1, "output", "Output"> output;

	lvhelp::InputPort<
		lvhelp::port_type::Control, 2, "control", "Control",
		lvhelp::port::property::minimum<-90.0>,
		lvhelp::port::property::maximum<10.0>,
		lvhelp::port::property::default_value<0.0>
	> control;

	// The form for a port is `[PortType]<SpecificType, index, "symbol", "Name", PROPERTIEs...>`.
	//`(Input/Output)AudioPort` is an alias where the specific type is already specified.
};

struct Uris{}; // Not yet implemented
```

This `struct` would then be passed as a template argument for the base from which the plugin must inherit. (Here lvhelp will ensure no 2 ports share an index at compile time).

```cpp
#include "lvhelp/plugin.hpp"
#include "ports_and_uris.hpp"

class TestPlugin : public lvhelp::Plugin<lvtk::Plugin<TestPlugin>, Ports, Uris>{
	// ... code ...
};
```

And it would also be used by the ttl generator. This is a current weak point as presently a template (in the mundane sense of the word) is provided and the user may edit it to change the ttl output.

The intention however is to provide a cleaner interface where things like the plugin type and other configurable elements are declared in a similar manner to the ports and not streched and lost among lines of code.

The output is perfectly legible:

```ttl
@prefix doap: <http://usefulinc.com/ns/doap#>.
@prefix lv2core: <http://lv2plug.in/ns/lv2core#>.
@prefix foaf: <http://xmlns.com/foaf/0.1/>.
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>.

<http://github.com/SmoothProcess/lvhelp-example>
	rdf:type lv2core:Plugin;
	doap:name "LVhelp Volume Example";
	lv2core:project <http://github.com/SmoothProcess/lvhelp-examples>;
	lv2core:minorVersion 1;
	lv2core:microVersion 0;
	lv2core:optionalFeature lv2core:hardRTCapable;
	lv2core:port [
		rdf:type lv2core:InputPort, lv2core:AudioPort;
		lv2core:index 0;
		lv2core:symbol "input";
		lv2core:name "Input"
	], [
		rdf:type lv2core:OutputPort, lv2core:AudioPort;
		lv2core:index 1;
		lv2core:symbol "output";
		lv2core:name "Output"
	], [
		rdf:type lv2core:InputPort, lv2core:ControlPort;
		lv2core:index 2;
		lv2core:symbol "control";
		lv2core:name "Control";
		lv2core:minimum -90.000000;
		lv2core:maximum 10.000000;
		lv2core:default 0.000000
	].
```

## Example

[Volume Example](https://github.com/SmoothProcess/lvhelp-example)

---

## License

Copyright (c) 2022 Rui Pedro Costa (SmoothProcess)

Released under 
[the MIT license](https://github.com/SmoothProcess/lvhelp/blob/main/LICENSE)