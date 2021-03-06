#include "stdafx.h"
#include "Emu/Memory/Memory.h"
#include "Emu/System.h"
#include "Emu/IdManager.h"
#include "Crypto/unself.h"
#include "Loader/ELF.h"

#include "Emu/Cell/ErrorCodes.h"
#include "Crypto/unedat.h"
#include "sys_prx.h"

namespace vm { using namespace ps3; }

extern std::shared_ptr<lv2_prx> ppu_load_prx(const ppu_prx_object&, const std::string&);
extern void ppu_initialize(const ppu_module&);

logs::channel sys_prx("sys_prx", logs::level::notice);

s32 prx_load_module(std::string path, u64 flags, vm::ptr<sys_prx_load_module_option_t> pOpt)
{
	sys_prx.warning("prx_load_module(path='%s', flags=0x%llx, pOpt=*0x%x)", path.c_str(), flags, pOpt);

	const auto loadedkeys = fxm::get_always<LoadedNpdrmKeys_t>();

	const ppu_prx_object obj = decrypt_self(fs::file(vfs::get(path)), loadedkeys->devKlic.data());

	if (obj != elf_error::ok)
	{
		return CELL_PRX_ERROR_ILLEGAL_LIBRARY;
	}

	const auto prx = ppu_load_prx(obj, path.substr(path.find_last_of('/') + 1));

	if (!prx)
	{
		return CELL_PRX_ERROR_ILLEGAL_LIBRARY;
	}

	ppu_initialize(*prx);

	return idm::last_id();
}

error_code sys_prx_get_ppu_guid()
{
	sys_prx.todo("sys_prx_get_ppu_guid()");
	return CELL_OK;
}

error_code _sys_prx_load_module_by_fd()
{
	sys_prx.todo("_sys_prx_load_module_by_fd()");
	return CELL_OK;
}

error_code _sys_prx_load_module_on_memcontainer_by_fd()
{
	sys_prx.todo("_sys_prx_load_module_on_memcontainer_by_fd()");
	return CELL_OK;
}

error_code _sys_prx_load_module_list(s32 count, vm::cpptr<char> path_list, u64 flags, vm::ptr<sys_prx_load_module_option_t> pOpt, vm::ptr<u32> id_list)
{
	sys_prx.warning("_sys_prx_load_module_list(count=%d, path_list=*0x%x, flags=0x%llx, pOpt=*0x%x, id_list=*0x%x)", count, path_list, flags, pOpt, id_list);

	for (s32 i = 0; i < count; ++i)
	{
		auto path = path_list[i];
		std::string name = path.get_ptr();
		s32 result = prx_load_module(name, flags, pOpt);

		if (result < 0)
			return result;

		id_list[i] = result;
	}

	return CELL_OK;
}

error_code _sys_prx_load_module_list_on_memcontainer()
{
	sys_prx.todo("_sys_prx_load_module_list_on_memcontainer()");
	return CELL_OK;
}

error_code _sys_prx_load_module_on_memcontainer()
{
	sys_prx.todo("_sys_prx_load_module_on_memcontainer()");
	return CELL_OK;
}

error_code _sys_prx_load_module(vm::cptr<char> path, u64 flags, vm::ptr<sys_prx_load_module_option_t> pOpt)
{
	sys_prx.warning("_sys_prx_load_module(path=%s, flags=0x%llx, pOpt=*0x%x)", path, flags, pOpt);

	return prx_load_module(path.get_ptr(), flags, pOpt);
}

error_code _sys_prx_start_module(u32 id, u64 flags, vm::ptr<sys_prx_start_module_option_t> pOpt)
{
	sys_prx.warning("_sys_prx_start_module(id=0x%x, flags=0x%llx, pOpt=*0x%x)", id, flags, pOpt);

	const auto prx = idm::get<lv2_obj, lv2_prx>(id);

	if (!prx)
	{
		return CELL_ESRCH;
	}

	//if (prx->is_started)
	//	return CELL_PRX_ERROR_ALREADY_STARTED;

	//prx->is_started = true;
	pOpt->entry_point.set(prx->start ? prx->start.addr() : ~0ull);

	return CELL_OK;
}

error_code _sys_prx_stop_module(u32 id, u64 flags, vm::ptr<sys_prx_stop_module_option_t> pOpt)
{
	sys_prx.warning("_sys_prx_stop_module(id=0x%x, flags=0x%llx, pOpt=*0x%x)", id, flags, pOpt);

	const auto prx = idm::get<lv2_obj, lv2_prx>(id);

	if (!prx)
	{
		return CELL_ESRCH;
	}

	//if (!prx->is_started)
	//	return CELL_PRX_ERROR_ALREADY_STOPPED;

	//prx->is_started = false;
	pOpt->entry_point.set(prx->stop ? prx->stop.addr() : -1);

	return CELL_OK;
}

