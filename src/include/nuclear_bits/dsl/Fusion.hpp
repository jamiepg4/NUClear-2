/*
 * Copyright (C) 2013-2016 Trent Houliston <trent@houliston.me>, Jake Woods <jake.f.woods@gmail.com>
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

#ifndef NUCLEAR_DSL_FUSION_HPP
#define NUCLEAR_DSL_FUSION_HPP

#include "nuclear_bits/threading/ReactionHandle.hpp"
#include "nuclear_bits/dsl/fusion/BindFusion.hpp"
#include "nuclear_bits/dsl/fusion/GetFusion.hpp"
#include "nuclear_bits/dsl/fusion/PreconditionFusion.hpp"
#include "nuclear_bits/dsl/fusion/PriorityFusion.hpp"
#include "nuclear_bits/dsl/fusion/RescheduleFusion.hpp"
#include "nuclear_bits/dsl/fusion/PostconditionFusion.hpp"

namespace NUClear {
    namespace dsl {

        template <typename... TWords>
        struct Fusion
        : public fusion::BindFusion<TWords...>
        , public fusion::GetFusion<TWords...>
        , public fusion::PreconditionFusion<TWords...>
        , public fusion::PriorityFusion<TWords...>
        , public fusion::RescheduleFusion<TWords...>
        , public fusion::PostconditionFusion<TWords...> {};

    }  // namespace dsl
}  // namespace NUClear

#endif  // NUCLEAR_DSL_FUSION_HPP
