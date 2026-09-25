/***************************************************************************
 *            test_array.cpp
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

#include "array.hpp"
#include "container.hpp"

#include "test.hpp"

using namespace Helper;

struct TestConvertibleTo {
    TestConvertibleTo(int a_) : a(a_) { }
    int a;
};

struct TestClass {
    TestClass(int a_) : a(a_) { }
    explicit TestClass(TestConvertibleTo const& c) : TestClass(c.a) { }
    int a;
};

class TestArray {
  public:

    void test_convert() {
        Array<TestClass> tca = {TestClass(1), TestClass(2)};
        Array<TestConvertibleTo> tcta = {TestConvertibleTo(1), TestConvertibleTo(2)};
        HELPER_TEST_EXECUTE(Array<TestClass> tcac(tcta));
    }

    void test_print() {
        Array<int> a1;
        HELPER_TEST_PRINT(a1);
        Array<int> a2 = {1, 2};
        HELPER_TEST_PRINT(a2);
    }

    void test() {
        HELPER_TEST_CALL(test_convert());
        HELPER_TEST_CALL(test_print());
    }

};

int main() {
    TestArray().test();
    return HELPER_TEST_FAILURES;
}
