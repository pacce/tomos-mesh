#ifndef TOMOS_MESH_HPP__
#define TOMOS_MESH_HPP__

#include <filesystem>

#include "tomos-elements.hpp"
#include "tomos-nodes.hpp"
#include "tomos-version.hpp"

namespace tomos {
namespace mesh {
    struct Mesh {
        Nodes       nodes;
        Elements    elements;

        Mesh() {}
        Mesh(const Nodes& ns, const Elements& es) : nodes(ns), elements(es) {}

        // template <typename Precision>
        // Mesh(const ::mesh::Mesh<Precision>& source) {
        //     nodes.reserve(source.nodes.size());
        //     for (const auto& [_, n] : source.nodes) {
        //         nodes.push_back({n.x(), n.y(), n.z()});
        //     }
        //     elements.reserve(source.element.size());
        //     for (const auto& [_, e] : source.element) {
        //         tomos::mesh::element::Type type;
        //         switch (e.type) {
        //             case ::mesh::element::Type::LINE2:          { type = tomos::mesh::element::Type::LINE2; break; }
        //             case ::mesh::element::Type::TRIANGLE3:      { type = tomos::mesh::element::Type::TRIANGLE3; break; }
        //             case ::mesh::element::Type::QUADRANGLE4:    { type = tomos::mesh::element::Type::QUADRANGLE4; break; }
        //             case ::mesh::element::Type::TETRATHEDRON4:  { type = tomos::mesh::element::Type::TETRATHEDRON4; break; }
        //             case ::mesh::element::Type::HEXAHEDRON8:    { type = tomos::mesh::element::Type::HEXAHEDRON8; break; }
        //             case ::mesh::element::Type::PRISM6:         { type = tomos::mesh::element::Type::PRISM6; break; }
        //             case ::mesh::element::Type::PYRAMID5:       { type = tomos::mesh::element::Type::PYRAMID5; break; }
        //             case ::mesh::element::Type::LINE3:          { type = tomos::mesh::element::Type::LINE3; break; }
        //             case ::mesh::element::Type::TRIANGLE6:      { type = tomos::mesh::element::Type::TRIANGLE6; break; }
        //             case ::mesh::element::Type::QUADRANGLE9:    { type = tomos::mesh::element::Type::QUADRANGLE9; break; }
        //             case ::mesh::element::Type::TETRAHEDRON10:  { type = tomos::mesh::element::Type::TETRAHEDRON10; break; }
        //             case ::mesh::element::Type::HEXAHEDRON27:   { type = tomos::mesh::element::Type::HEXAHEDRON27; break; }
        //             case ::mesh::element::Type::PRISM18:        { type = tomos::mesh::element::Type::PRISM18; break; }
        //             case ::mesh::element::Type::PYRAMID14:      { type = tomos::mesh::element::Type::PYRAMID14; break; }
        //             case ::mesh::element::Type::POINT1:         { type = tomos::mesh::element::Type::POINT1; break; }
        //             case ::mesh::element::Type::QUADRANGLE8:    { type = tomos::mesh::element::Type::QUADRANGLE8; break; }
        //             case ::mesh::element::Type::HEXAHEDRON20:   { type = tomos::mesh::element::Type::HEXAHEDRON20; break; }
        //             case ::mesh::element::Type::PRISM15:        { type = tomos::mesh::element::Type::PRISM15; break; }
        //             case ::mesh::element::Type::PYRAMID13:      { type = tomos::mesh::element::Type::PYRAMID13; break; }
        //         }
        //         tomos::mesh::node::Numbers indices;
        //         indices.reserve(e.nodes.size());
        //         for (auto index : e .nodes) { indices.push_back(index - 1); }

        //         elements.push_back({type, indices});
        //     }
        // }
    };
} // namespace mesh
} // namespace tomos

BOOST_FUSION_ADAPT_STRUCT(
        tomos::mesh::Mesh,
        (tomos::mesh::Nodes,    nodes)
        (tomos::mesh::Elements, elements)
        );

namespace tomos {
namespace mesh {
namespace decoder {
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct mesh : qi::grammar<Iterator, Mesh> {
        mesh() : mesh::base_type(rule) {
            rule %= qi::omit[versionp]
                >>  nodesp
                >>  elementsp
                ;
        }

        version<Iterator>           versionp;
        nodes<Iterator>             nodesp;
        elements<Iterator>          elementsp;

        qi::rule<Iterator, Mesh>    rule;
    };
} // namespace decoder
    template <typename Iterator>
    Mesh
    decode(const Iterator begin, const Iterator end) {
        tomos::mesh::Mesh msh;

        tomos::mesh::decoder::mesh<Iterator> grammar;
        if (!boost::spirit::qi::parse(begin, end, grammar, msh)) {
            throw std::runtime_error("failed to decode mesh file");
        }
        return msh;
    }

    Mesh
    decode(const std::filesystem::path& path);
} // namespace mesh
} // namespace tomos

#endif // TOMOS_MESH_HPP__
