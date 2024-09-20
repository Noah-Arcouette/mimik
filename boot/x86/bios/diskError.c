#include "colors.h"
#include "lang.h"
#include "unreal.h"

void
diskError (unsigned char error)
{
	switch (error)
	{
	case 0x00:
		puts(DISK_ERROR_SUCCESS, FG_GREEN);
		break;
	case 0x01:
		puts(DISK_ERROR_INVALID_COMMAND, FG_RED);
		break;
	case 0x02:
		puts(DISK_ERROR_ADDRESS_MARK, FG_RED);
		break;
	case 0x03:
		puts(DISK_ERROR_WRITE_PROT, FG_RED);
		break;
	case 0x04:
		puts(DISK_ERROR_SECTOR_NOT_FOUND, FG_RED);
		break;
	case 0x05:
		puts(DISK_ERROR_RESET_FAILED, FG_RED);
		break;
	case 0x06:
		puts(DISK_ERROR_CHANGE_ACTIVE, FG_RED);
		break;
	case 0x07:
		puts(DISK_ERROR_PARAM_FAILED, FG_RED);
		break;
	case 0x08:
		puts(DISK_ERROR_DMA_OVERRUN, FG_RED);
		break;
	case 0x09:
		puts(DISK_ERROR_DMA_BOUNDARY, FG_RED);
		break;
	case 0x0A:
		puts(DISK_ERROR_BAD_SECTOR, FG_RED);
		break;
	case 0x0B:
		puts(DISK_ERROR_BAD_TRACK, FG_RED);
		break;
	case 0x0C:
		puts(DISK_ERROR_MEDIA_NOT_FOUND, FG_RED);
		break;
	case 0x0D:
		puts(DISK_ERROR_INVALID_SECTORS, FG_RED);
		break;
	case 0x0E:
		puts(DISK_ERROR_CONTROL_MARK, FG_RED);
		break;
	case 0x0F:
		puts(DISK_ERROR_DMA_RANGE, FG_RED);
		break;
	case 0x10:
		puts(DISK_ERROR_ECC_ERROR, FG_RED);
		break;
	case 0x11:
		puts(DISK_ERROR_ECC_CORRECTED, FG_RED);
		break;
	case 0x20:
		puts(DISK_ERROR_CONTROLLER_FAILED, FG_RED);
		break;
	case 0x40:
		puts(DISK_ERROR_SEEK_FAILED, FG_RED);
		break;
	case 0x80:
		puts(DISK_ERROR_TIMED_OUT, FG_RED);
		break;
	case 0xAA:
		puts(DISK_ERROR_NOT_READY, FG_RED);
		break;
	case 0xBB:
		puts(DISK_ERROR_UNDEFINED, FG_RED);
		break;
	case 0xCC:
		puts(DISK_ERROR_WRITE_FAULT, FG_RED);
		break;
	case 0xE0:
		puts(DISK_ERROR_STATUS_ERROR, FG_RED);
		break;
	case 0xFF:
		puts(DISK_ERROR_SENSE_FAILED, FG_RED);
		break;
	default:
		puts(DISK_ERROR_UNKNOWN, FG_RED);
		break;
	}
}
