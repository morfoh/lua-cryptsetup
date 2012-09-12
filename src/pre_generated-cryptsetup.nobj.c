/***********************************************************************************************
************************************************************************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!! Warning this file was generated from a set of *.nobj.lua definition files !!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
************************************************************************************************
***********************************************************************************************/

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define REG_PACKAGE_IS_CONSTRUCTOR 0
#define REG_MODULES_AS_GLOBALS 0
#define REG_OBJECTS_AS_GLOBALS 0
#define OBJ_DATA_HIDDEN_METATABLE 1
#define USE_FIELD_GET_SET_METHODS 0
#define LUAJIT_FFI 1


#include <libcryptsetup.h>



#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#ifdef _MSC_VER
#define __WINDOWS__
#else
#if defined(_WIN32)
#define __WINDOWS__
#endif
#endif

#ifdef __WINDOWS__

/* for MinGW32 compiler need to include <stdint.h> */
#ifdef __GNUC__
#include <stdint.h>
#include <stdbool.h>
#else

/* define some standard types missing on Windows. */
#ifndef __INT32_MAX__
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
#ifndef __INT64_MAX__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef int bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#endif

/* wrap strerror_s(). */
#ifdef __GNUC__
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) do { \
	strncpy((buf), strerror(errno), (buflen)-1); \
	(buf)[(buflen)-1] = '\0'; \
} while(0)
#endif
#else
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) strerror_s((buf), (buflen), (errno))
#endif
#endif

#define FUNC_UNUSED

#define LUA_NOBJ_API __declspec(dllexport)

#else

#define LUA_NOBJ_API LUALIB_API

#include <stdint.h>
#include <stdbool.h>

#define FUNC_UNUSED __attribute__((unused))

#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define assert_obj_type(type, obj) \
	assert(__builtin_types_compatible_p(typeof(obj), type *))
#else
#define assert_obj_type(type, obj)
#endif

void *nobj_realloc(void *ptr, size_t osize, size_t nsize);

void *nobj_realloc(void *ptr, size_t osize, size_t nsize) {
	(void)osize;
	if(0 == nsize) {
		free(ptr);
		return NULL;
	}
	return realloc(ptr, nsize);
}

#define obj_type_free(type, obj) do { \
	assert_obj_type(type, obj); \
	nobj_realloc((obj), sizeof(type), 0); \
} while(0)

#define obj_type_new(type, obj) do { \
	assert_obj_type(type, obj); \
	(obj) = nobj_realloc(NULL, 0, sizeof(type)); \
} while(0)

typedef struct obj_type obj_type;

typedef void (*base_caster_t)(void **obj);

typedef void (*dyn_caster_t)(void **obj, obj_type **type);

#define OBJ_TYPE_FLAG_WEAK_REF (1<<0)
#define OBJ_TYPE_SIMPLE (1<<1)
struct obj_type {
	dyn_caster_t    dcaster;  /**< caster to support casting to sub-objects. */
	int32_t         id;       /**< type's id. */
	uint32_t        flags;    /**< type's flags (weak refs) */
	const char      *name;    /**< type's object name. */
};

typedef struct obj_base {
	int32_t        id;
	base_caster_t  bcaster;
} obj_base;

typedef enum obj_const_type {
	CONST_UNKOWN    = 0,
	CONST_BOOLEAN   = 1,
	CONST_NUMBER    = 2,
	CONST_STRING    = 3
} obj_const_type;

typedef struct obj_const {
	const char      *name;    /**< constant's name. */
	const char      *str;
	double          num;
	obj_const_type  type;
} obj_const;

typedef enum obj_field_type {
	TYPE_UNKOWN    = 0,
	TYPE_UINT8     = 1,
	TYPE_UINT16    = 2,
	TYPE_UINT32    = 3,
	TYPE_UINT64    = 4,
	TYPE_INT8      = 5,
	TYPE_INT16     = 6,
	TYPE_INT32     = 7,
	TYPE_INT64     = 8,
	TYPE_DOUBLE    = 9,
	TYPE_FLOAT     = 10,
	TYPE_STRING    = 11
} obj_field_type;

typedef struct obj_field {
	const char      *name;  /**< field's name. */
	uint32_t        offset; /**< offset to field's data. */
	obj_field_type  type;   /**< field's data type. */
	uint32_t        flags;  /**< is_writable:1bit */
} obj_field;

typedef enum {
	REG_OBJECT,
	REG_PACKAGE,
	REG_META,
} module_reg_type;

typedef struct reg_impl {
	const char *if_name;
	const void *impl;
} reg_impl;

typedef struct reg_sub_module {
	obj_type        *type;
	module_reg_type req_type;
	const luaL_reg  *pub_funcs;
	const luaL_reg  *methods;
	const luaL_reg  *metas;
	const obj_base  *bases;
	const obj_field *fields;
	const obj_const *constants;
	const reg_impl  *implements;
	int             bidirectional_consts;
} reg_sub_module;

#define OBJ_UDATA_FLAG_OWN (1<<0)
#define OBJ_UDATA_FLAG_LOOKUP (1<<1)
#define OBJ_UDATA_LAST_FLAG (OBJ_UDATA_FLAG_LOOKUP)
typedef struct obj_udata {
	void     *obj;
	uint32_t flags;  /**< lua_own:1bit */
} obj_udata;

/* use static pointer as key to weak userdata table. */
static char obj_udata_weak_ref_key[] = "obj_udata_weak_ref_key";

/* use static pointer as key to module's private table. */
static char obj_udata_private_key[] = "obj_udata_private_key";

#if LUAJIT_FFI
typedef int (*ffi_export_func_t)(void);
typedef struct ffi_export_symbol {
	const char *name;
	union {
	void               *data;
	ffi_export_func_t  func;
	} sym;
} ffi_export_symbol;
#endif





static obj_type obj_types[] = {
#define obj_type_id_CryptDevice 0
#define obj_type_CryptDevice (obj_types[obj_type_id_CryptDevice])
  { NULL, 0, OBJ_TYPE_FLAG_WEAK_REF, "CryptDevice" },
  {NULL, -1, 0, NULL},
};


#if LUAJIT_FFI

/* nobj_ffi_support_enabled_hint should be set to 1 when FFI support is enabled in at-least one
 * instance of a LuaJIT state.  It should never be set back to 0. */
static int nobj_ffi_support_enabled_hint = 0;
static const char nobj_ffi_support_key[] = "LuaNativeObject_FFI_SUPPORT";
static const char nobj_check_ffi_support_code[] =
"local stat, ffi=pcall(require,\"ffi\")\n" /* try loading LuaJIT`s FFI module. */
"if not stat then return false end\n"
"return true\n";

static int nobj_check_ffi_support(lua_State *L) {
	int rc;
	int err;

	/* check if ffi test has already been done. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_rawget(L, LUA_REGISTRYINDEX);
	if(!lua_isnil(L, -1)) {
		rc = lua_toboolean(L, -1);
		lua_pop(L, 1);
		/* use results of previous check. */
		goto finished;
	}
	lua_pop(L, 1); /* pop nil. */

	err = luaL_loadbuffer(L, nobj_check_ffi_support_code,
		sizeof(nobj_check_ffi_support_code) - 1, nobj_ffi_support_key);
	if(0 == err) {
		err = lua_pcall(L, 0, 1, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Error when checking for FFI-support: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
		return 0;
	}
	/* check results of test. */
	rc = lua_toboolean(L, -1);
	lua_pop(L, 1); /* pop results. */
		/* cache results. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_pushboolean(L, rc);
	lua_rawset(L, LUA_REGISTRYINDEX);

finished:
	/* turn-on hint that there is FFI code enabled. */
	if(rc) {
		nobj_ffi_support_enabled_hint = 1;
	}

	return rc;
}

typedef struct {
	const char **ffi_init_code;
	int offset;
} nobj_reader_state;

static const char *nobj_lua_Reader(lua_State *L, void *data, size_t *size) {
	nobj_reader_state *state = (nobj_reader_state *)data;
	const char *ptr;

	(void)L;
	ptr = state->ffi_init_code[state->offset];
	if(ptr != NULL) {
		*size = strlen(ptr);
		state->offset++;
	} else {
		*size = 0;
	}
	return ptr;
}

