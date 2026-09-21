#pragma once

#include <concepts>
#include <ranges>

namespace clap::concepts::ranges
{
template<class Range, class T>
concept RangeTo = std::ranges::range<Range>
				  && std::convertible_to<std::ranges::range_value_t<Range>, T>;

template<class Range, class T>
concept ViewOf =
	std::ranges::view<Range> && std::same_as<std::ranges::range_value_t<Range>, T>;
} // namespace clap::concepts::ranges

namespace clap::concepts::functional
{
template<class F, class R>
concept Supplier = std::is_invocable_r_v<R, F>;

template<class F>
concept BoolSupplier = Supplier<F, bool>;

template<class F>
concept StringSupplier = Supplier<F, std::string>;
} // namespace clap::concepts::functional

namespace clap::concepts
{
template<class From, class To>
concept ActuallyConvertibleTo = std::convertible_to<std::remove_cvref_t<From>, To>;
}