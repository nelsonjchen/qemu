/*
 * Raspberry Pi emulation (c) 2012 Gregory Estrade
 * Upstreaming code cleanup [including bcm2835_*] (c) 2013 Jan Petrous
 *
 * Rasperry Pi 2 emulation and refactoring Copyright (c) 2015, Microsoft
 * Written by Andrew Baumann
 *
 * This code is licensed under the GNU GPLv2 and later.
 */

#ifndef BCM2835_FB_H
#define BCM2835_FB_H

#include "hw/sysbus.h"
#include "exec/address-spaces.h"
#include "ui/console.h"

#define TYPE_BCM2835_FB "bcm2835_fb"
#define BCM2835_FB(obj) OBJECT_CHECK(Bcm2835FbState, (obj), TYPE_BCM2835_FB)

typedef struct {
    SysBusDevice busdev;
    uint32_t vcram_base, vcram_size;

    MemoryRegion *dma_mr;
    AddressSpace dma_as;
    MemoryRegion iomem;
    MemoryRegionSection fbsection;

    QemuConsole *con;
    bool lock, invalidate;

    uint32_t xres, yres;
    uint32_t xres_virtual, yres_virtual;
    uint32_t xoffset, yoffset;
    uint32_t bpp;
    uint32_t base, pitch, size;
    uint32_t pixo, alpha;

    int pending;
    qemu_irq mbox_irq;
} Bcm2835FbState;

void bcm2835_fb_reconfigure(Bcm2835FbState *s, uint32_t *xres, uint32_t *yres,
                            uint32_t *xoffset, uint32_t *yoffset, uint32_t *bpp,
                            uint32_t *pixo, uint32_t *alpha);

#endif
