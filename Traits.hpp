#pragma once

_GL_BEGIN
namespace detail {
// STRUCT TEMPLATE is_vector
template<class T>
struct is_vector : public std::false_type
{
};

template<class T>
struct is_vector<std::vector<T>> : public std::true_type
{
};

template<class T>
inline constexpr bool is_vector_v = is_vector<T>::value;

// STRUCT TEMPLATE is_shared_ptr
template<class T>
struct is_shared_ptr : public std::false_type
{
};

template<class T>
struct is_shared_ptr<std::shared_ptr<T>> : public std::true_type
{
};

template<class T>
inline constexpr bool is_shared_ptr_v = is_shared_ptr<T>::value;

// STRUCT TEMPLATE is_glm_vec
template<class T>
struct is_glm_vec : public std::false_type
{
};

template<class T, glm::precision P>
struct is_glm_vec<glm::tvec1<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_vec<glm::tvec2<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_vec<glm::tvec3<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_vec<glm::tvec4<T, P>> : public std::true_type
{
};

template<class T>
inline constexpr bool is_glm_vec_v = is_glm_vec<T>::value;

// STRUCT TEMPLATE is_glm_mat
template<class T>
struct is_glm_mat : public std::false_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat2x2<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat2x3<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat2x4<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat3x2<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat3x3<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat3x4<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat4x2<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat4x3<T, P>> : public std::true_type
{
};

template<class T, glm::precision P>
struct is_glm_mat<glm::tmat4x4<T, P>> : public std::true_type
{
};

template<class T>
inline constexpr bool is_glm_mat_v = is_glm_mat<T>::value;

// STRUCT TEMPLATE remove_shared_ptr
template<class T>
struct remove_shared_ptr
{
	using type = T;
};

template<class T>
struct remove_shared_ptr<std::shared_ptr<T>>
{
	using type = T;
};

template<class T>
using remove_shared_ptr_t = typename remove_shared_ptr<T>::type;

// STRUCT TEMPLATE remove_glm
template<class T>
struct remove_glm
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tvec1<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tvec2<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tvec3<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tvec4<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat2x2<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat2x3<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat2x4<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat3x2<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat3x3<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat3x4<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat4x2<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat4x3<T, P>>
{
	using type = T;
};

template<class T, glm::precision P>
struct remove_glm<glm::tmat4x4<T, P>>
{
	using type = T;
};

template<class T>
using remove_glm_t = typename remove_glm<T>::type;

// STRUCT TEMPLATE ObjectType
template<class T, class Default = void>
struct ObjectType
{
	inline static constexpr OBJECT_TYPE value = OBJECT_TYPE::OTHER;
};

template<class T>
struct ObjectType<T, std::enable_if_t<std::is_base_of_v<GLSL, T>>>
{
	inline static constexpr OBJECT_TYPE value = OBJECT_TYPE::GLSL;
};

template<class T>
struct ObjectType<T, std::enable_if_t<std::is_base_of_v<GLRegular, T>>>
{
	inline static constexpr OBJECT_TYPE value = OBJECT_TYPE::REGULAR;
};

template<class T>
struct ObjectType<T, std::enable_if_t<std::is_base_of_v<GLContainer, T>>>
{
	inline static constexpr OBJECT_TYPE value = OBJECT_TYPE::CONTAINER;
};

template<class T>
inline static constexpr OBJECT_TYPE ObjectType_v = ObjectType<T>::value;
}
_GL_END