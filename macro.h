#pragma once

// all the useful macros, mostly used internally

// namespace
#define _GL_BEGIN namespace GL {
#define _GL_END   }

// chaining
#define EL_PSY_CONGROO return this

// OpenGL objects has to be initialized after context is created
// defer everything after that
#define _GL_INIT_BEGIN					\
Initializer::Push([=]()	\
{

// Note that container cannot be shared,
// has to be initialized for each context
#define _GL_INIT_END					\
}, detail::ObjectType_v<std::decay_t<decltype(*this)>>)
