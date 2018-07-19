
#include <vector>
#include <exception>

#include "catch.hpp"
#include "vector.hpp"

TEST_CASE("Constructing vector") {

    SECTION("simple constructor") {
        art::vector<int> art_vec;
        art::vector<int>::size_type expected_capacity = 0;
        REQUIRE(art_vec.capacity() == expected_capacity);
        REQUIRE(art_vec.size() == expected_capacity);
        REQUIRE(art_vec.empty());
    }

    SECTION("pass size") {
        art::vector<int>::size_type expected_size = 7;
        art::vector<int> art_vec(expected_size);
        REQUIRE(art_vec.size() == expected_size);
        REQUIRE(art_vec.capacity() >= expected_size);
    }

    SECTION("pass size and value") {
        std::vector<int>::size_type expected_size = 7;
        std::vector<int>::value_type expected_value = 125;
        std::vector<int> expected(expected_size, expected_value);
        art::vector<int> art_vec(expected_size, expected_value);
        REQUIRE(art_vec.capacity() >= expected.size());
        REQUIRE(art_vec.size() == expected.size());
        REQUIRE(art_vec == expected);
    }

    SECTION("pass two iterators") {
        std::vector<int> expected{4, 5, 65, 7841};
        art::vector<int> art_vec(expected.begin(), expected.end());
        REQUIRE(art_vec.capacity() >= expected.size());
        REQUIRE(art_vec == expected);
    }

    SECTION("pass initializer list") {
        std::vector<int> expected{1, 2, 3, 4};
        art::vector<int> art_vec{1, 2, 3, 4};
        REQUIRE(art_vec.capacity() >= expected.size());
        REQUIRE(art_vec == expected);
    }
}

TEST_CASE("STL eqaul") {
    SECTION ("Compare functions") {
        std::vector<int> std_vec_1 = {1, 2, 3};
        std::vector<int> std_vec_2 = {1, 2, 3, 4};
        art::vector<int> art_vec_1 = {1, 2, 3};
        art::vector<int> art_vec_2 = {1, 2, 3, 4};
        REQUIRE(art_vec_1[0] == 1);
        REQUIRE(art_vec_1[1] == 2);
        REQUIRE(art_vec_1[2] == 3);
        REQUIRE((std_vec_1 < std_vec_2) == (art_vec_1 < art_vec_2));
    }

    SECTION("std::sort") {
        std::vector<int> std_vec = {0, 1, 2, 3, 4, 5};
        art::vector<int> art_vec = {5, 3, 2, 4, 1, 0};
        std::sort(art_vec.begin(), art_vec.end());
        REQUIRE(art_vec == std_vec);
    }

}

TEST_CASE("Data info access") {

    SECTION("vector size") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 4};
        REQUIRE(art_vec.max_size() == std_vec.max_size());
    }

    SECTION("At access") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 4};
        REQUIRE(art_vec.at(1) == std_vec.at(1));
        REQUIRE(art_vec.at(2) == std_vec.at(2));
        REQUIRE(art_vec.at(3) == std_vec.at(3));
        REQUIRE(art_vec[3] == std_vec[3]);
        REQUIRE_FALSE(art_vec.at(3) == std_vec.at(1));
    }

    SECTION("Front and back access") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 4};
        REQUIRE(art_vec.front() == std_vec.front());
        REQUIRE(art_vec.back() == std_vec.back());
    }

    SECTION("Data access") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 4};
        REQUIRE(*(art_vec.data()) == *(std_vec.data()));
    }

    SECTION("Allocator access") {
        art::vector<int> art_vec = {1, 2, 3, 4};
        typename art::vector<int>::allocator_type a = art_vec.get_allocator();
        REQUIRE(a == art_vec.get_allocator());
        REQUIRE_FALSE(a != art_vec.get_allocator());
    }

}