static int nobj_try_loading_ffi(lua_State *L, const char *ffi_mod_name,
		const char *ffi_init_code[], const ffi_export_symbol *ffi_exports, int priv_table)
{
	nobj_reader_state state = { ffi_init_code, 0 };
	int err;

	/* export symbols to priv_table. */
	while(ffi_exports->name != NULL) {
		lua_pushstring(L, ffi_exports->name);
		lua_pushlightuserdata(L, ffi_exports->sym.data);
		lua_settable(L, priv_table);
		ffi_exports++;
	}
	err = lua_load(L, nobj_lua_Reader, &state, ffi_mod_name);
	if(0 == err) {
		lua_pushvalue(L, -2); /* dup C module's table. */
		lua_pushvalue(L, priv_table); /* move priv_table to top of stack. */
		lua_remove(L, priv_table);
		lua_pushvalue(L, LUA_REGISTRYINDEX);
		err = lua_pcall(L, 3, 0, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Failed to install FFI-based bindings: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
	}
	return err;
}
#endif


typedef struct {
	void *impl;
	void *obj;
} obj_implement;

static FUNC_UNUSED void *obj_implement_luaoptional(lua_State *L, int _index, void **impl, char *if_name) {
	void *ud;
	if(lua_isnoneornil(L, _index)) {
		return NULL;
	}
	/* get the implements table for this interface. */
	lua_pushlightuserdata(L, if_name);
	lua_rawget(L, LUA_REGISTRYINDEX);

	/* get pointer to userdata value & check if it is a userdata value. */
	ud = (obj_implement *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* get the userdata's metatable */
		if(lua_getmetatable(L, _index)) {
			/* lookup metatable in interface table for this object's implementation of the interface. */
			lua_gettable(L, -2);
		} else {
			/* no metatable. */
			goto no_interface;
		}
#if LUAJIT_FFI
	} else if(nobj_ffi_support_enabled_hint) { /* handle cdata. */
		/* get cdata interface check function from interface table. */
		lua_getfield(L, -1, "cdata");
		if(lua_isfunction(L, -1)) {
			/* pass cdata to function, return value should be an implmentation. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			/* get pointer to cdata. */
			ud = (void *)lua_topointer(L, _index);
		} else {
			lua_pop(L, 1); /* pop non-function. */
			goto no_interface;
		}
#endif
	} else {
		goto no_interface;
	}

	if(!lua_isnil(L, -1)) {
		*impl = lua_touserdata(L, -1);
		lua_pop(L, 2); /* pop interface table & implementation. */
		/* object implements interface. */
		return ud;
	} else {
		lua_pop(L, 1); /* pop nil. */
	}
no_interface:
	lua_pop(L, 1); /* pop interface table. */
	return NULL;
}

static FUNC_UNUSED void *obj_implement_luacheck(lua_State *L, int _index, void **impl, char *type) {
	void *ud = obj_implement_luaoptional(L, _index, impl, type);
	if(ud == NULL) {
#define ERROR_BUFFER_SIZE 256
		char buf[ERROR_BUFFER_SIZE];
		snprintf(buf, ERROR_BUFFER_SIZE-1,"Expected object with %s interface", type);
		/* value doesn't implement this interface. */
		luaL_argerror(L, _index, buf);
	}
	return ud;
}

/* use static pointer as key to interfaces table. (version 1.0) */
static char obj_interfaces_table_key[] = "obj_interfaces<1.0>_table_key";

static void obj_get_global_interfaces_table(lua_State *L) {
	/* get global interfaces table. */
	lua_getfield(L, LUA_REGISTRYINDEX, obj_interfaces_table_key);
	if(lua_isnil(L, -1)) {
		/* Need to create global interfaces table. */
		lua_pop(L, 1); /* pop nil */
		lua_createtable(L, 0, 4); /* 0 size array part, small hash part. */
		lua_pushvalue(L, -1); /* dup table. */
		/* store interfaces table in Lua registery. */
		lua_setfield(L, LUA_REGISTRYINDEX, obj_interfaces_table_key);
	}
}

static void obj_get_interface(lua_State *L, const char *name, int global_if_tab) {
	/* get a interface's implementation table */
	lua_getfield(L, global_if_tab, name);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil */
		/* new interface. (i.e. no object implement it yet.)
		 *
		 * create an empty table for this interface that will be used when an
		 * implementation is registered for this interface.
		 */
		lua_createtable(L, 0, 2); /* 0 size array part, small hash part. */
		lua_pushvalue(L, -1); /* dup table. */
		lua_setfield(L, global_if_tab, name); /* store interface in global interfaces table. */
	}
}

static int obj_get_userdata_interface(lua_State *L) {
	/* get the userdata's metatable */
	if(lua_getmetatable(L, 2)) {
		/* lookup metatable in interface table for the userdata's implementation of the interface. */
		lua_gettable(L, 1);
		if(!lua_isnil(L, -1)) {
			/* return the implementation. */
			return 1;
		}
	}
	/* no metatable or no implementation. */
	return 0;
}

static void obj_interface_register(lua_State *L, char *name, int global_if_tab) {
	/* get the table of implementations for this interface. */
	obj_get_interface(L, name, global_if_tab);

	/* check for 'userdata' function. */
	lua_getfield(L, -1, "userdata");
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		/* add C function for getting a userdata's implementation. */
		lua_pushcfunction(L, obj_get_userdata_interface);
		lua_setfield(L, -2, "userdata");
	} else {
		/* already have function. */
		lua_pop(L, 1); /* pop C function. */
	}
	/* we are going to use a lightuserdata pointer for fast lookup of the interface's impl. table. */
	lua_pushlightuserdata(L, name);
	lua_insert(L, -2);
	lua_settable(L, LUA_REGISTRYINDEX);
}

static void obj_register_interfaces(lua_State *L, char *interfaces[]) {
	int i;
	int if_tab;
	/* get global interfaces table. */
	obj_get_global_interfaces_table(L);
	if_tab = lua_gettop(L);

	for(i = 0; interfaces[i] != NULL ; i++) {
		obj_interface_register(L, interfaces[i], if_tab);
	}
	lua_pop(L, 1); /* pop global interfaces table. */
}

static void obj_type_register_implement(lua_State *L, const reg_impl *impl, int global_if_tab, int mt_tab) {
	/* get the table of implementations for this interface. */
	obj_get_interface(L, impl->if_name, global_if_tab);

	/* register object's implement in the interface table. */
	lua_pushvalue(L, mt_tab);
	lua_pushlightuserdata(L, (void *)impl->impl);
	lua_settable(L, -3);

	lua_pop(L, 1); /* pop inteface table. */
}

static void obj_type_register_implements(lua_State *L, const reg_impl *impls) {
	int if_tab;
	int mt_tab;
	/* get absolute position of object's metatable. */
	mt_tab = lua_gettop(L);
	/* get global interfaces table. */
	obj_get_global_interfaces_table(L);
	if_tab = lua_gettop(L);

	for(; impls->if_name != NULL ; impls++) {
		obj_type_register_implement(L, impls, if_tab, mt_tab);
	}
	lua_pop(L, 1); /* pop global interfaces table. */
}

#ifndef REG_PACKAGE_IS_CONSTRUCTOR
#define REG_PACKAGE_IS_CONSTRUCTOR 1
#endif

#ifndef REG_MODULES_AS_GLOBALS
#define REG_MODULES_AS_GLOBALS 0
#endif

#ifndef REG_OBJECTS_AS_GLOBALS
#define REG_OBJECTS_AS_GLOBALS 0
#endif

#ifndef OBJ_DATA_HIDDEN_METATABLE
#define OBJ_DATA_HIDDEN_METATABLE 1
#endif

static FUNC_UNUSED obj_udata *obj_udata_toobj(lua_State *L, int _index) {
	obj_udata *ud;
	size_t len;

	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	/* verify userdata size. */
	len = lua_objlen(L, _index);
	if(len != sizeof(obj_udata)) {
		/* This shouldn't be possible */
		luaL_error(L, "invalid userdata size: size=%d, expected=%d", len, sizeof(obj_udata));
	}
	return ud;
}

