#pragma once

#define GL_OOP

// io
#include <string>
#include <fstream>

// data structure
#include <any>
#include <array>
#include <map>
#include <optional>
#include <stack>
#include <variant>
#include <vector>

// utility
#include <numeric>
#include <memory>
#include <functional>
#include <type_traits>

#ifndef _LIB
#ifndef GL_TRUE
#error "Include OpenGL loader first! See https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library for how to."
#endif
#else
#if _WIN32
#include <Windows.h>
#endif
#include <gl/gl.h>
#define GL_GLEXT_PROTOTYPES
#include <gl/glext.h>
#endif

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "macro.h"

// Desgin choices:
// 1. Returning raw pointer (for most objects)
//	a) Why not void
//	-	Want to have function chaining.
//	b) Why not smart pointer
//		C++ requires covariant return type.
//		1) Why not name hiding (not use virtual functions)?
//		-	It's not c++ style
//		2) Why not curiously recurring template pattern (CRTP)?
//		-	Multilevel inheritance requires abstract base class
//		3) Why not use an abstract base class?
//		-	Need virtual inheritance, which comlicates things
//		-	However, we actually use this for some class with the help
//			from class GL::Shared
//	c) Why not reference
//	-	Need to seperate variable declaration from function calls.
//	-	Though it is possible to have a container of reference via
//		reference_wrapper, it makes things unnecessary complicated
// 2. Why factory class Make? (why not constructor?)
//	-	Keep constructor simple
//	-	Let Data() do actual work, no need to overload constructor again

// Note:
// Need call functions in order of from derived to base class

// TODO
// 1) perfect capture for lambda function, currently still copying
// 2) string, starts_with
// 3) if constexpr in lambda function
// 4) PmxObjObject

// base
#include "Enum.hpp"
#include "Unique.hpp"
#include "Attribute.hpp"
#include "IDObject.hpp"
#include "Shared.hpp"

// OpenGL objects
#include "GLObject.hpp"
// Standard OpenGL objects
// https://www.khronos.org/opengl/wiki/OpenGL_Object
#include "GLStandardObject.hpp"
// 0. GLSL objects
#include "GLSL.hpp"
// 1. regular objects
#include "GLRegular.hpp"
// 2. container objects
#include "GLContainer.hpp"
// Non-standard objects
// 3. other objects
#include "GLExtraObject.hpp"

// utility
#include "Traits.hpp"
#include "Utility.hpp"
#include "Initializer.hpp"
#include "Make.hpp"

// 1.1 buffer objects
// https://www.khronos.org/opengl/wiki/Buffer_Object
#include "Buffer.hpp"
#include "Buffer2D.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
// 1.5 texture objects
// https://www.khronos.org/opengl/wiki/Texture
#include "Texture.hpp"
#include "Texture1D.hpp"
#include "Texture2D.hpp"

// 3.1 Program Attribute objects
#include "ProgramAttribute.hpp"
// 3.1.1 matrix
#include "Matrix.hpp"
#include "ProjMatrix.hpp"
#include "ViewMatrix.hpp"
#include "ModelMatrix.hpp"

// https://www.khronos.org/opengl/wiki/GLSL_Object
// 0.2 Shader objects (Note: it's not an attribute!)
#include "Shader.hpp"
// 0.1 Program objects
#include "Program.hpp"

// 3.1.2 Color
#include "Color3.hpp"
#include "Color4.hpp"

// Renderable objects
#include "Object.hpp"
#include "Group.hpp"
#include "World.hpp"

// 2.1 framebuffer objects
// https://www.khronos.org/opengl/wiki/Framebuffer_Object
#include "FBO.hpp"
// 2.4 vertex array objects
// https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object
#include "VAO.hpp"

#include "helper.h"