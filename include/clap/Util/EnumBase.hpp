#pragma once

#include <boost/optional.hpp>
#include <variant>

namespace clap::detail::util
{
////////////////////////////////////////////////////////////
// EnumBase
////////////////////////////////////////////////////////////

template<class... Ts> class EnumBase
{
public:
	template<class T> bool is() const { return std::holds_alternative<T>(inner_); }

	template<class T> T& get() { return std::get<T>(inner_); }

	template<class T> const T& get() const { return std::get<T>(inner_); }

	template<class T> T *get_ptr() { return std::get_if<T>(&inner_); }

	template<class T> const T *get_ptr() const { return std::get_if<T>(&inner_); }

    template<class T>
	boost::optional<T&> try_get()
	{
		if (auto ptr = std::get_if<T>(&inner_); ptr == nullptr)
		{
			return {};
		}
		else
		{
			return *ptr;
		}
	}

	template<class T>
	boost::optional<T&> try_get() const
	{
		if (auto ptr = std::get_if<T>(&inner_); ptr == nullptr)
		{
			return {};
		}
		else
		{
			return *ptr;
		}
	}

protected:
	template<class T>
	EnumBase(T&& value) : inner_ {std::in_place_type<T>, std::forward<T>(value)}
	{
	}

	using Inner = std::variant<Ts...>;

	Inner& inner() { return inner_; }
private:
	Inner inner_;
};
} // namespace clap::detail::util