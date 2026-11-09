/*
    RB3Enhanced - MemoryOverlay.h
    Restores Rnd overlay stuff.
*/

#ifndef _MEMORYOVERLAY_H
#define _MEMORYOVERLAY_H

#include "rb3/Data.h"
#include "rb3/TextStream.h"

void InitialiseMemoryOverlay();

extern void RndEndWorld(void *thisRnd);
extern void RndPreInit(void *thisRnd);
extern void RndOverlayDrawAll(int modalOnly);
extern void RndOverlaySetLines(TextStream *overlay, int lines);
extern TextStream *TextStreamWrite(TextStream *stream, const char *text);
extern void MemFreeBlockStats(int heap, int *leftFragments, int *rightFragments, int *freeBytes, int *largestBlock);
extern const char *MemHeapName(int heap);
extern void RndOnToggleHeap(DataNode *node, void *thisRnd, DataArray *args);

#endif // _MEMORYOVERLAY_H
