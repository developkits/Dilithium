/**
 * @file ErrorHandling.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of Dilithium
 * For the latest info, see https://github.com/gongminmin/Dilithium
 *
 * @section LICENSE
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Minmin Gong. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _DILITHIUM_ERROR_HANDLING_HPP
#define _DILITHIUM_ERROR_HANDLING_HPP

#pragma once

#include <Dilithium/Compiler.hpp>
#include <Dilithium/CXX17/string_view.hpp>
#include <system_error>
#include <exception>

namespace Dilithium
{
	DILITHIUM_ATTRIBUTE_NORETURN void ReportFatalError(char const * reason);
	DILITHIUM_ATTRIBUTE_NORETURN void ReportFatalError(std::string const & reason);
	DILITHIUM_ATTRIBUTE_NORETURN void ReportFatalError(std::string_view reason);

#if defined(DILITHIUM_DEBUG) || !defined(DILITHIUM_BUILTIN_UNREACHABLE)
	DILITHIUM_ATTRIBUTE_NORETURN void UnreachableInternal(char const * msg = nullptr, char const * file = nullptr, uint32_t line = 0);

	#define DILITHIUM_UNREACHABLE(msg) ::Dilithium::UnreachableInternal(msg, __FILE__, __LINE__)
#else
	#define DILITHIUM_UNREACHABLE(msg) DILITHIUM_BUILTIN_UNREACHABLE
#endif

	#define DILITHIUM_NOT_IMPLEMENTED DILITHIUM_UNREACHABLE("Not implemented")

	inline void TERROR(char const * msg = nullptr)
	{
		throw std::runtime_error(msg);
	}

	inline void TEC(std::error_code ec, char const * msg = nullptr)
	{
		throw std::system_error(ec, msg);
	}

	inline void TIFEC(std::error_code ec, char const * msg = nullptr)
	{
		if (ec)
		{
			TEC(ec, msg);
		}
	}

	inline void TIFBOOL(bool x, char const * msg = nullptr)
	{
		if (!x)
		{
			TERROR(msg);
		}
	}
}

#endif		// _DILITHIUM_ERROR_HANDLING_HPP
