/*=================================================================================================   Copyright (c) 2016 Joel de Guzman   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.   http://creativecommons.org/licenses/by-sa/4.0/=================================================================================================*/#if !defined(PHOTON_GUI_LIB_CANVAS_MAY_3_2016)#define PHOTON_GUI_LIB_CANVAS_MAY_3_2016#include <photon/support/color.hpp>#include <photon/support/rect.hpp>#include <vector>namespace photon{   class view;   struct canvas_impl;   class canvas   {   public:      /////////////////////////////////////////////////////////////////////////////////////////////      // Path building      void              begin_path();      void              close_path();      void              fill();      void              stroke();      void              clip();      void              move_to(point p);      void              line_to(point p);      void	            arc_to(point p1, point p2, float radius);      void	            arc(                           point p, float radius,                           float start_angle, float end_angle,                           bool ccw = false                        );      void              rect(struct rect r);      void              round_rect(struct rect r, float radius);      /////////////////////////////////////////////////////////////////////////////////////////////      // Styles      void              fill_style(color c);      void              stroke_style(color c);      void              line_width(float w);      void              shadow_style(point offs, float blur, color c = colors::black);      /////////////////////////////////////////////////////////////////////////////////////////////      // Gradients      struct linear_gradient      {         point start;         point end;      };      struct radial_gradient      {         point start;         float start_radius;         point end;         float end_radius;      };      struct color_stop      {         float offset;         color color;      };      void              fill_style(linear_gradient gr);      void              fill_style(radial_gradient gr);      void              color_space(std::vector<color_stop> const& space);      /////////////////////////////////////////////////////////////////////////////////////////////      // Rectangles      void              fill_rect(struct rect r);      void              fill_round_rect(struct rect r, float radius);      void              stroke_rect(struct rect r);      void              stroke_round_rect(struct rect r, float radius);      /////////////////////////////////////////////////////////////////////////////////////////////      // Font      enum font_style      {         normal   = 0,         bold     = 1,         italic   = 2      };      void              font(char const* family, float size = 16, int = normal);      /////////////////////////////////////////////////////////////////////////////////////////////      // Text      enum text_alignment      {         // Horizontal align         left     = 0,        // Default, align text horizontally to left.         center   = 1,	      // Align text horizontally to center.         right    = 2,	      // Align text horizontally to right.         // Vertical align         baseline = 4,        // Default, align text vertically to baseline.         top      = 8,        // Align text vertically to top.         middle	= 12,       // Align text vertically to middle.         bottom	= 16        // Align text vertically to bottom.      };      struct text_metrics      {         float       ascent;         float       descent;         float       leading;         float       width;         struct rect bounds;      };      void              fill_text(point p, char const* f, char const* l = 0);      void              stroke_text(point p, char const* f, char const* l = 0);      text_metrics      measure_text(char const* f, char const* l = 0);      void              text_align(int align);      /////////////////////////////////////////////////////////////////////////////////////////////      // Image      class image      {      public:         class rep;                        image(char const* filename);                        ~image();         photon::size   size() const;      private:         friend class canvas;                        image(image const&) = delete;                        image& operator=(image const&) = delete;         rep*           _rep;      };      void              draw(image const& img, photon::rect src, photon::rect dest);      /////////////////////////////////////////////////////////////////////////////////////////////      // States      class state      {      public:                        state(canvas& cnv_) : cnv(&cnv_)    { cnv->save(); }                        state(state&& rhs) : cnv(rhs.cnv)   { rhs.cnv = 0; }                        ~state()                            { if (cnv) cnv->restore(); }         state&         operator=(state&& rhs)         {            cnv = rhs.cnv;            rhs.cnv = 0;            return *this;         }      private:         state(state const&) = delete;         state& operator=(state const&) = delete;         canvas* cnv;      };      state             new_state()   { return state{ *this }; }      void              save();      void              restore();   private:                        canvas(canvas_impl* impl, view& view_);      friend class view;      canvas_impl*      _impl;      view&             _view;   };}#endif