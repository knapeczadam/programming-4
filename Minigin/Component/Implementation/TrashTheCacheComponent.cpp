#include "TrashTheCacheComponent.h"

// Project includes
#include "TrashTheCacheManager.h"

// ImGui includes
#include "imgui.h"
#include "imgui_plot.h"

namespace dae
{
    void TrashTheCacheComponent::RenderUI() const
    {
        ImGui::Begin("Exercise 2 - 20'000'000 elements", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        
        if (ImGui::Button("Trash the cache with GameObject3D"))
        {
            TrashTheCacheManager::GetInstance().CalculateData();
        }
        
        static ImU32 colors[2] = { ImColor(255, 0, 0), ImColor(0, 255, 0)};
        
        if (not TrashTheCacheManager::GetInstance().GetData().empty())
        {
            const float x_data[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
            
            ImGui::PlotConfig conf;
            conf.values.xs = x_data; // this line is optional
            conf.values.ys = TrashTheCacheManager::GetInstance().GetData().data();
            conf.values.count = static_cast<int>(TrashTheCacheManager::GetInstance().GetData().size());
            conf.values.color = colors[0];
            conf.scale.min = 0;
            conf.scale.max = TrashTheCacheManager::GetInstance().GetData()[0];
            conf.tooltip.show = true;
            conf.tooltip.format = "x=%.2f, y=%.2f";
            conf.grid_x.show = true;
            conf.grid_y.show = true;
            conf.frame_size = ImVec2(200, 100);
            conf.line_thickness = 2.f;
        
            ImGui::Plot("plot", conf);
        }
        if (ImGui::Button("Trash the cache with GameObject3DAlt"))
        {
            TrashTheCacheManager::GetInstance().CalculateDataAlt();
        }
        if (not TrashTheCacheManager::GetInstance().GetDataAlt().empty())
        {
            const float x_data[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
            
            ImGui::PlotConfig conf;
            conf.values.xs = x_data; // this line is optional
            conf.values.ys = TrashTheCacheManager::GetInstance().GetDataAlt().data();
            conf.values.count = static_cast<int>(TrashTheCacheManager::GetInstance().GetDataAlt().size());
            conf.values.color = colors[1];
            conf.scale.min = 0;
            conf.scale.max = TrashTheCacheManager::GetInstance().GetDataAlt()[0];
            conf.tooltip.show = true;
            conf.tooltip.format = "x=%.2f, y=%.2f";
            conf.grid_x.show = true;
            conf.grid_y.show = true;
            conf.frame_size = ImVec2(200, 100);
            conf.line_thickness = 2.f;
        
            ImGui::Plot("plot2", conf);
        }
        if (not TrashTheCacheManager::GetInstance().GetData().empty() and not TrashTheCacheManager::GetInstance().GetDataAlt().empty())
        {
            ImGui::Text("Combined:");
            
            const float x_data[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
            const float* list[] = { TrashTheCacheManager::GetInstance().GetData().data(), TrashTheCacheManager::GetInstance().GetDataAlt().data() };
            
            ImGui::PlotConfig conf;
            conf.values.xs = x_data; // this line is optional
            conf.values.count = static_cast<int>(TrashTheCacheManager::GetInstance().GetData().size());
            conf.values.ys_list = list;
            conf.values.ys_count = 2;
            conf.values.colors = colors;
            conf.scale.min = 0;
            conf.scale.max = TrashTheCacheManager::GetInstance().GetData()[0];
            conf.tooltip.show = true;
            conf.tooltip.format = "x=%.2f, y=%.2f";
            conf.grid_x.show = true;
            conf.grid_y.show = true;
            conf.frame_size = ImVec2(200, 100);
            conf.line_thickness = 2.f;
        
            ImGui::Plot("plot3", conf);
        }
        ImGui::End();
    }
}
