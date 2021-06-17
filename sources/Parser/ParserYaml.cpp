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
#include <Component/Gamepad/GamepadComponent.hpp>
#include <Component/Renderer/Drawable2DComponent.hpp>
#include <System/Lobby/LobbySystem.hpp>
#include <filesystem>
#include "Utils/Utils.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM {

	const std::string ParserYAML::fileName = "save";
	std::stringstream ParserYAML::_block("");
	std::stringstream ParserYAML::_bonus("");
	std::stringstream ParserYAML::_player("");
	std::vector<std::string> ParserYAML::playerName = {};
	std::vector<Vector3f> ParserYAML::playerPosition = {};
	std::vector<int> ParserYAML::playerBombCount = {};
	std::vector<float> ParserYAML::playerExplosionRange = {};
	std::vector<float> ParserYAML::playerSpeed = {};
	std::vector<std::string> ParserYAML::playerAssets = {};

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
		_bonus << "position: [" << std::to_string(position->getX()) << "," << std::to_string(position->getY()) << "," << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::_savePlayer(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();
		auto *model = entity.tryGetComponent<Drawable3DComponent>();
		auto *controllable = entity.tryGetComponent<ControllableComponent>();
		auto name = entity.getName();

		if (!position || !bombHolder || !model || !controllable)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_player << std::endl << "  " << name << ":" << std::endl << "    ";
		_player << "texture_path: " << dynamic_cast<RAY3D::Model *>(model->drawable.get())->getTextureByMaterial(MAP_DIFFUSE).getResourcePath() << std::endl << "    ";
		_player << "max_bomb: " << std::to_string(bombHolder->maxBombCount) << std::endl << "    ";
		_player << "explosion_radius: " << std::to_string(bombHolder->explosionRadius) << std::endl << "    ";
		_player << "speed: " << std::to_string(controllable->speed) << std::endl << "    ";
		_player << "position: [" << std::to_string(position->getX()) << "," << std::to_string(position->getY()) << "," << std::to_string(position->getZ()) << "]";
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
		_block << "position: [" << std::to_string(position->getX()) << "," << std::to_string(position->getY()) << "," << std::to_string(position->getZ()) << "]";
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

		_player << "players:";
		_bonus << "bonuses:";
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
		_block = std::stringstream();
		_player = std::stringstream();
		_bonus = std::stringstream();
	}

	void ParserYAML::_loadPlayer(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index, int countPlayer)
	{
		std::string name;
		std::string tmpAssets;
		std::map<std::string, RAY::Color> map = {
				{"red", RED},
				{"blue", BLUE},
				{"yellow", YELLOW},
				{"green", GREEN}
		};

		for (; index != lines.size(); index++) {
			if (lines[index].find("max_bomb") != std::string::npos && !name.empty()) {
				playerBombCount.push_back(_parseMaxBomb(lines[index]));
			} else if (lines[index].find("explosion_radius") != std::string::npos && !name.empty()) {
				playerExplosionRange.push_back(_parseExplosionRadius(lines[index]));
			} else if (lines[index].find("position") != std::string::npos && !name.empty()) {
				playerPosition.push_back(_parsePosition(lines[index]));
			} else if (lines[index].find("texture_path") != std::string::npos && !name.empty()) {
				playerAssets.push_back(_parseAssets(lines[index]));
				tmpAssets = _parseAssets(lines[index]);
			} else if (lines[index].find("speed") != std::string::npos && !name.empty()) {
				playerSpeed.push_back(_parseSpeed(lines[index]));
			} else {
				if (!name.empty()) {
					break;
				}
				name = lines[index];
				name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
				name = name.substr(0, name.find(':'));
				std::replace(name.begin(), name.end(), '_', ' ');
				playerName.push_back(name);
			}
		}
		if ((tmpAssets.find("red.png") == std::string::npos && tmpAssets.find("blue.png") == std::string::npos &&
		tmpAssets.find("green.png") == std::string::npos && tmpAssets.find("yellow.png") == std::string::npos &&
		tmpAssets.find("ai.png") == std::string::npos) || !std::filesystem::exists(tmpAssets)) {
			throw (ParserError("Error with saved map: One asset is invalid.\n                Loading default maps..."));
		}
		auto start = tmpAssets.find_last_of("/") + 1;
		auto color = map.at(tmpAssets.substr(start, tmpAssets.length() - start - 4));
		auto resumeScene = Runner::gameState._loadedScenes[GameState::SceneID::ResumeLobbyScene];
		auto &playerTile = resumeScene->addEntity("player tile")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3), RAY::Vector2(200, 200), color);
		auto &playerLogo = resumeScene->addEntity("player")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>(tmpAssets.replace(tmpAssets.find("textures"), 8, "icons"));
		auto &ready = resumeScene->addEntity("ready")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>();
		playerLogo.addComponent<LobbyComponent>(countPlayer, ready, playerTile);
	}

	void ParserYAML::_loadPlayers(std::shared_ptr<WAL::Scene> scene)
	{
		std::ifstream file("save/" + fileName + "_player.yml");
		std::string line;
		std::vector<std::string> lines;
		int countPlayer = 0;

		if (!file.good())
			throw (ParserError("File error"));
		while (std::getline(file, line)) {
			if (line.empty() || line.find("players:") != std::string::npos)
				continue;
			lines.push_back(line);
		}
		for (int index = 0; lines.size() != index; index++) {
			_loadPlayer(scene, lines, index, countPlayer);
			index--;
			countPlayer++;
		}
	}

	void ParserYAML::_loadBlock(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index, MapGenerator::MapBlock &map)
	{
		std::string tmpName = "";
		Vector3f pos;
		MapGenerator::BlockType blockType = MapGenerator::NOTHING;

		for (; index != lines.size(); index++) {
			if (lines[index].find("position") != std::string::npos && !tmpName.empty()) {
				pos = _parsePosition(lines[index]);
			} else if (lines[index].find("block_type") != std::string::npos && !tmpName.empty()) {
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

	void ParserYAML::_loadBlocks(std::shared_ptr<WAL::Scene> scene, Node &node)
	{
		MapGenerator::MapBlock map;
		int size = -1;

		if (!Utils::tryParseInteger(node.getProperty("width"), size)) {
			throw ParserError("width property must be an int");
		}
		Runner::mapWidth = size;
		if (!Utils::tryParseInteger(node.getProperty("height"), size)) {
			throw ParserError("width property must be an int");
		}
		Runner::mapHeight = size;

		for (int i = 0; i < Runner::mapWidth; i++)
			for (int j = 0; j < Runner::mapHeight; j++)
				map[std::make_tuple(i, 0, j)] = MapGenerator::NOTHING;
		/*for (int index = 0; lines.size() != index; index++) {
			_loadBlock(scene, lines, index, map);
			index--;
		}*/
		MapGenerator::loadMap(Runner::mapWidth, Runner::mapHeight, map, scene);
	}

	void ParserYAML::_loadBonus(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index)
	{
		auto &entity = scene->addEntity("");
		Vector3f pos;
		Bonus::BonusType bonusType;

		for (; index != lines.size(); index++) {
			if (lines[index].find("position") != std::string::npos && !entity.getName().empty()) {
				pos = _parsePosition(lines[index]);
			} else if (lines[index].find("bonus_type") != std::string::npos && !entity.getName().empty()) {
				bonusType = _parseBonusType(lines[index]);
			} else {
				if (!entity.getName().empty()) {
					break;
				}
				_parseEntityName(lines[index], entity);
			}
		}
		if (bonusType == Bonus::NOTHING) {
			entity.scheduleDeletion();
			return;
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
			if (line.empty() || line.find("bonuses:") != std::string::npos)
				continue;
			lines.push_back(line);
		}
		for (int index = 0; lines.size() != index; index++) {
			_loadBonus(scene, lines, index);
			index--;
		}
	}

	void ParserYAML::load(std::shared_ptr<WAL::Scene> gameScene)
	{
		Node blocksInfos = parseFile("assets/save_block.yml");
		Node bonusesInfos = parseFile("assets/save_bonus.yml");
		Node playerInfos = parseFile("assets/save_player.yml");
		_loadBlocks(gameScene, blocksInfos);
		_loadBonuses(gameScene);
		_loadPlayers(gameScene);
	}

	WAL::Entity &ParserYAML::_parseEntityName(std::string line, WAL::Entity &entity)
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		auto name = line.substr(0, line.find(':'));
		std::replace(name.begin(), name.end(), '_', ' ');
		entity.setName(name);
		return (entity);
	}

	std::string ParserYAML::_parseAssets(std::string &line)
	{
		if (line.find(":", 0) == std::string::npos)
			throw (ParserError("Error with saved map: Error parsing assets.\n                Loading default maps..."));
		auto start = line.find(":", 0) + 2;
		return (line.substr(start, line.length() - start));
	}

	Vector3f ParserYAML::_parsePosition(std::string &line)
	{
		std::string x;
		std::string y;
		std::string z;
		std::string subStr;

		try {
			auto start = line.find("[", 0) + 1;
			subStr = line.substr(start, line.find("]", 0) - 1 - start);
			auto pos = Utils::splitStr(subStr, ' ');
			if (pos.size() != 3)
				throw (ParserError("Error with saved map: Error parsing position.\n                Loading default maps..."));
			x = pos[0];
			y = pos[1];
			z = pos[2];
		} catch (const std::out_of_range &err) {
			throw (ParserError("Error with saved map: Error parsing position.\n                Loading default maps..."));
		}
		//if (!_isFloat(x) || !_isFloat(y) || !_isFloat(z))
		//	throw (ParserError("Error with saved map: Error parsing position.\n                Loading default maps..."));
		return Vector3f(std::atof(x.c_str()), std::atof(y.c_str()), std::atof(z.c_str()));
	}

	int ParserYAML::_parseMaxBomb(std::string &line)
	{
		//if (line.find(": ") == std::string::npos || !_isInteger(line.substr(line.find(": ") + 2)))
		//	throw (ParserError("Error with saved map: Couldn't parse max bomb.\n                Loading default maps..."));
		if (line.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse max bomb.\n                Loading default maps..."));
		return (std::atoi(line.substr(line.find(": ") + 2).c_str()));
	}

	float ParserYAML::_parseExplosionRadius(std::string &line)
	{
		//if (line.find(": ") == std::string::npos || !_isFloat(line.substr(line.find(": ") + 2)))
		//	throw (ParserError("Error with saved map: Couldn't parse explosion radius.\n                Loading default maps..."));
		if (line.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse explosion radius.\n                Loading default maps..."));
		return (std::atof(line.substr(line.find(": ") + 2).c_str()));
	}

	float ParserYAML::_parseSpeed(std::string &line)
	{
		//if (line.find(": ") == std::string::npos || !_isFloat(line.substr(line.find(": ") + 2)))
		//	throw (ParserError("Error with saved map: Couldn't parse speed.\n                Loading default maps..."));
		if (line.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse speed.\n                Loading default maps..."));
		return (std::atof(line.substr(line.find(": ") + 2).c_str()));
	}

	MapGenerator::BlockType ParserYAML::_parseBlockType(std::string &blockType)
	{
		//if (blockType.find(": ") == std::string::npos || !_isInteger(blockType.substr(blockType.find(": ") + 2)))
		//	throw (ParserError("Error with saved map: Couldn't parse block type.\n                Loading default maps..."));
		if (blockType.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse block type.\n                Loading default maps..."));
		return (static_cast<MapGenerator::BlockType>(std::atoi(blockType.substr(blockType.find(": ") + 2).c_str())));
	}

	Bonus::BonusType ParserYAML::_parseBonusType(std::string &bonusType)
	{
		//if (bonusType.find(": ") == std::string::npos || !_isInteger(bonusType.substr(bonusType.find(": ") + 2)))
		//	throw (ParserError("Error with saved map: Couldn't parse bonus type.\n                Loading default maps..."));
		if (bonusType.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse bonus type.\n                Loading default maps..."));
		return (static_cast<Bonus::BonusType>(std::atoi(bonusType.substr(bonusType.find(": ") + 2).c_str())));
	}

	std::string ParserYAML::parseHeader(const std::string &line)
	{
		std::stringstream ss(line);
		std::string headerName;
		std::string garbage;

		ss >> headerName >> garbage;


		if (!garbage.empty()) {
			throw ParserError("ill formed header, line: " + Utils::trimCopy(line));
		}
		if (headerName.back() != ':') {
			throw ParserError("header not ended with ':' , line: " + Utils::trimCopy(line));
		}
		headerName.pop_back();
		return headerName;
	}

	std::pair<std::string, std::string> ParserYAML::parseProperty(const std::string &line)
	{
		std::stringstream ss(line);
		std::string propertyName;
		std::string propertyValue;
		std::string garbage;

		ss >> propertyName >> propertyValue >> garbage;

		if (!garbage.empty()) {
			throw ParserError("ill formed property, line: " + Utils::trimCopy(line));
		}
		if (propertyName.back() != ':') {
			throw ParserError("property name not ended with ':' , line: " + Utils::trimCopy(line));
		}
		propertyName.pop_back();
		return std::make_pair(propertyName, propertyValue);
	}

	bool ParserYAML::isHeader(const std::string &line)
	{
		return line.back() == ':';
	}

	Node ParserYAML::parseFile(const std::string &path)
	{
		std::ifstream file(path);

		return parseNode(file, "root");
	}

	Node ParserYAML::parseNode(std::ifstream &file, const std::string &nodeName, int indentLevel)
	{
		std::string line;
		Node node(nodeName);

		while(std::getline(file, line)) {
			if (line.empty())
				continue;
			float lineIndentLevel = getIndent(line);
			if (lineIndentLevel != static_cast<int>(lineIndentLevel)) {
				throw ParserError("Yaml only support 2 spaces as indent");
			}
			if (lineIndentLevel > indentLevel) {
				throw ParserError("indent issue");
			}
			if (lineIndentLevel < indentLevel) {
				file.seekg(static_cast<size_t>(file.tellg()) - (line.length() + 1));
				return node;
			}
			if (isHeader(line)) {
				node.addChildNode(parseNode(file, parseHeader(line), indentLevel + 1));
			} else {
				node.setProperty(parseProperty(line));
			}
		}
		return node;
	}

	float ParserYAML::getIndent(const std::string &line)
	{
		int nb = 0;
		for (const auto &c : line) {
			if (!std::isspace(c))
				break;
			if (c != ' ')
				throw ParserError("Yaml only support 2 spaces as indent");
			nb++;
		}
		return static_cast<float>(nb / 2.);
	}
}