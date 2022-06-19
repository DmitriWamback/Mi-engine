//
//  style.m
//  mac-build
//
//  Created by NewTest on 2022-06-18.
//

#import <Foundation/Foundation.h>
#import "imgui.h"

void UpdateStyle() {
    ImGuiStyle* style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_Text] = ImColor(255, 0, 0, 255);
}
