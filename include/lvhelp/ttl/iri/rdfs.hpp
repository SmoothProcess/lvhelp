#ifndef LVHELP_TTL_IRI_RDFS_HPP
#define LVHELP_TTL_IRI_RDFS_HPP

#include "helper.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{

namespace rdfs{
	namespace internal{
		template<TEMPLATE_STR term>
		using rdfs_iri = lvhelp::ttl::iri::internal::iri_helper<term, "rdfs", "http://www.w3.org/2000/01/rdf-schema#">;

	}

	using see_also = internal::rdfs_iri<"seeAlso">;

}

} // iri
} // ttl
} // lvhelp


#endif