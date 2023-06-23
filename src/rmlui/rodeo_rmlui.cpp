
#define RMLUI_STATIC_LIB

// -- internal --
// public
#include "rodeo/gfx.h"
// private
#include "rmlui/irodeo_rmlui.hpp"

// -- external --
#include "RmlUi/Core/Core.h"
#include "RmlUi/Core/FileInterface.h"
#include "RmlUi/Core/Log.h"
#include "RmlUi/Core/Platform.h"



RenderInterface_Rodeo::RenderInterface_Rodeo()
{
}

RenderInterface_Rodeo::~RenderInterface_Rodeo()
{
}

void RenderInterface_Rodeo::SetViewport(int width, int height)
{
	viewport_width = width;
	viewport_height = height;
}

void RenderInterface_Rodeo::BeginFrame()
{
	SetViewport((int)rodeo_gfx_width_get(), (int)rodeo_gfx_height_get());
	rodeo_gfx_renderer_flush();
	rodeo_gfx_matrix_push();
}

void RenderInterface_Rodeo::EndFrame() 
{
	//if(is_projecting)
	//{
	//	rlMatrixMode(RL_PROJECTION);
	//	rlPopMatrix();
	//	rlMatrixMode(RL_MODELVIEW);
	//	is_projecting = false;
	//}
	rodeo_gfx_renderer_flush();
	rodeo_gfx_matrix_pop();
	rodeo_gfx_scissor_end();
}

void RenderInterface_Rodeo::RenderGeometry(
		Rml::Vertex* vertices,
		int num_vertices, // ignore?
		int* indices,
		int num_indices,
		const Rml::TextureHandle texture,
		const Rml::Vector2f& translation
		)
{
	unsigned int textureId = 0;
	if(texture != NULL)
	{
		textureId = texture;
	}

	rlBegin(RL_TRIANGLES);
	rlSetTexture(textureId);
	rlPushMatrix();
	rlTranslatef(translation.x, translation.y, 0);

	for (unsigned int i = 0; i <= (num_indices - 3); i += 3)
	{
		if(rlCheckRenderBatchLimit(3))
		{
			rlBegin(RL_TRIANGLES);
			rlSetTexture(textureId);
		}

		int indexA = indices[i];
		int indexB = indices[i + 1];
		int indexC = indices[i + 2];

		Rml::Vertex vertexA = vertices[indexA];
		Rml::Vertex vertexB = vertices[indexB];
		Rml::Vertex vertexC = vertices[indexC];

		RenderInterface_Rodeo::RodeoTriangleVert(vertexA);
		RenderInterface_Rodeo::RodeoTriangleVert(vertexB);
		RenderInterface_Rodeo::RodeoTriangleVert(vertexC);
	}


	rlPopMatrix();
	rlDrawRenderBatchActive();
	rlEnd();
}


void RenderInterface_Rodeo::EnableScissorRegion(bool enable)
{
	if(enable)
	{
		// do nothing
	}
	else
	{
		rodeo_gfx_scissor_end();
	}
}

void RenderInterface_Rodeo::SetScissorRegion(int x, int y, int width, int height)
{
	rodeo_gfx_scissor_begin(
		{ (float)x, (float)y, (float)width, (float)height }
	);
	//rlScissor(x, viewport_height - (y + height), width, height);
}


bool RenderInterface_Rodeo::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
{
	rodeo_gfx_texture_2d_t texture = rodeo_gfx_texture_2d_create_from_path(cstr_from(source.c_str()));

	texture_dimensions.x = (int)texture.width;
	texture_dimensions.y = (int)texture.height;
	texture_handle = (Rml::TextureHandle) texture.data;

	return true;
}

bool RenderInterface_Rodeo::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
{
	rodeo_gfx_texture_2d_t texture = rodeo_gfx_texture_2d_create_from_RGBA8(
			(uint16_t)source_dimensions.x,
			(uint16_t)source_dimensions.y,
			source
		);
	//Image image = GenImageColor(source_dimensions.x, source_dimensions.y, BLANK);
	//Texture texture = LoadTextureFromImage(image);

	texture_handle = (Rml::TextureHandle)texture.data;

	return true;
}

void RenderInterface_Rodeo::ReleaseTexture(Rml::TextureHandle texture_handle)
{
	rodeo_gfx_texture_2d_destroy({ (irodeo_gfx_texture_2d_t*)texture_handle, 0, 0 });
}

void RenderInterface_Rodeo::SetTransform(const Rml::Matrix4f* new_transform)
{
	if(new_transform != nullptr)
	{
		//if(!is_projecting)
		//{
		//	rlMatrixMode(RL_PROJECTION);
		//	rlPushMatrix();
		//	rlLoadIdentity();
		//	rlFrustum(0.0, viewport_width, 0.0, viewport_height, -100.0, 100.0);
		//	rlMatrixMode(RL_MODELVIEW);
		//	is_projecting = true;
		//}
		//rlLoadIdentity();

		rodeo_math_mat4_t matrix;
		memcpy(matrix.raw, new_transform->data(), sizeof(matrix));
		rodeo_gfx_matrix_set(matrix);
		
		//rlScalef(1.0,1.0,0.001);
		//rlTranslatef(0.0,0.0,100.0);
	}
	else
	{
		rodeo_gfx_matrix_pop();
		rodeo_gfx_matrix_push();
	}
}
