#pragma once

#include <memory>

namespace nexc {

	template<typename T> using Ref = std::shared_ptr<T>;
	template<typename T> using WRef = std::weak_ptr<T>;
	template<typename T> using URef = std::unique_ptr<T>;

	template<typename T, typename R> inline Ref<T> RefCast(const Ref<R>& ref) { return std::move(std::static_pointer_cast<T>(ref)); };

	template<typename T, typename ...R > inline Ref<T> New(R ... args) {
		auto obj = std::make_shared<T>(args...);
		return std::move(obj);
	};

}