TEST_CASE("Vectors copy operator") {

    SECTION("Assign vector to initializer list") {
        std::vector<int> std_vec;
        std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec;
        art_vec = {1, 2, 3, 4};
        REQUIRE(art_vec.capacity() >= std_vec.size());
        REQUIRE(art_vec == std_vec);
    }

    SECTION("Assign vector to vector") {
        art::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec;
        art_vec = std_vec;
        REQUIRE(art_vec == std_vec);
    }

    SECTION("Move assign vector to vector") {
        art::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> moveable = {1, 2, 3, 4};
        art::vector<int> art_vec;
        art_vec = std::move(moveable);
        REQUIRE(art_vec == std_vec);
        REQUIRE(moveable.empty());
    }

    SECTION("Assign vector to the same vector") {
        art::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 4};
        art_vec = art_vec;
        art_vec = std::move(art_vec);
        REQUIRE(art_vec == std_vec);
    }

}

TEST_CASE("Vector resizing") {

    SECTION("Pass size") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        std_vec.resize(3);
        art::vector<int> art_vec = {1, 2, 3, 4};
        art_vec.resize(3);
        REQUIRE(art_vec.capacity() >= std_vec.size());
        REQUIRE(art_vec == std_vec);
    }

    SECTION("Pass size and default value for added elements") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        std_vec.resize(6, 3);
        art::vector<int> art_vec = {1, 2, 3, 4};
        art_vec.resize(6, 3);
        REQUIRE(art_vec.capacity() >= std_vec.size());
        REQUIRE(art_vec == std_vec);
    }
}

TEST_CASE("reserve") {

    SECTION("pass integer") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        std_vec.reserve(20);
        art::vector<int> art_vec = {1, 2, 3, 4};
        art_vec.reserve(20);
        REQUIRE(art_vec.capacity() >= std_vec.capacity());
        REQUIRE(art_vec.size() == 4);
        REQUIRE(art_vec == std_vec);
    }

}

TEST_CASE("Vector modifications") {

    SECTION("assign function passing size and value") {
        std::vector<int> std_vec;
        std_vec.assign(5, 1);
        art::vector<int> art_vec;
        art_vec.assign(5, 1);
        REQUIRE(art_vec.capacity() >= std_vec.size());
        REQUIRE(art_vec == std_vec);
    }

    SECTION("assign funtion passing two iterators") {
        art::vector<int> std_vec{1, 2, 3, 4, 5};
        art::vector<int> art_vec;
        art_vec.assign(std_vec.begin(), std_vec.end());
        REQUIRE(art_vec.capacity() >= std_vec.size());
        REQUIRE(art_vec == std_vec);
    }

    SECTION("push_back") {
        art::vector<int> expected = {9, 6, 44, 52, 1};
        art::vector<int> art_vec;
        art_vec.push_back(9);
        art_vec.push_back(6);
        art_vec.push_back(44);
        art_vec.push_back(52);
        art_vec.push_back(1);
        REQUIRE(art_vec.size() == expected.size());
        REQUIRE(art_vec[0] == expected[0]);
        REQUIRE(art_vec[4] == expected[4]);
        REQUIRE(art_vec[1] == 6);
        REQUIRE(art_vec[2] == 44);
    }

    SECTION("pop items") {
        std::vector<int> std_vec = {1};
        art::vector<int> art_vec = {1, 2, 3, 4};
        for (int i = 0; i < 3; ++i) {
            art_vec.pop_back();
        }
        REQUIRE(art_vec == std_vec);
    }

    SECTION("insert one item") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 3, 4};
        art_vec.insert(art_vec.begin() + 1, 2);
        REQUIRE(art_vec == std_vec);
    }

    SECTION("insert iterator range") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> resourse = {2, 3, 4};
        art::vector<int> art_vec = {1};
        art_vec.insert(art_vec.begin() + 1, resourse.begin(), resourse.end());
        REQUIRE(art_vec == std_vec);
    }

    SECTION("insert initializer list") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1};
        art_vec.insert(art_vec.begin() + 1, {2, 3, 4});
        REQUIRE(art_vec == std_vec);
    }

    SECTION("erase one element") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 3, 4};
        art_vec.erase(art_vec.begin() + 2);
        REQUIRE(art_vec == std_vec);
    }

    SECTION("erase elements") {
        std::vector<int> std_vec = {1, 2, 3, 4};
        art::vector<int> art_vec = {1, 2, 3, 3, 3, 3, 4};
        art_vec.erase(art_vec.begin() + 2, art_vec.begin() + 5);
        REQUIRE(art_vec == std_vec);
    }

    SECTION("clear vector") {
        art::vector<int> art_vec = {1, 2, 3, 4, 5};
        art_vec.clear();
        REQUIRE(art_vec.capacity() == 0);
        REQUIRE(art_vec.empty());
    }

    SECTION("shrink vector") {
        art::vector<int> art_vec = {1, 2, 3, 4, 5, 6};
        art_vec.shrink_to_fit();
        REQUIRE(art_vec.capacity() == art_vec.size());
    }
    SECTION("emplace item back") {
        art::vector<int>::value_type val = 4;
        art::vector<int> art_vec;
        art_vec.emplace_back(4);
        REQUIRE(art_vec.front() == val);
    }
}

