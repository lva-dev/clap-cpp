#pragma once

#include <clap/Util/Concepts.hpp>
#include <clap/Util/Macros.hpp>

#include <concepts>
#include <functional>
#include <print>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#ifdef CLAP_CONFIG_DEBUG
namespace clap::debug
{
template<std::invocable F> void debug(F&& f)
{
	std::invoke(std::forward<F>(f));
}

void debug_assert(concepts::functional::BoolSupplier auto&& conditionFn,
	concepts::functional::StringSupplier auto&& formatFn,
	std::source_location src = std::source_location::current())
{
	if (std::invoke_r<bool>(std::forward<decltype(conditionFn)>(conditionFn)))
	{

		std::print(stderr,
			"failed assertion in function `{}` in file {}:{}:{}",
			src.function_name(),
			src.file_name(),
			src.line(),
			src.column());

		auto msg = std::invoke_r<std::string>(std::forward<decltype(formatFn)>(formatFn));
		if (!msg.empty())
		{
			std::print(stderr, ": {}", msg);
		}

		std::println(stderr);
	}
}

template<concepts::functional::BoolSupplier ConditionFn>
void debug_assert(ConditionFn&& condition,
	std::string_view msg = {},
	std::source_location src = std::source_location::current())
{
	debug_assert(
		std::forward<ConditionFn>(condition), [msg]() { return std::string {msg}; }, src);
}
} // namespace clap::debug
#else
namespace clap::debug
{
template<std::invocable F> void debug(F&& f) {}

template<class C, class Fmt>
void debug_assert(C&& cnd, Fmt&&, std::source_location src = {})
{
}

template<concepts::functional::Supplier<bool> C>
void debug_assert(C&& cnd, std::string_view msg = {}, std::source_location src = {})
{
}
} // namespace clap::debug
#endif