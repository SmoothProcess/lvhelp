#ifndef LVHELP_TTL_IRI_DOAP_HPP
#define LVHELP_TTL_IRI_DOAP_HPP

#include "helper.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{

namespace doap{
	namespace internal{
		template<TEMPLATE_STR term>
		using doap_iri = lvhelp::ttl::iri::internal::iri_helper<term, "doap", "http://usefulinc.com/ns/doap#">;
	}

	using project = internal::doap_iri<"Project">;
	using name = internal::doap_iri<"name">;
	using maintainer = internal::doap_iri<"maintainer">;

} // doap

} // iri
} // ttl
} // lvhelp

#endif