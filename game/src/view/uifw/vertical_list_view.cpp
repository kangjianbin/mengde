#include "vertical_list_view.h"

VerticalListView::VerticalListView(const Rect& frame) : CompositeView(frame), margin_(0) {
  SetPadding(0);

  // Initial height must be zero, the height value from frame is ignored
  SetSize({GetFrameSize().x , 0});
}

void VerticalListView::AddElement(View* e) {
  Vec2D frame_size   = GetFrameSize();
  Vec2D element_size = e->GetFrameSize();

  // Restriction : element's height must be equal to frame
  // TODO remove the restriction
  ASSERT_EQ(frame_size.x, element_size.x);

  e->SetCoords({0, frame_size.y + margin_});   // Move the coords of frame by the element's height
  frame_size += {0, element_size.y + margin_}; // Increment size of the frame by the element's height
  this->SetSize(frame_size);

  AddChild(e);
}
