-- Copyright (c) 2012 by Christian Wiese <chris@opensde.org>
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

--
-- CryptDevice
--

object "CryptDevice" {
	userdata_type = 'simple',
	c_source [[
typedef struct crypt_device *CryptDevice;
]],
	constructor "init" {
		c_call "int" "crypt_init" { "CryptDevice *", "&this", "const char *", "device" },
	},
	constructor "init_by_name_and_header" {
		var_in { "const char *", "header_device", is_optional = true, default = NULL },
		c_call "int" "crypt_init_by_name_and_header" {
			"CryptDevice *", "&this",
			"const char *", "name",
			"const char *", "header_device"
		},
	},
	constructor "init_by_name" {
		c_call "int" "crypt_init_by_name" {
			"CryptDevice *", "&this",
			"const char *", "name"
		},
	},
	destructor "free" {
		c_method_call "void" "crypt_free" {},
	},
	-- get device type
	method "get_type" {
		c_method_call "const char *" "crypt_get_type" {}
	},
	-- set which RNG (random number generator) is used for generating long term key
	method "set_rng_type" {
		c_method_call "void" "crypt_set_rng_type" { "int", "rng_type" }
	},
	-- get which RNG (random number generator) is used for generating long term key
	method "get_rng_type" {
		c_method_call "int" "crypt_get_rng_type" {}
	},
	-- get status info about device name
	method "status" {
		c_method_call "int" "crypt_status" { "const char *", "name" }
	},

	--
	-- TODO int crypt_dump(struct crypt_device *cd);
	--

	-- get cipher used in device
	method "get_cipher" {
		c_method_call "const char *" "crypt_get_cipher" {}
	},
	-- get cipher mode used in device
	method "get_cipher_mode" {
		c_method_call "const char *" "crypt_get_cipher_mode" {}
	},
	-- get device UUID
	method "get_uuid" {
		c_method_call "const char *" "crypt_get_uuid" {}
	},
	-- get path to underlaying device
	method "get_device_name" {
		c_method_call "const char *" "crypt_get_device_name" {}
	},
	-- get device offset in sectors where real data starts on underlying device
	method "get_data_offset" {
		c_method_call "uint64_t" "crypt_get_data_offset" {}
	},
	-- get IV offset in sectors
	method "get_iv_offset" {
		c_method_call "uint64_t" "crypt_get_iv_offset" {}
	},
	-- get size (in bytes) of volume key for crypt device
	method "get_volume_key_size" {
		c_method_call "int" "crypt_get_volume_key_size" {}
	},

	--
	-- TODO implement the rest of the keyslot related functions
	-- http://wiki.cryptsetup.googlecode.com/git/API/group__keyslot.html
	--

	-- get information about particular key slot
	method "keyslot_status" {
		c_method_call "int" "crypt_keyslot_status" { "int", "keyslot" }
	},
	-- backup header and keyslots to file
	method "header_backup" {
		c_method_call "int" "crypt_header_backup" { "const char *", "requested_type", "const char *", "backup_file" }
	},
	-- restore header and keyslots from backup file
	method "header_restore" {
		c_method_call "int" "crypt_header_restore" { "const char *", "requested_type", "const char *", "backup_file" }
	},
	-- get directory where mapped crypt devices are created
	method "get_dir" {
		c_call "const char *" "crypt_get_dir" {}
	},
}

