#pragma once

_GL_BEGIN
_PREFAB_BEGIN
#define _GLSL_VERSION "#version 330\n"

inline static const std::shared_ptr<Program> progUniformColor4 = Make<Program>(
	_GLSL_VERSION
	"layout (location = 0) in vec3 vertPosition;"
	"uniform mat4 projection;"
	"uniform mat4 view;"
	"uniform mat4 model;"
	"out vec3 fragColor;"
	"void main()"
	"{"
	"	gl_Position = projection * view * model * vec4(vertPosition, 1.0);"
	"}",
	_GLSL_VERSION
	"uniform vec4 fragColor;"
	"out vec4 color;"
	"void main()"
	"{"
	"	color = fragColor;"
	"}");

inline static const std::shared_ptr<Program> progColor3 = Make<Program>(
	_GLSL_VERSION
	"layout (location = 0) in vec3 vertPosition;"
	"layout (location = 1) in vec3 vertColor;"
	"uniform mat4 projection;"
	"uniform mat4 view;"
	"uniform mat4 model;"
	"out vec3 fragColor;"
	"void main()"
	"{"
	"	fragColor = vertColor;"
	"	gl_Position = projection * view * model * vec4(vertPosition, 1.0);"
	"}",
	_GLSL_VERSION
	"in vec3 fragColor;"
	"out vec4 color;"
	"void main()"
	"{"
	"	color = vec4(fragColor, 1.0);"
	"}");

inline static const std::shared_ptr<Program> progTexture = Make<Program>(
	_GLSL_VERSION
	"layout (location = 0) in vec3 vertPosition;"
	"layout (location = 1) in vec2 vertTexCoord;"
	"uniform mat4 projection;"
	"uniform mat4 view;"
	"uniform mat4 model;"
	"out vec2 fragTexCoord;"
	"void main()"
	"{"
	"	fragTexCoord = vertTexCoord;"
	"	gl_Position = projection * view * model * vec4(vertPosition, 1.0);"
	"}",
	_GLSL_VERSION
	"uniform sampler2D tex;"
	"in vec2 fragTexCoord;"
	"out vec4 color;"
	"void main()"
	"{"
	"	color = texture(tex, fragTexCoord);"
	"}");

inline static const std::shared_ptr<Program> progPmxMaterial = Make<Program>(
	_GLSL_VERSION
	"layout (location = 0) in vec3 vertPosition;"
	"layout (location = 1) in vec2 vertTexCoord;"
	"layout (location = 2) in vec3 vertNormal;"
	"uniform mat4 projection;"
	"uniform mat4 view;"
	"uniform mat4 model;"
	"out vec2 fragTexCoord;"
	"out vec3 fragNormal;"
	"void main()"
	"{"
	"	fragTexCoord = vertTexCoord;"
	"	fragNormal = vertNormal;"
	"	gl_Position = projection * view * model * vec4(vertPosition, 1.0);"
	"}",
	_GLSL_VERSION
	"struct Material"
	"{"
	"	bool bTexture;"
	"	sampler2D tDiffuse;"
	"	vec3 ambient;"
	"	vec3 diffuse;"
	"	vec3 specular;"
	"	float exponent;"
	"	float dissolve;"
	"};"
	"uniform Material m;"
	"in vec2 fragTexCoord;"
	"in vec3 fragNormal;"
	"out vec4 color;"
	"void main()"
	"{"
	"	if (m.bTexture)"
	"		color = texture(m.tDiffuse, fragTexCoord);"
	"	else"
	"	{"
	"		if (m.dissolve == 1.0)"
	"			color = vec4(m.diffuse, m.dissolve);"
	"		else"
	"			color = vec4(0.0, 1.0, 0.0, 1.0);"
	"	}"
	"}");
_PREFAB_END
_GL_END