static FUNC_UNUSED int obj_udata_is_compatible(lua_State *L, obj_udata *ud, void **obj, base_caster_t *caster, obj_type *type) {
	obj_base *base;
	obj_type *ud_type;
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(lua_rawequal(L, -1, -2)) {
		*obj = ud->obj;
		/* same type no casting needed. */
		return 1;
	} else {
		/* Different types see if we can cast to the required type. */
		lua_rawgeti(L, -2, type->id);
		base = lua_touserdata(L, -1);
		lua_pop(L, 1); /* pop obj_base or nil */
		if(base != NULL) {
			*caster = base->bcaster;
			/* get the obj_type for this userdata. */
			lua_pushliteral(L, ".type");
			lua_rawget(L, -3); /* type's metatable. */
			ud_type = lua_touserdata(L, -1);
			lua_pop(L, 1); /* pop obj_type or nil */
			if(base == NULL) {
				luaL_error(L, "bad userdata, missing type info.");
				return 0;
			}
			/* check if userdata is a simple object. */
			if(ud_type->flags & OBJ_TYPE_SIMPLE) {
				*obj = ud;
			} else {
				*obj = ud->obj;
			}
			return 1;
		}
	}
	return 0;
}

static FUNC_UNUSED obj_udata *obj_udata_luacheck_internal(lua_State *L, int _index, void **obj, obj_type *type, int not_delete) {
	obj_udata *ud;
	base_caster_t caster = NULL;
	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			if(obj_udata_is_compatible(L, ud, obj, &(caster), type)) {
				lua_pop(L, 2); /* pop both metatables. */
				/* apply caster function if needed. */
				if(caster != NULL && *obj != NULL) {
					caster(obj);
				}
				/* check object pointer. */
				if(*obj == NULL) {
					if(not_delete) {
						luaL_error(L, "null %s", type->name); /* object was garbage collected? */
					}
					return NULL;
				}
				return ud;
			}
		}
	} else if(!lua_isnoneornil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				*obj = *(void **)lua_topointer(L, _index);
				return ud;
			}
			lua_pop(L, 2);
		} else {
			lua_pop(L, 1);
		}
	}
	if(not_delete) {
		luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	}
	return NULL;
}

static FUNC_UNUSED void *obj_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	if(lua_isnoneornil(L, _index)) {
		return obj;
	}
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;
	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);
}

static FUNC_UNUSED void *obj_udata_luadelete_weak(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* remove object from weak table. */
	lua_pushlightuserdata(L, obj);
	lua_pushnil(L);
	lua_rawset(L, -3);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush_weak(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;

	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* lookup userdata instance from pointer. */
	lua_pushlightuserdata(L, obj);
	lua_rawget(L, -2);
	if(!lua_isnil(L, -1)) {
		lua_remove(L, -2);     /* remove objects table. */
		return;
	}
	lua_pop(L, 1);  /* pop nil. */

#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		lua_remove(L, -2);
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));

	/* init. obj_udata. */
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	/* add weak reference to object. */
	lua_pushlightuserdata(L, obj); /* push object pointer as the 'key' */
	lua_pushvalue(L, -2);          /* push object's udata */
	lua_rawset(L, -4);             /* add weak reference to object. */
	lua_remove(L, -2);     /* remove objects table. */
}

/* default object equal method. */
static FUNC_UNUSED int obj_udata_default_equal(lua_State *L) {
	obj_udata *ud1 = obj_udata_toobj(L, 1);
	obj_udata *ud2 = obj_udata_toobj(L, 2);

	lua_pushboolean(L, (ud1->obj == ud2->obj));
	return 1;
}

/* default object tostring method. */
static FUNC_UNUSED int obj_udata_default_tostring(lua_State *L) {
	obj_udata *ud = obj_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p, flags=%d", ud->obj, ud->flags);
	lua_concat(L, 2);

	return 1;
}

/*
 * Simple userdata objects.
 */
static FUNC_UNUSED void *obj_simple_udata_toobj(lua_State *L, int _index) {
	void *ud;

	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	return ud;
}

static FUNC_UNUSED void * obj_simple_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *ud;
	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			lua_pushlightuserdata(L, type);
			lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
			if(lua_rawequal(L, -1, -2)) {
				lua_pop(L, 2); /* pop both metatables. */
				return ud;
			}
		}
	} else if(!lua_isnoneornil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				return (void *)lua_topointer(L, _index);
			}
		}
	}
	luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	return NULL;
}

static FUNC_UNUSED void * obj_simple_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	if(lua_isnoneornil(L, _index)) {
		return NULL;
	}
	return obj_simple_udata_luacheck(L, _index, type);
}

static FUNC_UNUSED void * obj_simple_udata_luadelete(lua_State *L, int _index, obj_type *type) {
	void *obj;
	obj = obj_simple_udata_luacheck(L, _index, type);
	/* clear the metatable to invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void *obj_simple_udata_luapush(lua_State *L, void *obj, int size, obj_type *type)
{
	void *ud;
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_call(L, 1, 1);
		return obj;
	}
#endif
	/* create new userdata. */
	ud = lua_newuserdata(L, size);
	memcpy(ud, obj, size);
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	return ud;
}

/* default simple object equal method. */
static FUNC_UNUSED int obj_simple_udata_default_equal(lua_State *L) {
	void *ud1 = obj_simple_udata_toobj(L, 1);
	size_t len1 = lua_objlen(L, 1);
	void *ud2 = obj_simple_udata_toobj(L, 2);
	size_t len2 = lua_objlen(L, 2);

	if(len1 == len2) {
		lua_pushboolean(L, (memcmp(ud1, ud2, len1) == 0));
	} else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

/* default simple object tostring method. */
static FUNC_UNUSED int obj_simple_udata_default_tostring(lua_State *L) {
	void *ud = obj_simple_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p", ud);
	lua_concat(L, 2);

	return 1;
}

static int obj_constructor_call_wrapper(lua_State *L) {
	/* replace '__call' table with constructor function. */
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_replace(L, 1);

	/* call constructor function with all parameters after the '__call' table. */
	lua_call(L, lua_gettop(L) - 1, LUA_MULTRET);
	/* return all results from constructor. */
	return lua_gettop(L);
}

static void obj_type_register_constants(lua_State *L, const obj_const *constants, int tab_idx,
		int bidirectional) {
	/* register constants. */
	while(constants->name != NULL) {
		lua_pushstring(L, constants->name);
		switch(constants->type) {
		case CONST_BOOLEAN:
			lua_pushboolean(L, constants->num != 0.0);
			break;
		case CONST_NUMBER:
			lua_pushnumber(L, constants->num);
			break;
		case CONST_STRING:
			lua_pushstring(L, constants->str);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		/* map values back to keys. */
		if(bidirectional) {
			/* check if value already exists. */
			lua_pushvalue(L, -1);
			lua_rawget(L, tab_idx - 3);
			if(lua_isnil(L, -1)) {
				lua_pop(L, 1);
				/* add value->key mapping. */
				lua_pushvalue(L, -1);
				lua_pushvalue(L, -3);
				lua_rawset(L, tab_idx - 4);
			} else {
				/* value already exists. */
				lua_pop(L, 1);
			}
		}
		lua_rawset(L, tab_idx - 2);
		constants++;
	}
}

static void obj_type_register_package(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_reg *reg_list = type_reg->pub_funcs;

	/* create public functions table. */
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	lua_pop(L, 1);  /* drop package table */
}

static void obj_type_register_meta(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_reg *reg_list;

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	/* register methods. */
	luaL_register(L, NULL, type_reg->methods);

	/* create metatable table. */
	lua_newtable(L);
	luaL_register(L, NULL, type_reg->metas); /* fill metatable */
	/* setmetatable on meta-object. */
	lua_setmetatable(L, -2);

	lua_pop(L, 1);  /* drop meta-object */
}

static void obj_type_register(lua_State *L, const reg_sub_module *type_reg, int priv_table) {
	const luaL_reg *reg_list;
	obj_type *type = type_reg->type;
	const obj_base *base = type_reg->bases;

	if(type_reg->req_type == REG_PACKAGE) {
		obj_type_register_package(L, type_reg);
		return;
	}
	if(type_reg->req_type == REG_META) {
		obj_type_register_meta(L, type_reg);
		return;
	}

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register "constructors" as to object's public API */
		luaL_register(L, NULL, reg_list); /* fill public API table. */

		/* make public API table callable as the default constructor. */
		lua_newtable(L); /* create metatable */
		lua_pushliteral(L, "__call");
		lua_pushcfunction(L, reg_list[0].func); /* push first constructor function. */
		lua_pushcclosure(L, obj_constructor_call_wrapper, 1); /* make __call wrapper. */
		lua_rawset(L, -3);         /* metatable.__call = <default constructor> */

#if OBJ_DATA_HIDDEN_METATABLE
		lua_pushliteral(L, "__metatable");
		lua_pushboolean(L, 0);
		lua_rawset(L, -3);         /* metatable.__metatable = false */
#endif

		/* setmetatable on public API table. */
		lua_setmetatable(L, -2);

		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
	} else {
		/* register all methods as public functions. */
#if OBJ_DATA_HIDDEN_METATABLE
		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
#endif
	}

	luaL_register(L, NULL, type_reg->methods); /* fill methods table. */

	luaL_newmetatable(L, type->name); /* create metatable */
	lua_pushliteral(L, ".name");
	lua_pushstring(L, type->name);
	lua_rawset(L, -3);    /* metatable['.name'] = "<object_name>" */
	lua_pushliteral(L, ".type");
	lua_pushlightuserdata(L, type);
	lua_rawset(L, -3);    /* metatable['.type'] = lightuserdata -> obj_type */
	lua_pushlightuserdata(L, type);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, LUA_REGISTRYINDEX);    /* REGISTRY[type] = metatable */

	/* add metatable to 'priv_table' */
	lua_pushstring(L, type->name);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, priv_table);    /* priv_table["<object_name>"] = metatable */

	luaL_register(L, NULL, type_reg->metas); /* fill metatable */

	/* add obj_bases to metatable. */
	while(base->id >= 0) {
		lua_pushlightuserdata(L, (void *)base);
		lua_rawseti(L, -2, base->id);
		base++;
	}

	obj_type_register_constants(L, type_reg->constants, -2, type_reg->bidirectional_consts);

	obj_type_register_implements(L, type_reg->implements);

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table */
	lua_rawset(L, -3);                  /* metatable.__index = methods */
