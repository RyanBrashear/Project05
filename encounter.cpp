#include "encounter.hpp"


Encounter::Encounter()
{

}


// implement
// delete all entities within this list.
// YOU MUST EXPLICITLY DELETE ALL ENTITIES
// SINCE OUR DICTIONARY HOLDS POINTERS
Encounter::~Encounter()
{
    Stack<uint32_t> keys = _encounterDictionary.Keys();
    while(!keys.IsEmpty())
    {
        Entity * toDelete = _encounterDictionary.At(keys.PopItem());
        delete toDelete;
    }
}

// implement
// inserts a new Entity node with the entity parameter as its
// data.
// HINT: ALL ITEMS ARE INSERTED TO THE BACK OF THIS LIST.
// HINT: You do NOT have a _lastItem in this list, so you will
//       have to locate it every time you add an item to the 
//       back of the list.
void Encounter::AddEntity(Entity *entity)
{
    std::cout << "Inserting entity: " << entity->Name() << std::endl;
    _encounterDictionary.Insert(entity->UID(), entity);
}


// implement
// output only the specific entities status
// if the entity does not exist, call PrintBadAccessError with
// the entityID in question.
// HINT: use findEntity to find the correct entity.
// HINT: use Entity::OutputStatus() to print the entity's status
void Encounter::PrintEntityStatus(uint32_t entityID) const
{
    if(_encounterDictionary.Contains(entityID))
    {
        Entity * tmp = _encounterDictionary.At(entityID);
        tmp->OutputStatus();
    }
    else
    {
        PrintBadAccessError(entityID);
    }    
}

// implement
// print the status of all entities in the encounter
// between each unit, call Bars() to print bars to make the
// output better
// HINT: You are going to use Entity::OutputStatus() 
void Encounter::PrintAllStatuses() const
{
    Stack<uint32_t> keys = _encounterDictionary.Keys();
    while(!keys.IsEmpty())
    {
        uint32_t key = keys.PopItem();
        std::cout << key << std::endl;
        _encounterDictionary.At(key)->OutputStatus();
        if(!keys.IsEmpty())
        {
            Bars();
        }
    }
}


// provided for you
void Encounter::UseAction(uint32_t attackerUID, uint32_t targetUID, const std::string &spellName, const std::string & args)
{
    if(!_encounterDictionary.Contains(attackerUID))
    {
        PrintBadAccessError(attackerUID);
    }
    if(!_encounterDictionary.Contains(targetUID))
    {
        PrintBadAccessError(targetUID);
    }


    Entity *attacker = _encounterDictionary.At(attackerUID);
    Entity *target = _encounterDictionary.At(targetUID);


    if(attacker == nullptr)
    {
        PrintBadAccessError(attackerUID);
        return;
    }

    if(target == nullptr)
    {
        PrintBadAccessError(targetUID);
        return;
    }

    attacker->UseAction(target, spellName, args);

    if(!target->IsAlive())
    {
        attacker->LootAnEntity(target);
        _encounterDictionary.Remove(target->UID());
        delete target;
    }

    if(!attacker->IsAlive())
    {
        _encounterDictionary.Remove(target->UID());
        delete attacker;
    }
}

// provided for you
void Encounter::PrintBadAccessError(uint32_t uid) const
{
    std::cout << "Attempted to access an entity with a UID: " << uid 
              << " that did not exist within the list.  Exiting." << std::endl;
}

void Encounter::Bars() const
{
    std::cout << "--------------------------------" << std::endl;
}