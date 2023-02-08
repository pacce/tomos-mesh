#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <tomos/tomos-mesh.hpp>

TEST(Version, Parse) {
    std::string ss =
        "$MeshFormat\n"
        "2.2 0 8\n"
        "$EndMeshFormat\n"
        ;
    tomos::mesh::Version expected  = {2.2, 0, 8};
    tomos::mesh::Version actual    = {};

    using Iterator = std::string::iterator;

    tomos::mesh::decoder::version<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
