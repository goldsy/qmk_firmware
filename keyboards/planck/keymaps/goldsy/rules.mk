# This gets included at the beginning of the Planck's Makefile.
# Alternatively, you can run make from the keymap directory
# and the main Makefile will be included after.
#SUBPROJECT_DEFAULT = rev4

COMMAND_ENABLE = no   # Disable shift combination, which conflicts with shift-parens
NKRO_ENABLE    = yes  # N-key rollover required for use as a steno board
AUDIO_ENABLE   = yes  # Audio output on port C6
BACKLIGHT_ENABLE = yes # Enable backlighting

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
