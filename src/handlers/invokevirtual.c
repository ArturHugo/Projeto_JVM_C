#include "handlers/invokevirtual.h"
#include "class-file.h"
#include "frame.h"
#include "global.h"

void invokevirtual(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u1*    operands      = instruction + 1;

  u2 index = (operands[0] << 8) | operands[1];
}