#include "Viewport.h"

Viewport::Viewport()
{
	uly_name = "";
}

Viewport::Viewport(const std::string& name)
{
	uly_name = name;
	PushItem(new UI::TextureView("Viewport", 0, ImVec2(SCREEN_W, SCREEN_H)));
}

Viewport::Viewport(const std::string& name, GLuint texID)
{
	uly_name = name;
	PushItem(new UI::TextureView("Viewport", texID, ImVec2(SCREEN_W, SCREEN_H)));
}

Viewport::Viewport(const std::string& name, GLuint texID, const ImVec2& vp_size)
{
	uly_name = name;
	PushItem(new UI::TextureView("Viewport", texID, vp_size));
}

Viewport::~Viewport()
{

}

void Viewport::RenderLayer() const
{
	if (!uly_is_rendered)
		return;

	if (ImGui::Begin(uly_name.c_str(), &uly_is_rendered)) {

		item_list[0]->RenderItem();

		GetLayerSize();
		if (is_size_changed)
			if (resize_event)
				resize_event();
		if(IsChangeEnd())
			DEBUG(123123)

		is_size_changed_b = is_size_changed;
		is_size_changed = false;
		ImGui::End();
	}
	else {
		uly_is_rendered = false;
		ImGui::End();
	}
}
