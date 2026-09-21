#pragma once

#include <clap/Util/Concepts.hpp>

#include <any>
#include <functional>
#include <span>
#include <typeindex>
#include <typeinfo>

namespace clap::parser::detail
{
class MatchedArg
{
public:
	auto values() const -> concepts::ranges::ViewOf<std::any> auto
	{
		return std::span<const std::any> {&value_, 1};
	}

	const std::type_info& type() const { return type_.get(); }
private:
	std::any value_;
	std::reference_wrapper<const std::type_info> type_;
};
} // namespace clap::detail::parser