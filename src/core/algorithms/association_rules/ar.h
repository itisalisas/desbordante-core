#pragma once

#include <list>

#include "model/transaction/itemset.h"
#include "model/transaction/transactional_data.h"

namespace model {

struct ArIDs {
    std::vector<unsigned> left;   // antecedent
    std::vector<unsigned> right;  // consequent
    double confidence = -1;
    double support = -1;

    ArIDs() = default;

    ArIDs(std::vector<unsigned> left, std::vector<unsigned> right, double confidence,
          double support)
        : left(std::move(left)),
          right(std::move(right)),
          confidence(confidence),
          support(support) {}

    ArIDs(ArIDs const& other) = default;
    ArIDs& operator=(ArIDs const& other) = default;
    ArIDs(ArIDs&& other) = default;
    ArIDs& operator=(ArIDs&& other) = default;
};

struct ARStrings {
    std::list<std::string> left;   // antecedent
    std::list<std::string> right;  // consequent
    double confidence = -1;
    double support = -1;

    ARStrings() = default;

    ARStrings(std::list<std::string> left, std::list<std::string> right, double confidence,
              double support)
        : left(std::move(left)),
          right(std::move(right)),
          confidence(confidence),
          support(support) {}

    ARStrings(ArIDs const& id_format_rule, TransactionalData const* transactional_data)
        : confidence(id_format_rule.confidence), support(id_format_rule.support) {
        std::vector<std::string> const& item_names_map = transactional_data->GetItemUniverse();

        for (auto item_id : id_format_rule.left) {
            this->left.push_back(item_names_map[item_id]);
        }
        for (auto item_id : id_format_rule.right) {
            this->right.push_back(item_names_map[item_id]);
        }
    }

    ARStrings(ARStrings const& other) = default;
    ARStrings& operator=(ARStrings const& other) = default;
    ARStrings(ARStrings&& other) = default;
    ARStrings& operator=(ARStrings&& other) = default;

    std::string ToString() const {
        std::string result;
        result.append("conf: ");
        result.append(std::to_string(confidence));
        result.append("\tsup: ");
        result.append(std::to_string(support));
        result.append("\t{");
        for (auto const& item_name : left) {
            result.append(item_name);
            result.append(", ");
        }
        result.erase(result.size() - 2, 2);
        result.append("} -> {");
        for (auto const& item_name : right) {
            result.append(item_name);
            result.append(", ");
        }
        result.erase(result.size() - 2, 2);
        result.push_back('}');

        return result;
    }
};

}  // namespace model
