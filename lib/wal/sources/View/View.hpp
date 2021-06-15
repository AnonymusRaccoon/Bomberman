//
// Created by Zoe Roux on 2021-06-03.
//


#pragma once

#include <list>
#include <tuple>
#include <typeindex>
#include <functional>
#include <utility>
#include <optional>
#include "Entity/Entity.hpp"

namespace WAL
{
	template<typename ...Components>
	class ViewEntity
	{
	private:
		std::tuple<std::reference_wrapper<Entity>, std::reference_wrapper<Components>...> &_value;
	public:
		explicit ViewEntity(std::tuple<std::reference_wrapper<Entity>, std::reference_wrapper<Components>...> &value)
			: _value(value)
		{}

		Entity *operator->()
		{
			return &(std::get<0>(this->_value).get());
		}

		Entity &operator*()
		{
			return std::get<0>(this->_value);
		}

		operator Entity &()
		{
			return std::get<0>(this->_value);
		}

		template<typename T>
		T &get()
		{
			return std::get<std::reference_wrapper<T>>(this->_value);
		}

		template<std::size_t I>
		auto &get()
		{
			return std::get<I>(this->_value);
		}
	};

	template<typename It, typename ...Components>
	class ViewIterator
	{
	private:
		It _it;
		std::optional<ViewEntity<Components...>> _entity;

	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type        = ViewEntity<Components...>;
		using pointer           = value_type *;
		using reference         = value_type &;

		reference operator*()
		{
			if (!this->_entity)
				this->_entity.emplace(*this->_it);
			return *this->_entity;
		}

		pointer operator->()
		{
			if (!this->_entity)
				this->_entity =(*this->_it);
			return &this->_entity;
		}

		ViewIterator &operator++()
		{
			this->_it++;
			this->_entity = std::nullopt;
			return *this;
		}

		ViewIterator operator++(int)
		{
			ViewIterator copy = *this;
			this->_it++;
			this->_entity = std::nullopt;
			return *this;
		}

		bool operator==(const ViewIterator &other) const
		{
			return this->_it == other._it;
		}

		bool operator!=(const ViewIterator &other) const
		{
			return !this->operator==(other);
		}

		explicit ViewIterator(It current)
			: _it(current),
			_entity(std::nullopt)
		{}
	};

	//! @brief A basic view used to manipulate view without knowing their type at compile time.
	class IView
	{
	public:
		//! @brief The list of types that every entity of the view has.
		virtual const std::vector<std::type_index> &getTypes() const = 0;

		virtual void emplace_back(Entity &) = 0;

		virtual void erase(const Entity &) = 0;

		//! @brief A default destructor
		virtual ~IView() = default;
	};

	//! @brief A view allowing one to easily access entities containing a set list of component.
	//!        A view is always updated and only references to entities are kept.
	template<typename ...Components>
	class View : public IView
	{
	private:
		using entity_type = std::tuple<std::reference_wrapper<Entity>, std::reference_wrapper<Components>...>;

		//! @brief The list of entities in the view.
		std::vector<entity_type> _entities = {};
		//! @brief The list of types that every entity of the view has.
		std::vector<std::type_index> _types = {};
	public:
		using iterator = ViewIterator<typename std::vector<entity_type>::iterator, Components...>;

		iterator begin()
		{
			return iterator(this->_entities.begin());
		}

		iterator end()
		{
			return iterator(this->_entities.end());
		}

		std::size_t size() const
		{
			return this->_entities.size();
		}

		ViewEntity<Components...> front()
		{
			return *iterator(this->_entities.begin());
		}

		ViewEntity<Components...> back()
		{
			return *iterator(--this->_entities.end());
		}

		const std::vector<std::type_index> &getTypes() const override
		{
			return this->_types;
		}

		void emplace_back(Entity &entity) override
		{
			auto tuple = std::make_tuple<Components *...>(entity.tryGetComponent<Components>()...);
			if (std::apply([](const auto *...component) {return ((component == nullptr) || ...);}, tuple))
				return;
			std::apply([&](auto *...component) {
				this->_entities.emplace_back(entity, *component...);
			}, tuple);
		}

		void erase(const Entity &entity) override
		{
			this->_entities.erase(std::remove_if(this->_entities.begin(), this->_entities.end(), [&entity](const auto &ref) {
				return std::get<0>(ref).get().getUid() == entity.getUid();
			}), this->_entities.end());
		}

		//! @brief Construct a view from a list of entities.
		//!        Those entities are never copied but references to them are kept internally.
		explicit View(std::list<Entity> &scene)
		{
			this->_types = {typeid(Components)...};
			for (auto &entity : scene)
				this->emplace_back(entity);
		}

		//! @brief Copying a view is not possible since a view must be managed by a scene.
		View(const View &) = delete;
		//! @brief A default destructor
		~View() override = default;
		//! @brief A view is not assignable.
		View &operator=(const View &) = delete;
	};
}

namespace std
{
	template<typename ...Components>
	struct tuple_size<::WAL::ViewEntity<Components...>>
		: public std::integral_constant<std::size_t, 1 + sizeof...(Components)>
	{};

	template<typename ...Components>
	struct tuple_element<0, ::WAL::ViewEntity<Components...>>
	{
		using type = WAL::Entity &;
	};

	template<std::size_t N, typename ...Components>
	struct tuple_element<N, ::WAL::ViewEntity<Components...>>
	{
		using type = typename std::tuple_element<N - 1, std::tuple<Components...>>::type;
	};
}