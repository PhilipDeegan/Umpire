//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_json_file_store_HPP
#define UMPIRE_json_file_store_HPP

#include "umpire/event/event_store.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace umpire {
namespace event {

class event;

class json_file_store : public event_store {
  public:
  
    json_file_store(const std::string& filename, bool read_only = false);

    virtual void insert(event e);

    virtual std::vector<event> get_events();

  private:
    std::fstream m_fstream;
};

}
}
#endif // UMPIRE_json_file_store_HPP
