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

#include <cstdlib>
#include <time.h>
#include "typedefs.hpp"

namespace Utility {

template<class T> struct Randomiser;

template<> struct Randomiser<double> {
    //! \get Return a value between 0 and \a value
    static double get(ExactDouble const& min, double const& max) {
        double min_d = min.get_d();
        double max_d = max.get_d();
        return static_cast<double>((max_d-min_d)*rand()/RAND_MAX + min_d);
    }
};

template<> struct Randomiser<size_t> {
    //! \get Return a value between 0 and \a value
    static size_t get(DegreeType const& min, size_t const& max) {
        return static_cast<size_t>(min + rand() % (max-min+1));
    }
};

} // namespace Utility

inline bool _init_randomiser() {
    srand(time(nullptr));
    return true;
}

static const bool init_randomiser = _init_randomiser();

#endif /* UTILITY_RANDOMISER_HPP */
