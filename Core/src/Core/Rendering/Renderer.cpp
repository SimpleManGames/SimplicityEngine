#include "Core/Rendering/Renderer.h"

#include "Core/System/Graphics.h"
#include "Core/System/Manager/SystemManager.h"

#include "GLEW\glew.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

#include "Diagnostics/Logger.h"

#include "Defines\assert.h"
#include "Defines\deletemacros.h"
#include "Defines\systemdefines.h"

#include "Helpers/Singleton.h"

Renderer::Renderer() {}
Renderer::~Renderer() {}

bool Renderer::Initialize() {
	this->graphics = GetSystem(Graphics, SystemType::GRAPHICS_SYSTEM);
	assert( this->graphics != nullptr );

	return true;
}
bool Renderer::Shutdown() {
	return true;
}

void Draw_Internal::BeginDraw( const Shader & s, const Geometry & g, const Framebuffer & r ) {
	glBindFramebuffer( GL_FRAMEBUFFER, r.handle );
	glUseProgram( s.handle );
	glBindVertexArray( g.vao );

	glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	glViewport( 0, 0, r.width, r.height );
}

void Draw_Internal::EndDraw( const Shader & s, const Geometry & g, const Framebuffer & r ) {
	glDrawElements( GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0 );

	glBindVertexArray( 0 );
	glUseProgram( 0 );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

size_t Draw_Internal::Format( size_t idx, size_t tex, int val ) {
	glUniform1i( idx, val );
	return 0;
}

size_t Draw_Internal::Format( size_t idx, size_t tex, float val ) {
	glUniform1f( idx, val );
	return 0;
}

size_t Draw_Internal::Format( size_t idx, size_t tex, const Texture & val ) {
	glActiveTexture( GL_TEXTURE0 + tex );
	glBindTexture( GL_TEXTURE_2D, val.handle );
	glUniform1i( idx, tex );
	return tex + 1;
}

size_t Draw_Internal::Format( size_t idx, size_t tex, const glm::vec3 & val ) {
	glUniform3fv( idx, 1, glm::value_ptr( val ) );
	return 0;
}

size_t Draw_Internal::Format( size_t idx, size_t tex, const glm::mat4 & val ) {
	glUniformMatrix4fv( idx, 1, GL_FALSE, glm::value_ptr( val ) );
	return 0;
}

size_t Draw_Internal::Format( size_t idx, size_t tex, const float val[ 16 ] ) {
	glUniformMatrix4fv( idx, 1, GL_FALSE, val );
	return 0;
}