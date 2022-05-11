#ifndef LVHELP_TTL_IRI_FOAF_HPP
#define LVHELP_TTL_IRI_FOAF_HPP

#include "helper.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{

namespace foaf{
	namespace internal{
		template<TEMPLATE_STR term>
		using foaf_iri = lvhelp::ttl::iri::internal::iri_helper<term, "foaf", "http://xmlns.com/foaf/0.1/">;
	}

	using person = internal::foaf_iri<"Person">;
	using name = internal::foaf_iri<"name">;
	using mbox = internal::foaf_iri<"mbox">;
	using homepage = internal::foaf_iri<"homepage">;

} // foaf

} // iri
} // ttl
} // lvhelp

#endif