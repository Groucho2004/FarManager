﻿#ifndef PLATFORM_CHRONO_HPP_4942BDE7_47FB_49F8_B8F6_EE0AFF4EC61D
#define PLATFORM_CHRONO_HPP_4942BDE7_47FB_49F8_B8F6_EE0AFF4EC61D
#pragma once

/*
platform.chrono.hpp

*/
/*
Copyright © 2017 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Internal:

// Platform:

// Common:

// External:

//----------------------------------------------------------------------------

namespace os::chrono
{
	// TrivialClock with fixed period (100 ns) and epoch (1 Jan 1601)
	class nt_clock
	{
	public:
		using rep = unsigned long long;
		using period = std::ratio_multiply<std::ratio<100, 1>, std::nano>;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<nt_clock>;

		static inline constexpr bool is_steady = false;

		[[nodiscard]]
		static time_point now() noexcept;

		[[nodiscard]]
		static time_t to_time_t(const time_point& Time) noexcept;

		[[nodiscard]]
		static time_point from_time_t(time_t Time) noexcept;

		[[nodiscard]]
		static FILETIME to_filetime(const time_point& Time) noexcept;

		[[nodiscard]]
		static time_point from_filetime(FILETIME Time) noexcept;

		[[nodiscard]]
		static time_point from_int64(int64_t Time) noexcept;

		[[nodiscard]]
		static int64_t to_int64(const time_point& Time) noexcept;
	};

	using duration = nt_clock::duration;
	using time_point = nt_clock::time_point;

	// Q: WTF is this, it's in the standard!
	// A: MSVC implemented it in terms of sleep_until, which is mental
	void sleep_for(std::chrono::milliseconds Duration);

	[[nodiscard]]
	bool get_process_creation_time(HANDLE Process, time_point& CreationTime);

	[[nodiscard]]
	string format_time();

	namespace literals
	{
		[[nodiscard]]
		constexpr duration(operator"" _tick)(unsigned long long Value) noexcept
		{
			return duration(Value);
		}
	}
}

#endif // PLATFORM_CHRONO_HPP_4942BDE7_47FB_49F8_B8F6_EE0AFF4EC61D
