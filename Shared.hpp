#pragma once

_GL_BEGIN
// enable return shared_ptr from this
namespace detail {
class VirtualShared : public std::enable_shared_from_this<VirtualShared>
{
public:
	virtual ~VirtualShared() = default;
};
}

template <class T>
class Shared : virtual public detail::VirtualShared
{
public:
	// QED¡¸495Äê¤Î²¨¼y¡¹
	[[nodiscard]] std::shared_ptr<T> QED()
	{
		return std::dynamic_pointer_cast<T>(VirtualShared::shared_from_this());
	}
};
_GL_END