TEST_CASE("Iterator tests") {

    SECTION("iter compare") {
        art::vector<int> art_vec = {1, 2, 3, 4, 5};
        art::vector<int>::iterator first = art_vec.begin();
        art::vector<int>::iterator last = art_vec.end();
        REQUIRE(first < last);
        REQUIRE(first == first);
        REQUIRE(last > first);
        REQUIRE(last >= last);
        REQUIRE(last >= first);
        REQUIRE(first <= last);
        REQUIRE(first <= first);
        REQUIRE(first != last);
    }

    SECTION("forward iteration") {
        std::vector<int> std_vec = {1, 2, 3, 4, 5, 6, 7};
        art::vector<int> art_vec = {1, 2, 3, 4, 5, 6, 7};
        int i = 0;
        for (art::vector<int>::iterator it = art_vec.begin(); it != art_vec.end(); ++it, ++i) {
            REQUIRE(*it == std_vec[i]);
        }
    }

    SECTION("backward iteration") {
        std::vector<int> std_vec = {1, 2, 3, 4, 5, 6, 7};
        int i = 6;
        art::vector<int> art_vec = {1, 2, 3, 4, 5, 6, 7};
        for (art::vector<int>::iterator it = art_vec.end() - 1; it >= art_vec.begin(); --it, --i) {
            REQUIRE(*it == std_vec[i]);
        }
    }
}

TEST_CASE("Modifier elements methods") {
    SECTION("emplace first") {
        std::vector<int> std_vec = {9, 1, 2, 3};
        art::vector<int> art_vec = {1, 2, 3};
        art_vec.emplace(art_vec.cbegin(), 9);
        REQUIRE(art_vec.size() == std_vec.size());
        REQUIRE(art_vec[0] == std_vec[0]);
        REQUIRE(art_vec[0] == 9);
    }
    SECTION("emplace into middle") {
        std::vector<int> std_vec = {1, 2, 3, 4, 5, 6};
        art::vector<int> art_vec = {1, 2, 3, 5, 6};
        art_vec.emplace(art_vec.begin() + 3, 4);
        REQUIRE(art_vec.size() == std_vec.size());
        REQUIRE(art_vec[3] == std_vec[3]);
    }
    SECTION("emplace_back") {
        std::vector<int> std_vec = {4, 2};
        art::vector<int> art_vec = {4};
        art_vec.emplace_back(2);
        REQUIRE(art_vec.size() == std_vec.size());
        REQUIRE(art_vec[1] == std_vec[1]);
    }
}

TEST_CASE("emplace_back"){
    class SomeClass{
    public:
        SomeClass() : _a(10) {}

        SomeClass(const SomeClass&) = delete;
        SomeClass(SomeClass&&) = default;

        int getA() const { return _a; }
    private:
        int _a;
    };
    SECTION("emplace_back"){
        SECTION("true emplace_back()") {
            art::vector<SomeClass> art_vec;
            art_vec.emplace_back(SomeClass());

            REQUIRE(art_vec[0].getA() == 10);
        }
    }
}