#if OBJ_DATA_HIDDEN_METATABLE
	lua_pushliteral(L, "__metatable");
	lua_pushboolean(L, 0);
	lua_rawset(L, -3);                  /* hide metatable:
	                                       metatable.__metatable = false */
#endif
	lua_pop(L, 2);                      /* drop metatable & methods */
}

static FUNC_UNUSED int lua_checktype_ref(lua_State *L, int _index, int _type) {
	luaL_checktype(L,_index,_type);
	lua_pushvalue(L,_index);
	return luaL_ref(L, LUA_REGISTRYINDEX);
}



static char *obj_interfaces[] = {
  NULL,
};



#define obj_type_CryptDevice_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_CryptDevice))
#define obj_type_CryptDevice_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_CryptDevice))
#define obj_type_CryptDevice_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_CryptDevice), flags)
#define obj_type_CryptDevice_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_CryptDevice), flags)




static const char *cryptsetup_ffi_lua_code[] = { "local ffi=require\"ffi\"\n"
"local function ffi_safe_load(name, global)\n"
"	local stat, C = pcall(ffi.load, name, global)\n"
"	if not stat then return nil, C end\n"
"	if global then return ffi.C end\n"
"	return C\n"
"end\n"
"local function ffi_load(name, global)\n"
"	return assert(ffi_safe_load(name, global))\n"
"end\n"
"\n"
"local function ffi_string(ptr)\n"
"	if ptr ~= nil then\n"
"		return ffi.string(ptr)\n"
"	end\n"
"	return nil\n"
"end\n"
"\n"
"local function ffi_string_len(ptr, len)\n"
"	if ptr ~= nil then\n"
"		return ffi.string(ptr, len)\n"
"	end\n"
"	return nil\n"
"end\n"
"\n"
"local f_cast = ffi.cast\n"
"local pcall = pcall\n"
"local error = error\n"
"local type = type\n"
"local tonumber = tonumber\n"
"local tostring = tostring\n"
"local sformat = require\"string\".format\n"
"local rawset = rawset\n"
"local setmetatable = setmetatable\n"
"local package = (require\"package\") or {}\n"
"local p_config = package.config\n"
"local p_cpath = package.cpath\n"
"\n"
"\n"
"local ffi_load_cmodule\n"
"\n"
"-- try to detect luvit.\n"
"if p_config == nil and p_cpath == nil then\n"
"	ffi_load_cmodule = function(name, global)\n"
"		for path,module in pairs(package.loaded) do\n"
"			if module == name then\n"
"				local C, err = ffi_safe_load(path, global)\n"
"				-- return opened library\n"
"				if C then return C end\n"
"			end\n"
"		end\n"
"		error(\"Failed to find: \" .. name)\n"
"	end\n"
"else\n"
"	ffi_load_cmodule = function(name, global)\n"
"		local dir_sep = p_config:sub(1,1)\n"
"		local path_sep = p_config:sub(3,3)\n"
"		local path_mark = p_config:sub(5,5)\n"
"		local path_match = \"([^\" .. path_sep .. \"]*)\" .. path_sep\n"
"		-- convert dotted name to directory path.\n"
"		name = name:gsub('%.', dir_sep)\n"
"		-- try each path in search path.\n"
"		for path in p_cpath:gmatch(path_match) do\n"
"			local fname = path:gsub(path_mark, name)\n"
"			local C, err = ffi_safe_load(fname, global)\n"
"			-- return opened library\n"
"			if C then return C end\n"
"		end\n"
"		error(\"Failed to find: \" .. name)\n"
"	end\n"
"end\n"
"\n"
"local _M, _priv, reg_table = ...\n"
"local REG_MODULES_AS_GLOBALS = false\n"
"local REG_OBJECTS_AS_GLOBALS = false\n"
"local C = ffi.C\n"
"\n"
"local OBJ_UDATA_FLAG_OWN		= 1\n"
"\n"
"local function ffi_safe_cdef(block_name, cdefs)\n"
"	local fake_type = \"struct sentinel_\" .. block_name .. \"_ty\"\n"
"	local stat, size = pcall(ffi.sizeof, fake_type)\n"
"	if stat and size > 0 then\n"
"		-- already loaded this cdef block\n"
"		return\n"
"	end\n"
"	cdefs = fake_type .. \"{ int a; int b; int c; };\" .. cdefs\n"
"	return ffi.cdef(cdefs)\n"
"end\n"
"\n"
"ffi_safe_cdef(\"LuaNativeObjects\", [[\n"
"\n"
"typedef struct obj_type obj_type;\n"
"\n"
"typedef void (*base_caster_t)(void **obj);\n"
"\n"
"typedef void (*dyn_caster_t)(void **obj, obj_type **type);\n"
"\n"
"struct obj_type {\n"
"	dyn_caster_t    dcaster;  /**< caster to support casting to sub-objects. */\n"
"	int32_t         id;       /**< type's id. */\n"
"	uint32_t        flags;    /**< type's flags (weak refs) */\n"
"	const char      *name;    /**< type's object name. */\n"
"};\n"
"\n"
"typedef struct obj_base {\n"
"	int32_t        id;\n"
"	base_caster_t  bcaster;\n"
"} obj_base;\n"
"\n"
"typedef struct obj_udata {\n"
"	void     *obj;\n"
"	uint32_t flags;  /**< lua_own:1bit */\n"
"} obj_udata;\n"
"\n"
"int memcmp(const void *s1, const void *s2, size_t n);\n"
"\n"
"]])\n"
"\n"
"local nobj_callback_states = {}\n"
"local nobj_weak_objects = setmetatable({}, {__mode = \"v\"})\n"
"local nobj_obj_flags = {}\n"
"\n"
"local function obj_ptr_to_id(ptr)\n"
"	return tonumber(f_cast('uintptr_t', ptr))\n"
"end\n"
"\n"
"local function obj_to_id(ptr)\n"
"	return tonumber(f_cast('uintptr_t', f_cast('void *', ptr)))\n"
"end\n"
"\n"
"local function register_default_constructor(_pub, obj_name, constructor)\n"
"	local obj_pub = _pub[obj_name]\n"
"	if type(obj_pub) == 'table' then\n"
"		-- copy table since it might have a locked metatable\n"
"		local new_pub = {}\n"
"		for k,v in pairs(obj_pub) do\n"
"			new_pub[k] = v\n"
"		end\n"
"		setmetatable(new_pub, { __call = function(t,...)\n"
"			return constructor(...)\n"
"		end,\n"
"		__metatable = false,\n"
"		})\n"
"		obj_pub = new_pub\n"
"	else\n"
"		obj_pub = constructor\n"
"	end\n"
"	_pub[obj_name] = obj_pub\n"
"	_M[obj_name] = obj_pub\n"
"	if REG_OBJECTS_AS_GLOBALS then\n"
"		_G[obj_name] = obj_pub\n"
"	end\n"
"end\n"
"\n"
"ffi_safe_cdef(\"MutableBufferIF\", [[\n"
"typedef struct MutableBuffer_if {\n"
"  uint8_t * (* const data)(void *this_v);\n"
"  size_t (* const get_size)(void *this_v);\n"
"} MutableBufferIF;\n"
"]])\n"
"\n"
"ffi_safe_cdef(\"BufferIF\", [[\n"
"typedef struct Buffer_if {\n"
"  const uint8_t * (* const const_data)(void *this_v);\n"
"  size_t (* const get_size)(void *this_v);\n"
"} BufferIF;\n"
"]])\n"
"\n"
"ffi.cdef[[\n"
"typedef struct CryptDevice CryptDevice;\n"
"\n"
"]]\n"
"\n"
"ffi.cdef[[\n"
"int crypt_init(CryptDevice **, const char *);\n"
"\n"
"int crypt_init_by_name_and_header(CryptDevice **, const char *, const char *);\n"
"\n"
"int crypt_init_by_name(CryptDevice **, const char *);\n"
"\n"
"void crypt_free(CryptDevice *);\n"
"\n"
"const char * crypt_get_type(CryptDevice *);\n"
"\n"
"void crypt_set_rng_type(CryptDevice *, int);\n"
"\n"
"int crypt_get_rng_type(CryptDevice *);\n"
"\n"
"int crypt_status(CryptDevice *, const char *);\n"
"\n"
"const char * crypt_get_cipher(CryptDevice *);\n"
"\n"
"const char * crypt_get_cipher_mode(CryptDevice *);\n"
"\n"
"const char * crypt_get_uuid(CryptDevice *);\n"
"\n"
"const char * crypt_get_device_name(CryptDevice *);\n"
"\n"
"uint64_t crypt_get_data_offset(CryptDevice *);\n"
"\n"
"uint64_t crypt_get_iv_offset(CryptDevice *);\n"
"\n"
"int crypt_get_volume_key_size(CryptDevice *);\n"
"\n"
"int crypt_keyslot_status(CryptDevice *, int);\n"
"\n"
"int crypt_header_backup(CryptDevice *, const char *, const char *);\n"
"\n"
"int crypt_header_restore(CryptDevice *, const char *, const char *);\n"
"\n"
"const char * crypt_get_dir();\n"
"\n"
"\n"
"]]\n"
"\n"
"REG_MODULES_AS_GLOBALS = false\n"
"REG_OBJECTS_AS_GLOBALS = false\n"
"local _obj_interfaces_ffi = {}\n"
"local _pub = {}\n"
"local _meth = {}\n"
"local _push = {}\n"
"local _obj_subs = {}\n"
"for obj_name,mt in pairs(_priv) do\n"
"	if type(mt) == 'table' then\n"
"		_obj_subs[obj_name] = {}\n"
"		if mt.__index then\n"
"			_meth[obj_name] = mt.__index\n"
"		end\n"
"	end\n"
"end\n"
"for obj_name,pub in pairs(_M) do\n"
"	_pub[obj_name] = pub\n"
"end\n"
"\n"
"--\n"
"-- CData Metatable access\n"
"--\n"
"local _ctypes = {}\n"
"local _type_names = {}\n"
"local _get_mt_key = {}\n"
"local _ctype_meta_map = {}\n"
"\n"
"local f_typeof = ffi.typeof\n"
"local function get_cdata_type_id(cdata)\n"
"	return tonumber(f_typeof(cdata))\n"
"end\n"
"local function get_cdata_mt(cdata)\n"
"	return _ctype_meta_map[tonumber(f_typeof(cdata))]\n"
"end\n"
"\n"
"local function obj_register_ctype(name, ctype)\n"
"	local obj_mt = _priv[name]\n"
"	local obj_type = obj_mt['.type']\n"
"	local obj_ctype = ffi.typeof(ctype)\n"
"	local obj_type_id = tonumber(obj_ctype)\n"
"	_ctypes[name] = obj_ctype\n"
"	_type_names[name] = tostring(obj_ctype)\n"
"	_ctype_meta_map[obj_type_id] = obj_mt\n"
"	_ctype_meta_map[obj_mt] = obj_type_id\n"
"	return obj_mt, obj_type, obj_ctype\n"
"end\n"
"\n"
"--\n"
"-- Interfaces helper code.\n"
"--\n"
"local _obj_interfaces_key = \"obj_interfaces<1.0>_table_key\"\n"
"local _obj_interfaces_ud = reg_table[_obj_interfaces_key]\n"
"local _obj_interfaces_key_ffi = _obj_interfaces_key .. \"_LJ2_FFI\"\n"
"_obj_interfaces_ffi = reg_table[_obj_interfaces_key_ffi]\n"
"if not _obj_interfaces_ffi then\n"
"	-- create missing interfaces table for FFI bindings.\n"
"	_obj_interfaces_ffi = {}\n"
"	reg_table[_obj_interfaces_key_ffi] = _obj_interfaces_ffi\n"
"end\n"
"\n"
"local function obj_get_userdata_interface(if_name, expected_err)\n"
"	local impls_ud = _obj_interfaces_ud[if_name]\n"
"	if not impls_ud then\n"
"		impls_ud = {}\n"
"		_obj_interfaces_ud[if_name] = impls_ud\n"
"	end\n"
"	-- create cdata check function to be used by non-ffi bindings.\n"
"	if not impls_ud.cdata then\n"
"		function impls_ud.cdata(obj)\n"
"			return assert(impls_ud[get_cdata_mt(obj)], expected_err)\n"
"		end\n"
"	end\n"
"	return impls_ud\n"
"end\n"
"\n"
"local function obj_get_interface_check(if_name, expected_err)\n"
"	local impls_ffi = _obj_interfaces_ffi[if_name]\n"
"	if not impls_ffi then\n"
"		local if_type = ffi.typeof(if_name .. \" *\")\n"
"		local impls_ud = obj_get_userdata_interface(if_name, expected_err)\n"
"		-- create table for FFI-based interface implementations.\n"
"		impls_ffi = setmetatable({}, {\n"
"		__index = function(impls_ffi, mt)\n"
"			local impl = impls_ud[mt]\n"
"			if impl then\n"
"				-- cast to cdata\n"
"				impl = if_type(impl)\n"
"				rawset(impls_ffi, mt, impl)\n"
"			end\n"
"			return impl\n"
"		end})\n"
"		_obj_interfaces_ffi[if_name] = impls_ffi\n"
"\n"
"		-- create check function for this interface.\n"
"		function impls_ffi.check(obj)\n"
"			local impl\n"
"			if type(obj) == 'cdata' then\n"
"				impl = impls_ffi[get_cdata_type_id(obj)]\n"
"			else\n"
"				impl = impls_ud.userdata(impls_ffi, obj)\n"
"			end\n"
"			return assert(impl, expected_err)\n"
"		end\n"
"	end\n"
"	return impls_ffi.check\n"
"end\n"
"\n"
"local function obj_register_interface(if_name, obj_name)\n"
"	-- loopkup cdata id\n"
"	local obj_mt = _priv[obj_name]\n"
"	local obj_type_id = _ctype_meta_map[obj_mt]\n"
"	local impl_meths = {}\n"
"	local ffi_impls = _obj_interfaces_ffi[if_name]\n"
"	ffi_impls[obj_type_id] = impl_meths\n"
"	_meth[obj_name]['NOBJ_get_' .. if_name] = impl_meths\n"
"	return impl_meths\n"
"end\n"
"\n"
"\n"
"local obj_type_CryptDevice_check\n"
"local obj_type_CryptDevice_delete\n"
"local obj_type_CryptDevice_push\n"
"\n"
"do\n"
"	local obj_mt, obj_type, obj_ctype = obj_register_ctype(\"CryptDevice\", \"CryptDevice *\")\n"
"\n"
"	function obj_type_CryptDevice_check(ptr)\n"
"		-- if ptr is nil or is the correct type, then just return it.\n"
"		if not ptr or ffi.istype(obj_ctype, ptr) then return ptr end\n"
"		-- check if it is a compatible type.\n"
"		local ctype = tostring(ffi.typeof(ptr))\n"
"		local bcaster = _obj_subs.CryptDevice[ctype]\n"
"		if bcaster then\n"
"			return bcaster(ptr)\n"
"		end\n"
"		return error(\"Expected 'CryptDevice *'\", 2)\n"
"	end\n"
"\n"
"	function obj_type_CryptDevice_delete(ptr)\n"
"		local id = obj_ptr_to_id(ptr)\n"
"		local flags = nobj_obj_flags[id]\n"
"		if not flags then return nil, 0 end\n"
"		ffi.gc(ptr, nil)\n"
"		nobj_obj_flags[id] = nil\n"
"		return ptr, flags\n"
"	end\n"
"\n"
"	function obj_type_CryptDevice_push(ptr, flags)\n"
"		local id = obj_ptr_to_id(ptr)\n"
"		-- check weak refs\n"
"		if nobj_obj_flags[id] then return nobj_weak_objects[id] end\n"
"\n"
"		if flags ~= 0 then\n"
"			nobj_obj_flags[id] = flags\n"
"			ffi.gc(ptr, obj_mt.__gc)\n"
"		end\n"
"		nobj_weak_objects[id] = ptr\n"
"		return ptr\n"
"	end\n"
"\n"
"	function obj_mt:__tostring()\n"
"		return sformat(\"CryptDevice: %p, flags=%d\", self, nobj_obj_flags[obj_ptr_to_id(self)] or 0)\n"
"	end\n"
"\n"
"	-- type checking function for C API.\n"
"	_priv[obj_type] = obj_type_CryptDevice_check\n"
"	-- push function for C API.\n"
"	reg_table[obj_type] = function(ptr, flags)\n"
"		return obj_type_CryptDevice_push(ffi.cast(obj_ctype,ptr), flags)\n"
"	end\n"
"\n"
"end\n"
"\n"
"\n"
"local obj_type_MutableBuffer_check =\n"
"	obj_get_interface_check(\"MutableBufferIF\", \"Expected object with MutableBuffer interface\")\n"
"\n"
"local obj_type_Buffer_check =\n"
"	obj_get_interface_check(\"BufferIF\", \"Expected object with Buffer interface\")\n"
"\n"
"C = ffi_load(\"cryptsetup\",false)\n"
"\n"
"\n"
"-- Start \"CryptDevice\" FFI interface\n"
"-- method: init\n"
"function _pub.CryptDevice.init(device)\n"
"  local device_len = #device\n"
"  local this_flags = OBJ_UDATA_FLAG_OWN\n"
"  local self\n"
"  local rc_crypt_init = 0\n"
"  rc_crypt_init = C.crypt_init(self, device)\n"
"  return obj_type_CryptDevice_push(self, this_flags), rc_crypt_init\n"
"end\n"
"register_default_constructor(_pub,\"CryptDevice\",_pub.CryptDevice.init)\n"
"\n"
"-- method: init_by_name_and_header\n"
"function _pub.CryptDevice.init_by_name_and_header(header_device, name)\n"
"  header_device = tostring(header_device)\n"
"  local header_device_len = header_device and #header_device or 0\n"
"  local name_len = #name\n"
"  local this_flags = OBJ_UDATA_FLAG_OWN\n"
"  local self\n"
"  local rc_crypt_init_by_name_and_header = 0\n"
"  rc_crypt_init_by_name_and_header = C.crypt_init_by_name_and_header(self, name, header_device)\n"
"  return obj_type_CryptDevice_push(self, this_flags), rc_crypt_init_by_name_and_header\n"
"end\n"
"\n"
"-- method: init_by_name\n"
"function _pub.CryptDevice.init_by_name(name)\n"
"  local name_len = #name\n"
"  local this_flags = OBJ_UDATA_FLAG_OWN\n"
"  local self\n"
"  local rc_crypt_init_by_name = 0\n"
"  rc_crypt_init_by_name = C.crypt_init_by_name(self, name)\n"
"  return obj_type_CryptDevice_push(self, this_flags), rc_crypt_init_by_name\n"
"end\n"
"\n"
"-- method: free\n"
"function _meth.CryptDevice.free(self)\n"
"  local self,this_flags = obj_type_CryptDevice_delete(self)\n"
"  if not self then return end\n"
"  C.crypt_free(self)\n"
"  return \n"
"end\n"
"_priv.CryptDevice.__gc = _meth.CryptDevice.free\n"
"\n"
"-- method: get_type\n"
"function _meth.CryptDevice.get_type(self)\n"
"  \n"
"  local rc_crypt_get_type\n"
"  rc_crypt_get_type = C.crypt_get_type(self)\n"
"  return ffi_string(rc_crypt_get_type)\n"
"end\n"
"\n"
"-- method: set_rng_type\n"
"function _meth.CryptDevice.set_rng_type(self, rng_type)\n"
"  \n"
"  \n"
"  C.crypt_set_rng_type(self, rng_type)\n"
"  return \n"
"end\n"
"\n"
"-- method: get_rng_type\n"
"function _meth.CryptDevice.get_rng_type(self)\n"
"  \n"
"  local rc_crypt_get_rng_type = 0\n"
"  rc_crypt_get_rng_type = C.crypt_get_rng_type(self)\n"
"  return rc_crypt_get_rng_type\n"
"end\n"
"\n"
"-- method: status\n"
"function _meth.CryptDevice.status(self, name)\n"
"  \n"
"  local name_len = #name\n"
"  local rc_crypt_status = 0\n"
"  rc_crypt_status = C.crypt_status(self, name)\n"
"  return rc_crypt_status\n"
"end\n"
"\n"
"-- method: get_cipher\n"
"function _meth.CryptDevice.get_cipher(self)\n"
"  \n"
"  local rc_crypt_get_cipher\n"
"  rc_crypt_get_cipher = C.crypt_get_cipher(self)\n"
"  return ffi_string(rc_crypt_get_cipher)\n"
"end\n"
"\n"
"-- method: get_cipher_mode\n"
"function _meth.CryptDevice.get_cipher_mode(self)\n"
"  \n"
"  local rc_crypt_get_cipher_mode\n"
"  rc_crypt_get_cipher_mode = C.crypt_get_cipher_mode(self)\n"
"  return ffi_string(rc_crypt_get_cipher_mode)\n"
"end\n"
"\n"
"-- method: get_uuid\n"
"function _meth.CryptDevice.get_uuid(self)\n"
"  \n"
"  local rc_crypt_get_uuid\n"
"  rc_crypt_get_uuid = C.crypt_get_uuid(self)\n"
"  return ffi_string(rc_crypt_get_uuid)\n"
"end\n"
"\n"
"-- method: get_device_name\n"
"function _meth.CryptDevice.get_device_name(self)\n"
"  \n"
"  local rc_crypt_get_device_name\n"
"  rc_crypt_get_device_name = C.crypt_get_device_name(self)\n"
"  return ffi_string(rc_crypt_get_device_name)\n"
"end\n"
"\n"
"-- method: get_data_offset\n"
"function _meth.CryptDevice.get_data_offset(self)\n"
"  \n"
"  local rc_crypt_get_data_offset = 0\n"
"  rc_crypt_get_data_offset = C.crypt_get_data_offset(self)\n"
"  return rc_crypt_get_data_offset\n"
"end\n"
"\n"
"-- method: get_iv_offset\n"
"function _meth.CryptDevice.get_iv_offset(self)\n"
"  \n"
"  local rc_crypt_get_iv_offset = 0\n"
"  rc_crypt_get_iv_offset = C.crypt_get_iv_offset(self)\n"
"  return rc_crypt_get_iv_offset\n"
"end\n"
"\n"
"-- method: get_volume_key_size\n"
"function _meth.CryptDevice.get_volume_key_size(self)\n"
"  \n"
"  local rc_crypt_get_volume_key_size = 0\n"
"  rc_crypt_get_volume_key_size = C.crypt_get_volume_key_size(self)\n"
"  return rc_crypt_get_volume_key_size\n"
"end\n"
"\n"
"-- method: keyslot_status\n"
"function _meth.CryptDevice.keyslot_status(self, keyslot)\n"
"  \n"
"  \n"
"  local rc_crypt_keyslot_status = 0\n"
"  rc_crypt_keyslot_status = C.crypt_keyslot_status(self, keyslot)\n"
"  return rc_crypt_keyslot_status\n"
"end\n"
"\n"
"-- method: header_backup\n"
"function _meth.CryptDevice.header_backup(self, requested_type, backup_file)\n"
"  \n"
"  local requested_type_len = #requested_type\n"
"  local backup_file_len = #backup_file\n"
"  local rc_crypt_header_backup = 0\n", /* ----- CUT ----- */
"  rc_crypt_header_backup = C.crypt_header_backup(self, requested_type, backup_file)\n"
"  return rc_crypt_header_backup\n"
"end\n"
"\n"
"-- method: header_restore\n"
"function _meth.CryptDevice.header_restore(self, requested_type, backup_file)\n"
"  \n"
"  local requested_type_len = #requested_type\n"
"  local backup_file_len = #backup_file\n"
"  local rc_crypt_header_restore = 0\n"
"  rc_crypt_header_restore = C.crypt_header_restore(self, requested_type, backup_file)\n"
"  return rc_crypt_header_restore\n"
"end\n"
"\n"
"-- method: get_dir\n"
"function _meth.CryptDevice.get_dir(self)\n"
"  \n"
"  local rc_crypt_get_dir\n"
"  rc_crypt_get_dir = C.crypt_get_dir()\n"
"  return ffi_string(rc_crypt_get_dir)\n"
"end\n"
"\n"
"_push.CryptDevice = obj_type_CryptDevice_push\n"
"ffi.metatype(\"CryptDevice\", _priv.CryptDevice)\n"
"-- End \"CryptDevice\" FFI interface\n"
"\n", NULL };
typedef struct crypt_device CryptDevice;



