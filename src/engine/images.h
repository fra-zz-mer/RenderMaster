#pragma once
#include "common.h"

ICoreTexture *createFromDDS(unique_ptr<uint8_t[]> dataPtr, size_t size, TEXTURE_CREATE_FLAGS flags);

void importJPEG(const char* path);
void importPNG(const char* path);
