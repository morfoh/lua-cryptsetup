-- make generated variable nicer
set_variable_format "%s"

c_module "cryptsetup" {

-- enable FFI bindings support.
luajit_ffi = true,

-- load CRYPTSETUP shared library.
ffi_load"cryptsetup",

sys_include "libcryptsetup.h",

--export_definitions {
constants {
-- RNG
-- use /dev/urandom
CRYPT_RNG_URANDOM = 0,
-- use /dev/random (waits if no entropy is available)
CRYPT_RNG_RANDOM  = 1,

-- device types
CRYPT_PLAIN   = "PLAIN",
CRYPT_LUKS1   = "LUKS1",
CRYPT_LOOPAES = "LOOPAES",

CRYPT_ANY_SLOT = -1,

-- Activation flags
--
-- device is read only
CRYPT_ACTIVATE_READONLY		= 1,
-- only reported for device without uuid
CRYPT_ACTIVATE_NO_UUID 		= 2,
-- activate even if cannot grant exclusive access (DANGEROUS)
CRYPT_ACTIVATE_SHARED 		= 4,
-- enable discards aka TRIM
CRYPT_ACTIVATE_ALLOW_DISCARDS	= 8,
-- skip global udev rules in activation ("private device"), input only
CRYPT_ACTIVATE_PRIVATE		= 16,
},

subfiles {
"src/cryptdevice.nobj.lua",
},
}

