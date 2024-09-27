# `/strap/`

Strap is responsible for boot strapping the unreal mode of stage two.

## `stage2.S`

This file is the entry point for strap and will setup unreal mode by messing with the CPUs GDT descriptor cache and will enable thirty two bit data addressing. Before messing with the GDT it will attempt to enable the A20 line. It will then jump to unreal mode C code.

## `enableA20.S`

This will attempt to enable the A20 line and will panic if it fails to set it. The current implementation will only check if the A20 line is preset by the BIOS and will panic if not.

## `gdt.S`

The unreal mode GDT table and register.