/* method: init */
static int CryptDevice__init__meth(lua_State *L) {
  size_t device_len;
  const char * device;
  int this_flags = OBJ_UDATA_FLAG_OWN;
  CryptDevice * this;
  int rc_crypt_init = 0;
  device = luaL_checklstring(L,1,&(device_len));
  rc_crypt_init = crypt_init(&(this), device);
  obj_type_CryptDevice_push(L, this, this_flags);
  lua_pushinteger(L, rc_crypt_init);
  return 2;
}

/* method: init_by_name_and_header */
static int CryptDevice__init_by_name_and_header__meth(lua_State *L) {
  size_t header_device_len;
  const char * header_device;
  size_t name_len;
  const char * name;
  int this_flags = OBJ_UDATA_FLAG_OWN;
  CryptDevice * this;
  int rc_crypt_init_by_name_and_header = 0;
  header_device = luaL_optlstring(L,1,NULL,&(header_device_len));
  name = luaL_checklstring(L,2,&(name_len));
  rc_crypt_init_by_name_and_header = crypt_init_by_name_and_header(&(this), name, header_device);
  obj_type_CryptDevice_push(L, this, this_flags);
  lua_pushinteger(L, rc_crypt_init_by_name_and_header);
  return 2;
}

/* method: init_by_name */
static int CryptDevice__init_by_name__meth(lua_State *L) {
  size_t name_len;
  const char * name;
  int this_flags = OBJ_UDATA_FLAG_OWN;
  CryptDevice * this;
  int rc_crypt_init_by_name = 0;
  name = luaL_checklstring(L,1,&(name_len));
  rc_crypt_init_by_name = crypt_init_by_name(&(this), name);
  obj_type_CryptDevice_push(L, this, this_flags);
  lua_pushinteger(L, rc_crypt_init_by_name);
  return 2;
}