error_code _sys_prx_unload_module(u32 id, u64 flags, vm::ptr<sys_prx_unload_module_option_t> pOpt)
{
	sys_prx.warning("_sys_prx_unload_module(id=0x%x, flags=0x%llx, pOpt=*0x%x)", id, flags, pOpt);

	// Get the PRX, free the used memory and delete the object and its ID
	const auto prx = idm::withdraw<lv2_obj, lv2_prx>(id);

	if (!prx)
	{
		return CELL_ESRCH;
	}

	//Memory.Free(prx->address);

	//s32 result = prx->exit ? prx->exit() : CELL_OK;
	
	return CELL_OK;
}

error_code _sys_prx_register_module()
{
	sys_prx.todo("_sys_prx_register_module()");
	return CELL_OK;
}

error_code _sys_prx_query_module()
{
	sys_prx.todo("_sys_prx_query_module()");
	return CELL_OK;
}

error_code _sys_prx_register_library(vm::ptr<void> library)
{
	sys_prx.todo("_sys_prx_register_library(library=*0x%x)", library);
	return CELL_OK;
}

error_code _sys_prx_unregister_library(vm::ptr<void> library)
{
	sys_prx.todo("_sys_prx_unregister_library(library=*0x%x)", library);
	return CELL_OK;
}

error_code _sys_prx_link_library()
{
	sys_prx.todo("_sys_prx_link_library()");
	return CELL_OK;
}

error_code _sys_prx_unlink_library()
{
	sys_prx.todo("_sys_prx_unlink_library()");
	return CELL_OK;
}

error_code _sys_prx_query_library()
{
	sys_prx.todo("_sys_prx_query_library()");
	return CELL_OK;
}

error_code _sys_prx_get_module_list(u64 flags, vm::ptr<sys_prx_get_module_list_t> pInfo)
{
	sys_prx.todo("_sys_prx_get_module_list(flags=%d, pInfo=*0x%x)", flags, pInfo);
	return CELL_OK;
}

error_code _sys_prx_get_module_info(u32 id, u64 flags, vm::ptr<sys_prx_module_info_option_t> pOpt)
{
	sys_prx.todo("_sys_prx_get_module_info(id=%d, flags=%d, pOpt=*0x%x)", id, flags, pOpt);
	return CELL_OK;
}

error_code _sys_prx_get_module_id_by_name(vm::cptr<char> name, u64 flags, vm::ptr<sys_prx_get_module_id_by_name_option_t> pOpt)
{
	sys_prx.todo("_sys_prx_get_module_id_by_name(name=%s, flags=%d, pOpt=*0x%x)", name, flags, pOpt);

	//if (realName == "?") ...

	return CELL_PRX_ERROR_UNKNOWN_MODULE;
}

error_code _sys_prx_get_module_id_by_address(u32 addr)
{
	sys_prx.todo("_sys_prx_get_module_id_by_address(addr=0x%x)", addr);
	return CELL_OK;
}

error_code _sys_prx_start()
{
	sys_prx.todo("sys_prx_start()");
	return CELL_OK;
}

error_code _sys_prx_stop()
{
	sys_prx.todo("sys_prx_stop()");
	return CELL_OK;
}

template <>
void fmt_class_string<CellPrxError>::format(std::string& out, u64 arg)
{
	format_enum(out, arg, [](CellPrxError value)
	{
		switch (value)
		{
		STR_CASE(CELL_PRX_ERROR_ERROR);
		STR_CASE(CELL_PRX_ERROR_ILLEGAL_PERM);
		STR_CASE(CELL_PRX_ERROR_UNKNOWN_MODULE);
		STR_CASE(CELL_PRX_ERROR_ALREADY_STARTED);
		STR_CASE(CELL_PRX_ERROR_NOT_STARTED);
		STR_CASE(CELL_PRX_ERROR_ALREADY_STOPPED);
		STR_CASE(CELL_PRX_ERROR_CAN_NOT_STOP);
		STR_CASE(CELL_PRX_ERROR_NOT_REMOVABLE);
		STR_CASE(CELL_PRX_ERROR_LIBRARY_NOT_YET_LINKED);
		STR_CASE(CELL_PRX_ERROR_LIBRARY_FOUND);
		STR_CASE(CELL_PRX_ERROR_LIBRARY_NOTFOUND);
		STR_CASE(CELL_PRX_ERROR_ILLEGAL_LIBRARY);
		STR_CASE(CELL_PRX_ERROR_LIBRARY_INUSE);
		STR_CASE(CELL_PRX_ERROR_ALREADY_STOPPING);
		STR_CASE(CELL_PRX_ERROR_UNSUPPORTED_PRX_TYPE);
		STR_CASE(CELL_PRX_ERROR_INVAL);
		STR_CASE(CELL_PRX_ERROR_ILLEGAL_PROCESS);
		STR_CASE(CELL_PRX_ERROR_NO_LIBLV2);
		STR_CASE(CELL_PRX_ERROR_UNSUPPORTED_ELF_TYPE);
		STR_CASE(CELL_PRX_ERROR_UNSUPPORTED_ELF_CLASS);
		STR_CASE(CELL_PRX_ERROR_UNDEFINED_SYMBOL);
		STR_CASE(CELL_PRX_ERROR_UNSUPPORTED_RELOCATION_TYPE);
		STR_CASE(CELL_PRX_ERROR_ELF_IS_REGISTERED);
		}

		return unknown;
	});
}
