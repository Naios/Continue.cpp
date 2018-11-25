
/*

                        /~` _  _ _|_. _     _ |_ | _
                        \_,(_)| | | || ||_|(_||_)|(/_

                    https://github.com/Naios/continuable
                                   v3.0.0

  Copyright(c) 2015 - 2018 Denis Blank <denis.blank at outlook dot com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files(the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions :

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
**/

#ifndef CONTINUABLE_DETAIL_RESULT_TRAIT_HPP_INCLUDED
#define CONTINUABLE_DETAIL_RESULT_TRAIT_HPP_INCLUDED

#include <tuple>
#include <type_traits>
#include <utility>
#include <continuable/detail/core/hints.hpp>
#include <continuable/detail/utility/traits.hpp>

namespace cti {
namespace detail {
template <typename... T>
struct result_trait;
template <>
struct result_trait<> {
  struct value_t {};

  static constexpr value_t wrap() noexcept {
    return {};
  }
};
template <typename T>
struct result_trait<T> {
  using value_t = T;

  static auto wrap(T arg) {
    return std::move(arg);
  }
};
template <typename First, typename Second, typename... Rest>
struct result_trait<First, Second, Rest...> {
  using value_t = std::tuple<First, Second, Rest...>;

  static auto wrap(First first, Second second, Rest... rest) {
    return std::make_tuple(std::move(first), std::move(second),
                           std::move(rest)...);
  }
};
} // namespace detail
} // namespace cti

#endif // CONTINUABLE_DETAIL_RESULT_TRAIT_HPP_INCLUDED