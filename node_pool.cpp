/*
 * Copyright 2019-2021 Hans-Kristian Arntzen for Valve Corporation
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

#include "node_pool.hpp"
#include "node.hpp"
#include <utility>

namespace dxil_spv
{
CFGNodePool::CFGNodePool()
{
}

CFGNodePool::~CFGNodePool()
{
}

CFGNode *CFGNodePool::create_node()
{
	auto node = std::unique_ptr<CFGNode>(new CFGNode(*this));
	auto *ret = node.get();
	nodes.push_back(std::move(node));
	return ret;
}

} // namespace dxil_spv
