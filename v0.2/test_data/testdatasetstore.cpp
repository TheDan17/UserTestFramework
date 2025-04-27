#include "testdatasetstore.h"

#include <algorithm>


TestDatasetStore::TestDatasetStore(std::filesystem::path p) {
    if (!p.empty())
        addItemPath(p);
}

void TestDatasetStore::clearItems(){
    if (items.empty())
        return;
    while (!items.empty())
        items.erase(items.begin());
    while (!avaliableNames.empty())
        avaliableNames.erase(avaliableNames.begin());
}

void TestDatasetStore::addItemPath(std::filesystem::path p){
    itemFilePaths.push_back(p);
}

void TestDatasetStore::removeItemPath(std::filesystem::path p){
    auto it = std::find(itemFilePaths.begin(), itemFilePaths.end(), p);
    if (it != itemFilePaths.end())
        itemFilePaths.erase(it);
}

#include <QDebug>
void TestDatasetStore::loadItems(){
    this->clearItems();
    for (auto& path : itemFilePaths) {
        std::shared_ptr<TestDataset> datasetObj = std::make_shared<TestDataset>(path.string());
        avaliableNames.push_back(datasetObj->getName());
        items[datasetObj->getName()] = std::move(datasetObj);
    }
}
void TestDatasetStore::saveItems(){
    for (auto& dataset : this->items){
        dataset.second->save();
    }
}

bool TestDatasetStore::isItemExist(std::wstring datasetName){
    if (items.find(datasetName) != items.end())
        return true;
    else
        return false;
}
std::weak_ptr<TestDataset> TestDatasetStore::getItemPtr(std::wstring itemHeader) {
    return items[itemHeader];
}
std::vector<std::wstring> TestDatasetStore::getItemHeaders(){
    return this->avaliableNames;
}
