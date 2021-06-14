//
// Created by Louis Auzuret on 10/06/21
//

#include "LuaGate.hpp"

namespace LuaG
{
	State::State()
	: _state(luaL_newstate())
	{
		luaL_openlibs(_state);
	}

	State::~State()
	{
		lua_close(_state);
	}

	lua_State *State::getState(void)
	{
		return _state;
	}

	void State::dofile(std::string filepath)
	{
        luaL_dofile(_state, filepath.c_str());
	}

	void State::dostring(std::string str)
	{
        luaL_dostring(_state, str.c_str());
	}

	float State::getReturnNumber(void)
	{
		float res = 0;

		if (lua_isnil(_state, -1))
			return res;
		if (!lua_isnumber(_state, -1))
			return res;
		res = lua_tonumber(_state, -1);
		lua_pop(_state, 1);

		return res;
	}

	bool State::getReturnBool(void)
	{
		bool res = false;

		if (lua_isnil(_state, -1))
			return res;
		if (!lua_isboolean(_state, -1))
			return res;
		res = lua_toboolean(_state, -1);
		lua_pop(_state, 1);
		return res;
	}

	bool State::callFunction(std::string , int nbParams, int nbReturns)
	{
		lua_pcall(_state, nbParams, nbReturns, 0);
		return true;
	}

	void State::setTable(void)
	{
		lua_settable(_state, -3);
	}

	void State::push(float val)
	{
		lua_pushnumber(_state, val);
	}

	void State::push(std::string str)
	{
		lua_pushstring(_state, str.c_str());
	}

	void State::newTable(void)
	{
		lua_newtable(_state);
	}
}
