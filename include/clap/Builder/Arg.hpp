#pragma once

#include <clap/Builder/ArgAction.hpp>
#include <clap/Util/Util.hpp>

#include <boost/optional.hpp>

#include <optional>
#include <string>

namespace clap::builder
{
class Arg
{
public:
	static Arg create(const std::string& id) { return Arg {id}; }

	Arg short_(char name) &&
	{
		short_name_ = name;
		return std::move(*this);
	}

	Arg long_(std::string&& name) &&
	{
		long_name_ = std::move(name);
		return std::move(*this);
	}

	Arg required(bool yes) &&
	{
		is_required = yes;
		return std::move(*this);
	}

	Arg action(ArgAction action) &&
	{
		action_ = action;
		return std::move(*this);
	}

	const std::string& get_id() const { return id; }

	std::optional<char> get_short() const { return short_name_; }

	boost::optional<const std::string&> get_long() const
	{
		return ::clap::detail::util::optional::as_ref(long_name_);
	}

	ArgAction get_action() const { return action_; }

	bool is_positional() const { return !is_short() && !is_long(); }

	bool is_short() const { return short_name_.has_value(); }

	bool is_long() const { return long_name_.has_value(); }

	bool is_required_set() const { return is_required; }
private:
	std::string id;
	std::optional<char> short_name_;
	std::optional<std::string> long_name_;
	ArgAction action_ = ArgAction::Set;
	bool is_required = false;

	Arg(const std::string& id) : id {id} {}
};
} // namespace clap::builder