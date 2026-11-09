/*
    RB3Enhanced - MemoryOverlay.c
    Restores Rnd overlay stuff.
*/

#include <stddef.h>
#include <stdio.h>
#include "MemoryOverlay.h"
#include "ports.h"
#include "ppcasm.h"
#include "rb3/Mem.h"
#include "utilities.h"

// bank8 is already a debug build, doesnt need any of this stuff
#ifndef RB3E_WII_BANK8
static void RndEndWorldAndDrawOverlays(void *thisRnd)
{
    RndEndWorld(thisRnd);
    RndOverlayDrawAll(0);
}
#endif

#ifndef RB3E_WII
static void RndPreInitMemoryOverlayHook(void *thisRnd)
{
    void *heapOverlay;
    RndPreInit(thisRnd);
    heapOverlay = *(void **)((unsigned char *)thisRnd + 0x88); // Rnd::mHeapOverlay
    if (heapOverlay != NULL)
    {
        *(float *)((unsigned char *)heapOverlay + 0x24) = 0.7f; // tweak RndOverlay::mBackColor alpha, to make it easier to see
    }
}
#endif

#if defined(RB3E_WII) && !defined(RB3E_WII_BANK8)

// they compiled out this stuff in the Wii retail build so we need to recreate it, for whatever 360 still has it so this is only needed on Wii

static int ReadHeapStat(int heap, int offset)
{
    unsigned char *heapData = (unsigned char *)PORT_MEMHEAPS + heap * 0x34; // each heap is 0x34 bytes
    return *(int *)(heapData + offset);
}

static void PrintHeapLine(TextStream *overlay, int heap, int *totalFree, int *minimumTotalFree)
{
    char line[256];
    const char *heapName;
    int leftFragments;
    int rightFragments;
    int freeBytes;
    int largestBlock;
    int minimumFreeBytes;
    int minimumLargestBlock;
    int heapSize;

    MemFreeBlockStats(heap, &leftFragments, &rightFragments, &freeBytes, &largestBlock);
    minimumFreeBytes = ReadHeapStat(heap, 0x28);
    minimumLargestBlock = ReadHeapStat(heap, 0x30);
    heapSize = ReadHeapStat(heap, 0x0c);
    heapName = MemHeapName(heap);
    if (heapName == NULL)
    {
        heapName = "?";
    }
    sprintf(line, " [%5s] free:%5d big:%5d lfrag:%4d rfrag:%3d minfree:%5d minbig:%5d size:%6d\n", heapName, freeBytes >> 10, largestBlock >> 10, leftFragments, rightFragments, minimumFreeBytes >> 10, minimumLargestBlock >> 10, heapSize >> 8);
    TextStreamWrite(overlay, line);
    *totalFree += freeBytes;
    *minimumTotalFree += minimumFreeBytes;
}

static void RndUpdateHeapWii(void *thisRnd)
{
    char line[128];
    TextStream *overlay;
    int currentHeap;
    int heapCount;
    int heap;
    int totalFree;
    int minimumTotalFree;

    overlay = *(TextStream **)((unsigned char *)thisRnd + 0x78); // Rnd::mHeapOverlay
    if (overlay == NULL)
    {
        return;
    }
    currentHeap = *(int *)PORT_GCURHEAP;
    heapCount = MemNumHeaps();
    if (heapCount <= 0)
    {
        return;
    }
    if (currentHeap >= heapCount)
    {
        currentHeap = -1;
    }
    if (currentHeap < -1)
    {
        currentHeap = -1;
    }
    totalFree = 0;
    minimumTotalFree = 0;
    if (currentHeap == -1)
    {
        RndOverlaySetLines(overlay, heapCount + 1);
        for (heap = 0; heap < heapCount; heap++)
        {
            PrintHeapLine(overlay, heap, &totalFree, &minimumTotalFree);
        }
        sprintf(line, "totalFree: %7d minTotalFree: %7d, totalFree(64): %7d minTotalFree(64): %7d\n", totalFree >> 10, minimumTotalFree >> 10, (totalFree >> 10) - 0x10000, (minimumTotalFree >> 10) - 0x10000);
        TextStreamWrite(overlay, line);
    }
    else
    {
        RndOverlaySetLines(overlay, 1);
        PrintHeapLine(overlay, currentHeap, &totalFree, &minimumTotalFree);
    }
}
#endif

void InitialiseMemoryOverlay()
{
#ifndef RB3E_WII_BANK8
    POKE_PLUGIN_BL(PORT_RND_ENDWORLD_CALL, PLUGIN_PTR(RndEndWorldAndDrawOverlays));
#endif
#ifndef RB3E_WII
    HookFunction(PORT_RND_PREINIT, PLUGIN_PTR(RndPreInit), PLUGIN_PTR(RndPreInitMemoryOverlayHook));
#endif
#if defined(RB3E_WII) && !defined(RB3E_WII_BANK8)
    POKE_BL(PORT_RND_UPDATEHEAP_CALL, &RndUpdateHeapWii);
#endif
}
