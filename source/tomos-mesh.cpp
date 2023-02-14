#include "tomos/tomos-mesh.hpp"

#include <fstream>

namespace tomos {
namespace mesh {
    Mesh
    decode(const std::filesystem::path& p) {
        std::ifstream handle(p);
        if (not handle.is_open()) { throw std::runtime_error("could not open mesh file"); }
        handle.unsetf(std::ios::skipws);

        return tomos::mesh::decode(boost::spirit::istream_iterator(handle), {});
    }
} // namespace mesh
} // namespace tomos
