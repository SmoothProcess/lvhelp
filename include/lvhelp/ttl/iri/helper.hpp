#ifndef LVHELP_TTL_IRI_HELPER
#define LVHELP_TTL_IRI_HELPER

#include "lvhelp/util/template_literals.hpp"
#include "lvhelp/ttl/term.hpp"

namespace lvhelp{
namespace ttl{
namespace iri{
namespace internal{


template<TEMPLATE_STR term, TEMPLATE_STR abbrv, TEMPLATE_STR expanded>
struct iri_helper{
	static Iri get(){
		return Iri(term.value, Prefix(abbrv.value, expanded.value));
	}
};

} // internal
} // iri
} // tll
} // lvhelp

#endif