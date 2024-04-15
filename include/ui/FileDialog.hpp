/*
	Copyright 2020 Limeoats
	Original project: https://github.com/Limeoats/L2DFileDialog

	Changes by Vladimir Sigalkin
*/

#pragma once

#include <filesystem>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <ui/IconsFontAwesome6.hpp>

typedef int ImGuiFileDialogType;	// -> enum ImGuiFileDialogType_        // Enum: A file dialog type
typedef int ImGuiFileDialogGFlag;	// -> enum ImGuiFileDialogGFlag_        // Enum: A file dialog flag

enum ImGuiFileDialogType_ {
	ImGuiFileDialogType_OpenFile,
	ImGuiFileDialogType_SaveFile,
	ImGuiFileDialogType_COUNT
};

enum ImGuiFileDialogGFlag_ {
	ImGuiFileDialogGFlag_None = 0,
	ImGuiFileDialogGFlag_ShowHiddenFiles = 1 << 0,
};

struct ImFileDialogInfo {
	std::string title;
	ImGuiFileDialogType type;
	ImGuiFileDialogGFlag flags;
	std::vector<std::string> allowedExtensions;

	std::filesystem::path fileName;
	std::filesystem::path directoryPath;
	std::filesystem::path resultPath;

	bool refreshInfo;
	size_t currentIndex;
	std::vector<std::filesystem::directory_entry> currentFiles;
	std::vector<std::filesystem::directory_entry> currentDirectories;
};

namespace ImGui {
	IMGUI_API bool FileDialog(bool* open, ImFileDialogInfo* dialogInfo);
}