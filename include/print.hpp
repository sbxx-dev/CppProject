#pragma once

#ifndef COOL_PRINT_HPP
#define COOL_PRINT_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <locale>

// Одна общая переменная на всю программу (C++17 inline-переменные)
inline std::ostream* cool_out = &std::cout;
inline std::istream* cool_in  = &std::cin;

namespace cool
{
	// OUTPUT

	inline void setCyrillic()
	{
		setlocale(LC_ALL, "Russian");
	}

	inline void setPrintOut(std::ostream& os)
	{
		cool_out = &os;
	}

	inline std::ostream* getPrintOutPtr()
	{
		return cool_out;
	}

	inline void printFlush()
	{
		*cool_out << std::flush;
	}

	inline void print()
	{
		*cool_out << ' ';
	}

	template <typename Arg>
	inline void print(const Arg& arg)
	{
		*cool_out << std::fixed << std::setprecision(2) << arg;
	}

	template <typename Arg, typename... Args>
	void print(const Arg& arg, const Args&... args)
	{
		print(arg);
		print(args...);
	}
	////

	inline void println()
	{
		*cool_out << '\n';
	}

	template <typename Arg>
	inline void println(const Arg& arg)
	{
		*cool_out << std::fixed << std::setprecision(2) << arg << '\n';
	}

	template <typename... Args>
	void println(const Args&... args)
	{
		print(args...);
		println();
	}
	///

	inline void print0() { }

	template <typename Arg>
	inline void print0(const Arg& arg)
	{
		*cool_out << std::fixed << std::setprecision(2) << arg;
	}

	template <typename Arg, typename... Args>
	void print0(const Arg& arg, const Args&... args)
	{
		print0(arg);
		print0(args...);
	}

	// INPUT

	inline void setInputIn(std::istream& is)
	{
		cool_in = &is;
	}

	inline std::istream* getInputInPtr()
	{
		return cool_in;
	}

	template <typename Arg>
	void input(Arg& value)
	{
		*cool_in >> value;
	}

	template <typename T, typename... Args>
	void input(T& first, Args&... rest)
	{
		input(first);
		input(rest...);
	}

	inline void inputln(std::string& line)
	{
		std::getline(*cool_in, line);
	}

	// Combo-bonus function

	template <typename T>
	void prompt(const std::string& msg, T& value)
	{
		cool::print(msg);
		cool::input(value);
	}

	// Базовый случай (один аргумент)
	template <typename T>
	T sum(const T& arg)
	{
		return arg;
	}

	// Рекурсивный случай (два или более аргументов)
	template <typename T, typename... Args>
	auto sum(const T& first, const Args&... rest)
	{
		return first + sum(rest...);
	}

	template <typename T>
	T min(const T& arg) { return arg; }

	template <typename T, typename... Args>
	auto min(const T& first, const Args&... rest)
	{
		auto rest_min = min(rest...);
		return (first < rest_min) ? first : rest_min;
	}

	template <typename T>
	T max(const T& arg) { return arg; }

	template <typename T, typename... Args>
	auto max(const T& first, const Args&... rest)
	{
		auto rest_max = max(rest...);
		return (first > rest_max) ? first : rest_max;
	}

#define COOL_INFO(x) (std::string(#x) + " = " + std::to_string(x))
}
#endif
