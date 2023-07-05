//
// -- internal --
// private
#include "rmlui/irodeo_rmlui.hpp" // must be first to prevent issues
// public
extern "C" {
	#include "rodeo/rmlui.h"
	#include "rodeo/gfx.h"
	#include "rodeo/window.h"
	#include "rodeo.h"
}
// private
extern "C" {
	#include "gfx/irodeo_gfx.h"
	#include "rmlui/irodeo_rmlui_t.h"
}


// -- external --
extern "C" {
	#include "stc/cstr.h"
}
#include "RmlUi/Core/Core.h"
#include "RmlUi/Core/FileInterface.h"
#include "RmlUi/Core/Log.h"
#include "RmlUi/Core/Platform.h"

static irodeo_rmlui_state_t irodeo_rmlui_state = {};

extern "C" {

	void
	rodeo_rmlui_init(void)
	{
		irodeo_rmlui_state.cpp = (icpprodeo_rmlui_state_t*)malloc(sizeof(*irodeo_rmlui_state.cpp));
		Rml::SetRenderInterface(&irodeo_rmlui_state.cpp->render_interface);
		Rml::SetSystemInterface(&irodeo_rmlui_state.cpp->system_interface);

		Rml::Initialise();

		irodeo_rmlui_state.cpp->default_context = Rml::CreateContext(
				"default",
				Rml::Vector2i((int32_t)rodeo_gfx_width_get(), (int32_t)rodeo_gfx_height_get())
			);
		if(!irodeo_rmlui_state.cpp->default_context)
		{
			rodeo_log(
				rodeo_logLevel_error,
				"Failed to initialise RmlUi"
			);
			return;
		}
	}

	void
	rodeo_rmlui_deinit(void)
	{
		Rml::Shutdown();
		free(irodeo_rmlui_state.cpp);
	}

	void
	rodeo_rmlui_font_load(cstr path)
	{
		Rml::LoadFontFace(cstr_str(&path));
	}

	rodeo_rmlui_document_t
	rodeo_rmlui_document_load(cstr path)
	{
		rodeo_rmlui_document_t doc;
		doc.data = (irodeo_rmlui_document_data*)malloc(sizeof(*doc.data));
		doc.data->document = irodeo_rmlui_state.cpp->default_context->LoadDocument(Rml::String("assets/demo.html"));
		if(!doc.data->document)
		{
			rodeo_log(
				rodeo_logLevel_error,
				"Failed to load RmlUi Document"
			);
			return {};
		}
		return doc;
	}

	void
	rodeo_rmlui_document_show(rodeo_rmlui_document_t document)
	{
		document.data->document->Show();
	}

	void
	rodeo_rmlui_update(void)
	{
		irodeo_rmlui_state.cpp->default_context->Update();
	}

	void
	rodeo_rmlui_render(void)
	{
		irodeo_rmlui_state.cpp->default_context->Render();
	}

}

// interface implementation

double SystemInterface_Rodeo::GetElapsedTime()
{
	return (double)rodeo_window_elapsedTime_ms() / 1000.0;
}

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
	if(
		rodeo_gfx_vertex_maxSize() > rodeo_gfx_vertex_size() + num_vertices
		 ||
		rodeo_gfx_index_maxSize() > rodeo_gfx_index_size() + num_indices
	)
	{
		rodeo_gfx_renderer_flush();
	}
	for(int32_t i = 0; i < num_vertices; ++i)
	{
		rodeo_gfx_vertex_t vert = {};
		rodeo_color_RGBA8_t color = {};

		vert.x = vertices[i].position.x;
		vert.y = vertices[i].position.y;

		color.colors.alpha = vertices[i].colour.alpha;
		color.colors.red = vertices[i].colour.red;
		color.colors.green = vertices[i].colour.green;
		color.colors.blue = vertices[i].colour.blue;
		vert.color = rodeo_color_RGBA8_to_RGBAFloat(color);

		vert.texture_x = vertices[i].tex_coord.x;
		vert.texture_y = vertices[i].tex_coord.y;

		if(NULL == (rodeo_gfx_texture_2d_t*)texture)
		{
			vert.texture_id = 0;
		}
		else
		{
			rodeo_gfx_texture_set(*(rodeo_gfx_texture_2d_t*)texture);
			vert.texture_id = 1;
		}

		rodeo_gfx_vertex_add(vert);
	}

	for(int32_t i = 0; i < num_indices; ++i)
	{
		rodeo_gfx_index_add(rodeo_gfx_index_count_get() + (uint16_t)indices[i]);
	}
	rodeo_gfx_index_count_increment((uint16_t)num_indices);

	//unsigned int textureId = 0;
	//if(texture != NULL)
	//{
	//	textureId = texture;
	//}

	//rlBegin(RL_TRIANGLES);
	//rlSetTexture(textureId);
	//rlPushMatrix();
	//rlTranslatef(translation.x, translation.y, 0);

	//for (unsigned int i = 0; i <= (num_indices - 3); i += 3)
	//{
	//	if(rlCheckRenderBatchLimit(3))
	//	{
	//		rlBegin(RL_TRIANGLES);
	//		rlSetTexture(textureId);
	//	}

	//	int indexA = indices[i];
	//	int indexB = indices[i + 1];
	//	int indexC = indices[i + 2];

	//	Rml::Vertex vertexA = vertices[indexA];
	//	Rml::Vertex vertexB = vertices[indexB];
	//	Rml::Vertex vertexC = vertices[indexC];

	//	RenderInterface_Rodeo::RodeoTriangleVert(vertexA);
	//	RenderInterface_Rodeo::RodeoTriangleVert(vertexB);
	//	RenderInterface_Rodeo::RodeoTriangleVert(vertexC);
	//}

	//rlPopMatrix();
	//rlDrawRenderBatchActive();
	//rlEnd();
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
	rodeo_gfx_texture_2d_t *texture = (rodeo_gfx_texture_2d_t*)malloc(sizeof(rodeo_gfx_texture_2d_t));
		*texture = rodeo_gfx_texture_2d_create_from_path(cstr_from(source.c_str()));

	texture_dimensions.x = (int)texture->width;
	texture_dimensions.y = (int)texture->height;
	texture_handle = (Rml::TextureHandle)texture;

	return true;
}

bool RenderInterface_Rodeo::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
{
	rodeo_gfx_texture_2d_t *texture = (rodeo_gfx_texture_2d_t*)malloc(sizeof(rodeo_gfx_texture_2d_t));
	*texture = rodeo_gfx_texture_2d_create_from_RGBA8(
			(uint16_t)source_dimensions.x,
			(uint16_t)source_dimensions.y,
			source
		);
	//Image image = GenImageColor(source_dimensions.x, source_dimensions.y, BLANK);
	//Texture texture = LoadTextureFromImage(image);

	texture_handle = (Rml::TextureHandle)texture;

	return true;
}

void RenderInterface_Rodeo::ReleaseTexture(Rml::TextureHandle texture_handle)
{
	rodeo_gfx_texture_2d_destroy(*(rodeo_gfx_texture_2d_t*)texture_handle);
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
