
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Music/MusicComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Drawables/Texture.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadScoreScene(WAL::Scene &gameScene)
	{
        auto scene = std::make_shared<WAL::Scene>();
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
        static const std::vector<RAY::Color> tilesColor = {
            GOLD, GRAY, BROWN, PURPLE
        };

        addMenuControl(*scene);
        scene->addEntity("Audio ressources")
			.addComponent<MusicComponent>("assets/musics/music_result.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
        for (int i = 0; i < 4; i++) {
			auto &playerTile = scene->addEntity("player tile")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 2.5, 0)
				.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(224 * (i + 1) + 200 * i, 1080 / 3), RAY::Vector2(200, 200),tilesColor[i]);
			auto &player = scene->addEntity("player")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 2.5, 0)
				.addComponent<Drawable2DComponent, RAY::Texture>("assets/player/icons/none.png");
        }
        scene->addEntity("back to main menu")
			.addComponent<PositionComponent>(10, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back_hovered.png");
			});
        return scene;
    }
}