#include <modules/config/config.hpp>
#include <modules/gui/gui.hpp>
#include <modules/gui/components/toggle.hpp>
#include <modules/hack/hack.hpp>

#include <Geode/modify/RewardUnlockLayer.hpp>

namespace eclipse::hacks::Bypass {
    class $hack(FastChests) {
        void init() override {
            auto tab = gui::MenuTab::find("tab.bypass");
            tab->addToggle("bypass.fastchests")->handleKeybinds()->setDescription();
        }

        [[nodiscard]] const char* getId() const override { return "Fast Chests"; }
    };

    REGISTER_HACK(FastChests)

    class $modify(FastChestsRWLHook, RewardUnlockLayer) {
        ADD_HOOKS_DELEGATE("bypass.fastchests")

        bool init(int chestType, RewardsPage* rewardsPage) {
            if (!RewardUnlockLayer::init(chestType, rewardsPage))
                return false;

            // Skip animations entirely, go straight to step3
            this->step3();

            return true;
        }
    };
}