/* method: free */
static int CryptDevice__free__meth(lua_State *L) {
  int this_flags = 0;
  CryptDevice * this;
  this = obj_type_CryptDevice_delete(L,1,&(this_flags));
  if(!(this_flags & OBJ_UDATA_FLAG_OWN)) { return 0; }
  crypt_free(this);
  return 0;
}

/* method: get_type */
static int CryptDevice__get_type__meth(lua_State *L) {
  CryptDevice * this;
  const char * rc_crypt_get_type = NULL;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_type = crypt_get_type(this);
  lua_pushstring(L, rc_crypt_get_type);
  return 1;
}

/* method: set_rng_type */
static int CryptDevice__set_rng_type__meth(lua_State *L) {
  CryptDevice * this;
  int rng_type;
  this = obj_type_CryptDevice_check(L,1);
  rng_type = luaL_checkinteger(L,2);
  crypt_set_rng_type(this, rng_type);
  return 0;
}

/* method: get_rng_type */
static int CryptDevice__get_rng_type__meth(lua_State *L) {
  CryptDevice * this;
  int rc_crypt_get_rng_type = 0;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_rng_type = crypt_get_rng_type(this);
  lua_pushinteger(L, rc_crypt_get_rng_type);
  return 1;
}

/* method: status */
static int CryptDevice__status__meth(lua_State *L) {
  CryptDevice * this;
  size_t name_len;
  const char * name;
  int rc_crypt_status = 0;
  this = obj_type_CryptDevice_check(L,1);
  name = luaL_checklstring(L,2,&(name_len));
  rc_crypt_status = crypt_status(this, name);
  lua_pushinteger(L, rc_crypt_status);
  return 1;
}

