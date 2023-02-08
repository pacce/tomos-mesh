#include <gtest/gtest.h>
#include <tomos/tomos-mesh.hpp>

TEST(Mesh, Grammar) {
    std::string ss = 
        "$MeshFormat\n"
        "2.2 0 8\n"
        "$EndMeshFormat\n"
        "$Nodes\n"
        "6\n"
        "1 0.0 0.0 0.0\n"
        "2 1.0 0.0 0.0\n"
        "3 1.0 1.0 0.0\n"
        "4 0.0 1.0 0.0\n"
        "5 2.0 0.0 0.0\n"
        "6 2.0 1.0 0.0\n"
        "$EndNodes\n"
        "$Elements\n"
        "2\n"
        "1 3 2 99 2 1 2 3 4\n"
        "2 3 2 99 2 2 5 6 3\n"
        "$EndElements\n"
        ;
    tomos::mesh::Nodes nodes = {
          {{0.0f, 0.0f, 0.0f}}
        , {{1.0f, 0.0f, 0.0f}}
        , {{1.0f, 1.0f, 0.0f}}
        , {{0.0f, 1.0f, 0.0f}}
        , {{2.0f, 0.0f, 0.0f}}
        , {{2.0f, 1.0f, 0.0f}}
    };
    tomos::mesh::Elements elements = {
          {tomos::mesh::element::Type::QUADRANGLE4, {0, 1, 2, 3}}
        , {tomos::mesh::element::Type::QUADRANGLE4, {1, 4, 5, 2}}
    };
    tomos::mesh::Mesh expected = {nodes, elements};
    tomos::mesh::Mesh actual;

    using Iterator = std::string::iterator;

    tomos::mesh::decoder::mesh<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);

    ASSERT_EQ(actual.nodes.size(), expected.nodes.size());
    for (std::size_t i = 0; i < actual.nodes.size(); i++) {
    for (std::size_t j = 0; j < 3; j++) {
        EXPECT_EQ(actual.nodes[i].s[j], expected.nodes[i].s[j]);
    }
    }

    ASSERT_EQ(actual.elements.size(), expected.elements.size());
    for (std::size_t i = 0; i < actual.elements.size(); i++) {
        EXPECT_EQ(actual.elements[i], expected.elements[i]);
    }
}
 
TEST(Mesh, Iterator) {
    std::string ss = 
        "$MeshFormat\n"
        "2.2 0 8\n"
        "$EndMeshFormat\n"
        "$Nodes\n"
        "6\n"
        "1 0.0 0.0 0.0\n"
        "2 1.0 0.0 0.0\n"
        "3 1.0 1.0 0.0\n"
        "4 0.0 1.0 0.0\n"
        "5 2.0 0.0 0.0\n"
        "6 2.0 1.0 0.0\n"
        "$EndNodes\n"
        "$Elements\n"
        "2\n"
        "1 3 2 99 2 1 2 3 4\n"
        "2 3 2 99 2 2 5 6 3\n"
        "$EndElements\n"
        ;
    tomos::mesh::Nodes nodes = {
          {{0.0f, 0.0f, 0.0f}}
        , {{1.0f, 0.0f, 0.0f}}
        , {{1.0f, 1.0f, 0.0f}}
        , {{0.0f, 1.0f, 0.0f}}
        , {{2.0f, 0.0f, 0.0f}}
        , {{2.0f, 1.0f, 0.0f}}
    };
    tomos::mesh::Elements elements = {
          {tomos::mesh::element::Type::QUADRANGLE4, {0, 1, 2, 3}}
        , {tomos::mesh::element::Type::QUADRANGLE4, {1, 4, 5, 2}}
    };
    tomos::mesh::Mesh expected  = {nodes, elements};
    tomos::mesh::Mesh actual    = tomos::mesh::decode(ss.begin(), ss.end());

    ASSERT_EQ(actual.nodes.size(), expected.nodes.size());
    for (std::size_t i = 0; i < actual.nodes.size(); i++) {
    for (std::size_t j = 0; j < 3; j++) {
        EXPECT_EQ(actual.nodes[i].s[j], expected.nodes[i].s[j]);
    }
    }

    ASSERT_EQ(actual.elements.size(), expected.elements.size());
    for (std::size_t i = 0; i < actual.elements.size(); i++) {
        EXPECT_EQ(actual.elements[i], expected.elements[i]);
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
