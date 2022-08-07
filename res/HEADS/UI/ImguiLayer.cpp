#include "ImguiLayer.h"

ImguiLayer::ImguiLayer()
{
	uly_name = "";
}

ImguiLayer::ImguiLayer(const std::string& name)
{
	uly_name = name;
}

ImguiLayer::~ImguiLayer()
{

}

ImVec2 ImguiLayer::GetLayerSize() const
{
	if (ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin() == uly_size) {
		is_size_changed = false;
		return uly_size;
	}
	else
	{
		uly_size = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
		is_size_changed = true;
		return uly_size;
	}


}

void ImguiLayer::PushItem(ImguiItem* item)
{
	int repeat_count = 0;
	std::string name = item->uitm_name;
	while (item_list.find(item->uitm_name)!=item_list.end())
	{
		repeat_count++;
		item->Rename(name + ("." + std::to_string(repeat_count)));
		
	}
	item_list.insert(std::pair<std::string, ImguiItem*>(item->uitm_name, item));
	name_list.push_back(item->uitm_name);
}

void ImguiLayer::PushItem(ImItemType type)
{
	auto item = new ImguiItem(type,"123");
	PushItem(item);
}

ImguiItem* ImguiLayer::FindImguiItem(const std::string& name) const
{
	if (item_list.find(name) != item_list.end())
		return item_list[name];
	DEBUG("[ no item named "+name+" ]")
	return nullptr;
}

void ImguiLayer::RenderLayer() const
{
	ImGui::Begin(uly_name.c_str(), &uly_activate);
	if (pre_RenderLayer)
		pre_RenderLayer();
	for (const auto& name : name_list) {
		const auto& item = item_list[name];
		uly_show_type ? item->EnableTagName() : item->DisableTagName();
		item->RenderItem();
	}
	if(extra_RenderLayer)
		extra_RenderLayer();

	GetLayerSize();
	if (is_size_changed)
		if(resize_event)
			resize_event();

	is_size_changed = false;
	ImGui::End();
}
