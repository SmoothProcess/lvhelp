#ifndef LVHELP_TTL_RDF_HPP
#define LVHELP_TTL_RDF_HPP

#include "helper.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{

namespace rdf{
	namespace internal{
		template<TEMPLATE_STR term>
		using rdf_iri = lvhelp::ttl::iri::internal::iri_helper<term, "rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#">;
	}

	using is_type = internal::rdf_iri<"type">;

} // rdf

} // iri
} // ttl
} // lvhelp

#endif