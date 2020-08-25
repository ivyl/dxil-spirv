/*
 * Copyright 2019-2020 Hans-Kristian Arntzen for Valve Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>

namespace dxil_spv
{
extern unsigned alloc_count;
template <typename T>
class ThreadLocalAllocator
{
public:
	using value_type = T;

	ThreadLocalAllocator() noexcept = default;
	template <typename U>
	ThreadLocalAllocator(const ThreadLocalAllocator<U> &) noexcept {}

	value_type *allocate(std::size_t n)
	{
		alloc_count++;
		fprintf(stderr, "Count = %u\n", alloc_count);
		return static_cast<T *>(::malloc(sizeof(T) * n));
	}

	void deallocate(value_type *p, std::size_t)
	{
		::free(p);
	}

	using is_always_equal = std::true_type;
};

template <typename A, typename B>
static inline bool operator==(const ThreadLocalAllocator<A> &, const ThreadLocalAllocator<B> &)
{
	return true;
}

template <typename A, typename B>
static inline bool operator!=(const ThreadLocalAllocator<A> &, const ThreadLocalAllocator<B> &)
{
	return false;
}

template <typename T>
using Vector = std::vector<T, ThreadLocalAllocator<T>>;

template <typename T>
using UnorderedSet = std::unordered_set<T, std::hash<T>, std::equal_to<T>, ThreadLocalAllocator<T>>;

template <typename Key, typename Value, typename Hash = std::hash<Key>>
using UnorderedMap = std::unordered_map<Key, Value, std::hash<Key>, std::equal_to<Key>, ThreadLocalAllocator<std::pair<const Key, Value>>>;

void begin_thread_allocator_context();
void end_thread_allocator_context();
void reset_thread_allocator_context();
}
