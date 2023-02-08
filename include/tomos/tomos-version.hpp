#ifndef TOMOS_VERSION_HPP__
#define TOMOS_VERSION_HPP__

#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <ostream>

namespace tomos {
namespace mesh {
    struct Version {
        float   version;
        int32_t format;
        int32_t size;

        friend bool
        operator==(const Version& lhs, const Version& rhs) {
            return lhs.version  == rhs.version
                && lhs.format   == rhs.format
                && lhs.size     == rhs.size
                ;
        }

        friend bool
        operator!=(const Version& lhs, const Version& rhs) {
            return lhs.version  != rhs.version
                || lhs.format   != rhs.format
                || lhs.size     != rhs.size
                ;
        }

        friend std::ostream&
        operator<<(std::ostream& os, const Version& v) {
            os  << v.version
                << " "
                << v.format
                << " "
                << v.size
                ;
            return os;
        }
    };
} // namespace mesh
} // namespace tomos

BOOST_FUSION_ADAPT_STRUCT(
        tomos::mesh::Version,
        (float,     version)
        (int32_t,   format)
        (int32_t,   size)
        );

namespace tomos {
namespace mesh {
namespace decoder {
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct version : qi::grammar<Iterator, Version> {
        version() : version::base_type(rule) {
            rule %= qi::skip(qi::eol)
                [  qi::lit("$MeshFormat")
                >> qi::skip(qi::space)[qi::float_ >> qi::int_(0) >> qi::int_(8)]
                >> qi::lit("$EndMeshFormat")
                ]
                ;
        }

        qi::rule<Iterator, Version>  rule;
    };
} // namespace decoder
} // namespace mesh
} // namespace tomos

#endif // TOMOS_VERSION_HPP__
