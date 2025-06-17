#include "CGWorldFrame.h"

//auto CGWorldFrame_GetScreenCoordinates = reinterpret_cast<bool(__fastcall*)(CGWorldFrame * self, Vector3 * input, Vector3 * output, bool unk)>(Offsets::Offset_CGWorldFrame_GetScreenCoordinates);
//
//bool CGWorldFrame::worldToScreen(Vector3* input, Vector3* output)
//{
//	if (!CGWorldFrame_GetScreenCoordinates(this, input, output, false))
//		return false;
//
//	output->x = (output->x / this->fovX) * 1280.0f;
//	output->y = 720.0f - (720.0f * (output->y / this->fovY));
//	return true;
//}
