/***************************************************************************
 *            test_lru_cache.cpp
 *
 *  Copyright  2009-21  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Helper.
 *
 *  Helper is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Helper is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Helper.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>

#include "string.hpp"
#include "lru_cache.hpp"

#include "test.hpp"

using namespace Helper;

using CacheType = LRUCache<String,int>;

class TestLRUCache {
  public:

    void test_construct() {
        HELPER_TEST_FAIL(CacheType(0));
        CacheType cache(1);
        HELPER_TEST_EQUALS(cache.current_size(),0);
        HELPER_TEST_EQUALS(cache.maximum_size(),1);
    }

    void test_find() {
        CacheType cache(2);
        HELPER_TEST_ASSERT(not cache.has_label("something"));
    }

    void test_get_failure() {
        CacheType cache(2);
        HELPER_TEST_FAIL(cache.get("something"));
    }

    void test_put_single() {
        CacheType cache(2);
        cache.put("first",42);
        HELPER_TEST_EQUALS(cache.current_size(),1);
        HELPER_TEST_EQUALS(cache.age("first"),0);
        auto val = cache.get("first");
        HELPER_TEST_EQUALS(val,42);
    }

    void test_put_multiple() {
        CacheType cache(2);
        cache.put("first",42);
        cache.put("second",10);
        HELPER_TEST_EQUALS(cache.current_size(),2);
        HELPER_TEST_EQUALS(cache.age("first"),1);
        HELPER_TEST_EQUALS(cache.age("second"),0);
    }

    void test_put_multiple_over() {
        CacheType cache(3);
        cache.put("first",42);
        cache.put("second",10);
        cache.put("third",5);
        cache.put("fourth",12);
        HELPER_TEST_EQUALS(cache.current_size(),3);
        HELPER_TEST_ASSERT(not cache.has_label("first"));
        HELPER_TEST_EQUALS(cache.age("second"),2);
        HELPER_TEST_EQUALS(cache.age("third"),1);
        HELPER_TEST_EQUALS(cache.age("fourth"),0);
    }

    void test_get() {
        CacheType cache(4);
        cache.put("first",42);
        cache.put("second",10);
        cache.put("third",5);
        cache.put("fourth",12);
        cache.get("second");
        HELPER_TEST_EQUALS(cache.age("second"),0);
        HELPER_TEST_EQUALS(cache.age("first"),3);
        HELPER_TEST_EQUALS(cache.age("third"),2);
        HELPER_TEST_EQUALS(cache.age("fourth"),1);
    }

    void test() {
        HELPER_TEST_CALL(test_construct());
        HELPER_TEST_CALL(test_find());
        HELPER_TEST_CALL(test_get_failure());
        HELPER_TEST_CALL(test_put_single());
        HELPER_TEST_CALL(test_put_multiple());
        HELPER_TEST_CALL(test_put_multiple_over());
        HELPER_TEST_CALL(test_get());
    }

};

int main() {
    TestLRUCache().test();
    return HELPER_TEST_FAILURES;
}
