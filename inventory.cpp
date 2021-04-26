#include "inventory.hpp"


Inventory::~Inventory()
{
    std::cout << "inventory dtr called" << std::endl;
}


/// provided
void Inventory::Init(JsonItemBuilder &jsonBuilder, const std::vector<int> & uids)
{
    for(const auto & uid : uids)
    {
        _inventoryData.Insert(uid, {jsonBuilder, static_cast<uint32_t>(uid)});
    }
}

void Inventory::AddItemToInventory(const Item &item)
{
    _inventoryData.Insert(item.UID(), item);
}


Item Inventory::LootAnItem(uint32_t uid)
{
    return _inventoryData.Remove(uid);
}

void Inventory::LootAnotherInventory(Inventory & inventory)
{
    // while(!inventory.IsEmpty())
    // {
    //     Item looted = inventory._inventoryData.Pop();
    //     _inventoryData.Insert(looted.UID(), looted);
    // }

    Stack<uint32_t> itemKeys = inventory._inventoryData.Keys();
    while(!itemKeys.IsEmpty())
    {
        uint32_t key = itemKeys.PopItem();
        Item lootedItem = inventory._inventoryData.Remove(key);
        _inventoryData.Insert(key, lootedItem);
    }
}


bool Inventory::IsEmpty() const
{
    return _inventoryData.IsEmpty();
}


// implement
// loops through the list and calls the item to 
// print its contents though the Item::PrintData()
void Inventory::PrintInventory() const
{
    Stack<uint32_t> keys = _inventoryData.Keys();
    while(!keys.IsEmpty())
    {
        uint32_t key = keys.PopItem();
        std::cout << _inventoryData.At(key) << std::endl;
    }
}
