//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_file_recorder_HPP
#define UMPIRE_file_recorder_HPP

#include <fstream>

namespace umpire {
namespace event {

class event;

class file_recorder {
  public:
  
  file_recorder(const std::string& filename);

  void record(event e);

  private:
  std::ofstream m_fstream;
};

}
}
#endif // UMPIRE_file_recorder_HPP
