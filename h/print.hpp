#pragma once

#ifndef COOL_PRINT_HPP
#define COOL_PRINT_HPP

#include <string>
#include <iostream>
#include <iomanip>

namespace
{
	std::ostream* out = &std::cout;
	std::istream* in = &std::cin;
}

namespace cool
{
	// OUTPUT

	inline void setCyrillic()
	{
		setlocale(LC_ALL, "Russian");
	}

	void setPrintOut(std::ostream& os)
	{
		::out = &os;
	}

	std::ostream* getPrintOutPtr()
	{
		return ::out;
	}
	
	inline void printFlush()
	{
		*::out << std::flush;
	}

	inline void print() 
	{ 
		*::out << ' ';
	}
	template <typename Arg>
	inline void print(const Arg& arg)
	{
		*::out <<  std::fixed << std::setprecision(2) << arg << ' ';
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
		*::out << '\n';
	}
	template <typename Arg>
	inline void println(const Arg& arg)
	{
		*::out << std::fixed << std::setprecision(2) << arg << '\n';
	}

	template <typename... Args>
	void println(const Args&... args)
	{
		print(args...);
		println();
	}
	///
	void print0() { }

	template <typename Arg>
	inline void print0(const Arg& arg)
	{
		*::out << std::fixed << std::setprecision(2) << arg;
	}

	template <typename Arg, typename... Args>
	void print0(const Arg& arg, const Args&... args)
	{
		print0(arg);
		print0(args...);
	}

	// INPUT

	void setInputIn(std::istream& is){
		::in = &is;
	}

	std::istream* getInputInPtr(){
		return ::in;
	}

	template <typename Arg>
	void input(Arg& value){
		*::in >> value;
	}

	template <typename T, typename... Args>
	void input(T& first, Args&... rest){
		input(first);
		input(rest...);
	}

	inline void inputln(std::string& line){
		std::getline(*::in, line);
	}

	// Combo-bonus function

	template <typename T>
	void prompt(const std::string& msg, T& value){
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
	T min(const T& arg) {return arg;}

	template <typename T, typename... Args>
	auto min(const T& first, const Args&... rest){
		auto rest_min = min(rest...);
		return (first < rest_min) ? first : rest_min;
	}

	template <typename T>
	T max(const T& arg) {return arg;}

	template <typename T, typename... Args>
	auto max(const T& first, const Args&... rest){
		auto rest_max = max(rest...);
		return (first > rest_max) ? first : rest_max;
	}

#define COOL_INFO(x) (std::string(#x) + " = " + std::to_string(x))
}

#endif