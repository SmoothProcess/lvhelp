#ifndef LVHELP_TTL_IRI_LV2CORE_HPP
#define LVHELP_TTL_IRI_LV2CORE_HPP

#include <lv2.h>
#include "lvhelp/ttl/iri/helper.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{
namespace lv2{

namespace core{
	namespace internal{
		template<TEMPLATE_STR term>
		using lv2core_iri = lvhelp::ttl::iri::internal::iri_helper<term, "lv2core", LV2_CORE_PREFIX>;
	}

	namespace plugin{
		using PluginBase = internal::lv2core_iri<"PluginBase">;
		using Plugin = internal::lv2core_iri<"Plugin">;
		using Allpass = internal::lv2core_iri<"AllpassPlugin">;
		using Amplifier = internal::lv2core_iri<"AmplifierPlugin">;
		using Analyser = internal::lv2core_iri<"AnalyserPlugin">;
		using Bandpass = internal::lv2core_iri<"BandpassPlugin">;
		using Chorus = internal::lv2core_iri<"ChorusPlugin">;
		using Comb = internal::lv2core_iri<"CombPlugin">;
		using Compressor = internal::lv2core_iri<"CompressorPlugin">;
		using Constant = internal::lv2core_iri<"ConstantPlugin">;
		using Converter = internal::lv2core_iri<"ConverterPlugin">;
		using Delay = internal::lv2core_iri<"DelayPlugin">;
		using Distortion = internal::lv2core_iri<"DistortionPlugin">;
		using Dynamics = internal::lv2core_iri<"DynamicsPlugin">;
		using EQ = internal::lv2core_iri<"EQPlugin">;
		using Envelope = internal::lv2core_iri<"EnvelopePlugin">;
		using Expander = internal::lv2core_iri<"ExpanderPlugin">;
		using Filter = internal::lv2core_iri<"FilterPlugin">;
		using Flanger = internal::lv2core_iri<"FlangerPlugin">;
		using Function = internal::lv2core_iri<"FunctionPlugin">;
		using Gate = internal::lv2core_iri<"GatePlugin">;
		using Generator = internal::lv2core_iri<"GeneratorPlugin">;
		using Highpass = internal::lv2core_iri<"HighpassPlugin">;
		using Instrument = internal::lv2core_iri<"InstrumentPlugin">;
		using Limiter = internal::lv2core_iri<"LimiterPlugin">;
		using Lowpass = internal::lv2core_iri<"LowpassPlugin">;
		using Mixer = internal::lv2core_iri<"MixerPlugin">;
		using Modulator = internal::lv2core_iri<"ModulatorPlugin">;
		using Multi_eq = internal::lv2core_iri<"MultiEQPlugin">;
		using Oscillator = internal::lv2core_iri<"OscillatorPlugin">;
		using ParaEQ = internal::lv2core_iri<"ParaEQPlugin">;
		using Phaser = internal::lv2core_iri<"PhaserPlugin">;
		using Pitch = internal::lv2core_iri<"PitchPlugin">;
		using Reverb = internal::lv2core_iri<"ReverbPlugin">;
		using Simulator = internal::lv2core_iri<"SimulatorPlugin">;
		using Spatial = internal::lv2core_iri<"SpatialPlugin">;
		using Spectral = internal::lv2core_iri<"SpectralPlugin">;
		using Utility = internal::lv2core_iri<"UtilityPlugin">;
		using Waveshaper = internal::lv2core_iri<"WaveshaperPlugin">;

		using port = internal::lv2core_iri<"port">;
	} // plugin

	using project = internal::lv2core_iri<"project">;
	using prototype = internal::lv2core_iri<"prototype">;

	using Feature = internal::lv2core_iri<"Feature">;
	using ExtensionData = internal::lv2core_iri<"ExtensionData">;

	namespace port{
		using Port = internal::lv2core_iri<"Port">;
		using Input = internal::lv2core_iri<"InputPort">;
		using Output = internal::lv2core_iri<"OutputPort">;

		using Audio = internal::lv2core_iri<"AudioPort">;
		using CV = internal::lv2core_iri<"CVPort">;
		using Control = internal::lv2core_iri<"ControlPort">;

		using Property = internal::lv2core_iri<"PortProperty">;
		using property = internal::lv2core_iri<"portProperty">;
	} // port

	using Point = internal::lv2core_iri<"Point">;
	using Resource = internal::lv2core_iri<"Resource">;
	using ScalePoint = internal::lv2core_iri<"ScalePoint">;
	using Specification = internal::lv2core_iri<"Specification">;

	using applies_to = internal::lv2core_iri<"appliesTo">;
	using binary = internal::lv2core_iri<"binary">;
	using connection_optional = internal::lv2core_iri<"connectionOptional">;
	using designation = internal::lv2core_iri<"designation">;
	using documentation = internal::lv2core_iri<"documentation">;
	using enabled = internal::lv2core_iri<"enabled">;
	using enumeration = internal::lv2core_iri<"enumeration">;

	using extension_data = internal::lv2core_iri<"extensionData">;
	using free_wheeling = internal::lv2core_iri<"freeWheeling">;
	using hard_RT_capable = internal::lv2core_iri<"hardRTCapable">;
	using in_place_broken = internal::lv2core_iri<"inPlaceBroken">;
	using is_live = internal::lv2core_iri<"isLive">;
	using latency = internal::lv2core_iri<"latency">;

	using symbol = internal::lv2core_iri<"symbol">;
	using name = internal::lv2core_iri<"name">;
	using control = internal::lv2core_iri<"control">;
	using default_value = internal::lv2core_iri<"default">;
	using index = internal::lv2core_iri<"index">;
	using integer = internal::lv2core_iri<"integer">;
	using maximum = internal::lv2core_iri<"maximum">;
	using minimum = internal::lv2core_iri<"minimum">;

	using micro_version = internal::lv2core_iri<"microVersion">;
	using minor_version = internal::lv2core_iri<"minorVersion">;

	using optional_feature = internal::lv2core_iri<"optionalFeature">;
	using required_feature = internal::lv2core_iri<"requiredFeature">;
	
	using reports_latency = internal::lv2core_iri<"reportsLatency">;
	using sample_rate = internal::lv2core_iri<"sampleRate">;
	using scale_point = internal::lv2core_iri<"scalePoint">;
	using toggled = internal::lv2core_iri<"toggled">;

} // core
} // lv2
} // iri
} // ttl
} // lvhelp


#endif