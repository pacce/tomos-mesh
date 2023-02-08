#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <tomos/tomos-mesh.hpp>

TEST(Elements, Parse) {
    std::string ss = 
        "$Elements\n"
        "2\n"
        "1 3 2 99 2 1 2 3 4\n"
        "2 3 2 99 2 2 5 6 3\n"
        "$EndElements\n"
        ;
    tomos::mesh::Elements expected = {
          {tomos::mesh::element::Type::QUADRANGLE4, {0, 1, 2, 3}}
        , {tomos::mesh::element::Type::QUADRANGLE4, {1, 4, 5, 2}}
    };
    tomos::mesh::Elements actual;

    using Iterator = std::string::iterator;

    tomos::mesh::decoder::elements<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    ASSERT_EQ(actual.size(), expected.size());
    for (std::size_t i = 0; i < actual.size(); i++) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
