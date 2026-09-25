/***************************************************************************
 *            test_lazy.cpp
 *
 *  Copyright  2023  Luca Geretti
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
#include "lazy.hpp"

#include "test.hpp"

using namespace Helper;

class TestClass {
  public:
    TestClass(double a) {
        _value = a*a;
        HELPER_TEST_PRINT("TestClass object created")
    }

    double value() { return _value; }

  private:
    double _value;
};

class TestLazy {
  public:

    void test_creation() {
        double arg = 2.0;
        Lazy<TestClass> lazy([arg]{ return new TestClass(arg); });

        HELPER_TEST_PRINT("Lazy created")
        TestClass obj = lazy();
        HELPER_TEST_EQUAL(obj.value(),4.0)
    }

    void test() {
        HELPER_TEST_CALL(test_creation());
    }

};

int main() {
    TestLazy().test();
    return HELPER_TEST_FAILURES;
}
