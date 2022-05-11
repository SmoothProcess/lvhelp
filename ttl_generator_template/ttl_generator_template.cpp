#include "lvhelp/ttl.hpp"
#include "lvhelp/port.hpp"
#include "lvhelp/port_traits.hpp"

#include <iostream>
#include <fstream>

#include <boost/pfr.hpp>

#include "config.hpp"
#include "ports_and_uris.hpp"

void generate_manifest(const char* out_path, const char* turtle);
void generate_turtle(const char* out_path);

namespace iri = lvhelp::ttl::iri;

template<typename PORTs>
lvhelp::ttl::Predicate generate_port_nodes(){

	using Predicate = lvhelp::ttl::Predicate;
	using NestedNode = lvhelp::ttl::NestedBlankNode;
	using RawTerm = lvhelp::ttl::RawTerm;
	using Literal = lvhelp::ttl::Literal;

	Predicate port_predicate{iri::lv2::core::plugin::port::get()};
	PORTs ports;
	boost::pfr::for_each_field(ports,
		[&port_predicate](const auto& field){
			NestedNode node;

			node.append(lvhelp::type_iri::of<decltype(field)>::get());


			node.append(
				Predicate{iri::lv2::core::index::get(), RawTerm(lvhelp::port_traits::index<decltype(field)>)},
				Predicate{iri::lv2::core::symbol::get(), Literal(lvhelp::port_traits::symbol<decltype(field)>)},
				Predicate{iri::lv2::core::name::get(), Literal(lvhelp::port_traits::name<decltype(field)>)}
			);

			node.append(lvhelp::type_iri::properties_of<decltype(field)>::get());

			port_predicate.append(node);

		}
	);
	return port_predicate;
}

int main(int argc, char const *argv[]) {

	if(argc != 3){
		std::cout << "Usage requires 2 arguments: <path/to/manifest.ttl> <path/to/seeAlso.ttl>\n";

		return EXIT_FAILURE;
	}

	generate_manifest(argv[1], argv[2]);
	generate_turtle(argv[2]);

	return EXIT_SUCCESS;
}

void generate_manifest(const char* out_path, const char* turtle_file){

	using lvhelp::ttl::Triple;
	using lvhelp::ttl::Iri;
	using lvhelp::ttl::Predicate;
	using lvhelp::ttl::Literal;
	using lvhelp::ttl::NestedBlankNode;
	using lvhelp::ttl::RawTerm;

	Triple plugin{Iri(PLUGIN_IRI),
		Predicate{iri::rdf::is_type::get(), iri::lv2::core::plugin::Plugin::get()},
		Predicate{iri::lv2::core::binary::get(), Iri(BINARY_PATH)},
		Predicate{iri::rdfs::see_also::get(), Iri(turtle_file)}
	};


	lvhelp::ttl::PrefixList prefix_list;

	prefix_list.add_from(plugin);

	std::ofstream fstream;

	{
	fstream.open(out_path);
		fstream << prefix_list.get_string() << "\n";
		fstream << plugin.get_string() << "\n\n";
	fstream.close();
	}
}

void generate_turtle(const char* out_path){

	using lvhelp::ttl::Triple;
	using lvhelp::ttl::Iri;
	using lvhelp::ttl::Predicate;
	using lvhelp::ttl::Literal;
	using lvhelp::ttl::NestedBlankNode;
	using lvhelp::ttl::RawTerm;

	Triple author{Iri(AUTHOR_IRI),
		Predicate{iri::rdf::is_type::get(), iri::foaf::person::get()},
		Predicate{iri::foaf::name::get(), Literal(AUTHOR_NAME)},
		Predicate{iri::foaf::mbox::get(), Iri(AUTHOR_EMAIL)},
		Predicate{iri::foaf::homepage::get(), Iri(AUTHOR_HOMEPAGE)}
	};
	
	Triple project{Iri(PROJECT_IRI),
		Predicate{iri::rdf::is_type::get(), iri::doap::project::get()},
		Predicate{iri::doap::name::get(), Literal(PROJECT_NAME)},
		Predicate{iri::doap::maintainer::get(), Iri(AUTHOR_IRI)}
	};

	Triple plugin{Iri(PLUGIN_IRI),
		Predicate{iri::rdf::is_type::get(), iri::lv2::core::plugin::Plugin::get()},
		Predicate{iri::doap::name::get(), Literal(PLUGIN_NAME)},
		Predicate{iri::lv2::core::project::get(), Iri(PROJECT_IRI)},
		Predicate{iri::lv2::core::minor_version::get(), RawTerm(VERSION_MINOR)},
		Predicate{iri::lv2::core::micro_version::get(), RawTerm(VERSION_PATCH)},
		Predicate{iri::lv2::core::optional_feature::get(), iri::lv2::core::hard_RT_capable::get()}
	};


	plugin.append(generate_port_nodes<Ports>());

	lvhelp::ttl::PrefixList prefix_list;

	prefix_list.add_from(author, project, plugin);

	{
	std::ofstream fstream;
	fstream.open(out_path);
		fstream << prefix_list.get_string() << "\n";

		fstream << author.get_string() << "\n\n";
		fstream << project.get_string() << "\n\n";
		fstream << plugin.get_string() << "\n\n";
	fstream.close();
	}
}