/*
 * Copyright (c) 2016 Luke San Antonio Bialecki
 * All rights reserved.
 *
 * Released under the BSD 2-clause license. See LICENSE in the top-level source
 * tree for the entire license text.
 */
#include "translate.h"
namespace al
{
  Lang language_;

  void set_lang(Lang const& lang) noexcept
  {
    language_ = lang;
  }
  Lang get_lang() noexcept
  {
    return language_;
  }
}
