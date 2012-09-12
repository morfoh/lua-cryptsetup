-- [NOTE]
--
-- This very simple test relies that you have setup a crypt device called
-- 'cryptostorage' yet.
-- It's very quick and dirty but should give you a fairly good understanding
-- how things have to be used for now ;)
--

local crypt = require"cryptsetup"

local name = "cryptostorage"
local device = crypt.CryptDevice.init_by_name(name)
print("device", device)
print("name", name)
print("device:get_rng_type()", device:get_rng_type())
print("device:set_rng_type(1)", device:set_rng_type(1))
print("device:get_rng_type()", device:get_rng_type())
print("device:get_type()", device:get_type())
print("device:status(name)", device:status(name))
print("device:get_cipher()", device:get_cipher())
print("device:get_cipher_mode()", device:get_cipher_mode())
print("device:get_uuid()", device:get_uuid())
print("device:get_device_name()", device:get_device_name())
print("device:get_data_offset()", device:get_data_offset())
print("device:get_iv_offset()", device:get_iv_offset())
print("device:get_volume_key_size()", device:get_volume_key_size())
print("device:keyslot_status(0)", device:keyslot_status(0))
-- print("device:header_backup(\"LUKS1\", \"cryptostorage.cryptheader.backup\")", device:header_backup("LUKS1", "cryptostorage.cryptheader.backup"))
print("device:get_dir()", device:get_dir())

print(device:free())