/* method: get_cipher */
static int CryptDevice__get_cipher__meth(lua_State *L) {
  CryptDevice * this;
  const char * rc_crypt_get_cipher = NULL;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_cipher = crypt_get_cipher(this);
  lua_pushstring(L, rc_crypt_get_cipher);
  return 1;
}

/* method: get_cipher_mode */
static int CryptDevice__get_cipher_mode__meth(lua_State *L) {
  CryptDevice * this;
  const char * rc_crypt_get_cipher_mode = NULL;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_cipher_mode = crypt_get_cipher_mode(this);
  lua_pushstring(L, rc_crypt_get_cipher_mode);
  return 1;
}

/* method: get_uuid */
static int CryptDevice__get_uuid__meth(lua_State *L) {
  CryptDevice * this;
  const char * rc_crypt_get_uuid = NULL;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_uuid = crypt_get_uuid(this);
  lua_pushstring(L, rc_crypt_get_uuid);
  return 1;
}

/* method: get_device_name */
static int CryptDevice__get_device_name__meth(lua_State *L) {
  CryptDevice * this;
  const char * rc_crypt_get_device_name = NULL;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_device_name = crypt_get_device_name(this);
  lua_pushstring(L, rc_crypt_get_device_name);
  return 1;
}

/* method: get_data_offset */
static int CryptDevice__get_data_offset__meth(lua_State *L) {
  CryptDevice * this;
  uint64_t rc_crypt_get_data_offset = 0;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_data_offset = crypt_get_data_offset(this);
  lua_pushinteger(L, rc_crypt_get_data_offset);
  return 1;
}

/* method: get_iv_offset */
static int CryptDevice__get_iv_offset__meth(lua_State *L) {
  CryptDevice * this;
  uint64_t rc_crypt_get_iv_offset = 0;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_iv_offset = crypt_get_iv_offset(this);
  lua_pushinteger(L, rc_crypt_get_iv_offset);
  return 1;
}

/* method: get_volume_key_size */
static int CryptDevice__get_volume_key_size__meth(lua_State *L) {
  CryptDevice * this;
  int rc_crypt_get_volume_key_size = 0;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_volume_key_size = crypt_get_volume_key_size(this);
  lua_pushinteger(L, rc_crypt_get_volume_key_size);
  return 1;
}

