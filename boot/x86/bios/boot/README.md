# `/boot/`

All files in this folder will reside in the MBR boot sector. Their only purpose is to load the next stage into memory.

## `init.S`

This is the first code to be executed. It sets up the segmentation and saves the `bootDisk` number given by the BIOS. It then passes execution to the boot sector's main code.

## `bootsect.S`

This is the main operation of the boot sector, again it's only purpose is to load the next stage. It does three things:

 - Setup 80x25 text video memory on page one
   - This is needed incase a panic occurs while reading the stage two data and it needs to write to the screen
 - Load the next stage into memory
 - Entering the stage two

## `setupVideo.S`

This sets up video memory into 80x25 text mode in page one. It also disables the cursor. This also defines the amount of `columns` and `rows` in the `videoMemory`. These values shall be used to reduce hard coding.

## `loadStage2.S`

This reads the stage two into memory from the second sector on the boot disk. This value is hard coded so make sure the MBR Break is right after the MBR and is large enough to support the stage two.

## `panic.S`

This file handles writing a panic message to video memory. It will draw a red screen then write the error message and halt the CPU.
