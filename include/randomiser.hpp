/***************************************************************************
 *            randomiser.hpp
 *
 *  Copyright  2011-20  Luca Geretti
 *
 ****************************************************************************/

/*
 * This file is part of Utility, under the MIT license.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*! \file randomiser.hpp
 *  \brief Generators of random numbers for a type.
 *  \details The values are generated uniformly in the provided interval.
 */

#ifndef UTILITY_RANDOMISER_HPP
#define UTILITY_RANDOMISER_HPP

#include <random>

namespace Utility {

template<class T> class RandomiserInterface {
  public:
    virtual T get() = 0;
};

template<class T> class RandomiserBase : public RandomiserInterface<T> {
  protected:
    RandomiserBase() {
        std::random_device rd;
        std::mt19937::result_type seed = rd() ^ (
                (std::mt19937::result_type) std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
                (std::mt19937::result_type) std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
                );

        _engine = std::mt19937(seed);
    }

    std::mt19937 _engine;
};

template<class T> struct UniformRealRandomiser : public RandomiserBase<T> {
  public:
    UniformRealRandomiser(T min, T max) : RandomiserBase<T>(), _distribution(min,max) { }
    T get() override { return _distribution(this->_engine); }
  private:
    std::uniform_real_distribution<T> _distribution;
};

template<class T> struct UniformIntRandomiser : public RandomiserBase<T> {
  public:
    UniformIntRandomiser(T min, T max) : RandomiserBase<T>(), _distribution(min,max) { }
    T get() override { return _distribution(this->_engine); }
  private:
    std::uniform_int_distribution<T> _distribution;
};

} // namespace Utility

#endif /* UTILITY_RANDOMISER_HPP */
