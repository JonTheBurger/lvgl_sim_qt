// Local
#include "LvglRenderer.hpp"

static void lvglFlushCallback(lv_disp_drv_t* display_driver, const lv_area_t* area, lv_color_t* colors);
static void loadColorTable(QImage& image);

LvglRenderer::LvglRenderer()
    : display_frame1_{}
    , display_frame2_{}
    , current_frame_{}
    , display_driver_{}
    , image_(reinterpret_cast<uint8_t*>(current_frame_),
             sizeof(*current_frame_) / sizeof(**current_frame_),
             sizeof(current_frame_) / sizeof(*current_frame_),
             Image_Format)
{
  loadColorTable(image_);
  lv_init();
  lv_disp_buf_init(&display_buffer_,
                   display_frame1_,
                   display_frame2_,
                   sizeof(display_frame1_) / sizeof(*display_frame1_));
  lv_disp_drv_init(&display_driver_);
  display_driver_.buffer    = &display_buffer_;
  display_driver_.flush_cb  = &lvglFlushCallback;
  display_driver_.user_data = this;
  lv_disp_drv_register(&display_driver_);
}

void LvglRenderer::flush(const lv_disp_drv_t* const, const lv_area_t* const area, const lv_color_t* colors) noexcept
{
  const auto x1    = area->x1;
  const auto x2    = area->x2;
  const auto y1    = area->y1;
  const auto y2    = area->y2;
  const auto width = x2 - x1;

  for (auto y = y1; y <= y2; ++y)
  {
    memcpy(&current_frame_[y][x1], colors, sizeof(*colors) * width);
    colors += (width + 1);
  }
}

QPixmap LvglRenderer::pixmap() const
{
  return QPixmap::fromImage(image_);
}

static void lvglFlushCallback(lv_disp_drv_t* display_driver, const lv_area_t* area, lv_color_t* colors)
{
  auto* renderer = static_cast<LvglRenderer*>(display_driver->user_data);
  renderer->flush(display_driver, area, colors);
  lv_disp_flush_ready(display_driver);
}

static void loadColorTable(QImage& image)
{
#if (LV_COLOR_DEPTH == 8)
  static QVector<QRgb> Color_Table;
  Color_Table.reserve(256);
  for (auto i = 0; i < 256; ++i)
  {
    lv_color8_t truncated{};
    truncated.full = i;
    // Shift bitfields by remaining bits in a uint8_t to give their representation maximum impact
    Color_Table.push_back(qRgb(truncated.ch.red << 5, truncated.ch.green << 5, truncated.ch.blue << 6));
  }
  Color_Table[255] = ~0;
  image.setColorTable(Color_Table);
#elif (LV_COLOR_DEPTH == 1)
  static QVector<QRgb> Color_Table(256, 0);
  Color_Table[LV_COLOR_WHITE.full] = ~0;
  image.setColorTable(Color_Table);
#else
  static_cast<void>(image);
#endif
}
