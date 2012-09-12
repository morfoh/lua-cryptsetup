#!/usr/bin/env lua

package	= 'lua-cryptsetup'
version	= 'scm-0'
source	= {
	url	= 'https://github.com/morfoh/lua-cryptsetup'
}
description	= {
	summary	= "Lua bindings for libcryptsetup.",
	detailed	= '',
	homepage	= 'https://github.com/morfoh/lua-cryptsetup',
	license	= 'MIT',
	maintainer = "Christian Wiese",
}
dependencies = {
	'lua >= 5.1',
}
external_dependencies = {
	CRYPTSETUP = {
		header = "libcryptsetup.h",
		library = "cryptsetup",
	}
}
build	= {
	type = "builtin",
	modules = {
		cryptsetup = {
			sources = { "src/pre_generated-cryptsetup.nobj.c" },
			libraries = { "cryptsetup" },
		}
	}
}