/* method: keyslot_status */
static int CryptDevice__keyslot_status__meth(lua_State *L) {
  CryptDevice * this;
  int keyslot;
  int rc_crypt_keyslot_status = 0;
  this = obj_type_CryptDevice_check(L,1);
  keyslot = luaL_checkinteger(L,2);
  rc_crypt_keyslot_status = crypt_keyslot_status(this, keyslot);
  lua_pushinteger(L, rc_crypt_keyslot_status);
  return 1;
}

/* method: header_backup */
static int CryptDevice__header_backup__meth(lua_State *L) {
  CryptDevice * this;
  size_t requested_type_len;
  const char * requested_type;
  size_t backup_file_len;
  const char * backup_file;
  int rc_crypt_header_backup = 0;
  this = obj_type_CryptDevice_check(L,1);
  requested_type = luaL_checklstring(L,2,&(requested_type_len));
  backup_file = luaL_checklstring(L,3,&(backup_file_len));
  rc_crypt_header_backup = crypt_header_backup(this, requested_type, backup_file);
  lua_pushinteger(L, rc_crypt_header_backup);
  return 1;
}

/* method: header_restore */
static int CryptDevice__header_restore__meth(lua_State *L) {
  CryptDevice * this;
  size_t requested_type_len;
  const char * requested_type;
  size_t backup_file_len;
  const char * backup_file;
  int rc_crypt_header_restore = 0;
  this = obj_type_CryptDevice_check(L,1);
  requested_type = luaL_checklstring(L,2,&(requested_type_len));
  backup_file = luaL_checklstring(L,3,&(backup_file_len));
  rc_crypt_header_restore = crypt_header_restore(this, requested_type, backup_file);
  lua_pushinteger(L, rc_crypt_header_restore);
  return 1;
}

/* method: get_dir */
static int CryptDevice__get_dir__meth(lua_State *L) {
  CryptDevice * this;
  const char * rc_crypt_get_dir = NULL;
  this = obj_type_CryptDevice_check(L,1);
  rc_crypt_get_dir = crypt_get_dir();
  lua_pushstring(L, rc_crypt_get_dir);
  return 1;
}



static const luaL_reg obj_CryptDevice_pub_funcs[] = {
  {"init", CryptDevice__init__meth},
  {"init_by_name_and_header", CryptDevice__init_by_name_and_header__meth},
  {"init_by_name", CryptDevice__init_by_name__meth},
  {NULL, NULL}
};

static const luaL_reg obj_CryptDevice_methods[] = {
  {"free", CryptDevice__free__meth},
  {"get_type", CryptDevice__get_type__meth},
  {"set_rng_type", CryptDevice__set_rng_type__meth},
  {"get_rng_type", CryptDevice__get_rng_type__meth},
  {"status", CryptDevice__status__meth},
  {"get_cipher", CryptDevice__get_cipher__meth},
  {"get_cipher_mode", CryptDevice__get_cipher_mode__meth},
  {"get_uuid", CryptDevice__get_uuid__meth},
  {"get_device_name", CryptDevice__get_device_name__meth},
  {"get_data_offset", CryptDevice__get_data_offset__meth},
  {"get_iv_offset", CryptDevice__get_iv_offset__meth},
  {"get_volume_key_size", CryptDevice__get_volume_key_size__meth},
  {"keyslot_status", CryptDevice__keyslot_status__meth},
  {"header_backup", CryptDevice__header_backup__meth},
  {"header_restore", CryptDevice__header_restore__meth},
  {"get_dir", CryptDevice__get_dir__meth},
  {NULL, NULL}
};

static const luaL_reg obj_CryptDevice_metas[] = {
  {"__gc", CryptDevice__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_CryptDevice_bases[] = {
  {-1, NULL}
};

static const obj_field obj_CryptDevice_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_CryptDevice_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_CryptDevice_implements[] = {
  {NULL, NULL}
};

static const luaL_reg cryptsetup_function[] = {
  {NULL, NULL}
};

static const obj_const cryptsetup_constants[] = {
  {"CRYPT_RNG_URANDOM", NULL, 0, CONST_NUMBER},
  {"CRYPT_LOOPAES", "LOOPAES", 0.0, CONST_STRING},
  {"CRYPT_ACTIVATE_NO_UUID", NULL, 2, CONST_NUMBER},
  {"CRYPT_ACTIVATE_READONLY", NULL, 1, CONST_NUMBER},
  {"CRYPT_RNG_RANDOM", NULL, 1, CONST_NUMBER},
  {"CRYPT_ACTIVATE_PRIVATE", NULL, 16, CONST_NUMBER},
  {"CRYPT_PLAIN", "PLAIN", 0.0, CONST_STRING},
  {"CRYPT_LUKS1", "LUKS1", 0.0, CONST_STRING},
  {"CRYPT_ACTIVATE_ALLOW_DISCARDS", NULL, 8, CONST_NUMBER},
  {"CRYPT_ACTIVATE_SHARED", NULL, 4, CONST_NUMBER},
  {"CRYPT_ANY_SLOT", NULL, -1, CONST_NUMBER},
  {NULL, NULL, 0.0 , 0}
};



static const reg_sub_module reg_sub_modules[] = {
  { &(obj_type_CryptDevice), REG_OBJECT, obj_CryptDevice_pub_funcs, obj_CryptDevice_methods, obj_CryptDevice_metas, obj_CryptDevice_bases, obj_CryptDevice_fields, obj_CryptDevice_constants, obj_CryptDevice_implements, 0},
  {NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0}
};





#if LUAJIT_FFI
static const ffi_export_symbol cryptsetup_ffi_export[] = {
  {NULL, { NULL } }
};
#endif




static const luaL_Reg submodule_libs[] = {
  {NULL, NULL}
};



static void create_object_instance_cache(lua_State *L) {
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(!lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop weak table. */
		return;
	}
	lua_pop(L, 1); /* pop nil. */
	/* create weak table for object instance references. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_newtable(L);               /* weak table. */
	lua_newtable(L);               /* metatable for weak table. */
	lua_pushliteral(L, "__mode");
	lua_pushliteral(L, "v");
	lua_rawset(L, -3);             /* metatable.__mode = 'v'  weak values. */
	lua_setmetatable(L, -2);       /* add metatable to weak table. */
	lua_rawset(L, LUA_REGISTRYINDEX);  /* create reference to weak table. */
}

LUA_NOBJ_API int luaopen_cryptsetup(lua_State *L) {
	const reg_sub_module *reg = reg_sub_modules;
	const luaL_Reg *submodules = submodule_libs;
	int priv_table = -1;

	/* register interfaces */
	obj_register_interfaces(L, obj_interfaces);

	/* private table to hold reference to object metatables. */
	lua_newtable(L);
	priv_table = lua_gettop(L);
	lua_pushlightuserdata(L, obj_udata_private_key);
	lua_pushvalue(L, priv_table);
	lua_rawset(L, LUA_REGISTRYINDEX);  /* store private table in registry. */

	/* create object cache. */
	create_object_instance_cache(L);

	/* module table. */
#if REG_MODULES_AS_GLOBALS
	luaL_register(L, "cryptsetup", cryptsetup_function);
#else
	lua_newtable(L);
	luaL_register(L, NULL, cryptsetup_function);
#endif

	/* register module constants. */
	obj_type_register_constants(L, cryptsetup_constants, -1, 0);

	for(; submodules->func != NULL ; submodules++) {
		lua_pushcfunction(L, submodules->func);
		lua_pushstring(L, submodules->name);
		lua_call(L, 1, 0);
	}

	/* register objects */
	for(; reg->type != NULL ; reg++) {
		lua_newtable(L); /* create public API table for object. */
		lua_pushvalue(L, -1); /* dup. object's public API table. */
		lua_setfield(L, -3, reg->type->name); /* module["<object_name>"] = <object public API> */
#if REG_OBJECTS_AS_GLOBALS
		lua_pushvalue(L, -1);                 /* dup value. */
		lua_setglobal(L, reg->type->name);    /* global: <object_name> = <object public API> */
#endif
		obj_type_register(L, reg, priv_table);
	}

#if LUAJIT_FFI
	if(nobj_check_ffi_support(L)) {
		nobj_try_loading_ffi(L, "cryptsetup.nobj.ffi.lua", cryptsetup_ffi_lua_code,
			cryptsetup_ffi_export, priv_table);
	}
#endif



	return 1;
}


