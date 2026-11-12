#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <utility>

#include "json.hpp"
using json = nlohmann::json;

namespace fs = std::filesystem;

struct Ingredient {
    std::string item_id {};
    int count {};
};

struct Item {
    std::string display_name  {}; // "displayname"
    std::string internal_name {}; // "internalname"
    std::string craft_text    {}; // "crafttext"
    double sell_offer      {}; 
    double insta_sell      {};
    
    std::vector<Ingredient> recipe {};

    Item(
        std::string display_name,
        std::string internal_name,
        std::string craft_text,
        double sell_offer,
        double insta_sell
    ) 
        :display_name(std::move(display_name)), 
        internal_name(std::move(internal_name)),
        craft_text(std::move(craft_text)),
        sell_offer(sell_offer),
        insta_sell(insta_sell)
    {};

    void print() const {
        std::cout << "Item:\n";
        std::cout << "  " << "display_name : " << this->display_name << '\n';
        std::cout << "  " << "internal_name : " << this->internal_name << '\n';
        std::cout << "  " << "craft_text : " << this->craft_text << '\n';
        std::cout << "  " << "sell_offer : $" << this->sell_offer << '\n';
        std::cout << "  " << "insta_sell : $" << this->insta_sell << '\n';
    }
};

class ItemDB {
public:
    void add_item(Item item) {
        m_Items.emplace(item.internal_name, std::move(item));
    }
    const Item* find(const std::string& id) const {
        auto it = m_Items.find(id);
        return it == m_Items.end() ? nullptr : &it->second;
    }

private:
    std::unordered_map<std::string, Item> m_Items {};
};


template <typename T>
static inline T get_value(const json& data, const std::string& key, const T& fallback) {
    if (!data.contains(key)) return fallback;
    return data.at(key).get<T>(); 
}

using map_type = std::unordered_map<std::string, json>;

void parse_recipes(json& data) {
    int i = 0;
    if (!data.contains("recipes")) return;
    for (const auto& entry : data.at("recipes")) {
        if (!entry.contains("A1")) continue;
        std::cout << entry.at("A1").get<std::string>() << '\n'; 
    }
};

static constexpr char neu_path[] = "./NotEnoughUpdates-REPO/items";
void parse_neu(ItemDB& database) {
    std::cout << "running...\n";
    for (const auto& entry : fs::directory_iterator(neu_path)) {

        std::ifstream file(entry.path());
        json data = json::parse(file);
        std::string displayname  {get_value<std::string>(data, "displayname", "ERROR:displayname")};
        std::string internalname {get_value<std::string>(data, "internalname", "ERROR:displayname")};
        std::string crafttext    {get_value<std::string>(data, "crafttext", "")};
        
        Item temp {displayname, internalname, crafttext, 0, 0};
        
        parse_recipes(data);

        // TODO, get the recipe table from the json
        
        database.add_item(std::move(temp));





        
    }
}

int main(int argc, char* argv[]) {
    ItemDB ItemDatabase {};
    parse_neu(ItemDatabase);
    const auto* item = ItemDatabase.find("HYPERION");
    if (item) {
        item->print();
    } else {
        std::cout << "bruh\n";
    }
}
