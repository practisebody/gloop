#pragma once

_GL_BEGIN
// helper class for factory class
template<size_t>
struct Any
{
};

// helper factory class
template<class Ret>
class Make : public std::shared_ptr<Ret>
{
public:
	using element_type = Ret;

	template<class... T>
	Make(T&&... t)
		: std::shared_ptr<Ret>(std::make_shared<Ret>())
	{
		if constexpr (sizeof...(T) > 0)
		{
			Initializer::Push([p = this->get(), t...]()
			{
				p->Data(t...);
			}, detail::ObjectType_v<std::decay_t<Ret>>);
		}
	}
};

template<class Ret, class... Args>
class Make<Ret(Args...)> : public std::shared_ptr<Ret>
{
public:
	using element_type = Ret;

	template<class... T>
	Make(Args&&... args, T&&... t)
		: std::shared_ptr<Ret>(std::make_shared<Ret>(std::forward<Args>(args)...))
	{
		if constexpr (sizeof...(T) > 0)
		{
			Initializer::Push([p = this->get(), t...]()
			{
				p->Data(t...);
			}, detail::ObjectType_v<std::decay_t<Ret>>);
		}
	}
};

template<class Ret, size_t N>
class Make<Ret(Any<N>)> : public std::shared_ptr<Ret>
{
public:
	using element_type = Ret;

	template<class... T>
	Make(T&&... t) : Make(std::forward_as_tuple(std::forward<T>(t)...), std::make_index_sequence<N>())
	{
		static_assert(sizeof...(T) >= N, "Not enough parameters for constructor~");
		if constexpr (sizeof...(T) - N > 0)
		{
			Initializer::Push([p = this->get(), t...]()
			{
				Data(p, std::forward_as_tuple(t...), std::make_index_sequence<sizeof...(T) - N>());
			}, detail::ObjectType_v<std::decay_t<Ret>>);
		}
	}
protected:
	template<class T, size_t... I>
	Make(T&& t, std::index_sequence<I...>)
		: std::shared_ptr<Ret>(std::make_shared<Ret>(std::get<I>(t)...))
	{
	}

	template<class P, class T, size_t... I>
	static void Data(P&& p, T&& t, std::index_sequence<I...>)
	{
		p->Data(std::get<I + N>(t)...);
	}
};
_GL_END