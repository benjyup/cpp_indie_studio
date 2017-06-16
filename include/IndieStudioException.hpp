//
// Created by vincent on 23/05/17.
//

#pragma once

#include <exception>
#include <string>

namespace is
{
  class IndieStudioException : public std::exception
  {
   public:
    IndieStudioException(const std::string &msg = "") noexcept;
    virtual ~IndieStudioException() noexcept ;
    virtual const char *what() const noexcept ;

   private:
    std::string			_msg;
  };
}
