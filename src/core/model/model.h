#pragma once

#include <algorithm>
#include <deque>
#include <memory>
#include <string_view>

namespace core::model {

struct IModel {
    IModel() {
        static uint64_t nextId = 1;
        ModelId = nextId++;
    }

    virtual std::string_view GetScheme() const = 0;
    virtual std::string_view GetData() const = 0;

    virtual bool AddSubmodel(const std::shared_ptr<IModel> &model) {
        Submodels.push_back(model);
        return true;
    }

    virtual bool RemoveSubmodel(const std::shared_ptr<IModel> &model) {
        if (auto it = std::find(Submodels.begin(), Submodels.end(), model); it != Submodels.end()) {
            Submodels.erase(it);
            return true;
        }
        return false;
    }

protected:
    std::deque<std::shared_ptr<IModel>> Submodels;
    uint64_t ModelId;
};

}