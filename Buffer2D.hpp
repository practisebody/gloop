#pragma once

_GL_BEGIN
// a 2D buffer object as matrix
// # of rows = # of vertices, # of cols = # of dimensions
template<BUFFER_TYPE type>
class Buffer2D : public Buffer<type>
{
public:
	template<class T>
	const Buffer2D* Data(T&& data, bool normalized = false, size_t stride = 0)
	{
		if constexpr (detail::is_vector_v<std::decay_t<T>>)
		{
			using vector_type = typename std::decay_t<T>::value_type;
			using value_type = typename vector_type::value_type;
			m_uWidth = vector_type::length();
			m_uHeight = data.size();
			Buffer<type>::Data(m_uWidth * m_uHeight,
				reinterpret_cast<const value_type*>(std::addressof(data.front())));
		}
		else
		{
			static_assert(false, "Unknown data format. std::vector only~");
		}
		EL_PSY_CONGROO;
	}

	const size_t& Width() const
	{
		return m_uWidth;
	}

	const size_t& Height() const
	{
		return m_uHeight;
	}

protected:
	size_t m_uWidth;
	size_t m_uHeight;
};
_GL_END