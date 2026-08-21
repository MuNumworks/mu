#include "script_store.h"
#include <string.h>

namespace Code {

constexpr char ScriptStore::k_scriptExtension[];
int ScriptStore::k_minusInExamMode = 0;

void ScriptStore::setKMinusInExamMode(int value) {
  k_minusInExamMode = value;
}

// void ScriptStore::examRename(int value) {
//   const char* oldExtension = value == 1 ? ".py" : ".txtInExam";
//   const char* newExtension = value == 1 ? ".txtInExam" : ".py";

//   size_t numRecords = Ion::Storage::sharedStorage()->numberOfRecordsWithExtension(oldExtension);

//   for (size_t i = 0; i < numRecords; i++) {
//     Ion::Storage::Record record = Ion::Storage::sharedStorage()->recordWithExtensionAtIndex(oldExtension, i);
//     if (!record.isNull()) {
//       // Get the base name and create the new name
//       const char* baseName = record.fullName();
//       size_t baseNameLength = strlen(baseName) - strlen(oldExtension);
      
//       // Create new name with the new extension
//       char newName[baseNameLength + strlen(newExtension) + 1];
//       strncpy(newName, baseName, baseNameLength);
//       strcpy(newName + baseNameLength, newExtension);

//       // Get the record content
//       size_t recordSize = record.value().size;
//       const void* recordData = record.value().buffer;

//       // Create a new record with the new name and the same content
//       Ion::Storage::Record::ErrorStatus err = Ion::Storage::sharedStorage()->createRecordWithFullName(newName, recordData, recordSize);
//       if (err == Ion::Storage::Record::ErrorStatus::None) {
//         // Delete the old record if the new record was successfully created
//         Ion::Storage::sharedStorage()->destroyRecord(record);
//       }
//     }
//   }
// }

bool ScriptStore::ScriptNameIsFree(const char * baseName) {
  return ScriptBaseNamed(baseName).isNull();
}

// Here we add "base" script
ScriptStore::ScriptStore() {
  // addScriptFromTemplate(ScriptTemplate::Pygame());
  addScriptFromTemplate(ScriptTemplate::Blue());
}

void ScriptStore::deleteAllScripts() {
  for (int i = numberOfScripts() - 1; i >= 0; i--) {
    scriptAtIndex(i).destroy();
  }
}

bool ScriptStore::isFull() {
  return Ion::Storage::sharedStorage()->availableSize() < k_fullFreeSpaceSizeLimit;
}

const char * ScriptStore::contentOfScript(const char * name, bool markAsFetched) {
  Script script = ScriptNamed(name);
  if (script.isNull()) {
    return nullptr;
  }
  if (markAsFetched) {
    script.setFetchedFromConsole(true);
  }
  return script.content();
}

void ScriptStore::clearVariableBoxFetchInformation() {
  // TODO optimize fetches
  const int scriptsCount = numberOfScripts();
  for (int i = 0; i < scriptsCount; i++) {
    scriptAtIndex(i).setFetchedForVariableBox(false);
  }
}

void ScriptStore::clearConsoleFetchInformation() {
  // TODO optimize fetches
  const int scriptsCount = numberOfScripts();
  for (int i = 0; i < scriptsCount; i++) {
    scriptAtIndex(i).setFetchedFromConsole(false);
  }
}

Script::ErrorStatus ScriptStore::addScriptFromTemplate(const ScriptTemplate * scriptTemplate) {
  size_t valueSize = Script::StatusSize() + strlen(scriptTemplate->content()) + 1; // (auto importation status + content fetched status) + scriptcontent size + null-terminating char
  assert(Script::nameCompliant(scriptTemplate->name()));
  Script::ErrorStatus err = Ion::Storage::sharedStorage()->createRecordWithFullName(scriptTemplate->name(), scriptTemplate->value(), valueSize);
  assert(err != Script::ErrorStatus::NonCompliantName);
  return err;
}

}
