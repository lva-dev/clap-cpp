#pragma once

#include <clap/Parser/MatchedArg.hpp>
#include <clap/Util/Macros.hpp>
#include <clap/Util/Util.hpp>

#include <boost/none.hpp>
#include <boost/optional.hpp>

#include <algorithm>
#include <any>
#include <flat_map>
#include <format>
#include <ranges>
#include <string>
#include <typeindex>

#include "clap/Error/Exception.hpp"

namespace clap::parser::detail
{
class ArgMatcher;
}

namespace clap::parser
{
class ArgMatches
{
public:
	bool get_flag(const std::string& id) const
	{
		if (auto value = get_one<bool>(id); value.has_value())
		{
			return *value;
		}

		throw error::Exception::formatted(
			"arg `{}`'s `ArgAction` should be one of `SetTrue`, "
			"`SetFalse` which should provide a default",
			id);
	}

	template<class T> boost::optional<const T&> get_one(const std::string& id) const
	{
		if (auto arg = get_arg_t<T>(id); arg.has_value())
		{
			return *std::any_cast<T>(&arg->values().front());
		}

		return {};
	}

	bool contains_id(const std::string& id) const { return args.contains(id); }
private:
	std::flat_map<std::string, detail::MatchedArg> args = {};
#ifdef CLAP_CONFIG_DEBUG
	std::vector<std::string> valid_args;
#endif

	friend parser::detail::ArgMatcher;

	static ArgMatches create(decltype(valid_args)&& valid_args)
	{
		return ArgMatches {std::move(valid_args)};
	};

	ArgMatches(decltype(valid_args)&& valid_args) : valid_args {std::move(valid_args)} {}

	boost::optional<const detail::MatchedArg&> get_arg(const std::string& id) const
	{
#ifdef CLAP_CONFIG_DEBUG
		if (!std::ranges::contains(valid_args, id))
		{
			throw error::Exception::formatted(
				"`{}` is not an id of an argument.\n"
				"Make sure you're using the name of the argument"
				"itself and not the name of short or long flags.",
				id);
		}
#endif

		return ::clap::detail::util::container::try_get(args, id);
	}

	template<class T>
	boost::optional<const detail::MatchedArg&> get_arg_t(const std::string& id) const
	{
		auto arg = get_arg(id);
		if (!arg.has_value())
		{
			return {};
		}

		if (arg->type() != typeid(T))
		{
			throw error::Exception::formatted(
				"Could not any_cast to {}, need to any_cast to {}",
				typeid(T).name(),
				arg->type().name());
		}

		return arg;
	}
};
} // namespace clap::parser