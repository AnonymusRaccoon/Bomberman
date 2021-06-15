//
// Created by hbenjamin on 10/06/2021.
//

#include <fstream>
#include <map>
#include <Component/Position/PositionComponent.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include <Map/Map.hpp>
#include <Component/BombHolder/BombHolderComponent.hpp>
#include <sstream>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Component/Shaders/ShaderComponent.hpp>
#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Tag/TagComponent.hpp>
#include <Component/Animation/AnimationsComponent.hpp>
#include <Component/Sound/SoundComponent.hpp>
#include <Component/Bonus/PlayerBonusComponent.hpp>
#include <Component/Music/MusicComponent.hpp>
#include <Items/Bonus.hpp>
#include <Exception/Error.hpp>
#include "ParserYaml.hpp"
#include <algorithm>
#include <Component/Levitate/LevitateComponent.hpp>
#include <Runner/Runner.hpp>
#include <cstring>
#include <sstream>

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM {

	const std::string ParserYAML::fileName = "save";
	std::stringstream ParserYAML::_block("");
	std::stringstream ParserYAML::_bonus("bonuses:");
	std::stringstream ParserYAML::_player("players:");

	std::string ParserYAML::_getBlockType(std::string blockName)
	{
		static std::map<std::string, MapGenerator::BlockType> map {
			{"Upper Floor", MapGenerator::BlockType::UPPERFLOOR},
			{"Bumper Block", MapGenerator::BlockType::BUMPER},
			{"Breakable Block", MapGenerator::BlockType::BREAKABLE},
			{"Unbreakable Block", MapGenerator::BlockType::UNBREAKABLE},
			{"Hole Block", MapGenerator::BlockType::HOLE}
		};

		return (std::to_string(map.at(blockName)));
	}

	std::string ParserYAML::_getBonusType(std::string bonusName)
	{
		static std::map<std::string, Bonus::BonusType> map {
			{"Bonus Bomb Up", Bonus::BonusType::BOMBSTOCK},
			{"Bonus Speed Up", Bonus::BonusType::SPEEDUP},
			{"Bonus Fire Up", Bonus::BonusType::EXPLOSIONINC}
		};

		return (std::to_string(map.at(bonusName)));
	}

	void ParserYAML::_saveBonus(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_bonus << std::endl << "  " << name << ":" << std::endl << "    ";
		_bonus << std::string("bonus_type: ") << _getBonusType(entity.getName()) << std::endl << "    ";
		_bonus << "position: [" << std::to_string(position->getX()) << " " << std::to_string(position->getY()) << " " << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::_savePlayer(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();
		auto name = entity.getName();

		if (!position || !bombHolder)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_player << std::endl << "  " << name << ":" << std::endl << "    ";
		_player << "max_bomb: " << std::to_string(bombHolder->maxBombCount) << std::endl << "        ";
		_player << "explosion_radius: " << std::to_string(bombHolder->explosionRadius) << std::endl << "        ";
		_player << "position: [" << std::to_string(position->getX()) << " " << std::to_string(position->getY()) << " " << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::_saveBlock(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_block << std::endl << "  " << name << ":" << std::endl << "    ";
		_block << std::string("block_type: ") << _getBlockType(entity.getName()) << std::endl << "    ";
		_block << "position: [" << std::to_string(position->getX()) << " " << std::to_string(position->getY()) << " " << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::save(std::shared_ptr<WAL::Scene> scene)
	{
		std::string block = std::string("save/" + fileName + "_block.yml");
		std::string player = std::string("save/" + fileName + "_player.yml");
		std::string bonus = std::string("save/" + fileName + "_bonus.yml");
		std::map<std::string, std::function<void (const WAL::Entity &)>> savingGame = {
				{"Bonus", &_saveBonus},
				{"Block", &_saveBlock},
				{"Upper Floor", &_saveBlock},
				{"Player", &_savePlayer}
		};
		std::ofstream blockFile(block);
		std::ofstream playerFile(player);
		std::ofstream bonusFile(bonus);

		_block << "width: " << std::to_string(Runner::mapWidth);
		_block << std::endl << "height: " + std::to_string(Runner::mapHeight);
		_block << std::endl << "blocks:";
		for (const auto &entity : scene->getEntities()) {
			for (const auto& type : savingGame) {
				if (entity.getName().find(type.first) != std::string::npos) {
					type.second(entity);
				}
			}
		}
		blockFile << _block.str() << std::endl;
		playerFile << _player.str() << std::endl;
		bonusFile << _bonus.str() << std::endl;
		_block.clear();
		_player.clear();
		_bonus.clear();
	}

	void ParserYAML::_loadPlayer(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index)
	{
		auto &entity = scene->addEntity("");
		static std::map<SoundComponent::SoundIndex, std::string> soundPath ={
				{SoundComponent::JUMP, "assets/sounds/jump.wav"},
				{SoundComponent::MOVE, "assets/sounds/move.ogg"},
				{SoundComponent::BOMB, "assets/sounds/bomb_drop.ogg"},
				//{SoundComponent::DEATH, "assets/sounds/death.ogg"}
		};
		int maxBomb = 3;
		float explosionRadius = 3;
		Vector3f pos;

		for (; index != lines.size(); index++) {
			if (lines[index].find("max_bomb") != std::string::npos) {
				maxBomb = _parseMaxBomb(lines[index]);
			} else if (lines[index].find("explosion_radius") != std::string::npos) {
				explosionRadius = _parseExplosionRadius(lines[index]);
			} else if (lines[index].find("position") != std::string::npos) {
				pos = _parsePosition(lines[index]);
			} else {
				if (!entity.getName().empty()) {
					break;
				}
				_parseEntityName(lines[index], entity);
			}
		}
		entity.addComponent<PositionComponent>(pos)
			.addComponent<BombHolderComponent>(maxBomb, explosionRadius)
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", true, std::make_pair(MAP_DIFFUSE, "assets/player/blue.png"))
			.addComponent<ControllableComponent>()
			.addComponent<AnimatorComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<ShaderComponentModel>("assets/shaders/glsl330/predator.fs")
			.addComponent<TagComponent<Blowable>>()
			.addComponent<AnimationsComponent>(RAY::ModelAnimations("assets/player/player.iqm"), 3)
			.addComponent<CollisionComponent>(BBM::Vector3f{0.25, 0, 0.25}, BBM::Vector3f{.75, 2, .75})
			.addComponent<MovableComponent>()
			.addComponent<SoundComponent>(soundPath)
			.addComponent<MusicComponent>("assets/musics/music_battle.ogg")
			.addComponent<PlayerBonusComponent>()
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity, WAL::Wal &wal) {
				auto &animation = entity.getComponent<AnimationsComponent>();
				animation.setAnimIndex(5);
			});
	}

	void ParserYAML::_loadPlayers(std::shared_ptr<WAL::Scene> scene)
	{
		std::ifstream file("save/" + fileName + "_player.yml");
		std::string line;
		std::vector<std::string> lines;

		if (!file.good())
			throw (ParserError("File error"));
		while (std::getline(file, line)) {
			if (line.empty() || !line.compare("players:"))
				continue;
			lines.push_back(line);
		}
		for (int index = 0; lines.size() != index; index++) {
			_loadPlayer(scene, lines, index);
			index--;
		}
	}

	void ParserYAML::_loadBlock(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index, MapGenerator::MapBlock &map)
	{
		std::string tmpName = "";
		Vector3f pos;
		MapGenerator::BlockType blockType = MapGenerator::NOTHING;

		for (; index != lines.size(); index++) {
			if (lines[index].find("position") != std::string::npos) {
				pos = _parsePosition(lines[index]);
			} else if (lines[index].find("block_type") != std::string::npos) {
				blockType = _parseBlockType(lines[index]);
			} else {
				if (!tmpName.empty()) {
					break;
				}
				tmpName = lines[index];
			}
		}
		if (blockType == MapGenerator::NOTHING)
			throw (ParserError("Invalid block_type field."));
		if (blockType == MapGenerator::HOLE)
			pos.y += 1.0f;
		map[std::make_tuple(pos.x, pos.y, pos.z)] = blockType;
	}

	void ParserYAML::_loadBlocks(std::shared_ptr<WAL::Scene> scene)
	{
		std::ifstream file("save/" + fileName + "_block.yml");
		std::string line;
		std::vector<std::string> lines;
		MapGenerator::MapBlock map;

		if (!file.good())
			throw (ParserError("File error"));
		while (std::getline(file, line)) {
			if (line.find("width:") != std::string::npos) {
				Runner::mapWidth = std::atoi(line.substr(line.find(": ", 0) + 2, line.length()).c_str());
				continue;
			}
			if (line.find("height:") != std::string::npos) {
				Runner::mapHeight = std::atoi(line.substr(line.find(": ", 0) + 2, line.length()).c_str());
				continue;
			}
			if (line.empty() || line.find("blocks:") != std::string::npos)
				continue;
			lines.push_back(line);
		}
		for (int i = 0; i < Runner::mapWidth; i++)
			for (int j = 0; j < Runner::mapHeight; j++)
				map[std::make_tuple(i, 0, j)] = MapGenerator::NOTHING;
		for (int index = 0; lines.size() != index; index++) {
			_loadBlock(scene, lines, index, map);
			index--;
		}
		MapGenerator::loadMap(Runner::mapWidth, Runner::mapHeight, map, scene);
	}

	void ParserYAML::_loadBonus(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index)
	{
		auto &entity = scene->addEntity("");
		std::string tmpName = "";
		Vector3f pos;
		Bonus::BonusType bonusType;

		for (; index != lines.size(); index++) {
			if (lines[index].find("position") != std::string::npos) {
				pos = _parsePosition(lines[index]);
			} else if (lines[index].find("bonus_type") != std::string::npos) {
				bonusType = _parseBonusType(lines[index]);
			} else {
				if (!tmpName.empty()) {
					break;
				}
				_parseEntityName(lines[index], entity);
			}
		}
		MapGenerator::createBonus(entity, pos, bonusType);
	}

	void ParserYAML::_loadBonuses(std::shared_ptr<WAL::Scene> scene)
	{
		std::ifstream file("save/" + fileName + "_bonus.yml");
		std::string line;
		std::vector<std::string> lines;

		if (!file.good())
			throw (ParserError("File error"));
		while (std::getline(file, line)) {
			if (line.empty() || !line.compare("bonuses:"))
				continue;
			lines.push_back(line);
		}
		for (int index = 0; lines.size() != index; index++) {
			_loadBonus(scene, lines, index);
			index--;
		}
	}

	void ParserYAML::load(std::shared_ptr<WAL::Scene> scene)
	{
		_loadBlocks(scene);
		_loadBonuses(scene);
		_loadPlayers(scene);
	}

	WAL::Entity &ParserYAML::_parseEntityName(std::string line, WAL::Entity &entity)
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		auto name = line.substr(0, line.find(':'));
		std::replace(name.begin(), name.end(), '_', ' ');
		entity.setName(name);
		return (entity);
	}

	Vector3f ParserYAML::_parsePosition(std::string &line) {
		std::string x;
		std::string y;
		std::string z;
		std::string subStr;

		try {
			auto start = line.find("[", 0) + 1;
			subStr = line.substr(start, line.find("]", 0) - 1 - start);
			auto pos = _splitStr(subStr, ' ');
			if (pos.size() != 3)
				throw (ParserError("Error parsing position"));
			x = pos[0];
			y = pos[1];
			z = pos[2];
		} catch (const std::out_of_range &err) {
			throw (ParserError("Error parsing position"));
		}
		if (!_isFloat(x) || !_isFloat(y) || !_isFloat(z))
			throw (ParserError("Error parsing position"));
		return Vector3f(std::atof(x.c_str()), std::atof(y.c_str()), std::atof(z.c_str()));
	}

	int ParserYAML::_parseMaxBomb(std::string &line)
	{
		if (line.find(": ") == std::string::npos || !_isInteger(line.substr(line.find(": ") + 2)))
			throw (ParserError("Couldn't parse max bomb"));
		return (std::atoi(line.substr(line.find(": ") + 2).c_str()));
	}

	float ParserYAML::_parseExplosionRadius(std::string &line)
	{
		if (line.find(": ") == std::string::npos || !_isFloat(line.substr(line.find(": ") + 2)))
			throw (ParserError("Couldn't parse explosion radius"));
		return (std::atof(line.substr(line.find(": ") + 2).c_str()));
	}

	MapGenerator::BlockType ParserYAML::_parseBlockType(std::string blockType)
	{
		if (blockType.find(": ") == std::string::npos || !_isInteger(blockType.substr(blockType.find(": ") + 2)))
			throw (ParserError("Couldn't parse block type"));
		return (static_cast<MapGenerator::BlockType>(std::atoi(blockType.substr(blockType.find(": ") + 2).c_str())));
	}

	Bonus::BonusType ParserYAML::_parseBonusType(std::string bonusType)
	{
		if (bonusType.find(": ") == std::string::npos || !_isInteger(bonusType.substr(bonusType.find(": ") + 2)))
			throw (ParserError("Couldn't parse bonus type"));
		return (static_cast<Bonus::BonusType>(std::atoi(bonusType.substr(bonusType.find(": ") + 2).c_str())));
	}

	bool ParserYAML::_isInteger(const std::string &s)
	{
		std::istringstream iss(s);
		int i;

		iss >> std::noskipws >> i;
		return iss.eof() && !iss.fail();
	}

	bool ParserYAML::_isFloat(const std::string &s)
	{
		std::istringstream iss(s);
		float f;

		iss >> std::noskipws >> f;
		return iss.eof() && !iss.fail();
	}

	std::vector<std::string> ParserYAML::_splitStr(const std::string &str, char delim)
	{
		std::vector<std::string> strings;
		std::istringstream f(str);
		std::string buffer;

		while (std::getline(f, buffer, delim)) {;
			strings.push_back(buffer);
		}
		return strings;
	}
}