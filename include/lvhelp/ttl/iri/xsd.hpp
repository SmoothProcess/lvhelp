#ifndef LVHELP_TTL_IRI_XSD_HPP
#define LVHELP_TTL_IRI_XSD_HPP

#include "helper.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{

namespace xsd{
	namespace internal{
		template<TEMPLATE_STR term>
		using xsd_iri = lvhelp::ttl::iri::internal::iri_helper<term, "xsd", "http://www.w3.org/2001/XMLSchema#">;
	}

	using xsd_string = internal::xsd_iri<"string">;
	using xsd_integer = internal::xsd_iri<"integer">;
	using xsd_double = internal::xsd_iri<"double">;

} // xsd

} // iri
} // ttl
} // lvhelp

#endif