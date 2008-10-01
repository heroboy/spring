/*
	Copyright (c) 2008 Robin Vobruba <hoijui.quaero@gmail.com>
	
	This program is free software {} you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation {} either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY {} without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "GroupAILibraryInfo.h"

#include "Interface/aidefines.h"
#include "Interface/SGAILibrary.h"
#include "Interface/SAIInterfaceLibrary.h"
#include "IGroupAILibrary.h"

#include "Platform/errorhandler.h"

CGroupAILibraryInfo::CGroupAILibraryInfo(const IGroupAILibrary& ai, const SAIInterfaceSpecifyer& interfaceSpecifyer) {
	infos = ai.GetInfos();
	options = ai.GetOptions();
	//levelOfSupport = ai.GetLevelOfSupportFor(std::string(ENGINE_VERSION_STRING),
	//		ENGINE_VERSION_NUMBER, interfaceSpecifyer);
}

CGroupAILibraryInfo::CGroupAILibraryInfo(const CGroupAILibraryInfo& aiInfo) {
	infos = std::map<std::string, InfoItem>(
			aiInfo.infos.begin(),
			aiInfo.infos.end());
	options = std::vector<Option>(
			aiInfo.options.begin(),
			aiInfo.options.end());
	//levelOfSupport = aiInfo.levelOfSupport;
}

CGroupAILibraryInfo::CGroupAILibraryInfo(
		const std::string& aiInfoFile,
		const std::string& aiOptionFile,
		const std::string& fileModes,
		const std::string& accessModes) {
	
	InfoItem tmpInfos[MAX_INFOS];
	unsigned int num = ParseInfos(aiInfoFile.c_str(), fileModes.c_str(), accessModes.c_str(), tmpInfos, MAX_INFOS);
    for (unsigned int i=0; i < num; ++i) {
		infos[std::string(tmpInfos[i].key)] = tmpInfos[i];
    }
	
	if (!aiOptionFile.empty()) {
		Option tmpOptions[MAX_OPTIONS];
		num = ParseOptions(aiOptionFile.c_str(), fileModes.c_str(), accessModes.c_str(), "", tmpOptions, MAX_OPTIONS);
		for (unsigned int i=0; i < num; ++i) {
			options.push_back(tmpOptions[i]);
		}
	}
}

/*
LevelOfSupport CGroupAILibraryInfo::GetLevelOfSupportForCurrentEngine() const {
	return levelOfSupport;
}
*/
	
std::string CGroupAILibraryInfo::GetShortName() const { // restrictions: none of the following: spaces, '_', '#'
	return GetInfo(GROUP_AI_PROPERTY_SHORT_NAME);
}
std::string CGroupAILibraryInfo::GetVersion() const { // restrictions: none of the following: spaces, '_', '#'
	return GetInfo(GROUP_AI_PROPERTY_VERSION);
}
std::string CGroupAILibraryInfo::GetName() const {
	return GetInfo(GROUP_AI_PROPERTY_NAME);
}
std::string CGroupAILibraryInfo::GetDescription() const {
	return GetInfo(GROUP_AI_PROPERTY_DESCRIPTION);
}
std::string CGroupAILibraryInfo::GetURL() const {
	return GetInfo(GROUP_AI_PROPERTY_URL);
}
std::string CGroupAILibraryInfo::GetInterfaceShortName() const {
	return GetInfo(GROUP_AI_PROPERTY_INTERFACE_SHORT_NAME);
}
std::string CGroupAILibraryInfo::GetInterfaceVersion() const {
	return GetInfo(GROUP_AI_PROPERTY_INTERFACE_VERSION);
}
std::string CGroupAILibraryInfo::GetInfo(const std::string& key) const {
	return infos.at(key).value;
}
const std::map<std::string, InfoItem>* CGroupAILibraryInfo::GetInfos() const {
	return &infos;
}

const std::vector<Option>* CGroupAILibraryInfo::GetOptions() const {
	return &options;
}


void CGroupAILibraryInfo::SetShortName(const std::string& shortName) { // restrictions: none of the following: spaces, '_', '#'
	SetInfo(GROUP_AI_PROPERTY_SHORT_NAME, shortName);
}
void CGroupAILibraryInfo::SetVersion(const std::string& version) { // restrictions: none of the following: spaces, '_', '#'
	SetInfo(GROUP_AI_PROPERTY_VERSION, version);
}
void CGroupAILibraryInfo::SetName(const std::string& name) {
	SetInfo(GROUP_AI_PROPERTY_NAME, name);
}
void CGroupAILibraryInfo::SetDescription(const std::string& description) {
	SetInfo(GROUP_AI_PROPERTY_DESCRIPTION, description);
}
void CGroupAILibraryInfo::SetURL(const std::string& url) {
	SetInfo(GROUP_AI_PROPERTY_URL, url);
}
void CGroupAILibraryInfo::SetInterfaceShortName(const std::string& interfaceShortName) {
	SetInfo(GROUP_AI_PROPERTY_INTERFACE_SHORT_NAME, interfaceShortName);
}
void CGroupAILibraryInfo::SetInterfaceVersion(const std::string& interfaceVersion) {
	SetInfo(GROUP_AI_PROPERTY_INTERFACE_VERSION, interfaceVersion);
}
bool CGroupAILibraryInfo::SetInfo(const std::string& key, const std::string& value) {
	
	if (key == GROUP_AI_PROPERTY_SHORT_NAME ||
			key == GROUP_AI_PROPERTY_VERSION) {
		if (value.find_first_of("\t _#") != std::string::npos) {
			handleerror(NULL, "Error", "Group AI info (shortName or version) contains illegal characters ('_', '#' or white spaces)", MBF_OK | MBF_EXCL);
			return false;
		}
	}
	
	InfoItem ii = {key.c_str(), value.c_str(), NULL};
	infos[key] = ii;
	return true;
}

void CGroupAILibraryInfo::SetOptions(const std::vector<Option>& _options) {
	options = std::vector<Option>(_options.begin(), _options.end()); // implicit convertible types -> range-ctor can be used
}
