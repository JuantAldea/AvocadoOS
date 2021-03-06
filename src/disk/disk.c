#include <stddef.h>

#include "disk.h"
#include "../string/string.h"
#include "../io/io.h"
#include "../status.h"
#include "../fs/file.h"

struct disk_t disks[1];

int disk_read_sector(const struct disk_t *const disk, const int lba, const int n, void *const buf)
{
    outb(0x1F6, (lba >> 24) | disk->port);
    outb(0x1F2, n);
    outb(0x1F3, (uint8_t)(lba & 0xFF));
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));
    outb(0x1F7, 0x20);

    uint16_t *ptr = buf;

    for (int block = 0; block < n; ++block) {
        uint8_t status;

        do {
            status = insb(0x1F7);
        } while ((status & BUSY_BIT) || !(status & DRQ_BIT));

        for (int i = 0; i < 256; ++i) {
            *ptr++ = insw(0x1F0);
        }
    }

    return 0;
}

void disk_init()
{
    memset(&disks, 0, sizeof(disks)); // NOLINT
    disks[0].type = DISK_TYPE_PHYSICAL;
    disks[0].sector_size = DISK_SECTOR_SIZE;
    disks[0].port = ATA_MASTER;
    disks[0].id = 0;
    disks[0].fs_operations = fs_probe_fs(&disks[0]);
}

int disk_get(int disk_index, struct disk_t **disk)
{
    if (disk_index != 0) {
        *disk = NULL;
        return -ENOMEDIUM;
    }
    *disk = &disks[disk_index];
    return 0;
}

int disk_read_block(const struct disk_t *const disk, const unsigned int lba, const int n, void *const buffer)
{
    if (disk != &disks[0]) {
        return -ENOMEDIUM;
    }

    return disk_read_sector(disk, lba, n, buffer);
}
