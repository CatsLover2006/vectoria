// Draw String
void drawString(std::string str, double x, double y, double scale, double weight, u32 color);
// Draw Button
void drawButton (button* buttonToDraw, u32 color, double weight);
// Anti-Aliasing
C3D_RenderTarget* C2D_CreateScreenTargetAA(gfxScreen_t screen, gfx3dSide_t side);
C3D_RenderTarget* C2D_CreateScreenTargetHAA(gfxScreen_t screen, gfx3dSide_t side);