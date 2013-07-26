/**
 * Copyright (C) 2013 Jake Woods <jake.f.woods@gmail.com>, Trent Houliston <trent@houliston.me>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef NUCLEAR_INTERNAL_MAGIC_METAPROGRAMMING_H
#define NUCLEAR_INTERNAL_MAGIC_METAPROGRAMMING_H

#include <type_traits>

namespace NUClear {
namespace Internal {
namespace Magic {
namespace MetaProgramming {
namespace Meta {
    
    template <typename T>
    using Do = typename T::type;
    
    template <typename If, typename Then, typename Else = void>
    using If = Do<std::conditional<If::value, Then, Else>>;
    
    template <typename TType>
    using AddConst = Do<std::add_const<TType>>;
    
    template <typename TType>
    using AddLRef = Do<std::add_lvalue_reference<TType>>;
    
    template <typename TType>
    using RemoveRef = Do<std::remove_reference<TType>>;
    
    template <typename... T>
    struct All : std::true_type {};
    template <typename Head, typename... Tail>
    struct All<Head, Tail...> : If<Head, All<Tail...>, std::false_type> {};
    
    template <typename T>
    struct Not : If<T, std::false_type, std::true_type> {};
    
    template <typename... Conditions>
    struct EnableIf : Do<std::enable_if<All<Conditions...>::value, std::nullptr_t>> {};
    
}
}
}
}
}

#endif