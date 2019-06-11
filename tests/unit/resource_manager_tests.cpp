//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory
//
// Created by David Beckingsale, david@llnl.gov
// LLNL-CODE-747640
//
// All rights reserved.
//
// This file is part of Umpire.
//
// For details, see https://github.com/LLNL/Umpire
// Please also see the LICENSE file for MIT license.
//////////////////////////////////////////////////////////////////////////////
#include "gtest/gtest.h"

#include "umpire/ResourceManager.hpp"

TEST(ResourceManager, Constructor) {
  umpire::ResourceManager& rm = umpire::ResourceManager::getInstance();

  (void) rm;
  SUCCEED();
}

TEST(ResourceManager, findAllocationRecord)
{
  auto& rm = umpire::ResourceManager::getInstance();

  auto alloc = rm.getAllocator("HOST");

  const size_t size = 1024 * 1024;
  const size_t offset = 1024;

  char* ptr = static_cast<char*>(alloc.allocate(size));
  const umpire::util::AllocationRecord* rec_begin = rm.findAllocationRecord(ptr);
  const umpire::util::AllocationRecord* rec_middle = rm.findAllocationRecord(ptr + offset);
  const umpire::util::AllocationRecord* rec_end = rm.findAllocationRecord(ptr + (size-1));

  ASSERT_EQ(ptr, rec_begin->m_ptr);
  ASSERT_EQ(ptr, rec_middle->m_ptr);
  ASSERT_EQ(ptr, rec_end->m_ptr);

  ASSERT_THROW(rm.findAllocationRecord(ptr + size), umpire::util::Exception);

  ASSERT_THROW(rm.findAllocationRecord(ptr + size+1), umpire::util::Exception);

  alloc.deallocate(ptr);

  ASSERT_THROW(rm.findAllocationRecord(nullptr), umpire::util::Exception);
}

TEST(ResourceManager, getAllocatorByName)
{

  auto& rm = umpire::ResourceManager::getInstance();

  EXPECT_NO_THROW({
    auto alloc = rm.getAllocator("HOST");
    UMPIRE_USE_VAR(alloc);
  });

  ASSERT_THROW(
      rm.getAllocator("BANANA"),
      umpire::util::Exception);
}

TEST(ResourceManager, getAllocatorById)
{

  auto& rm = umpire::ResourceManager::getInstance();

  EXPECT_NO_THROW({
    auto alloc = rm.getAllocator(0);
    UMPIRE_USE_VAR(alloc);
  });

  ASSERT_THROW(
      rm.getAllocator(-4),
      umpire::util::Exception);
}
