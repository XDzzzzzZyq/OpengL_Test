#include "ImguiLayer.h"

ImguiLayer::ImguiLayer()
{
	uly_name = "";
	EventInit();
}

ImguiLayer::ImguiLayer(const std::string& name)
{
	uly_name = name;
	EventInit();
}

ImguiLayer::~ImguiLayer()
{
}

ImVec2 ImguiLayer::GetLayerSize()
{
	const ImVec2 size = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
	is_size_changed = !(size == uly_size);
	uly_size = size;

	return uly_size;
}

void ImguiLayer::UpdateLayerPos()
{
	content_pos = ImGui::GetWindowContentRegionMin();
	content_size = ImGui::GetWindowContentRegionMax() - content_pos;

}

void ImguiLayer::PushItem(std::shared_ptr<ImguiItem> item)
{
	int repeat_count = 0;
	std::string name = item->uitm_name;
	std::string name2 = item->uitm_name;
	while (item_name_buffer.find(name2) != item_name_buffer.end())
	{
		repeat_count++;
		name2 = name2 + ("." + std::to_string(repeat_count));

	}
	item->uitm_id = item_list.size();
	item_list.push_back(item);
	item_name_buffer[item->uitm_name] = item->uitm_id;
}

void ImguiLayer::PushItem(ImItemType type)
{
	auto item = std::make_shared<ImguiItem>(type, "123");
	PushItem(item);
}

ImguiItem* ImguiLayer::FindImguiItem(const std::string& name) const
{
	if (item_name_buffer.find(name) != item_name_buffer.end())
		return item_list[item_name_buffer[name]].get();
	DEBUG("[ no item named " + name + " ]");
	return nullptr;
}

ImguiItem* ImguiLayer::FindImguiItem(int id) const
{
	if (id > item_list.size() - 1)
		return nullptr;
	return item_list[id].get();
}

void ImguiLayer::EventInit()
{
	EventList[GenIntEvent(0, 0, 0, 1, 0)] = REGIST_EVENT(ImguiLayer::LMB);
}

void ImguiLayer::LMB()
{
	//if (IsClick());
}
