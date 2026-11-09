#include <iostream>
#include <vector>
<<<<<<< Updated upstream
#include <fstream>
#include <string>
#include <utility>
=======
#include <string>
#include <utility>
#include <fstream>
>>>>>>> Stashed changes
#include <unordered_map>

#include "json.hpp"
using json = nlohmann::json;

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
    void add(Item item) {
        m_Items.emplace(item.internal_name, std::move(item));
    }
    const Item* find(const std::string& id) const {
        auto it = m_Items.find(id);
        return it == m_Items.end() ? nullptr : &it->second;
    }

private:
    std::unordered_map<std::string, Item> m_Items {};
};

void parse_neu(ItemDB& database) {
    std::cout << "parsing...\n";
    std::ifstream f{}

<<<<<<< Updated upstream
void parse_neu_repo() {

}



int main() {

    ItemDB ItemDatabase {};

    Item planks         {"Wooden Planks",  "wooden_planks",  "", 1.0f, 1.0f};
    Item stick          {"Stick",          "stick",          "", 1.0f, 1.0f};
    Item wooden_pickaxe {"Wooden Pickaxe", "wooden_pickaxe", "", 1.0f, 1.0f};
    
     
    planks.print();
    ItemDatabase.add(std::move(planks));
    return 0;
=======
};

int main(int argc, char* argv[]) {
    ItemDB ItemDatabase {};
    parse_neu(ItemDatabase);
>>>>>>> Stashed changes
}
