#include "QuestMaster.h"
#include "../GameMethods.h"
#include "../Offsets.h"

namespace QuestMaster {

    void PickUp() {
         std::cout << "PickUp" << std::endl;
       
        //auto el = Leveling::GetPickUpEl(Leveling::getOrderElById(Leveling::getOrderId()).QuestId);

         uint32_t state = *reinterpret_cast<uint32_t*>(Offsets::Offset_Quest_IsQuestComplete);//GlobalVars::g_hModuleBase + 0x2DC2B10);
         uint32_t Reward = *reinterpret_cast<uint32_t*>(Offsets::Offset_Quest_GetQuestReward);//GlobalVars::g_hModuleBase + 0x2DD2110);
         uint64_t RewardId = *reinterpret_cast<uint64_t*>(Offsets::Offset_Quest_GetQuestRewardid); //uint64_t RewardId;
        
        std::cout << "State: " << state << " QuestId: " /*<< el.QuestId*/ << std::endl;

        //switch (state) {
        //case 0:
        //case 1:
        //    if (GameMethods::isGossipOpenned() || GameMethods::IsQuestWindowOpen()) {
        //        GameMethods::Invoke<void>(
        //            GlobalVars::g_hModuleBase + 0x1448250,
        //            GlobalVars::LocalPlayer,
        //            GlobalVars::LocalPlayer->GetTargetGuid(),
        //            el.QuestId
        //        );
        //    }
        //    if (state == 1 && (GameMethods::IsQuestWindowOpen() || GameMethods::IsHuetaOpened())) {
        //        GameMethods::Invoke<void>(GlobalVars::g_hModuleBase + 0x1875C90); // accept quest
        //    }
        //    if (GlobalVars::LocalPlayer->GetActiveQuestById(el.QuestId).QuestId) {
        //        StateManager::forceState(States::Check);
        //    }
        //    break;

        //case 2:
        //    GameMethods::Invoke<void>(
        //        GlobalVars::g_hModuleBase + 0x1445250,
        //        GlobalVars::LocalPlayer,
        //        GlobalVars::LocalPlayer->GetTargetGuid(),
        //        *reinterpret_cast<uint32_t*>(GlobalVars::g_hModuleBase + 0x2DC2B14),
        //        0
        //    );
        //    if (ProfileUtils::isQuestComplete(el.QuestId)) {
        //        StateManager::forceState(States::Check);
        //    }
        //    break;

        //case 3:
        //    if (GameMethods::isGossipOpenned() || GameMethods::IsQuestWindowOpen()) {
        //        GameMethods::Invoke<void>(
        //            GlobalVars::g_hModuleBase + 0x1448250,
        //            GlobalVars::LocalPlayer,
        //            GlobalVars::LocalPlayer->GetTargetGuid(),
        //            el.QuestId
        //        );
        //    }
        //    if (Reward <= 0) {
        //        GameMethods::Invoke<void>(
        //            GlobalVars::g_hModuleBase + 0x1444870,
        //            GlobalVars::LocalPlayer,
        //            GlobalVars::LocalPlayer->GetTargetGuid(),
        //            *reinterpret_cast<uint32_t*>(GlobalVars::g_hModuleBase + 0x2DC2B14),
        //            0
        //        );
        //    }
        //    else {
        //        RewardId = *(unsigned int*)(0x88 * 1 + *reinterpret_cast<uint64_t*>(GlobalVars::g_hModuleBase + 0x2DD2118) + 8);
        //        GameMethods::Invoke<void>(
        //            GlobalVars::g_hModuleBase + 0x1444870,
        //            GlobalVars::LocalPlayer,
        //            GlobalVars::LocalPlayer->GetTargetGuid(),
        //            *reinterpret_cast<uint32_t*>(GlobalVars::g_hModuleBase + 0x2DC2B14),
        //            RewardId
        //        );
        //    }
        //    break;

        //default:
        //    break;
        //}
    }

    void TurnIn() {
        std::cout << "TurnIn" << std::endl;
        //auto el = Leveling::GetTurnInEl(Leveling::getOrderElById(Leveling::getOrderId()).QuestId);

        uint32_t state = *reinterpret_cast<uint32_t*>(Offsets::Offset_Quest_IsQuestComplete);//GlobalVars::g_hModuleBase + 0x2DC2B10);
        uint32_t Reward = *reinterpret_cast<uint32_t*>(Offsets::Offset_Quest_GetQuestReward);//GlobalVars::g_hModuleBase + 0x2DD2110);
        uint64_t RewardId = *reinterpret_cast<uint64_t*>(Offsets::Offset_Quest_GetQuestRewardid); //uint64_t RewardId;

        std::cout << "State: " << state << " QuestId: " /*<< el.QuestId */<< std::endl;

      /*  switch (state) {
        case 0:
        case 1:
            if (GameMethods::isGossipOpenned() || GameMethods::IsQuestWindowOpen()) {
                GameMethods::Invoke<void>(
                    GlobalVars::g_hModuleBase + 0x14415A0,
                    GlobalVars::LocalPlayer,
                    GlobalVars::LocalPlayer->GetTargetGuid(),
                    el.QuestId, 0
                );
            }
            if (state == 1 && (GameMethods::IsQuestWindowOpen() || GameMethods::IsHuetaOpened())) {
                GameMethods::Invoke<void>(GlobalVars::g_hModuleBase + 0x1875C90);
            }
            if (ProfileUtils::isQuestComplete(el.QuestId)) {
                StateManager::forceState(States::Check);
            }
            break;

        case 2:
            if (GameMethods::isGossipOpenned() || GameMethods::IsQuestWindowOpen()) {
                GameMethods::Invoke<void>(
                    GlobalVars::g_hModuleBase + 0x14415A0,
                    GlobalVars::LocalPlayer,
                    GlobalVars::LocalPlayer->GetTargetGuid(),
                    el.QuestId, 0
                );
            }
            if (GameMethods::IsQuestWindowOpen()) {
                GameMethods::Invoke<void>(
                    GlobalVars::g_hModuleBase + 0x1445250,
                    GlobalVars::LocalPlayer,
                    GlobalVars::LocalPlayer->GetTargetGuid(),
                    *reinterpret_cast<uint32_t*>(GlobalVars::g_hModuleBase + 0x2DC2B14),
                    0
                );
            }
            if (ProfileUtils::isQuestComplete(el.QuestId)) {
                StateManager::forceState(States::Check);
            }
            break;

        case 3:
            if (GameMethods::isGossipOpenned() || GameMethods::IsQuestWindowOpen()) {
                GameMethods::Invoke<void>(
                    GlobalVars::g_hModuleBase + 0x14415A0,
                    GlobalVars::LocalPlayer,
                    GlobalVars::LocalPlayer->GetTargetGuid(),
                    el.QuestId, 0
                );
            }
            break;

        default:
            break;
        }*/
    }
    //CGCore::GameTime() - (int)GameMethods::getCurrentTime();
    void QuestMaster() {
    //    if (Utils::timeSinceEpochMillisec() - GlobalVars::QuestWindowDelay > 1000) {
    //        GlobalVars::QuestWindowDelay = Utils::timeSinceEpochMillisec();

    //        int curQuestId = Leveling::getOrderElById(Leveling::getOrderId()).QuestId;
    //        std::string questGiver = Leveling::GetPickUpEl(curQuestId).GiverName;
    //        std::string turnInName = Leveling::GetTurnInEl(curQuestId).TurnInName;

    //        // Logic for quest handling (not fully provided in original code)
    //    }
    }
}