#ifndef TESTDATASETSTORE_H
#define TESTDATASETSTORE_H

#include "testdataset.h"

#include <string>
#include <map>
#include <vector>
#include <filesystem>
#include <memory>

class TestDatasetStore {
    std::vector<std::filesystem::path> itemFilePaths;
    std::vector<std::wstring> avaliableNames;
    std::map<std::wstring, std::shared_ptr<TestDataset>> items;
    void clearItems();
public:
    TestDatasetStore(std::filesystem::path p = "");

    void addItemPath(std::filesystem::path p);
    void removeItemPath(std::filesystem::path p);

    void loadItems();
    void saveItems();

    bool isItemExist(std::wstring itemHeader);
    std::weak_ptr<TestDataset> getItemPtr(std::wstring itemHeader);
    std::vector<std::wstring> getItemHeaders();
};

#endif // TESTDATASETSTORE_H
