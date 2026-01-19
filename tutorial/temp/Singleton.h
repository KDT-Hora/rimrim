#pragma once

//	継承先でフレンド指定する
//	汎用シングルトンクラス

template <typename T>
class Singleton
{
protected:

	Singleton()noexcept
		= default;
	~Singleton()noexcept
		= default;

public:

	static T& Instance()
	{
		static T instance;
		return instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

};