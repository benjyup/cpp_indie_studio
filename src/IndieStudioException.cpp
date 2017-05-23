//
// Created by vincent on 23/05/17.
//

#include "IndieStudioException.hpp"

is::IndieStudioException::IndieStudioException(const std::string &msg) noexcept : _msg(msg)
{

}

is::IndieStudioException::~IndieStudioException() noexcept
{

}

const char *is::IndieStudioException::what() const noexcept
{
  return (_msg.c_str());
}
