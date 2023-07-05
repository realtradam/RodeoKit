#pragma once

// internal 

// external
#include "RmlUi/Core.h"
#include "RmlUi/Core/Platform.h"
#include "RmlUi/Core/RenderInterface.h"
#include "RmlUi/Core/SystemInterface.h"

class SystemInterface_Rodeo : public Rml::SystemInterface {
public:
		double GetElapsedTime() override;
};

class RenderInterface_Rodeo : public Rml::RenderInterface {
	public:

		bool is_projecting = false;

		RenderInterface_Rodeo();
		~RenderInterface_Rodeo();

		// The viewport should be updated whenever the window size changes.
		void SetViewport(int viewport_width, int viewport_height);

		// Sets up OpenGL states for taking rendering commands from RmlUi.
		void BeginFrame();
		void EndFrame();

		// -- Inherited from Rml::RenderInterface --

		void RenderGeometry(
			Rml::Vertex* vertices,
			int num_vertices,
			int* indices,
			int num_indices,
			Rml::TextureHandle texture,
			const Rml::Vector2f& translation
		) override;

		void EnableScissorRegion(bool enable) override;
		void SetScissorRegion(int x, int y, int width, int height) override;

		bool LoadTexture(
			Rml::TextureHandle& texture_handle,
			Rml::Vector2i& texture_dimensions,
			const Rml::String& source
		) override;
		bool GenerateTexture(
			Rml::TextureHandle& texture_handle,
			const Rml::byte* source,
			const Rml::Vector2i& source_dimensions
		) override;
		void ReleaseTexture(Rml::TextureHandle texture_handle) override;

		void SetTransform(const Rml::Matrix4f* transform) override;

		// Can be passed to RenderGeometry() to enable texture rendering without changing the bound texture.
		static const Rml::TextureHandle TextureEnableWithoutBinding = Rml::TextureHandle(-1);

	private:
		//Rml::Matrix4f transform, projection;
		//ProgramId transform_dirty_state = ProgramId::All;
		//bool transform_active = false;

		//enum class ScissoringState { Disable, Scissor, Stencil };
		//ScissoringState scissoring_state = ScissoringState::Disable;

		int viewport_width = 0;
		int viewport_height = 0;

};

struct
icpprodeo_rmlui_state
{
	RenderInterface_Rodeo render_interface;
	SystemInterface_Rodeo system_interface;
	Rml::Context *default_context;
};

struct irodeo_rmlui_document_data
{
	Rml::ElementDocument *document;
};
