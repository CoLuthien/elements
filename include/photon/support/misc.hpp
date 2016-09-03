/*=================================================================================================   Copyright (c) 2016 Joel de Guzman   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.   http://creativecommons.org/licenses/by-sa/4.0/=================================================================================================*/#if !defined(PHOTON_GUI_LIB_MISC_APRIL_10_2016)#define PHOTON_GUI_LIB_MISC_APRIL_10_2016#include <photon/support/rect.hpp>#include <photon/support/point.hpp>#include <cfloat>#include <cstdint>#include <cassert>#include <chrono>namespace photon{   ////////////////////////////////////////////////////////////////////////////////////////////////   // Time   ////////////////////////////////////////////////////////////////////////////////////////////////   using duration       = std::chrono::duration<double>;   using microseconds   = std::chrono::duration<double, std::micro>;   using milliseconds   = std::chrono::duration<double, std::milli>;   using seconds        = std::chrono::duration<double>;   using minutes        = std::chrono::duration<double, std::ratio<60>>;   using hours          = std::chrono::duration<double, std::ratio<60*60>>;   using time_point     = std::chrono::time_point<std::chrono::steady_clock, duration>;   inline time_point now()   {      return std::chrono::high_resolution_clock::now();   }   ////////////////////////////////////////////////////////////////////////////////////////////////   // Limits   ////////////////////////////////////////////////////////////////////////////////////////////////   constexpr float   full_extent    = 1E6;   constexpr rect    full_limits    = { 0.0, 0.0, full_extent, full_extent };   constexpr rect    empty_limits   = { 0.0, 0.0, 0.0, 0.0 };   constexpr rect    empty_rect     = { 0.0, 0.0, 0.0, 0.0 };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Mouse Button   ////////////////////////////////////////////////////////////////////////////////////////////////   struct mouse_button   {      enum what      {         left,         middle,         right      };      bool  is_pressed;      int   num_clicks;      what  state;      point pos;   };      ////////////////////////////////////////////////////////////////////////////////////////////////   // Cursor tracking   ////////////////////////////////////////////////////////////////////////////////////////////////   enum class cursor_tracking   {      entering,      hovering,      leaving   };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Text info   ////////////////////////////////////////////////////////////////////////////////////////////////   struct text_info   {      uint32_t    codepoint;      int         modifiers;   };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Focus request   ////////////////////////////////////////////////////////////////////////////////////////////////   enum class focus_request   {      wants_focus,      begin_focus,      end_focus   };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Utilities   ////////////////////////////////////////////////////////////////////////////////////////////////   template <typename T, typename U>   inline void clamp_max(T& val, U const& max)   {      if (val > max)         val = max;   }   template <typename T, typename U>   inline void clamp_min(T& val, U const& min)   {      if (val < min)         val = min;   }   template <typename T, typename U, typename V>   inline void clamp(T& val, U const& min, V const& max)   {      assert(min <= max);      clamp_min(val, min);      clamp_max(val, max);   }   template <typename T, typename U, typename V>   inline bool within(T const& val, U const& min, V const& max)   {      return (val >= min) && (val <= max);   }   inline char const* codepoint_to_UTF8(int cp, char str[8])   {      int n = 0;      if (cp < 0x80) n = 1;      else if (cp < 0x800) n = 2;      else if (cp < 0x10000) n = 3;      else if (cp < 0x200000) n = 4;      else if (cp < 0x4000000) n = 5;      else if (cp <= 0x7fffffff) n = 6;      str[n] = '\0';      switch (n)      {         case 6: str[5] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x4000000;         case 5: str[4] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x200000;         case 4: str[3] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x10000;         case 3: str[2] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x800;         case 2: str[1] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0xc0;         case 1: str[0] = cp;      }      return str;   }   ////////////////////////////////////////////////////////////////////////////////////////////////   // Generic contextual setter   ////////////////////////////////////////////////////////////////////////////////////////////////   template <typename T>   struct setter   {      setter(T& ref, T const& new_val)       : _ref(ref)       , _save(ref)      {         _ref = new_val;      }      ~setter()      {         _ref = _save;      }      T& _ref;      T  _save;   };   template <typename T>   inline setter<T> set(T& ref, T const& new_val)   {      return { ref, new_val };   };}#endif